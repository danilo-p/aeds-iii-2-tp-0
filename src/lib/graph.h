#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

void emptyDestructor();

typedef struct {
    void *data;
    List *edges;
} Vertex;

typedef struct {
    List *vertices;
} Graph;

Vertex * Vertex_create(void *data);

void Vertex_setEdge(Vertex *vertex1, Vertex *vertex2);

void Vertex_destroy(Vertex *vertex, void (* destructor)(void *));

Graph * Graph_create();

void Graph_destroy(Graph *graph, void (* destructor)(void *));

void Graph_insertVertex(Graph *graph, Vertex *vertex);

Vertex * Graph_searchVertex(Graph *graph, int (* check)(void *));

#endif
