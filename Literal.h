#ifndef LITERAL_H
#define LITERAL_H
#include <QString>

using namespace std;

class Literal
{
public:
    Literal(const QString & l);
    Literal(const Literal & l);
    QString obtenerLiteral() const;
    Literal obtenerComplemento() const;
    bool esComplemento() const;
    bool operator<(const Literal & l) const;
    void operator = (const Literal &l);
    bool operator==(const Literal & l) const;
    virtual ~Literal();
protected:
private:
    QString literal;
};

#endif // LITERAL_H
