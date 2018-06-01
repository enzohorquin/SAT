#include "uitablero.h"
#include "ui_uitablero.h"
#include <QGraphicsPixmapItem>

UITablero::UITablero(const list<list<QString> > &vals, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UITablero)
{
    ui->setupUi(this);
    valuaciones=vals;
    it=valuaciones.begin();
    cantvaluaciones=valuaciones.size();
    cantvariables=it->size();
    list<QString> aux=*it;
    list<QString>::iterator al=aux.begin();
    lado = 50;
    mostrarTablero();
    crearItems();
}

UITablero::~UITablero()
{
    delete ui;
}

void UITablero::on_pushSiguiente_clicked()
{
    if (it==valuaciones.begin())
        ui->pushSiguiente->setText("Siguiente");
    mostrarValuacion();
    it++;
    if (it==valuaciones.end())
        it=valuaciones.begin();
}

void UITablero::mostrarValuacion() const
{
    list<QString> valuacion=*it;
    list<QString>::const_iterator it2=valuacion.begin();
    list<QGraphicsPixmapItem*>::const_iterator ititem=items.begin();
    int x,y;
    while (it2!=valuacion.end())
    {
        QString var=*it2;
        x=var.mid(2,1).toInt()-1;
        y=var.mid(1,1).toInt()-1;
        (*ititem)->setX(lado * x + 5);
        (*ititem)->setY(lado * y + 5);
        it2++;
        ititem++;
    }
    ititem=items.begin();
    for (int i=0; i<cantvariables; i++)
    {
        (*ititem)->setScale(0.02);
        escena->addItem(*ititem);
        ititem++;
    }
    it2=valuacion.begin();
}

void UITablero::mostrarTablero()
{
    escena = new QGraphicsScene();
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    for (int i = 0; i < cantvariables ; i++)
        for (int j = 0; j < cantvariables; j++)
        {
            QBrush brush;
            if ((i+j)%2 == 0)
            {
                brush.setStyle(Qt::SolidPattern);
                brush.setColor(QColor(51,25,0));
            }
            escena->addRect(lado*i,lado*j,lado,lado,pen,brush);
        }
    ui->graphicsView->setScene(escena);
    ui->graphicsView->setFixedHeight(cantvariables*lado + 3);
    ui->graphicsView->setFixedWidth(cantvariables*lado + 3);
    this->setFixedSize(cantvariables*lado + 50, cantvariables*lado + 120);
}

void UITablero::crearItems()
{
    QGraphicsPixmapItem * pixmap1 = new QGraphicsPixmapItem(QPixmap(":/iconos/reina.png"));
    QGraphicsPixmapItem * pixmap2 = new QGraphicsPixmapItem(QPixmap(":/iconos/reina.png"));
    QGraphicsPixmapItem * pixmap3 = new QGraphicsPixmapItem(QPixmap(":/iconos/reina.png"));
    QGraphicsPixmapItem * pixmap4 = new QGraphicsPixmapItem(QPixmap(":/iconos/reina.png"));
    QGraphicsPixmapItem * pixmap5 = new QGraphicsPixmapItem(QPixmap(":/iconos/reina.png"));
    QGraphicsPixmapItem * pixmap6 = new QGraphicsPixmapItem(QPixmap(":/iconos/reina.png"));
    QGraphicsPixmapItem * pixmap7 = new QGraphicsPixmapItem(QPixmap(":/iconos/reina.png"));
    QGraphicsPixmapItem * pixmap8 = new QGraphicsPixmapItem(QPixmap(":/iconos/reina.png"));
    QGraphicsPixmapItem * pixmap9 = new QGraphicsPixmapItem(QPixmap(":/iconos/reina.png"));

    items.push_front(pixmap1);
    items.push_front(pixmap2);
    items.push_front(pixmap3);
    items.push_front(pixmap4);
    items.push_front(pixmap5);
    items.push_front(pixmap6);
    items.push_front(pixmap7);
    items.push_front(pixmap8);
    items.push_front(pixmap9);
}

void UITablero::on_actionAtras_triggered()
{
    UINReinas * n= new UINReinas();
    n->show();
    this->close();
}
