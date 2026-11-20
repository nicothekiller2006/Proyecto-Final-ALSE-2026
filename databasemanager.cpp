#include "databasemanager.h"

// Librerías de Qt necesarias para manejar carpetas, archivos, consultas SQL y depuración de errores
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Crea el gestor de la base de datos y abre la conexión.
 */
DatabaseManager::DatabaseManager()
    : m_isReady(false) // Inicializa el estado como no listo por defecto
{
    // Ejecuta la inicialización; si tiene éxito, m_isReady será true
    m_isReady = initializeDatabase();
}

/**
 * @brief Cierra la conexión con la base de datos.
 */
DatabaseManager::~DatabaseManager()
{
    // Si la base de datos sigue abierta al cerrar el programa, la cierra de forma segura
    if (m_database.isOpen()) {
        m_database.close();
    }
}

/**
 * @brief Comprueba si la base de datos está lista para usarse.
 * @return True si la base de datos se inicializó correctamente.
 */
bool DatabaseManager::isReady() const
{
    return m_isReady;
}

/**
 * @brief Inicializa la base de datos SQLite.
 * @return True si la base de datos se inicializó correctamente.
 */
bool DatabaseManager::initializeDatabase()
{
    // Verifica y crea la carpeta "db" si no existe. Falla si no hay permisos.
    if (!QDir().mkpath("db")) {
        qDebug() << "No se pudo crear el directorio de la base de datos.";
        return false;
    }

    // Configura el driver para SQLite y establece la ruta del archivo
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("db/inventario.db");

    // Intenta abrir la conexión. Si falla, imprime el motivo del error
    if (!m_database.open()) {
        qDebug() << "Error de conexión a la base de datos:"
                 << m_database.lastError().text();
        return false;
    }

    // Si la conexión fue exitosa, procede a crear las tablas
    return createTables();
}

/**
 * @brief Crea las tablas de la base de datos utilizando el script SQL.
 * @return True si las tablas se crearon correctamente.
 */
bool DatabaseManager::createTables()
{
    // Busca el archivo con el script de creación de tablas
    QFile file("db/inventario.sql");

    // Intenta abrir el archivo en modo texto y solo lectura
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo SQL:"
                 << file.errorString();
        return false;
    }

    // Lee todo el texto del archivo y lo guarda en un QString, luego cierra el archivo
    QString sql = QString::fromUtf8(file.readAll());
    file.close();

    QSqlQuery query;

    // Ejecuta las instrucciones leídas del archivo .sql
    if (!query.exec(sql)) {
        qDebug() << "Error al crear las tablas de la base de datos:"
                 << query.lastError().text();
        return false;
    }

    return true;
}

/**
 * @brief Recupera todos los componentes almacenados en la base de datos.
 * @return Lista que contiene todos los componentes almacenados.
 */
QList<Component> DatabaseManager::getComponents()
{
    QList<Component> components;

    // Validación de seguridad: no intenta consultar si la BD no está lista
    if (!m_isReady) {
        return components;
    }

    // Prepara la consulta para seleccionar todos los registros de la tabla
    QSqlQuery query("SELECT * FROM components");

    // ESTO ES LO NUEVO QUE AÑADISTE: Verifica si la consulta se ejecutó correctamente
    if (!query.exec()) {
        qDebug() << "Error recuperando componentes:"
                 << query.lastError().text();
        return components; // Si falla, retorna la lista vacía de inmediato
    }

    // Recorre cada fila devuelta por la base de datos
    while (query.next()) {
        // Construye un componente leyendo las columnas correspondientes
        Component component(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("type").toString(),
            query.value("quantity").toInt(),
            query.value("location").toString(),
            QDate::fromString(
                query.value("purchase_date").toString(),
                Qt::ISODate
            ),
            query.value("minimum_quantity").toInt(),
            query.value("notes").toString()
        );

        // Agrega el componente creado a la lista
        components.append(component);
    }

    return components;
}

/**
 * @brief Inserta un componente en la base de datos.
 * @param component Componente a insertar.
 * @return True si el componente se insertó correctamente.
 */
bool DatabaseManager::addComponent(const Component &component)
{
    // Validación de seguridad
    if (!m_isReady) {
        return false;
    }

    QSqlQuery query;

    // Prepara la inserción usando "?" para proteger contra inyecciones SQL
    query.prepare(
        "INSERT INTO components "
        "(name, type, quantity, location, purchase_date, minimum_quantity, notes) "
        "VALUES (?, ?, ?, ?, ?, ?, ?)"
    );

    // Vincula los valores del objeto Component a cada "?" en orden
    query.addBindValue(component.getName());
    query.addBindValue(component.getType());
    query.addBindValue(component.getQuantity());
    query.addBindValue(component.getLocation());
    query.addBindValue(component.getPurchaseDate().toString(Qt::ISODate));
    query.addBindValue(component.getMinimumQuantity());
    query.addBindValue(component.getNotes());

    // Ejecuta la inserción
    if (!query.exec()) {
        qDebug() << "Error de inserción:"
                 << query.lastError().text();
        return false;
    }

    return true;
}

/**
 * @brief Actualiza un componente existente.
 * @param component Componente que contiene la información actualizada.
 * @return True si el componente se actualizó correctamente.
 */
bool DatabaseManager::updateComponent(const Component &component)
{
    // Validación de seguridad
    if (!m_isReady) {
        return false;
    }

    QSqlQuery query;

    // Prepara la consulta para actualizar las columnas correspondientes al ID
    query.prepare(
        "UPDATE components SET "
        "name = ?, type = ?, quantity = ?, location = ?, "
        "purchase_date = ?, minimum_quantity = ?, notes = ? "
        "WHERE id = ?"
    );

    // Vincula los nuevos valores en orden (los primeros 7)
    query.addBindValue(component.getName());
    query.addBindValue(component.getType());
    query.addBindValue(component.getQuantity());
    query.addBindValue(component.getLocation());
    query.addBindValue(component.getPurchaseDate().toString(Qt::ISODate));
    query.addBindValue(component.getMinimumQuantity());
    query.addBindValue(component.getNotes());
    
    // Vincula el último "?" al ID para identificar qué fila actualizar
    query.addBindValue(component.getId());

    // Ejecuta la actualización
    if (!query.exec()) {
        qDebug() << "Error de actualización:"
                 << query.lastError().text();
        return false;
    }

    // Retorna verdadero solo si al menos una fila fue modificada en la base de datos
    return query.numRowsAffected() > 0;
}

/**
 * @brief Elimina un componente de la base de datos.
 * @param id Identificador del componente a eliminar.
 * @return True si el componente se eliminó correctamente.
 */
bool DatabaseManager::removeComponent(int id)
{
    // Validación de seguridad
    if (!m_isReady) {
        return false;
    }

    QSqlQuery query;

    // Prepara la consulta de eliminación basada en el ID
    query.prepare("DELETE FROM components WHERE id = ?");
    query.addBindValue(id);

    // Ejecuta el borrado
    if (!query.exec()) {
        qDebug() << "Error de eliminación:"
                 << query.lastError().text();
        return false;
    }

    // Retorna verdadero solo si se encontró y eliminó exitosamente un registro
    return query.numRowsAffected() > 0;
}
