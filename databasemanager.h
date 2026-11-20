
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QList>
#include <QSqlDatabase>

#include "component.h"

/**
 * @brief Gestiona la base de datos SQLite del inventario.
 */
class DatabaseManager
{
public:

    /**
     * @brief Crea el gestor y abre la conexión con la base de datos.
     */
    DatabaseManager();

    /**
     * @brief Cierra la conexión con la base de datos.
     */
    ~DatabaseManager();

    /**
     * @brief Comprueba si la base de datos está lista.
     * @return True si se inicializó correctamente.
     */
    bool isReady() const;

    /**
     * @brief Recupera todos los componentes almacenados.
     * @return Lista de componentes.
     */
    QList<Component> getComponents();

    /**
     * @brief Inserta un componente.
     * @param component Componente a insertar.
     * @return True si se insertó correctamente.
     */
    bool addComponent(const Component &component);

    /**
     * @brief Actualiza un componente existente.
     * @param component Componente actualizado.
     * @return True si se actualizó correctamente.
     */
    bool updateComponent(const Component &component);

    /**
     * @brief Elimina un componente.
     * @param id Identificador del componente.
     * @return True si se eliminó correctamente.
     */
    bool removeComponent(int id);

private:

    QSqlDatabase m_database;
    bool m_isReady;

    /**
     * @brief Inicializa la base de datos SQLite.
     * @return True si la inicialización tuvo éxito.
     */
    bool initializeDatabase();

    /**
     * @brief Crea las tablas de la base de datos.
     * @return True si las tablas se crearon correctamente.
     */
    bool createTables();
};

#endif // DATABASEMANAGER_H
