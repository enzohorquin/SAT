#include "conjuntoclausulas.h"
#include <QDebug>


ConjuntoClausulas::ConjuntoClausulas()
{
    //ctor
}

ConjuntoClausulas::ConjuntoClausulas(const ConjuntoClausulas &c)
{
    conjuntoClausulas = c.obtenerConjuntoClausulas();
}

void ConjuntoClausulas::operator=(const ConjuntoClausulas &c)
{
    conjuntoClausulas = c.obtenerConjuntoClausulas();
}

ConjuntoClausulas::~ConjuntoClausulas()
{
    //dtor
}

Literal ConjuntoClausulas::tope() const
{
    set<Clausula>:: const_iterator It= conjuntoClausulas.begin();
    Literal L= It->tope();
    return L;
}

void ConjuntoClausulas::vaciarConjuntoClausulas()
{
    conjuntoClausulas.clear();
}

void ConjuntoClausulas::eliminarClausula(const Clausula &c)
{
    conjuntoClausulas.erase(c);
}

set<QString> ConjuntoClausulas::get_Variables()
{
    set<QString> conjVariables;
    set<Clausula>::const_iterator itConjuntoClausulas = conjuntoClausulas.begin();
    while (itConjuntoClausulas != conjuntoClausulas.end())
    {
        set<Literal> clausula = itConjuntoClausulas->obtenerClausula();
        set<Literal>::const_iterator itClausula = clausula.begin();
        while (itClausula != clausula.end())
        {
            QString aux=itClausula->obtenerLiteral();
            if (aux[0]=='~')
                aux.remove(0,1);//0 es la posicion donde se empieza a remover y 1 la cant de caracteres removidos
            conjVariables.insert(aux);
            itClausula++;
        }
        itConjuntoClausulas++;
    }
    return conjVariables;
}

int ConjuntoClausulas::cantClausulas()
{
    return conjuntoClausulas.size();
}

set<Literal> ConjuntoClausulas::get_Literales() const
{
    set<Literal> conjLiterales;
    set<Clausula>::const_iterator itConjuntoClausulas = conjuntoClausulas.begin();
    while (itConjuntoClausulas != conjuntoClausulas.end())
    {
        set<Literal> clausula = itConjuntoClausulas->obtenerClausula();
        set<Literal>::const_iterator itClausula = clausula.begin();
        while (itClausula != clausula.end())
        {
            conjLiterales.insert(*itClausula);
            itClausula++;
        }
        itConjuntoClausulas++;
    }
    return conjLiterales;
}

void ConjuntoClausulas::eliminacionPuro(const Literal & l)
{
    set<Clausula>::iterator it = conjuntoClausulas.begin();
    while (it != conjuntoClausulas.end())
        if (it->perteneceLiteral(l))
        {
            set<Clausula>::iterator elimina = it;
            it++;
            conjuntoClausulas.erase(elimina);
        }
        else
            it++;
}

void ConjuntoClausulas::eliminacionUnitaria(const Clausula & c)
{
    Literal l(c.tope());
    set<Clausula>::iterator it = conjuntoClausulas.begin();
    while (it != conjuntoClausulas.end())
    {
        if (it->perteneceLiteral(l))
        {
            set<Clausula>::iterator elimina = it;
            it++;
            conjuntoClausulas.erase(elimina);
        }
        else
            if (it->perteneceComplemento(l))
                {
                    Clausula aux(*it);
                    aux.eliminaLiteral(l.obtenerComplemento());
                    set<Clausula>::iterator elimina = it;
                    it++;
                    conjuntoClausulas.erase(elimina);
                    conjuntoClausulas.insert(aux);
                }
            else
                it++;
    }
}

Literal ConjuntoClausulas::devolverPuro() const
{
    set<Literal> conjLiterales = get_Literales();
    set<Literal>::const_iterator it = conjLiterales.begin();
    while (it != conjLiterales.end())
    {
      Literal Comp(it->obtenerComplemento());
      if  (conjLiterales.find(Comp) == conjLiterales.end())
          return *it;
      else
      {
          conjLiterales.erase(conjLiterales.find(Comp));
          it++;
      }
    }
    Literal l("+");
    return l;
}

Clausula ConjuntoClausulas::devolverUnitaria() const
{
    set<Clausula>::const_iterator it = conjuntoClausulas.begin();
    while ((it != conjuntoClausulas.end()) && (it->cantLiterales() != 1))
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

void ConjuntoClausulas::agregarClausula(const Clausula & c)
{
    conjuntoClausulas.insert(c);
}

set<Clausula> ConjuntoClausulas::obtenerConjuntoClausulas() const
{
    return conjuntoClausulas;
}

bool ConjuntoClausulas::vacio() const
{
    return conjuntoClausulas.empty();
}

bool ConjuntoClausulas::existeClausulaVacia() const
{
    set<Clausula>::const_iterator it = conjuntoClausulas.begin();
    while (it != conjuntoClausulas.end())
    {
        if (it->vacia())
            return 1;
        it++;
    }
    return 0;
}
