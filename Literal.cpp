#include "Literal.h"
#include "QDebug"

Literal::Literal(const QString &l)
{
    literal=l;
}

Literal::Literal(const Literal & l)
{
    literal = l.obtenerLiteral();
}

Literal::~Literal()
{
    //dtor
}

Literal Literal::obtenerComplemento() const
{
    QString aux = literal;
    if (aux[0] == '~')
        aux.remove(0,1);
    else
        aux.push_front('~');
    Literal l(aux);
    if (literal==" Azul_1")
        qDebug() << literal<<aux;//no mostro nada
    return aux;
}

QString Literal::obtenerLiteral() const
{
    return literal;
}

bool Literal::esComplemento() const
{
    return (literal[0]=='~');
}

bool Literal::operator==(const Literal & l) const
{
    if (l.obtenerLiteral() == literal)
        return true;
    else
        return false;
}

bool Literal::operator <(const Literal & l) const
{
    if (literal < l.obtenerLiteral())
        return true;
    else
        return false;
}

void Literal::operator=(const Literal &l)
{
    literal=l.obtenerLiteral();
}
