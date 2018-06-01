
#include "Clausula.h"


Clausula::Clausula()
{
    //ctor
}

Clausula::Clausula(const Clausula &c)
{
    clausula = c.obtenerClausula();
}

Clausula::~Clausula()
{
    //dtor
}

Literal Clausula::tope() const
{
    set<Literal>::const_iterator it = clausula.begin();
    return *it;
}
void Clausula::vaciar()
{
    clausula.clear();
}

bool Clausula::vacia() const
{
    return clausula.empty();
}

bool Clausula::operator<(const Clausula & c) const // {a,b,d} y {a,b,c) = 0 || {a,b,d} y {a,b,c} = 0
{
    if (clausula.size() < c.clausula.size())
        return 1;
    else
        if (clausula.size() > c.clausula.size())
            return 0;
        else
            {
                set<Literal> c2 = c.obtenerClausula();
                set<Literal>::const_iterator itC = c2.begin();
                set<Literal>::const_iterator itClausula = clausula.begin();
                while ((itClausula != clausula.end()) && (*itClausula == *itC))
                {
                    itClausula++;
                    itC++;
                }
                if (itClausula == clausula.end())
                    return 0;
                else
                    if (*itClausula < *itC)
                        return 1;
                    else
                        return 0;
            }
}

void Clausula::operator=(const Clausula &c)
{
    clausula = c.obtenerClausula();
}


void Clausula::agregarLiteral(const Literal & l)
{
    clausula.insert(l);
}

int Clausula::cantLiterales() const
{
    return clausula.size();
}

bool Clausula::perteneceLiteral(const Literal & l) const
{
    set<Literal>::const_iterator it = clausula.find(l);
    if (it == clausula.end())
        return 0;
    else
        return 1;
}

bool Clausula::perteneceComplemento(const Literal & l) const
{
    Literal l2(l.obtenerComplemento());
    set<Literal>::const_iterator it = clausula.find(l2);
    if (it == clausula.end())
        return false;
    else
        return true;
}

void Clausula::eliminaLiteral(const Literal & l)
{
    clausula.erase(l);
}

set<Literal> Clausula::obtenerClausula() const
{
    return clausula;
}
