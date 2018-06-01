#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <map>

using namespace std;

template <typename C> class Grafo
{
public:
    class Arco
    {
    public:
        Arco();
        Arco(int adyacente, const C & costo);
        int devolverAdyacente() const;
        const C & devolverCosto() const;
    private:
        int vertice;
        C costo;
    };

public:
    Grafo();
    Grafo(const Grafo & otroGrafo);
    ~Grafo();
    Grafo & operator = (const Grafo & otroGrafo);
    bool estaVacio() const;
    int devolverLongitud() const;
    bool existeVertice(int vertice) const;
    bool existeArco(int origen, int destino) const;
    const C & costoArco(int origen, int destino) const;
    void devolverVertices(list<int> & vertices) const;
    void devolverAdyacentes(int origen, list<Arco> & adyacentes) const;
    void agregarVertice(int vertice);
    void eliminarVertice(int vertice);
    void modificarCostoArco(int origen, int destino, const C & costo);
    void agregarArco(int origen, int destino, const C & costo);
    void eliminarArco(int origen, int destino);

    void vaciar();

private:
    /*
     * Definir la estructura interna
     */
    map<int, map<int, C> > grafo;
}; // class Grafo

#endif // GRAFO_H
