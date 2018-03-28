#include <stdlib.h>
#include "graph.h"
#include "list.h"

struct vertex {
    void *data;
    List *edges;
};

struct graph {
    List *vertices;
};

Vertex * Vertex_create(void *data) {
    Vertex *vertex = (Vertex *) malloc(sizeof(Vertex));
    vertex->data = data;
    vertex->edges = List_create();
    return vertex;
}

void * Vertex_getData(Vertex *vertex) {
    return vertex->data;
}

List * Vertex_getEdges(Vertex *vertex) {
    return vertex->edges;
}

void Vertex_destroy(Vertex *vertex) {
    List *edges = Vertex_getEdges(vertex);
    while (List_getSize(edges) > 0) {
        List_removeItem(edges, -1);
    }
    List_destroy(edges);
    free(vertex);
}

void Vertex_setEdge(Vertex *vertex1, Vertex *vertex2, int oriented) {
    List_insertItem(Vertex_getEdges(vertex1), vertex2, -1);

    if (!oriented) {
        List_insertItem(Vertex_getEdges(vertex2), vertex1, -1);
    }
}

Graph * Graph_create() {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->vertices = List_create();
    return graph;
}

List * Graph_getVertices(Graph *graph) {
    return graph->vertices;
}

void Graph_destroy(Graph *graph) {
    List *vertices = Graph_getVertices(graph);
    while (List_getSize(vertices) > 0) {
        Vertex *vertex = (Vertex *) List_removeItem(vertices, -1);
        Vertex_destroy(vertex);
    }
    List_destroy(vertices);
    free(graph);
}

void Graph_insertVertex(Graph *graph, Vertex *vertex) {
    List_insertItem(Graph_getVertices(graph), vertex, -1);
}
