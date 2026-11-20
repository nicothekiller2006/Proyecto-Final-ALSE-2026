#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include <QDate>

/**
 * @brief Representa un artículo almacenado en el inventario.
 *
 * Esta clase encapsula los datos asociados con un artículo del inventario.
 */
class Component
{
public:

    /**
     * @brief Crea un objeto Component.
     *
     * @param id Identificador único del componente.
     * @param name Nombre del componente.
     * @param type Tipo o categoría del componente.
     * @param quantity Cantidad actual en inventario.
     * @param location Ubicación física del componente.
     * @param purchaseDate Fecha en la que se compró el componente.
     * @param minimumQuantity Cantidad mínima aceptable.
     * @param notes Información adicional sobre el componente.
     */
    Component(
        int id = 0,
        const QString &name = "",
        const QString &type = "",
        int quantity = 0,
        const QString &location = "",
        const QDate &purchaseDate = QDate(),
        int minimumQuantity = 0,
        const QString &notes = ""
    );

    int getId() const;
    QString getName() const;
    QString getType() const;
    int getQuantity() const;
    QString getLocation() const;
    QDate getPurchaseDate() const;
    int getMinimumQuantity() const;
    QString getNotes() const;

    void setQuantity(int quantity);
    void setMinimumQuantity(int minimumQuantity);
    void setNotes(const QString &notes);

private:

    int m_id;
    QString m_name;
    QString m_type;
    int m_quantity;
    QString m_location;
    QDate m_purchaseDate;
    int m_minimumQuantity;
    QString m_notes;
};

#endif // COMPONENT_H
