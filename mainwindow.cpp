#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->hide();
    ui->textBrowser->hide();
    ui->botonReinas->setFixedSize(120,100);
    ui->botonColoreo->setFixedSize(120,100);
    ui->botonHerramienta->setFixedSize(120,100);
    ui->botonReinas->setIcon(QIcon(":/iconos/reina.png"));
    ui->botonColoreo->setIcon(QIcon(":/iconos/grafo_imagen.png"));
    ui->botonHerramienta->setIcon(QIcon(":/iconos/icono_herramienta.png"));
    QSize tamanoIconos;
    tamanoIconos.setHeight(70);
    tamanoIconos.setWidth(80);
    ui->botonReinas->setIconSize(tamanoIconos);
    ui->botonColoreo->setIconSize(tamanoIconos);
    ui->botonHerramienta->setIconSize(tamanoIconos);
    ui->textBrowser->setFixedHeight(250);
    ui->botonImagen->setIcon(QIcon(":/iconos/iconoVentanaTransparente.png"));
    QSize tamanoImagen;
    tamanoImagen.setHeight(200);
    tamanoImagen.setWidth(350);
    ui->botonImagen->setIconSize(tamanoImagen);
    this->setFixedSize(500,350);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Info_triggered()
{
    this->setFixedSize(500, 300);
    ui->toolBar->show();
    ui->textBrowser->show();
    ui->botonReinas->hide();
    ui->botonColoreo->hide();
    ui->botonHerramienta->hide();
    ui->botonImagen->hide();
    ui->labelSeleccion->hide();
}

void MainWindow::on_actionAtras_triggered()
{
    this->setFixedSize(500,380);
    ui->toolBar->hide();
    ui->botonImagen->show();
    ui->textBrowser->hide();
    ui->botonReinas->show();
    ui->botonColoreo->show();
    ui->botonHerramienta->show();
    ui->labelSeleccion->show();
}

void MainWindow::on_botonColoreo_clicked()
{
    UIColoreoGrafo * c = new UIColoreoGrafo ;
    c->setWindowTitle("Problema del coloreo de un grafo");
    c->show();
    this->close();
}

void MainWindow::on_botonReinas_clicked()
{
    UINReinas * n = new UINReinas();
    n->setWindowTitle("Problema de las n-reinas");
    n->show();
    this->close();
}
void MainWindow::on_botonHerramienta_clicked()
{
    UIHerramienta * h = new UIHerramienta();
    h->setWindowTitle("Herramienta");
    h->show();
    this->close();
}
