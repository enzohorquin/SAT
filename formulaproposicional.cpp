#include "FormulaProposicional.h"
#include <QDebug>


FormulaProposicional::FormulaProposicional()
{
    //ctor
}

FormulaProposicional::FormulaProposicional(const FormulaProposicional &c)
{
    Formula = c.obtenerFormulaProposicional();
}

void FormulaProposicional::operator=(const FormulaProposicional &c)
{
    Formula = c.obtenerFormulaProposicional();
}

FormulaProposicional::~FormulaProposicional()
{
    //dtor
}

Literal FormulaProposicional::tope() const
{
    set<Clausula>:: const_iterator It= Formula.begin();
    Literal L= It->tope();
    return L;
}

void FormulaProposicional::vaciarFormulaProposicional()
{
    Formula.clear();
}

void FormulaProposicional::eliminarClausula(const Clausula &c)
{
    Formula.erase(c);
}

set<QString> FormulaProposicional::get_Variables()
{
    set<QString> conjVariables;
    set<Clausula>::const_iterator itFormulaProposicional = Formula.begin();
    while (itFormulaProposicional != Formula.end())
    {
        set<Literal> clausula = itFormulaProposicional->obtenerClausula();
        set<Literal>::const_iterator itClausula = clausula.begin();
        while (itClausula != clausula.end())
        {
            QString aux=itClausula->obtenerLiteral();
            if (aux[0]=='~')
                aux.remove(0,1);//0 es la posicion donde se empieza a remover y 1 la cant de caracteres removidos
            conjVariables.insert(aux);
            itClausula++;
        }
        itFormulaProposicional++;
    }
    return conjVariables;
}

int FormulaProposicional::cantClausulas()
{
    return Formula.size();
}

set<Literal> FormulaProposicional::get_Literales() const
{
    set<Literal> conjLiterales;
    set<Clausula>::const_iterator itFormulaProposicional = Formula.begin();
    while (itFormulaProposicional != Formula.end())
    {
        set<Literal> clausula = itFormulaProposicional->obtenerClausula();
        set<Literal>::const_iterator itClausula = clausula.begin();
        while (itClausula != clausula.end())
        {
            conjLiterales.insert(*itClausula);
            itClausula++;
        }
        itFormulaProposicional++;
    }
    return conjLiterales;
}

void FormulaProposicional::eliminacionPuro(const Literal & l)
{
    set<Clausula>::iterator it = Formula.begin();
    while (it != Formula.end())
        if (it->perteneceLiteral(l))
        {
            set<Clausula>::iterator elimina = it;
            it++;
            Formula.erase(elimina);
        }
        else
            it++;
}

void FormulaProposicional::eliminacionUnitaria(const Clausula & c)
{
    Literal l(c.tope());
    set<Clausula>::iterator it = Formula.begin();
    while (it != Formula.end())
    {
        if (it->perteneceLiteral(l))
        {
            set<Clausula>::iterator elimina = it;
            it++;
            Formula.erase(elimina);
        }
        else
            if (it->perteneceComplemento(l))
                {
                    Clausula aux(*it);
                    aux.eliminaLiteral(l.obtenerComplemento());
                    set<Clausula>::iterator elimina = it;
                    it++;
                    Formula.erase(elimina);
                    Formula.insert(aux);
                }
            else
                it++;
    }
}

Literal FormulaProposicional::devolverPuro() const
{
    set<Literal> conjLiterales = get_Literales();
    set<Literal>::const_iterator it = conjLiterales.begin();
    while (it != conjLiterales.end())
    {
      Literal Comp(it->obtenerComplemento());
      if  (conjLiterales.find(Comp) == conjLiterales.end())
          return *it;
      else
          it++;
    }
    Literal l("+");
    return l;
}

Clausula FormulaProposicional::devolverUnitaria() const
{
    set<Clausula>::const_iterator it = Formula.begin();
    while ((it != Formula.end()) && (it->cantLiterales() != 1))
        it++;
    if (it->cantLiterales() == 1)
        return *it;
    else
    {
        Literal l1("+"); Literal l2("-");
        Clausula c;
        c.agregarLiteral(l1);
        c.agregarLiteral(l2);
        return c;
    }
}

void FormulaProposicional::agregarClausula(const Clausula & c)
{
    Formula.insert(c);
}

set<Clausula> FormulaProposicional::obtenerFormulaProposicional() const
{
    return Formula;
}

bool FormulaProposicional::vacio() const
{
    return Formula.empty();
}

bool FormulaProposicional::existeClausulaVacia() const
{
    set<Clausula>::const_iterator it = Formula.begin();
    while (it != Formula.end())
    {
        if (it->vacia())
            return 1;
        it++;
    }
    return 0;
}
