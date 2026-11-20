#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inventorymanager.h"
#include "databasemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(InventoryManager *inventory, DatabaseManager *db, QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_agregar_clicked();
    void on_editar_clicked();
    void on_eliminar_clicked();
    void on_nuevo_clicked();
    void on_tableWidget_itemSelectionChanged();
    void on_buscar_2_textChanged(const QString &text);
    void on_exportar_clicked();

private:
    Ui::MainWindow *ui;
    InventoryManager *m_inventory;
    DatabaseManager *m_db;

    void updateComponentTable(const QString &filterText = QString());
    void clearForm();
    void loadSelectedComponentData();

    Q_DISABLE_COPY(MainWindow)
};

#endif // MAINWINDOW_H
