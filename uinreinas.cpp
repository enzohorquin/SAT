#include "uinreinas.h"
#include "ui_uinreinas.h"
#include <sstream>
#include "uitablero.h"

UINReinas::UINReinas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UINReinas)
{
    ui->setupUi(this);

    n=-1;
    ui->lineN->setValidator(new QIntValidator(1,9,this));
    ui->textBrowser->hide();
    ui->textBrowser_2->hide();
    ui->pushFijarReina->setIcon(QIcon(":/iconos/reina.png"));
    ui->pushButtonN->setIcon(QIcon(":/iconos/Tablero.png"));
    ui->pushResolver->setIcon(QIcon(":/iconos/right127.png"));
    ui->pushValuaciones->setIcon(QIcon(":/iconos/search67.png"));
    ui->actionAtras->setIcon(QIcon(":/iconos/back28.png"));
    ui->pushTableros->setIcon(QIcon(":/iconos/approve9"));

    ui->textBrowserReinasFijas->setFixedSize(400,23);
    ui->espacio0->setFixedHeight(7);
    ui->espacio1->setFixedHeight(7);
    ui->pushResolver->setFixedHeight(30);
    ui->pushTableros->setFixedHeight(30);
    ui->pushValuaciones->setFixedHeight(30);
    this->setFixedSize(500, 350);
}


void UINReinas::cargarColumna (Clausula & clausula, Literal & l1, string & fila, string & columna)
{
    for (int p=1; p<=n; p++)
    {
        clausula.agregarLiteral(l1);
        string aux = static_cast<std::ostringstream*>(&(std::ostringstream() << p))->str();
        QString var;
        var = QString::fromStdString("~c"+aux+columna);
        Literal l2(var);
        clausula.agregarLiteral(l2);
        if (aux!=fila)
            C.agregarClausula(clausula);
        clausula.vaciar();
    }
}

void UINReinas::cargarFila (Clausula & clausula, Literal & l1, string & fila, string & columna)
{
    for (int p=1; p<=n; p++)
    {
        clausula.agregarLiteral(l1);
        string aux = static_cast<std::ostringstream*>(&(std::ostringstream() << p))->str();
        QString var;
        var = QString::fromStdString("~c"+fila+aux);
        Literal l2(var);
        clausula.agregarLiteral(l2);
        if (aux!=columna)
            C.agregarClausula(clausula);
        clausula.vaciar();
    }
}

void UINReinas::cargarDiagonal (Clausula & clausula, Literal l1, int & diagonal, int & i, int & j)
{
    int p=i,q=j;
    switch (diagonal)
    {
    case 1 : {p++; q++;break;}
    case 2 : {p++; q--;break;}
    case 3 : {p--; q++;break;}
    case 4 : {p--; q--;break;}
    }
    while ((q<=n) && (p<=n) && (q>0) && (p>0))
    {
        clausula.agregarLiteral(l1);
        string aux1= static_cast<std::ostringstream*>(&(std::ostringstream() << p))->str();
        string aux2= static_cast<std::ostringstream*>(&(std::ostringstream() << q))->str();
        QString var = QString::fromStdString("~c"+aux1+aux2);
        Literal l2(var);
        clausula.agregarLiteral(l2);
        C.agregarClausula(clausula);
        clausula.vaciar();
        switch (diagonal)
        {
        case 1 : {p++; q++;break;}
        case 2 : {p++; q--;break;}
        case 3 : {p--; q++;break;}
        case 4 : {p--; q--;break;}
        }
    }
}

void UINReinas::cargarConjunto ()
{
    for (int i=1; i<=n; i++)
    {
        Clausula clausula1;
        for (int j=1; j<=n; j++)
        {
            string aux1= static_cast<std::ostringstream*>(&(std::ostringstream() << i))->str();
            string aux2 = static_cast<std::ostringstream*>(&(std::ostringstream() << j))->str();
            QString var1 = QString::fromStdString("c"+aux1+aux2);
            Literal l1 (var1);
            clausula1.agregarLiteral(l1);
            Literal l2=l1.obtenerComplemento();
            Clausula clausula2;
            {
                cargarFila(clausula2,l2,aux1,aux2);
                cargarColumna(clausula2,l2, aux1,aux2);
                for (int p=1; p<=4; p++)
                    cargarDiagonal(clausula2,l2,p,i,j);
            }
        }
        C.agregarClausula(clausula1);
    }
}

UINReinas::~UINReinas()
{
    delete ui;
}

void UINReinas::on_pushResolver_clicked()
{
    if (n==-1)
        QMessageBox::warning(this,"Error","Antes de aplicar el algoritmo debe especificar el valor de n.",QMessageBox::Ok);
    else
    {
        cargarConjunto();
        DavisPutnam * dpll = new DavisPutnam(C,'n');
        dpll->set_VarFijas(reinasfijas);
        dpll->resolver();
        this->close();
        dpll->show();
    }
}

void UINReinas::on_pushValuaciones_clicked()
{
    if (n==-1)
        QMessageBox::warning(this,"Error","Antes de aplicar el algoritmo debe especificar el valor de n.",QMessageBox::Ok);
    else
    {
        cargarConjunto();
        DavisPutnam * dpll = new DavisPutnam(C,'n');
        dpll->set_VarFijas(reinasfijas);
        dpll->generar_Valuaciones();
        dpll->mostrar_Valuaciones();
        this->close();
        dpll->show();
    }
}

void UINReinas::on_pushTableros_clicked()
{
    if (n==-1)
        QMessageBox::warning(this,"Error","Antes de aplicar el algoritmo debe especificar el valor de n.",QMessageBox::Ok);
    else
    {
        cargarConjunto();
        DavisPutnam * dpll = new DavisPutnam(C,'n');
        dpll->set_VarFijas(reinasfijas);
        dpll->generar_Valuaciones();
        list<list<QString> > valuaciones=dpll->get_Valuaciones();
        dpll->close();
        if (!valuaciones.empty())
        {
            UITablero * tablero = new UITablero(valuaciones);
            this->close();
            tablero->setWindowTitle("Soluciones");
            tablero->show();
        }
        else
            QMessageBox::warning(this,"Atención","No hay soluciones que mostrar.",QMessageBox::Ok);
    }
}

bool UINReinas::existe_Coordenada(QString texto) const
{
    int i=texto.mid(0,1).toInt(), j=texto.mid(2,1).toInt();
    return ((i<=n)&&(i>0)&&(j<=n)&&(j>0));
}

bool UINReinas::hay_Error(QString texto)
{
    if (n<1)
    {
        QMessageBox::warning(this,"Error","Antes de fijar una reina debe especificar el valor de n.",QMessageBox::Ok);
        return true;
    }
    else if (reinasfijas.size()==n)
    {
        QMessageBox::warning(this,"Error","Ya ha fijado el numero maximo de reinas.",QMessageBox::Ok);
        return true;
    }
    else if(texto[1]!=',')
    {
        QMessageBox::warning(this,"Error","Para fijar una reina debe ingresar sus coordenadas separadas por una coma.",QMessageBox::Ok);
        return true;
    }
    else if (!existe_Coordenada(texto))
    {
        QMessageBox::warning(this,"Error","Las coordenadas ingresadas son incorrectas.",QMessageBox::Ok);
        return true;
    }
    else
        return false;
}

void UINReinas::on_pushFijarReina_clicked()
{
    QString texto = ui->lineReinas->text();
    ui->lineReinas->clear();
    if (!hay_Error(texto))
    {
        QString auxtexto=texto;
        auxtexto.remove(',');
        QString variable= "c" + auxtexto;
        Literal l(variable);
        Clausula unitaria;
        unitaria.agregarLiteral(l);
        if (reinasfijas.find(unitaria)==reinasfijas.end())
        {
            reinasfijas.insert(unitaria);
            QTextCursor c = ui->textBrowserReinasFijas->textCursor();
            QString Vacio="";
            QString T = ui->textBrowserReinasFijas->toPlainText();
            if(T==Vacio)
            {
                c.insertText("(");
                c.insertText(texto);
            }
            else
            {
                c.insertText(" , ");
                c.insertText("(");
                c.insertText(texto);
            }
            c.insertText(")");
        }
        else
            QMessageBox::warning(this,"Atención","Esta reina ya ha sido fijada.",QMessageBox::Ok);
    }
}

void UINReinas::on_actionAtras_triggered()
{
    if ((ui->textBrowser->isVisible()) || (ui->textBrowser_2->isVisible()))
    {
        ui->textBrowserReinasFijas->show();
        ui->lineN->show();
        ui->pushFijarReina->show();
        ui->pushResolver->show();
        ui->label->show();
        ui->label_2->show();
        ui->label_3->show();
        ui->espacio0->show();
        ui->espacio1->show();
        ui->lineReinas->show();
        ui->pushButtonN->show();
        ui->pushTableros->show();
        ui->pushValuaciones->show();
        if (ui->textBrowser->isVisible())
            ui->textBrowser->hide();
        else
            ui->textBrowser_2->hide();
    }
    else
    {
        MainWindow * w = new MainWindow();
        w->show();
        this->close();
    }

}

void UINReinas::on_action_Que_es_esto_triggered()
{
    if (ui->textBrowser_2->isVisible())
        ui->textBrowser_2->close();
    ui->label_3->hide();
    ui->espacio0->hide();
    ui->espacio1->hide();
    ui->textBrowserReinasFijas->hide();
    ui->lineN->hide();
    ui->pushFijarReina->hide();
    ui->pushResolver->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->lineReinas->hide();
    ui->pushButtonN->close();
    ui->pushValuaciones->close();
    ui->pushTableros->close();
    ui->textBrowser->show();

}

void UINReinas::on_actionExplicaci_n_triggered()
{
    if (ui->textBrowser->isVisible())
        ui->textBrowser->close();
    ui->textBrowserReinasFijas->hide();
    ui->label_3->hide();
    ui->lineN->hide();
    ui->espacio0->hide();
    ui->espacio1->hide();
    ui->pushFijarReina->hide();
    ui->pushResolver->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->lineReinas->hide();
    ui->pushButtonN->close();
    ui->pushValuaciones->close();
    ui->pushTableros->close();
    ui->textBrowser_2->show();
}

void UINReinas::on_actionNuevo_triggered()
{
    ui->lineN->clear();
    n=-1;
    reinasfijas.clear();
    ui->textBrowserReinasFijas->clear();
}

void UINReinas::on_pushButtonN_clicked()
{
    if (n==-1)
    {
        QString texto = ui->lineN->text();
        if (texto!="")
        {
            n=texto.toInt();
            ui->lineN->setText("n fijada.");
        }
        else
            QMessageBox::warning(this,"Error","Debe ingresar un valor de n.",QMessageBox::Ok);
    }
    else
    {
        ui->lineN->setText("n fijada.");
        QMessageBox::warning(this,"Error","El valor de n ya ha sido fijado.",QMessageBox::Ok);
    }
}


