#ifndef CONJUNTO_H
#define CONJUNTO_H
#include <iostream>
#include "Clausula.h"

using namespace std;

class Conjunto
{
    public:
        Conjunto();
        Conjunto(const Conjunto & c);
        void operator= (const Conjunto & c);
        void agregarClausula(const Clausula & c);
        Clausula devolverUnitaria() const;
        Literal devolverPuro() const;
        void eliminacionUnitaria(const Clausula & c);
        void eliminacionPuro(const Literal & l);
        set<Clausula> obtenerConjunto() const;
        bool vacio() const;
        bool existeClausulaVacia() const;
        Literal tope() const;
        void vaciarConjunto();
        void eliminarClausula(const Clausula & c);
        int cantClausulas();
        virtual ~Conjunto();
        set<Literal> conjuntoLiterales() const;

    protected:
    private:
        set<Clausula> conjuntoClausulas;
};

#endif // CONJUNTO_H

