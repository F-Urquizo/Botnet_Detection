//
//  Vertex.hpp
//  actividad4-2
//
//  Created by José Manuel García Zumaya on 08/11/23.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Edge.hpp"

template <class V, class E>
class Vertex {
    V info;
    std::vector< Edge<V, E> * > edges;
    std::vector< Edge<V, E> * > edgesEntrantes;
    int conexionesEntrantes = 0;
    int conexionesSalientes = 0;

public:
    Vertex() {}
    Vertex(V _info) : info(_info) {}
    ~Vertex();

    V getInfo() const;
    void setInfo(const V &);

    std::vector< Edge<V,E> * > * getEdges();
    std::vector< Edge<V,E> * > * getEdgesEntrantes();

    void addEdge(Edge<V,E> *);
    void addEdgeEntrante(Edge<V,E> *);
    void removeEdge(Edge<V,E> *);

    bool operator ==(const Vertex<V,E> &);

    template <class Vn, class En>
    friend std::ostream & operator <<(std::ostream &, const Vertex<Vn, En> &);

    int getConexionesEntrantes() const;
    int getConexionesSalientes() const;
    void plusConexionesEntrantes();
    void plusConexionesSalientes();
    void removeConexionesEntrantes();
    void removeConexionesSalientes();

};

template < class V, class E>
int Vertex<V,E>::getConexionesEntrantes() const
{
    return conexionesEntrantes;
}

template < class V, class E>
int Vertex<V,E>::getConexionesSalientes() const
{
    return conexionesSalientes;
}

template <class V, class E>
void Vertex<V,E>::plusConexionesEntrantes()
{
    conexionesEntrantes++;
}

template <class V, class E>
void Vertex<V,E>::plusConexionesSalientes()
{
    conexionesSalientes++;
}

template <class V, class E>
void Vertex<V,E>::removeConexionesEntrantes()
{
    conexionesEntrantes--;
}

template <class V, class E>
void Vertex<V,E>::removeConexionesSalientes()
{
    conexionesSalientes--;
}

template <class V, class E>
Vertex<V,E>::~Vertex()
{
    for (auto e : edges) {
        delete e;
    }

    edges.clear();
}

template <class V, class E>
V Vertex<V,E>::getInfo() const
{
    return info;
}

template <class V, class E>
void Vertex<V,E>::setInfo(const V & value)
{
    info = value;
}

template <class V, class E>
std::vector< Edge<V,E> * > * Vertex<V, E>::getEdges()
{
    return &edges;
}

template <class V, class E>
void Vertex<V,E>::addEdge(Edge<V,E> * edge)
{
    edges.push_back(edge);
}

template <class V, class E>
std::vector< Edge<V,E> * > * Vertex<V, E>::getEdgesEntrantes()
{
    return &edgesEntrantes;
}

template <class V, class E>
void Vertex<V,E>::addEdgeEntrante(Edge<V,E> * edge)
{
    edgesEntrantes.push_back(edge);
}


template <class V, class E>
void Vertex<V,E>::removeEdge(Edge<V,E> * edge)
{
    auto to_delete = find(edges.begin(), edges.end(), edge);
    edges.erase(to_delete);
}

template <class V, class E>
bool Vertex<V,E>::operator ==(const Vertex<V,E> & value)
{
    return info == value.getInfo();
}

template <class V, class E>
std::ostream & operator <<(std::ostream & os, const Vertex<V,E> & vertex)
{
    os << "Vertex: " << vertex.info << std::endl;

    for (auto  e : vertex.edges) {
        os << *e << std::endl;
    }

    return os;
}

#endif /* Vertex_hpp */