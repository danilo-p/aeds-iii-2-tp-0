#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex Vertex;

typedef struct graph Graph;

Vertex * Vertex_create(void *data);

void * Vertex_getData(Vertex *vertex);

List * Vertex_getEdges(Vertex *vertex);

void Vertex_destroy(Vertex *vertex);

void Vertex_setEdge(Vertex *vertex1, Vertex *vertex2, int oriented);

Graph * Graph_create();

List * Graph_getVertices(Graph *graph);

void Graph_destroy(Graph *graph);

void Graph_insertVertex(Graph *graph, Vertex *vertex);

#endif
