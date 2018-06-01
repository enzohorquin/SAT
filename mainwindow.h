#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "conjuntoclausulas.h"
#include "uiherramienta.h"
#include "uinreinas.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_botonReinas_clicked();

    void on_action_Info_triggered();

    void on_actionAtras_triggered();

    void on_botonColoreo_clicked();

    void on_botonHerramienta_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
