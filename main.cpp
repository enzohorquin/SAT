#include "mainwindow.h"
#include <QApplication>

/// cambie el tipo de opcionelegida, ahora es un char. Cambie todos los if de botonatras de davisputman por un switch
/// cambie en dpll.mostrarconjunto, agregue un if dsp del segundo while
/// agregue a davisputman dos metodos (uno privado y uno publico) y una estructura privada
/// agregue operador = a la clase conjunto


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
