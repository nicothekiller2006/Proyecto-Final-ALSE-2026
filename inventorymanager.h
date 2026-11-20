#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <QList>
#include <QString>

#include "component.h"
#include "databasemanager.h"

/**
 * @brief Gestiona las operaciones del inventario.
 *
 * Esta clase conecta la lógica de la aplicación con la base de datos.
 */
class InventoryManager
{
public:
    /**
     * @brief Crea un gestor de inventario.
     * @param database Puntero al gestor de la base de datos.
     */
    explicit InventoryManager(DatabaseManager *database);

    /**
     * @brief Devuelve todos los componentes almacenados en el inventario.
     * @return Lista de componentes.
     */
    QList<Component> getComponents();

    /**
     * @brief Añade un nuevo componente al inventario.
     * @param component Componente a añadir.
     * @return True si la operación tiene éxito.
     */
    bool addComponent(const Component &component);

    /**
     * @brief Actualiza un componente existente.
     * @param component Componente con la información actualizada.
     * @return True si la operación tiene éxito.
     */
    bool updateComponent(const Component &component);

    /**
     * @brief Elimina un componente del inventario.
     * @param id Identificador del componente.
     * @return True si la operación tiene éxito.
     */
    bool removeComponent(int id);

    /**
     * @brief Filtra los componentes por nombre, tipo o ubicación.
     * @param text Texto utilizado para la búsqueda.
     * @return Lista de componentes que coinciden con la búsqueda.
     */
    QList<Component> filterComponents(const QString &text);

private:
    DatabaseManager *m_database;
};

#endif
