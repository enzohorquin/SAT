#include "uicoloreografo.h"
#include "ui_uicoloreografo.h"
#include "grafo.h"

UIColoreoGrafo::UIColoreoGrafo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIColoreoGrafo)
{
    ui->setupUi(this);
    cont= 0 ;
    ui->Resolver->setIcon(QIcon(":/iconos/right127.png"));
    ui->BorraTodo->setIcon(QIcon(":/iconos/close33.png"));
    ui->borrarVertice->setIcon(QIcon(":/iconos/circular194.png"));
    ui->borrarUltimoArco->setIcon(QIcon(":/iconos/circular194.png"));
    ui->CargarArco->setIcon(QIcon(":/iconos/approve9.png"));
    ui->CargarVertice->setIcon(QIcon(":/iconos/approve9.png"));
    ui->actionAtras->setIcon(QIcon(":/iconos/back28.png"));
    ui->actionProblema_del_Coloreo_de_un_Grafo->setIcon(QIcon(":/iconos/configuration12")) ;
    ui->actionNuevo->setIcon(QIcon(":/iconos/add121.png"));
    ui->pushButtonVerGrafo->setIcon(QIcon(":/iconos/search67.png"));
    ui->pushButtonVerGrafo->hide();
    ui->textBrowser_2->hide();
    ui->textBrowserC->hide();
    ui->textBrowser->hide();
    ui->pushButtonVerVal->setIcon(QIcon(":/iconos/search67.png"));
    ui->botonGrafos->setIcon(QIcon(":/iconos/search67.png"));
    ui->textBrowserA->setFixedSize(450,23);
    ui->textBrowserV->setFixedSize(450,23);
    ui->lineArco->setFixedWidth(99);
    ui->espacio0->setFixedHeight(7);
    ui->espacio2->setFixedHeight(7);
    ui->Resolver->setFixedHeight(30);
    ui->botonGrafos->setFixedHeight(30);
    ui->pushButtonVerVal->setFixedHeight(30);
    this->setFixedSize(600,400);
}

void UIColoreoGrafo::GeneraConjuntoCondicion2(ConjuntoClausulas Conj,ConjuntoClausulas & Resultado)
{
    set<Clausula> C= Conj.obtenerConjuntoClausulas();
    set<Clausula> :: iterator  it = C.begin();
    while(it!= C.end())
    {
        set<Literal> Cl1;
        Cl1=it->obtenerClausula();
        set<Literal> :: const_iterator itec1= Cl1.begin();
        while(itec1!=Cl1.end())
        {
            Clausula Cl2;
            QString c= itec1->obtenerLiteral();
            c.push_front('~');
            Literal Comp(c);
            Cl2.agregarLiteral(Comp);
            set<Literal>:: const_iterator iteradorAux= itec1;
            iteradorAux++;
            set<Literal> :: const_iterator ite2= iteradorAux;
            while(ite2!=Cl1.end())
            {
                QString c= ite2->obtenerLiteral();
                c.push_front('~');
                Literal L(c);
                Cl2.agregarLiteral(L);
                Resultado.agregarClausula(Cl2);
                Cl2.eliminaLiteral(L);
                ite2++;

            }
            itec1++;

        }
    it++;
}
}

void UIColoreoGrafo::GeneraConjuntoCondicion3(Grafo<int> & G, ConjuntoClausulas &Resultado)
{
    list<int> ListaVertices ;
    G.devolverVertices(ListaVertices);
    list<int>::iterator ite=ListaVertices.begin();
    list<int>::iterator ite2=ite;
    while(ite!=ListaVertices.end())
    {
        int v=*ite;
        ite2=ite;
        ite2++;
        while(ite2!=ListaVertices.end())
        {
            Clausula C;
            int k=*ite2;
            if(G.existeArco(v,k))
            {
                QString Cad= QString::number(v);
                QString Cad2= QString::number(k);
                QString L="~Rojo_"+Cad;
                QString L1="~Rojo_"+Cad2;
                Literal a(L);
                Literal b(L1);
                C.agregarLiteral(a);
                C.agregarLiteral(b);
                Resultado.agregarClausula(C);
                C.vaciar();

                L="~Azul_"+Cad;
                L1="~Azul_"+Cad2;
                Literal c(L);
                Literal d(L1);
                C.agregarLiteral(c);
                C.agregarLiteral(d);
                Resultado.agregarClausula(C);
                C.vaciar();

                L="~Verde_"+Cad;
                L1="~Verde_"+Cad2;
                Literal e(L);
                Literal f(L1);
                C.agregarLiteral(e);
                C.agregarLiteral(f);
                Resultado.agregarClausula(C);
                C.vaciar();
            }
            ite2++;
        }
        ite++;

    }
}

void UIColoreoGrafo::GeneraConjuntoCondicion1(Grafo<int> & G, ConjuntoClausulas &conjunto)
{
    int k=3;
    list<int> ListaVertices;
    G.devolverVertices(ListaVertices);
    list<int>::iterator it= ListaVertices.begin();
    Clausula C;
    while(it!=ListaVertices.end())
    {
        int i= *it;
        for(int j=1;j<=k;j++)
        {
            QString cadena="";
            if(j==1)
            {
                cadena= QString::number(i);
                QString Rojo="Rojo_";
                cadena=Rojo+cadena;
                Literal L(cadena);
                C.agregarLiteral(L);
            }
            else if(j==2)
            {
                cadena= QString::number(i);
                QString Verde= "Verde_";
                cadena=Verde+cadena;
                Literal L(cadena);
                C.agregarLiteral(L);
            }
            else
            {
                cadena= QString::number(i);
                QString Blue="Azul_";
                cadena=Blue+cadena;
                Literal L(cadena);
                C.agregarLiteral(L);
            }
        }
        conjunto.agregarClausula(C);
        C.vaciar();
        it++;
    }

}

void UIColoreoGrafo::GeneraConjuntoClausulas(Grafo<int> & G, ConjuntoClausulas & conjunto)
{
    GeneraConjuntoCondicion1(G,conjunto);
    ConjuntoClausulas Aux(conjunto);
    GeneraConjuntoCondicion2(Aux,conjunto);
    GeneraConjuntoCondicion3(G,conjunto);
}

UIColoreoGrafo::~UIColoreoGrafo()
{
    delete ui;
}

void UIColoreoGrafo::Borra(int vertice)
{
    list<QPair<int,int> > :: iterator ite = ListaArcos.begin();
    while (ite!=ListaArcos.end())
    {
        if((ite->first==vertice) || ( ite->second==vertice))
        {
           list<QPair<int,int> > :: iterator ABorrar;
           ABorrar=ite;
           ite++;
           ListaArcos.erase(ABorrar);
        }
        else
            ite++;
    }
}

void UIColoreoGrafo::BorraTextBrowser(int vertice)
{

    QTextCursor c= ui->textBrowserA->textCursor();
    QString t = ui->textBrowserA->toPlainText();
    QString Guardado="";
    QString :: iterator ite= t.begin();
    if(t!="")
    {
        while(ite!=t.end())
        {
            if(*ite=='(')
            {
                ite++;
                QString Aux=*ite;
                int i = Aux.split(" ")[0].toInt();
                ite++;
                ite++;
                QString Aux2=*ite;
                int j = Aux2.split(" ")[0].toInt();
                if((i!=vertice)&&(j!=vertice))
                    Guardado= Guardado+"("+Aux+","+Aux2+")"+",";
                ite++;
                if(ite!=t.end())
                    ite++;
                if(ite!=t.end())
                    ite++;
            }

        }
    }
    if(Guardado!="")
    {
        int k = Guardado.size();
        if(Guardado[k-1]==',')
            Guardado.remove(k-1,1);
        ui->textBrowserA->clear();
        c.insertText(Guardado);
    }
    else
        ui->textBrowserA->clear();
}

bool UIColoreoGrafo::arcoCorrecto(QString & texto, int &origen, int & destino)
{
    bool tof=true;
    if (origen==0)
        if (texto[0]!='0')
            tof=false;
    if (destino==0)
        if (texto[2]!='0')
            tof=false;
    return ((texto.size()==3)&&(texto[1]==',')&&(origen>=0) && (destino>=0) && (origen!=destino) && tof);
}

void UIColoreoGrafo::on_CargarArco_clicked()
{
    QString texto = ui->lineArco->text();
    QString vacio= "";
    int origen,destino;
    QString A="";
    A+=texto[0];
    QString B="";
    B+=texto[2];
    origen = A.toInt();
    destino= B.toInt();
    if (arcoCorrecto (texto,origen,destino))
    {
        QTextCursor c= ui->textBrowserA->textCursor();
        QString t = ui->textBrowserA->toPlainText();
        if(G.existeVertice(origen)&&(G.existeVertice(destino)))
            if(!G.existeArco(origen,destino))
            {
                G.agregarArco(origen,destino,1);
                G.agregarArco(destino,origen,1);
                QPair<int,int> Aux  ;
                Aux.first=origen;
                Aux.second=destino;
                ListaArcos.push_back(Aux);
                ui->lineArco->clear();
                if(t==vacio)
                {
                    c.insertText("(");
                    c.insertText(texto);
                }
                else
                {
                    c.insertText(",");
                    c.insertText("(");
                    c.insertText(texto);
                }
               c.insertText(")");
            }
            else
            {
                QMessageBox::warning(this,"Atención","Esta arista ya existe.",QMessageBox::Ok);
                ui->lineArco->clear();
            }
        else
        {
            QMessageBox::warning(this,"Atención","Alguno de los vértices no existe.",QMessageBox::Ok);
            ui->lineArco->clear();
        }
    }
    else
    {
        QMessageBox::warning(this,"Atención","Por favor, ingrese correctamente la arista.",QMessageBox::Ok);
        ui->lineArco->clear();
    }
}

void UIColoreoGrafo::on_BorraTodo_clicked()
{
    ui->textBrowserA->clear();
    ui->textBrowserC->clear();
    ui->textBrowserV->clear();
    G.vaciar();
    ListaArcos.clear();
    cont=0;
}

void UIColoreoGrafo::on_Resolver_clicked()
{
    GeneraConjuntoClausulas(G,conjunto);
    if(!G.estaVacio())
    {
        DavisPutnam * dpll = new DavisPutnam(conjunto,'c');
        dpll->resolver();
        dpll->show();
        conjunto.vaciarConjuntoClausulas();
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"Error."," Por favor, ingrese vertices y aristas correctamente.",QMessageBox::Ok);
        conjunto.vaciarConjuntoClausulas();
    }
}

void UIColoreoGrafo::on_CargarVertice_clicked()
{
    if(cont<6)
    {
        QString texto = QString::number(cont);
        G.agregarVertice(cont);
        cont++;
        QString vacio= "";
        QTextCursor c= ui->textBrowserV->textCursor();
        QString t= ui->textBrowserV->toPlainText();
        if (t==vacio)
            c.insertText(texto);
        else
        {
            c.insertText(",");
            c.insertText(texto);
        }
    }
    else
    {
        QMessageBox::warning(this,"Error."," Ya ha agregado el maximo de vertices posibles.",QMessageBox::Ok);
        ui->lineArco->clear();
    }
}

void UIColoreoGrafo::on_borrarVertice_clicked()
{
    QString Vertices= ui->textBrowserV->toPlainText();
    QString ultimaClausula="";
     QTextCursor c= ui->textBrowserV->textCursor();
    int vertice;
     if (Vertices != ultimaClausula)
    {
        int Size  =  Vertices.length();
        QString::const_iterator it = Vertices.end();
         it--;


        QString::const_iterator ite2=Vertices.begin();
        if(ite2==it)

        {   vertice = Vertices.split(" ")[0].toInt();
            Borra(vertice);
            BorraTextBrowser(vertice);
            G.eliminarVertice(vertice);
            cont--;
            ui->textBrowserV->clear();

        }
       else

        {  QChar Aux  = Vertices[Size-1];
           QString Aux2= "";
           Aux2+=Aux;
           int vertice  = Aux2.split(" ")[0].toInt();
            Borra(vertice);
            BorraTextBrowser(vertice);
           G.eliminarVertice(vertice);
           cont--;
           it--;

       while(ite2!=it)
       {
           ultimaClausula = ultimaClausula+ *ite2;
           ite2++;
       }
       ui->textBrowserV->clear();
       c.insertText(ultimaClausula);
     }}

}

void UIColoreoGrafo::on_borrarUltimoArco_clicked()
{
    QString Arco= ui->textBrowserA->toPlainText();
    QString UltimoArco="";
    QTextCursor c=ui->textBrowserA->textCursor();
    QString ::const_iterator it= Arco.end();
    QString ::const_iterator ite2=Arco.begin();
    if(Arco!=UltimoArco)
    {
        it--;it--;it--;it--;it--;
        if(it==ite2)
        {
            QChar A = Arco[1];
            QString A2= "";
            A2= A+A2;
            int ori = A2.split(" ")[0].toInt();
            A= Arco[3];
            A2="";
            A2=A+A2;
            int des = A2.split(" ")[0].toInt();
            if((G.existeVertice(ori)) && ( G.existeVertice(des)))
            {
                G.eliminarArco(ori,des);
                G.eliminarArco(des,ori);
                ListaArcos.pop_back();
            }
            ui->textBrowserA->clear();
        }
        else
        {
            it--;
            int Size= Arco.length();
            QChar A = Arco[Size-2];
            QString A2= "";
            A2= A+A2;
            int dest = A2.split(" ")[0].toInt();
            A=Arco[Size-4];
            A2="";
            A2=A+A2;
            int ori = A2.split(" ")[0].toInt();
            if((G.existeVertice(ori)) && ( G.existeVertice(dest)))
            {
                G.eliminarArco(ori,dest);
                G.eliminarArco(dest,ori);
                ListaArcos.pop_back();
            }
            while(ite2!=it)
            {
                UltimoArco = UltimoArco + *ite2;
                ite2++;
            }
            ui->textBrowserA->clear();
            c.insertText(UltimoArco);
        }
    }
}

void UIColoreoGrafo::on_action_Que_es_un_Grafo_triggered()
{
    ui->pushButtonVerGrafo->show();
    ui->textBrowser_2->hide();
    ui->borrarUltimoArco->hide();
    ui->borrarVertice->hide();
    ui->BorraTodo->hide();
    ui->textBrowserA->hide();
    ui->textBrowserC->hide();
    ui->textBrowserV->hide();
    ui->CargarArco->hide();
    ui->CargarVertice->hide();
    ui->espacio0->hide();
    ui->espacio2->hide();
    ui->label_5->hide();
    ui->Resolver->hide();
    ui->lineArco->hide();
    ui->botonGrafos->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->textBrowser->show();
    ui->pushButtonVerVal->hide();
}

void UIColoreoGrafo::on_actionNuevo_triggered()
{
    UIColoreoGrafo * c = new UIColoreoGrafo;
    c->setWindowTitle("Problema del coloreo de un grafo");
    c->show();
    this->close();
}

void UIColoreoGrafo::on_actionAtras_triggered()
{
    if ((ui->textBrowserC->isVisible()) || ( ui->textBrowser->isVisible() ) || (ui->textBrowser_2->isVisible()))
    {
        ui->pushButtonVerGrafo->hide();
        ui->textBrowser_2->hide();
        ui->textBrowserC->hide();
        ui->borrarUltimoArco->show();
        ui->borrarVertice->show();
        ui->BorraTodo->show();
        ui->textBrowserA->show();
        ui->textBrowserV->show();
        ui->CargarArco->show();
        ui->CargarVertice->show();
        ui->label_5->show();
        ui->espacio0->show();
        ui->espacio2->show();
        ui->Resolver->show();
        ui->lineArco->show();
        ui->botonGrafos->show();
        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->pushButtonVerVal->show();
        ui->textBrowser->hide();
        ui->centralwidget->show();
    }
    else
    {
        MainWindow * w = new MainWindow();
        w->show();
        this->close();
    }
}

void UIColoreoGrafo::on_actionProblema_del_Coloreo_de_un_Grafo_triggered()
{
    ui->pushButtonVerGrafo->hide();
    ui->pushButtonVerVal->hide();
    ui->textBrowserC->hide();
    ui->borrarUltimoArco->hide();
    ui->borrarVertice->hide();
    ui->BorraTodo->hide();
    ui->textBrowserA->hide();
    ui->textBrowser->hide();
    ui->textBrowserV->hide();
    ui->CargarArco->hide();
    ui->CargarVertice->hide();
    ui->label_5->hide();
    ui->espacio0->hide();
    ui->espacio2->hide();
    ui->botonGrafos->hide();
    ui->Resolver->hide();
    ui->lineArco->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->textBrowser_2->show();
}

void UIColoreoGrafo::on_pushButtonVerGrafo_clicked()    //Boton ver Grafo
{
    list<list<QString> > L;
    list<QPair<int, int > > Vacia;
    list<QString> Aux;
    for(int i=0; i<5; i++)
        Aux.push_back("Rojo_1");
    L.push_back(Aux);
    InterfazGrafo * w = new InterfazGrafo(Vacia,L);
    w->CreaEjemplo();
    w->setWindowTitle("Ejemplo de un Grafo.");
    this->close();
    w->show();
}

void UIColoreoGrafo::on_pushButtonVerVal_clicked() // Boton ver Valuaciones
{
    if(!G.estaVacio())
    {
        GeneraConjuntoClausulas(G,conjunto);
        DavisPutnam * dpll = new DavisPutnam(conjunto,'c');
        dpll->generar_Valuaciones();
        dpll->mostrar_Valuaciones();
        this->close();
        dpll->show();
    }
    else
    {
        QMessageBox::warning(this,"Atención","El grafo está vacío.",QMessageBox::Ok);
        ui->lineArco->clear();
    }
}

void UIColoreoGrafo::on_botonGrafos_clicked()
{
    if(!G.estaVacio())
    {
        if(!ListaArcos.empty())
        {
            GeneraConjuntoClausulas(G,conjunto);
            DavisPutnam * dpll = new DavisPutnam(conjunto,'c');
            dpll->generar_Valuaciones();
            conjunto.vaciarConjuntoClausulas();
            if(dpll->ExisteValuacion())
            {
               list<list<QString> > L  = dpll->get_Valuaciones();
               InterfazGrafo * g = new InterfazGrafo(ListaArcos,L);
               g->setWindowTitle("Grafos solución");
               g->show();
               this->close();
            }
            else
            {
                conjunto.vaciarConjuntoClausulas();
                QMessageBox::warning(this,"Atención", "No se encontro valuación que satisfaciera el conjunto de clausulas.");
            }
        }
        else
            QMessageBox::warning(this,"Atención", "Por favor, cargue alguna arista.");
    }
    else
        QMessageBox::warning(this,"Atención", "No ha cargado ningun vértice aún.");
}

void UIColoreoGrafo::on_actionVerFormalizacion_triggered()
{
    ui->pushButtonVerVal->hide();
    ui->textBrowser_2->hide();
    ui->borrarUltimoArco->hide();
    ui->borrarVertice->hide();
    ui->BorraTodo->hide();
    ui->textBrowserA->hide();
    ui->textBrowser->hide();
    ui->textBrowserV->hide();
    ui->CargarArco->hide();
    ui->CargarVertice->hide();
    ui->botonGrafos->hide();
    ui->Resolver->hide();
    ui->lineArco->hide();
    ui->pushButtonVerGrafo->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->textBrowserC->show();
    ui->label_5->hide();
    ui->espacio0->hide();
    ui->espacio2->hide();
}
