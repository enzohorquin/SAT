#include "grafo.h"
template <typename C> Grafo<C>::Arco::Arco()
{
}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename C> int Grafo<C>::Arco::devolverAdyacente() const
{
    return vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolverCosto() const
{
    return costo;
}


template <typename C> Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    this->operator=(otroGrafo);
}

template <typename C> Grafo<C>::~Grafo()

{
    grafo.clear();
}


template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    grafo.clear();
    typename map<int, map<int, C> >::const_iterator itOtro = otroGrafo.grafo.begin();
    while (itOtro != otroGrafo.grafo.end()) {
        grafo[itOtro->first] = itOtro->second;
        itOtro++;
    }

    return *this;
}

template <typename C> bool Grafo<C>::estaVacio() const
{
    return (grafo.empty());
}

template <typename C> int Grafo<C>::devolverLongitud() const
{
    return (grafo.size());
}

template <typename C> bool Grafo<C>::existeVertice(int vertice) const
{
    return (grafo.find(vertice) != grafo.end());
}

template <typename C> bool Grafo<C>::existeArco(int origen, int destino) const
{
    bool result = false;
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            result = true;
    }
    return result;
}

template <typename C> const C & Grafo<C>::costoArco(int origen, int destino) const
{
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    typename map<int, C>::const_iterator itA = itV->second.find(destino);
    return itA->second;
}

template <typename C> void Grafo<C>::devolverVertices(list<int> & vertices) const
{
    typename map<int, map<int, C> >::const_iterator itV = grafo.begin();
    while (itV != grafo.end()) {
        vertices.push_back(itV->first);
        itV++;
    }
}

template <typename C> void Grafo<C>::devolverAdyacentes(int origen, list<Arco> & adyacentes) const
{
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.begin();
        while (itA != itV->second.end()) {
            adyacentes.push_back(Arco(itA->first, itA->second));
            itA++;
        }
    }
}

template <typename C> void Grafo<C>::agregarVertice(int vertice)
{
    if (grafo.find(vertice) == grafo.end()) {
        map<int, C> adyacentes;
        grafo[vertice] = adyacentes;
    }
}

template <typename C> void Grafo<C>::eliminarVertice(int vertice)
{
    grafo.erase(vertice);
    typename map<int, map<int, C> >::iterator itV = grafo.begin();
    while (itV != grafo.end()) {
        typename map<int, C>::iterator itA = itV->second.find(vertice);
        if (itA != itV->second.end()) {
            itV->second.erase(itA);
        }
        itV++;
    }
}

template <typename C> void Grafo<C>::modificarCostoArco(int origen, int destino, const C & costo)
{
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            itA->second = costo;
    }
}

template <typename C> void Grafo<C>::agregarArco(int origen, int destino, const C & costo)
{
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        itV->second[destino] = costo;
    }
}

template <typename C> void Grafo<C>::eliminarArco(int origen, int destino)
{
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        itV->second.erase(destino);
    }
}

template <typename C> void Grafo<C>::vaciar()
{
    grafo.clear();
}

