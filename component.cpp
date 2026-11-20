// Incluye la definición de la clase y las librerías necesarias desde la cabecera
#include "component.h"

// Definición del constructor: recibe los parámetros necesarios para crear un componente
Component::Component(
    int id,
    const QString &name,
    const QString &type,
    int quantity,
    const QString &location,
    const QDate &purchaseDate,
    int minimumQuantity,
    const QString &notes
)
    // Lista de inicialización: transfiere directamente el valor de los parámetros a los atributos privados (m_)
    : m_id(id),                          // Asigna el id al atributo m_id
      m_name(name),                      // Asigna el nombre al atributo m_name
      m_type(type),                      // Asigna el tipo al atributo m_type
      m_quantity(quantity),              // Asigna la cantidad al atributo m_quantity
      m_location(location),              // Asigna la ubicación al atributo m_location
      m_purchaseDate(purchaseDate),      // Asigna la fecha de compra al atributo m_purchaseDate
      m_minimumQuantity(minimumQuantity),// Asigna la cantidad mínima al atributo m_minimumQuantity
      m_notes(notes)                     // Asigna las notas al atributo m_notes
{
    // El cuerpo del constructor está vacío porque la asignación de memoria ya se realizó en la lista anterior
}

// Retorna el valor del atributo privado m_id. "const" asegura que esta función no altera los datos originales.
int Component::getId() const
{
    return m_id;
}

// Retorna el nombre del componente guardado en m_name
QString Component::getName() const
{
    return m_name;
}

// Retorna el tipo de componente guardado en m_type
QString Component::getType() const
{
    return m_type;
}

// Retorna la cantidad actual en inventario guardada en m_quantity
int Component::getQuantity() const
{
    return m_quantity;
}

// Retorna la ubicación física del componente guardada en m_location
QString Component::getLocation() const
{
    return m_location;
}

// Retorna la fecha de compra guardada en m_purchaseDate
QDate Component::getPurchaseDate() const
{
    return m_purchaseDate;
}

// Retorna la cantidad mínima permitida guardada en m_minimumQuantity
int Component::getMinimumQuantity() const
{
    return m_minimumQuantity;
}

// Retorna las notas adicionales guardadas en m_notes
QString Component::getNotes() const
{
    return m_notes;
}

// Método "setter" para modificar la cantidad: sobrescribe el valor de m_quantity con el nuevo valor recibido
void Component::setQuantity(int quantity)
{
    m_quantity = quantity;
}

// Sobrescribe el valor de la cantidad mínima (m_minimumQuantity) con el nuevo valor recibido
void Component::setMinimumQuantity(int minimumQuantity)
{
    m_minimumQuantity = minimumQuantity;
}

// Sobrescribe las notas del componente (m_notes) con el nuevo texto recibido
void Component::setNotes(const QString &notes)
{
    m_notes = notes;

}
