#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex Vertex;

typedef struct graph Graph;

typedef struct dinamic_graph DinamicGraph;

Vertex * Vertex_create(void *data);

void * Vertex_getData(Vertex *vertex);

List * Vertex_getEdges(Vertex *vertex);

void Vertex_destroy(Vertex *vertex);

void Vertex_setEdge(Vertex *vertex1, Vertex *vertex2, int oriented);

DinamicGraph * DinamicGraph_create();

List * DinamicGraph_getVertices(DinamicGraph *graph);

void DinamicGraph_destroy(DinamicGraph *graph);

void DinamicGraph_insertVertex(DinamicGraph *graph, Vertex *vertex);

#endif
