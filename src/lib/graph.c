#include <stdlib.h>
#include "graph.h"
#include "list.h"

void emptyDestructor() {}

Vertex * Vertex_create(void *data) {
    Vertex *vertex = (Vertex *) malloc(sizeof(Vertex));
    vertex->data = data;
    vertex->edges = List_create();
    return vertex;
}

void Vertex_setEdge(Vertex *vertex1, Vertex *vertex2) {
    List_insertCell(vertex1->edges, Cell_create(vertex2), vertex1->edges->size);
}

void Vertex_destroy(Vertex *vertex, void (* destructor)(void *)) {
    destructor(vertex->data);
    List_destroy(vertex->edges, emptyDestructor);
    free(vertex);
}

Graph * Graph_create() {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->vertices = List_create();
    return graph;
}

void Graph_destroy(Graph *graph, void (* destructor)(void *)) {
    for (int i = graph->vertices->size; i > 0; i--) {
        Cell *vertexCell = List_removeCell(graph->vertices, i-1);
        Vertex *vertex = (Vertex *) vertexCell->data;
        Vertex_destroy(vertex, destructor);
        Cell_destroy(vertexCell, emptyDestructor);
    }
    free(graph->vertices);
    free(graph);
}

void Graph_insertVertex(Graph *graph, Vertex *vertex) {
    List_insertCell(graph->vertices, Cell_create(vertex),
        graph->vertices->size);
}

Vertex * Graph_searchVertex(Graph *graph, int (* check)(void *)) {
    Cell *vertexCell = List_searchCell(graph->vertices, check);
    return (Vertex *) vertexCell->data;
}