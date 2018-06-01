#include "davisputnam.h"
#include "ui_davisputnam.h"
#include "iostream"


DavisPutnam::DavisPutnam(const ConjuntoClausulas &conjunto,const char &opcion, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DavisPutnam)
{
    ui->setupUi(this);
    conjClausulas=conjunto;
    opcionElegida=opcion;
    ui->davisPutnam->close();
}

bool DavisPutnam::resolver()
{
    ui->davisPutnam->show();
    ui->davisPutnam->append("Para comenzar, llamamos a nuestro conjunto: ");
    mostrarConjunto(conjClausulas);
    if (!variablesfijas.empty())
    {
        ui->davisPutnam->append("");
        ui->davisPutnam->append("Primero, aplicamos eliminación unitaria a las clasulas que contienen a las varibles que siempre serán verdaderas.");
        ui->davisPutnam->append("");
        ui->davisPutnam->append("Variables fijas:");
        set<Clausula>::iterator it=variablesfijas.begin();
        set<Clausula>::iterator itfinal=variablesfijas.end();      
        itfinal--;        
        ui->davisPutnam->append("[ ");
        QTextCursor cursor = ui->davisPutnam->textCursor();
        while (it!=variablesfijas.end())
        {
            cursor.insertText(it->tope().obtenerLiteral());
            if (it!=itfinal)
                cursor.insertText("  ;  ");
            else
                cursor.insertText(" ]");
            it++;
        }
        eliminacionUnitariaVarFijas(conjClausulas);
    }
    ui->davisPutnam->append("");
    ui->davisPutnam->append("Ahora procedemos a resolver el algoritmo de Davis Putnam Logemann Loveland");
    ui->davisPutnam->append("");
    return resolver(conjClausulas);
}

bool DavisPutnam::resolver(ConjuntoClausulas conjunto)
{
    QTextCursor c = ui->davisPutnam->textCursor();
    Clausula unitaria=conjunto.devolverUnitaria();
    while (unitaria.cantLiterales() == 1)
    {
        mostrarConjunto(conjunto);
        QString literalUnitario = unitaria.tope().obtenerLiteral();
        ui->davisPutnam->append("");
        ui->davisPutnam->append("[Unitaria {");
        c.insertText(literalUnitario);
        c.insertText("}]    Aplicamos eliminacion unitaria.");
        ui->davisPutnam->append("");
        conjunto.eliminacionUnitaria(unitaria);
        if( conjunto.existeClausulaVacia() )
        {
            mostrarConjunto(conjunto);
            ui->davisPutnam->append("");
            ui->davisPutnam->append("Como llegamos a clausula vacia, el conjunto es insatisfacible.");
            return false;
        }
        unitaria=conjunto.devolverUnitaria();
    }
    Literal NoHayPuroL("+");
    Literal puro=conjunto.devolverPuro();
    while(!(puro == NoHayPuroL))
    {

        mostrarConjunto(conjunto);
        ui->davisPutnam->append("");
        ui->davisPutnam->append("[Puro ");
        QString literalPuro = puro.obtenerLiteral();
        c.insertText(literalPuro);
        c.insertText("]     Aplicamos eliminacion pura.");
        ui->davisPutnam->append("");
        conjunto.eliminacionPuro(puro);
        puro=conjunto.devolverPuro();
    }

    if (conjunto.vacio())
    {
        mostrarConjunto(conjunto);
        ui->davisPutnam->append("");
        ui->davisPutnam->append("Como llegamos a conjunto vacio, el mismo es satisfacible.");
        ui->davisPutnam->append("");
        return true;
    }
    else
    {
        mostrarConjunto(conjunto);
        Literal l=conjunto.tope();
        if (l.esComplemento())
            l=l.obtenerComplemento();
        ui->davisPutnam->append("");
        ui->davisPutnam->append("Como no hay literal puro, ni clausula unitaria, agregamos una clausula con el literal '");
        c.insertText(l.obtenerLiteral());
        c.insertText("'.");
        ui->davisPutnam->append("");
        Clausula AuxClausula;
        AuxClausula.agregarLiteral(l);
        conjunto.agregarClausula(AuxClausula);
        if (DavisPutnam::resolver(conjunto))
             return true;
        else
            {
                ui->davisPutnam->append("");
                ui->davisPutnam->append("Probamos ahora agregando una cláusula con el complemento de '");
                c.insertText(l.obtenerLiteral());
                c.insertText("'.");
                ui->davisPutnam->append("");
                conjunto.eliminarClausula(AuxClausula);
                Literal lcomp=l.obtenerComplemento();
                AuxClausula.vaciar();
                AuxClausula.agregarLiteral(lcomp);
                conjunto.agregarClausula(AuxClausula);
                return DavisPutnam::resolver(conjunto);
            }
    }
}

void DavisPutnam:: agregar_Valuacion (list<QString> &valparcial, QString & l)
{
    if ((opcionElegida=='n')||(opcionElegida=='c'))
    {
        if (l[0]!='~')
            valparcial.push_back(l);
    }
    else
    {
        if (l[0]=='~')
            valparcial.push_back(l.remove(0,1)+"=0");
        else
            valparcial.push_back(l+"=1");
    }
}

void DavisPutnam:: completar_Valuaciones(list<QString> valparcial, set<QString> variables)
{
    if (variables.empty())
    {
        valparcial.sort();
        valuaciones.push_back(valparcial);
    }
    else
    {
        QString aux=*(variables.begin());
        variables.erase(variables.begin());
        valparcial.push_back(aux+"=0");
        completar_Valuaciones(valparcial,variables);
        valparcial.pop_back();
        valparcial.push_back(aux+"=1");
        completar_Valuaciones(valparcial,variables);
    }
}

void DavisPutnam::set_VarFijas(const set<Clausula> &varFijas)
{
    variablesfijas=varFijas;
}

void DavisPutnam::generar_Valuaciones()
{
    set<QString> variables=conjClausulas.get_Variables();
    unsigned int cantvariables=variables.size();
    list<QString> valparcial;
    ConjuntoClausulas conjunto(conjClausulas);
    if (!variablesfijas.empty())
    {
        set<Clausula>::iterator it=variablesfijas.begin();
        while (it!=variablesfijas.end())
        {
            QString literal=it->tope().obtenerLiteral();
            valparcial.push_back(literal);
            variables.erase(literal);
            it++;
        }
        eliminacionUnitariaVarFijas(conjunto);
    }

    generar_Valuaciones(conjunto,valparcial,variables,cantvariables);
}

void DavisPutnam::generar_Valuaciones(ConjuntoClausulas conjunto,list<QString> valparcial, set<QString> variables, unsigned int cantliterales)
{
    eliminacionUnitariaSucesiva(conjunto, valparcial, variables);
    if (conjunto.vacio())
    {
        if ((opcionElegida=='h') && (valparcial.size()!=cantliterales))
            completar_Valuaciones(valparcial,variables);
        else
        {
            valparcial.sort();
            valuaciones.push_back(valparcial);
        }
    }
    else if (!conjunto.existeClausulaVacia())
    {
        Literal l=conjunto.tope();
        Clausula AuxClausula;
        for (int literalPosible=0; literalPosible<2; literalPosible++) // Dos casos: uno para determinado literal, y el otro para su negado.
        {
            if (literalPosible == 0)
            {
                AuxClausula.agregarLiteral(l);
                conjunto.agregarClausula(AuxClausula);
            }
            else
            {
                AuxClausula.agregarLiteral(l.obtenerComplemento());
                conjunto.agregarClausula(AuxClausula);
            }
            generar_Valuaciones(conjunto,valparcial,variables,cantliterales);
            conjunto.eliminarClausula(AuxClausula);
            AuxClausula.vaciar();
        }
    }
}

void DavisPutnam::eliminacionUnitariaSucesiva(ConjuntoClausulas & conjunto, list<QString> & valparcial, set<QString> & variables)
{
    Clausula unitaria=conjunto.devolverUnitaria();
    while (unitaria.cantLiterales() == 1)
    {
        conjunto.eliminacionUnitaria(unitaria);
        QString literal=unitaria.tope().obtenerLiteral();
        agregar_Valuacion(valparcial,literal);
        variables.erase(literal);
        unitaria=conjunto.devolverUnitaria();
    }
}


void DavisPutnam::mostrar_Valuaciones() const
{
    QTextCursor c = ui->davisPutnam->textCursor();
    unsigned int contador=1;
    list<list<QString> >::const_iterator it=valuaciones.begin();
    if (valuaciones.empty())
        ui->davisPutnam->append("No se ha encontrado ninguna valuación que satisfaciera al conjunto de cláusulas.");
    else
    {
        ui->davisPutnam->append("A continuación se mostrarán las " + QString::number(valuaciones.size()) + " valuaciones encontradas para conjunto de cláusulas: ");
        ui->davisPutnam->append("");
        if (opcionElegida!='h')
        {
            ui->davisPutnam->append("Para el Problema de");
            if (opcionElegida=='n')
                c.insertText(" las n Reinas");
            else if (opcionElegida=='c')
                c.insertText("l Coloreo de Grafo");
            c.insertText(" sólo se mostrarán las variables verdaderas.");
        }
        else
        {
            mostrarConjunto(conjClausulas);
        }
    }
    while (it!=valuaciones.end())
    {
        ui->davisPutnam->append("");
        ui->davisPutnam->append("Valuación ");
        QString aux=QString::number(contador);
        c.insertText(aux);
        c.insertText(": ");
        contador++;
        list<QString>::const_iterator it2=it->begin();
        list<QString>::const_iterator it2final=it->end();
        it2final--;
        while (it2!=it->end())
        {
            QString literal=*it2;
            c.insertText(literal);
            if (it2!=it2final)
                c.insertText(" ; ");
            else
                c.insertText(" .");
            it2++;
        }
        it++;
    }
    ui->davisPutnam->show();
}

list<list<QString> > DavisPutnam::get_Valuaciones() const
{
    return valuaciones;
}

DavisPutnam::~DavisPutnam()
{
    delete ui;
}

bool DavisPutnam::ExisteValuacion()
{
    return !valuaciones.empty();
}

void DavisPutnam::eliminacionUnitariaVarFijas(ConjuntoClausulas & conjunto)
{
    set<Clausula>::iterator it=variablesfijas.begin();
    while (it!=variablesfijas.end())
    {
        Clausula unitaria(*it);
        conjunto.eliminacionUnitaria(unitaria);
        it++;
    }
}

void DavisPutnam::mostrarConjunto(ConjuntoClausulas conjunto) const
{
    ui->davisPutnam->append("S = {  ");
    QTextCursor cursor = ui->davisPutnam->textCursor();
    set<Clausula> conj = conjunto.obtenerConjuntoClausulas();
    set<Clausula>::const_iterator itConj = conj.begin();
    while (itConj != conj.end())
    {
        set<Literal> clausula = itConj->obtenerClausula();
        set<Literal>::iterator itClausula = clausula.begin();
        cursor.insertText("{");
        while (itClausula != clausula.end())
        {
            cursor.insertText(itClausula->obtenerLiteral());
            cursor.insertText(",");
            itClausula++;
        }
        if (clausula.size()!=0)
            cursor.deletePreviousChar();
        cursor.insertText("} , ");
        itConj++;
    }
    cursor.deletePreviousChar();
    cursor.deletePreviousChar();
    cursor.insertText(" }");
}

void DavisPutnam::on_actionAtras_triggered()
{
    switch (opcionElegida)
    {
        case 'h' :
        {
            UIHerramienta * h = new UIHerramienta();
            h->setWindowTitle("Herramienta");
            h->show();
            break;
        }
        case 'c' :
        {
            UIColoreoGrafo * c = new UIColoreoGrafo();
            c->setWindowTitle("Problema del coloreo de un grafo");
            c->show();
            break;
        }
        case 'n' :
        {
            UINReinas *  n = new UINReinas();
            n->setWindowTitle("Problema de las n-reinas");
            n->show();
            break;
        }
    }
    this->close();
}
