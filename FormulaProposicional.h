#ifndef FORMULAPROPOSICIONAL_H
#define FORMULAPROPOSICIONAL_H
#include "Clausula.h"

class FormulaProposicional
{
public:
    FormulaProposicional();
    FormulaProposicional(const FormulaProposicional & c);
    void operator= (const FormulaProposicional & c);
    void agregarClausula(const Clausula & c);
    Clausula devolverUnitaria() const;
    Literal devolverPuro() const;
    void eliminacionUnitaria(const Clausula & c);
    void eliminacionPuro(const Literal & l);
    set<Clausula> obtenerFormulaProposicional() const;
    bool vacio() const;
    bool existeClausulaVacia() const;
    Literal tope() const;
    void vaciarFormulaProposicional();
    void eliminarClausula(const Clausula & c);
    set<QString> get_Variables();
    int cantClausulas();
    virtual ~FormulaProposicional();
    set<Literal> get_Literales() const;

protected:
private:
    set<Clausula> Formula;
};

#endif // FORMULAPROPOSICIONAL_H
