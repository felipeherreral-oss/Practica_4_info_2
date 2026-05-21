#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->txtConsoleOutput->append("=== SIMULADOR DE REDES INICIADO ===");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// CAPTURA DE COUT: Redirige las funciones de impresión a la pantalla de Qt
void MainWindow::actualizarPantalla() {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    // Ejecuta la impresión orientada a consola
    miRed.imprimirRed();

    // Devuelve el flujo normal a std::cout
    std::cout.rdbuf(oldCout);

    // Muestra el resultado en el componente gráfico
    ui->txtConsoleOutput->setText(QString::fromStdString(buffer.str()));
}

void MainWindow::on_btnLoadFile_clicked() {
    QString ruta = ui->txtFilePath->text();
    if(!ruta.isEmpty()) {
        miRed.cargarDesdeArchivo(ruta.toStdString());
        actualizarPantalla();
    } else {
        ui->txtConsoleOutput->append("[ERROR] Por favor ingresa una ruta de archivo valida.");
    }
}

void MainWindow::on_btnAddRouter_clicked() {
    std::string id = ui->txtRouterId->text().toStdString();
    if(!id.empty()) {
        miRed.agregarEnrutador(id);
        actualizarPantalla();
    }
}

void MainWindow::on_btnDeleteRouter_clicked() {
    std::string id = ui->txtRouterId->text().toStdString();
    if(!id.empty()) {
        miRed.eliminarEnrutador(id);
        actualizarPantalla();
    }
}

void MainWindow::on_btnConnect_clicked() {
    std::string orig = ui->txtOrig->text().toStdString();
    std::string dest = ui->txtDest->text().toStdString();
    int costo = ui->txtCost->text().toInt();

    if(!orig.empty() && !dest.empty() && costo > 0) {
        miRed.conectar(orig, dest, costo);
        actualizarPantalla();
    }
}

void MainWindow::on_btnDisconnect_clicked() {
    std::string orig = ui->txtOrig->text().toStdString();
    std::string dest = ui->txtDest->text().toStdString();

    if(!orig.empty() && !dest.empty()) {
        miRed.desconectar(orig, dest);
        actualizarPantalla();
    }
}

void MainWindow::on_btnCalculate_clicked() {
    std::string orig = ui->txtRouteOrig->text().toStdString();
    std::string dest = ui->txtRouteDest().toStdString();

    if(!orig.empty() && !dest.empty()) {
        int costoTotal = 0;
        std::vector<std::string> camino = miRed.obtenerRuta(orig, dest, costoTotal);

        ui->txtConsoleOutput->append("\n-----------------------------------");
        if(!camino.empty()) {
            QString resultado = "-> RUTA OPTIMA: ";
            for(size_t i = 0; i < camino.size(); ++i) {
                resultado += QString::fromStdString(camino[i]);
                if(i < camino.size() - 1) resultado += " -> ";
            }
            ui->txtConsoleOutput->append(resultado);
            ui->txtConsoleOutput->append("-> COSTO TOTAL DE ENRUTAMIENTO: " + QString::number(costoTotal));
        } else {
            ui->txtConsoleOutput->append("[ERROR] No se pudo hallar una ruta valida entre " + QString::fromStdString(orig) + " y " + QString::fromStdString(dest));
        }
        ui->txtConsoleOutput->append("-----------------------------------\n");
    }
}
