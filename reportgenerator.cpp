// Incluye la cabecera de la clase ReportGenerator
#include "reportgenerator.h"

// Librerías de Qt para manipular archivos y flujos de texto
#include <QFile>
#include <QTextStream>

/**
 * @brief Da formato a un valor de texto para exportarlo a CSV.
 * @param value Texto al que se le dará formato.
 * @return Texto formateado según las reglas de los archivos CSV.
 */
static QString formatCSVField(const QString &value)
{
    // Crea una copia del texto original para poder modificarlo
    QString formatted = value;
    
    // Regla de CSV: Si el texto original contiene una comilla doble ("), 
    // se debe reemplazar por dos comillas dobles juntas ("") para que Excel no se confunda.
    formatted.replace("\"", "\"\"");
    
    // Devuelve el texto envuelto en comillas dobles al principio y al final
    return "\"" + formatted + "\"";
}

/**
 * @brief Exporta los componentes del inventario a un archivo CSV.
 * @param components Componentes a exportar.
 * @param fileName Ruta del archivo de destino.
 * @return True si la exportación tiene éxito.
 */
bool ReportGenerator::exportToCSV(
    const QList<Component> &components,
    const QString &fileName
)
{
    // Prepara el archivo en la ruta especificada
    QFile file(fileName);

    // Intenta abrir el archivo en modo "Solo Escritura" y "Texto"
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false; // Falla si no hay permisos o la ruta es inválida
    }

    // Configura el flujo para escribir texto dentro del archivo
    QTextStream stream(&file);

    // Escribe la cabecera con los nombres de las columnas y salta a la siguiente línea (\n)
    stream << "ID,Nombre,Tipo,Cantidad,Ubicacion,Fecha,"
              "Cantidad minima,Notas\n";

    // Recorre todos los componentes de la lista uno por uno
    for (const Component &component : components) {
        
        // Escribe cada atributo separado por comas. 
        // Usa formatCSVField() para los textos, asegurando que no rompan el formato del Excel.
        stream << component.getId() << ","
               << formatCSVField(component.getName()) << ","
               << formatCSVField(component.getType()) << ","
               << component.getQuantity() << ","
               << formatCSVField(component.getLocation()) << ","
               << component.getPurchaseDate().toString(Qt::ISODate) << "," // La fecha ISO no requiere comillas
               << component.getMinimumQuantity() << ","
               << formatCSVField(component.getNotes()) << "\n"; // Añade un salto de línea al final de cada fila
    }

    // Cierra el archivo y guarda los cambios en el disco
    file.close();

    // Indica que la operación fue un éxito
    return true;
}
