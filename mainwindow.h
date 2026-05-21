#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "red.h" // Importamos nuestra lógica

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots automáticos de Qt para los clicks de los botones
    void on_btnLoadFile_clicked();
    void on_btnAddRouter_clicked();
    void on_btnDeleteRouter_clicked();
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void on_btnCalculate_clicked();

private:
    Ui::MainWindow *ui;
    Red miRed; // El cerebro de la red viviendo en la interfaz gráfica

    // Función auxiliar para refrescar la consola gráfica con el estado actual
    void actualizarPantalla();
};
#endif // MAINWINDOW_H
