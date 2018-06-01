#ifndef CONJUNTOCLAUSULAS_H
#define CONJUNTOCLAUSULAS_H
#include "Clausula.h"

class ConjuntoClausulas
{
public:
    ConjuntoClausulas();
    ConjuntoClausulas(const ConjuntoClausulas & c);
    void operator= (const ConjuntoClausulas & c);
    void agregarClausula(const Clausula & c);
    Clausula devolverUnitaria() const;
    Literal devolverPuro() const;
    void eliminacionUnitaria(const Clausula & c);
    void eliminacionPuro(const Literal & l);
    set<Clausula> obtenerConjuntoClausulas() const;
    bool vacio() const;
    bool existeClausulaVacia() const;
    Literal tope() const;
    void vaciarConjuntoClausulas();
    void eliminarClausula(const Clausula & c);
    set<QString> get_Variables();
    int cantClausulas();
    virtual ~ConjuntoClausulas();
    set<Literal> get_Literales() const;

protected:
private:
    set<Clausula> conjuntoClausulas;
};

#endif // ConjuntoClausulas_H
