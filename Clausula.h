#ifndef CLAUSULA_H
#define CLAUSULA_H
#include <iostream>
#include <set>
#include "Literal.h"

using namespace std;

class Clausula
{
    public:
        Clausula();
        Clausula(const Clausula & c);
        void agregarLiteral(const Literal & l);
        bool perteneceLiteral(const Literal & l) const;
        bool perteneceComplemento(const Literal & l) const;
        void eliminaLiteral(const Literal & l);
        set<Literal> obtenerClausula() const;
        int cantLiterales() const;
        bool operator<(const Clausula & c) const;
        void operator=(const Clausula & c);
        Literal tope() const;
        bool vacia() const;
        void vaciar();
        virtual ~Clausula();
    protected:
    private:
        set<Literal> clausula;
};

#endif // CLAUSULA_H
