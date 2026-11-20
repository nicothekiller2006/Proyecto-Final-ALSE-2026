// Librerías base de Qt para manejar la aplicación en general y mostrar ventanas de alerta
#include <QApplication>
#include <QMessageBox>

// Incluye las cabeceras de nuestras propias clases
#include "mainwindow.h"
#include "databasemanager.h"
#include "inventorymanager.h"

// Función principal de C++: el sistema operativo ejecuta esto al abrir el programa
int main(int argc, char *argv[])
{
    // Inicializa el entorno gráfico de Qt y maneja los argumentos de la línea de comandos
    QApplication application(argc, argv);

    // 1. Crea el gestor de la base de datos. (Recuerda que su constructor intenta conectarse automáticamente)
    DatabaseManager database;

    // 2. Verifica si hubo un error crítico al conectar o crear las tablas de la base de datos
    if (!database.isReady()) {
        // Muestra una ventana emergente de error crítico al usuario
        QMessageBox::critical(
            nullptr,                           // Sin ventana "padre" (porque aún no hemos creado la ventana principal)
            "Error de base de datos",          // Título de la ventana
            "No se pudo inicializar la base de datos." // Mensaje
        );

        // Termina el programa inmediatamente con el código 1 (que en Linux/Ubuntu significa "salida por error")
        return 1;
    }

    // 3. Crea el gestor de inventario pasándole la dirección de memoria (&) de nuestra base de datos
    InventoryManager inventory(&database);

    // 4. Crea la ventana principal de la interfaz gráfica.
    // Le pasa las direcciones de memoria de la lógica (inventory) y de los datos (database)
    MainWindow window(&inventory, &database);
    
    // Hace que la ventana principal se vuelva visible en la pantalla
    window.show();

    // 5. Inicia el "bucle de eventos" (event loop) de Qt. 
    // A partir de esta línea, el programa se queda esperando a que el usuario haga clics, escriba, etc.,
    // hasta que el usuario decida cerrar la ventana.
    return application.exec();
    }
