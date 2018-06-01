#include "interfazgrafo.h"
#include "ui_interfazgrafo.h"
#include "uicoloreografo.h"

InterfazGrafo::InterfazGrafo( list<QPair<int, int> > ListaArcos, list<list<QString> > ListaValuaciones, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterfazGrafo)

{
if(!ListaArcos.empty())
{   ListaVal=get_ValuacionesOrdenadas(ListaValuaciones);
    ite= ListaVal.begin();
    ListaA=ListaArcos;
    vector<QString> L = *ite;
    CantNodos = L.size();
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    nroNodo = 0;
    pos.first = 0; pos.second = 0;
    arrNodos = new QPair<int,int>[CantNodos];

    ui->graphicsView->setFixedHeight(CantNodos*50);
    ui->graphicsView->setFixedWidth(231);
    ui->pushButtonSiguiente->setFixedWidth(231);
    this->setFixedSize(245, CantNodos*50 + 120);
    Crea();
   }
else
{
    CantNodos=5;
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    nroNodo = 0;
    pos.first = 0; pos.second = 0;
    arrNodos = new QPair<int,int>[CantNodos];
    ui->graphicsView->setFixedHeight(CantNodos*50);
    ui->graphicsView->setFixedWidth(231);
    ui->pushButtonSiguiente->setFixedWidth(231);
    this->setFixedSize(245, CantNodos*50 + 120);


}
}

InterfazGrafo::~InterfazGrafo()
{
    delete ui;
}

void InterfazGrafo::crearNodo(QString color)
{
    ///SETEO EL COLOR DEL NODO Y SU BORDE.
    QColor colorNodo(color);
    QPen bordeNodo(Qt::black);

    ///ORGANIZO LAS COORDENADAS DE LOS NODOS.
    if (nroNodo%2 == 0)
    {
        pos.second += 100;
        pos.first = 0;
    }
    else
    {
        pos.first += 100;
    }

    ///CREO EL NODO.
    nodo = scene->addEllipse(pos.first,pos.second,30,30,bordeNodo,colorNodo);
    QString textoNodo = QString::number(nroNodo);
    text = scene->addText(textoNodo);
    text->setPos(pos.first+9, pos.second+5);
    text->setDefaultTextColor("white");
    arrNodos[nroNodo] = pos;
    nroNodo++;
}

void InterfazGrafo::crearArco(int primerNodo, int segundoNodo)
{
    QPair<int,int> posicionUno, posicionDos;

    posicionUno = arrNodos[primerNodo];

    posicionDos = arrNodos[segundoNodo];

    if (posicionUno.first <= posicionDos.first)
    {
        QLine arco(posicionUno.first+30, posicionUno.second+15, posicionDos.first, posicionDos.second+15);
        QPen edge("black");
        edge.setWidth(3);
        scene->addLine(arco, edge);
    }
    else
        if (posicionUno.first > posicionDos.first)
        {
            QLine arco(posicionUno.first, posicionUno.second+15, posicionDos.first+30, posicionDos.second+15);
            QPen edge("black");
            edge.setWidth(3);
            scene->addLine(arco, edge);
        }
}

void InterfazGrafo::CreaEjemplo()
{   ui->pushButtonSiguiente->hide();


    crearNodo("grey");
    crearNodo("grey");
    crearNodo("grey");
    crearNodo("grey");
    crearNodo("grey");
    crearArco(0,1);
    crearArco(0,2);
    crearArco(1,3);
    crearArco(2,3);
    crearArco(2,4);
    crearArco(3,4);


}
int InterfazGrafo::RetornaVertice(const QString C) const
{
    QString V="";

        if((C[0]=='R')||(C[0]=='A'))
        {
            V=C[5];


        }
        else
            if(C[0]=='V')
               {

                V=C[6];
            }


        int Vertice = V.split(" ")[0].toInt();

        return Vertice;

}

void InterfazGrafo::InsertaOrd(vector<QString> &A, QString C, int i, int cont, int size)
{ if(cont< size)
    {
        int c = RetornaVertice(A[cont]);

        if(c < i)
        {
            InsertaOrd(A,C,i,cont+1,size);


        }
        else
            A.insert(A.begin()+cont,C);

    }
    else
        A.push_back(C);


}

list<vector<QString> > InterfazGrafo::get_ValuacionesOrdenadas(list<list<QString> > valuaciones)
{

    list< list< QString> > :: iterator ite = valuaciones.begin();
    list< vector< QString> > ListaOrdenada;
    while( ite != valuaciones.end())
    {
        list<QString> Aux = *ite;
        list<QString> :: iterator IteLista= Aux.begin();

        vector<QString> AuxV;

        while(IteLista!=Aux.end())
            {int cont = 0;
               QString C = *IteLista;
            int i = RetornaVertice(C);
            InsertaOrd(AuxV,C,i,cont,AuxV.size());


            IteLista++;

            }
        ListaOrdenada.push_back(AuxV);
        ite++;

    }


    return ListaOrdenada;
}



void InterfazGrafo::on_actionAtras_triggered()
{

    UIColoreoGrafo * c = new  UIColoreoGrafo;
    c->setWindowTitle("Problema del coloreo de un grafo");
    c->show();

    this->close();
}

void InterfazGrafo::Crea()
{
    QString Color="";

    vector<QString> Aux = *ite;

    vector<QString> :: iterator ite2= Aux.begin();
    QString AuxPalabra = "";
    while(ite2!=Aux.end())
    {
        QString AuxString=  *ite2;
        AuxPalabra+=" ";
        AuxPalabra += AuxString;
        if(AuxString[0]=='R')
            Color="red";
        else
            if(AuxString[0]=='V')
            {
                Color="green";
            }
           else
                Color="blue";

        crearNodo(Color);

        ite2++;


    }

    list<QPair<int,int> > :: iterator iteAr= ListaA.begin();

    while(iteAr!=ListaA.end())
    {
       crearArco(iteAr->first,iteAr->second);
        iteAr++;


    }

}



void InterfazGrafo::on_pushButtonSiguiente_clicked()
{
    nroNodo=0;
    pos.first=0;
    pos.second=0;


ite++;
if(ite==ListaVal.end())
{
    ite=ListaVal.begin();
    Crea();
}
else
    Crea();








}
