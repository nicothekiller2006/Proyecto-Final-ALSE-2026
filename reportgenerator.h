 #ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QList>
#include <QString>

#include "component.h"

/**
 * @brief Genera reportes a partir de los datos del inventario.
 */
class ReportGenerator
{
public:

    /**
     * @brief Exporta los componentes del inventario a un archivo CSV.
     * @param components Lista de componentes a exportar.
     * @param fileName Ruta del archivo de destino.
     * @return True si la exportación tiene éxito.
     */
    static bool exportToCSV(
        const QList<Component> &components,
        const QString &fileName
    );
};

#endif
