#include "Conjunto.h"
#include <QDebug>


Conjunto::Conjunto()
{
    //ctor
}

Conjunto::Conjunto(const Conjunto &c)
{
    conjuntoClausulas = c.obtenerConjunto();
}

void Conjunto::operator=(const Conjunto &c)
{
    conjuntoClausulas = c.obtenerConjunto();
}

Conjunto::~Conjunto()
{
    //dtor
}

Literal Conjunto::tope() const
{
    set<Clausula>:: const_iterator It= conjuntoClausulas.begin();
    Literal L= It->tope();
    return L;
}

void Conjunto::vaciarConjunto()
{
    conjuntoClausulas.clear();
}

void Conjunto::eliminarClausula(const Clausula &c)
{
    conjuntoClausulas.erase(c);
}

int Conjunto::cantClausulas()
{
    return conjuntoClausulas.size();
}

set<Literal> Conjunto::conjuntoLiterales() const
{
    set<Literal> conjLiterales;
    set<Clausula>::const_iterator itConjunto = conjuntoClausulas.begin();
    while (itConjunto != conjuntoClausulas.end())
    {
        set<Literal> clausula = itConjunto->obtenerClausula();
        set<Literal>::const_iterator itClausula = clausula.begin();
        while (itClausula != clausula.end())
        {
            conjLiterales.insert(*itClausula);
            itClausula++;
        }
        itConjunto++;
    }
    return conjLiterales;
}

void Conjunto::eliminacionPuro(const Literal & l)
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

void Conjunto::eliminacionUnitaria(const Clausula & c)
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

Literal Conjunto::devolverPuro() const
{
    set<Literal> conjLiterales = conjuntoLiterales();
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

Clausula Conjunto::devolverUnitaria() const
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

void Conjunto::agregarClausula(const Clausula & c)
{
    conjuntoClausulas.insert(c);
}

set<Clausula> Conjunto::obtenerConjunto() const
{
    return conjuntoClausulas;
}

bool Conjunto::vacio() const
{
    return conjuntoClausulas.empty();
}

bool Conjunto::existeClausulaVacia() const
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
