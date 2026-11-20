#include "inventorymanager.h"

/**
 * @brief Crea un gestor de inventario.
 * @param database Puntero al gestor de la base de datos.
 */
InventoryManager::InventoryManager(DatabaseManager *database)
    // Lista de inicialización: guarda la dirección de memoria de la base de datos en nuestra variable privada
    : m_database(database) 
{
    // El cuerpo está vacío porque la asignación del puntero ya se hizo en la línea anterior
}

/**
 * @brief Devuelve todos los componentes almacenados en el inventario.
 * @return Lista de componentes.
 */
QList<Component> InventoryManager::getComponents()
{
    // Usa la flecha (->) para pedirle a la base de datos que ejecute su propia función getComponents()
    return m_database->getComponents();
}

/**
 * @brief Añade un nuevo componente al inventario.
 * @param component Componente a añadir.
 * @return True si la operación tiene éxito.
 */
bool InventoryManager::addComponent(const Component &component)
{
    // Delega la tarea de guardar el componente a la base de datos y retorna su resultado
    return m_database->addComponent(component);
}

/**
 * @brief Actualiza un componente existente.
 * @param component Componente con la información actualizada.
 * @return True si la operación tiene éxito.
 */
bool InventoryManager::updateComponent(const Component &component)
{
    // Delega la tarea de actualizar el componente a la base de datos
    return m_database->updateComponent(component);
}

/**
 * @brief Elimina un componente del inventario.
 * @param id Identificador del componente.
 * @return True si la operación tiene éxito.
 */
bool InventoryManager::removeComponent(int id)
{
    // Le pide a la base de datos que borre el registro con ese ID
    return m_database->removeComponent(id);
}

/**
 * @brief Filtra los componentes por nombre, tipo o ubicación.
 * @param text Texto utilizado para la búsqueda.
 * @return Lista de componentes que coinciden con la búsqueda.
 */
QList<Component> InventoryManager::filterComponents(const QString &text)
{
    // 1. Primero, obtiene la lista completa de TODOS los componentes desde la base de datos
    QList<Component> allComponents = m_database->getComponents();
    
    // 2. Crea una lista nueva y vacía donde guardará solo los que coincidan con la búsqueda
    QList<Component> filteredComponents;

    // 3. Inicia un bucle "for-each": revisa cada 'component' dentro de 'allComponents' uno por uno
    for (const Component &component : allComponents) {
        
        // Comprueba si el texto de búsqueda está contenido en el Nombre, Tipo O Ubicación.
        // Qt::CaseInsensitive hace que no importe si el usuario escribe en mayúsculas o minúsculas.
        if (component.getName().contains(text, Qt::CaseInsensitive) ||
            component.getType().contains(text, Qt::CaseInsensitive) ||
            component.getLocation().contains(text, Qt::CaseInsensitive)) {

            // Si encontró una coincidencia, añade este componente a nuestra lista de filtrados
            filteredComponents.append(component);
        }
    }

    // 4. Devuelve únicamente la lista con los resultados encontrados
    return filteredComponents;
}
