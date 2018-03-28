#include <stdio.h>
#include <stdlib.h>
#include "lib/list.h"
#include "lib/graph.h"

typedef struct {
    int id;
    int age;
    int listened;
    int liked;
} Person;

Person * Person_create(int id, int age) {
    Person *person = (Person *) malloc(sizeof(Person));
    person->id = id;
    person->age = age;
    person->listened = 0;
    person->liked = 0;
    return person;
}

void Person_destroy(void *person) {
    free(person);
}

void Person_spreadMusic(Vertex *vertex) {
    Person *person = (Person *) Vertex_getData(vertex);
    person->listened = 1;

    if (person->age < 35) {
        person->liked = 1;

        List *edges = Vertex_getEdges(vertex);
        for (int i = 0; i < List_getSize(edges); i += 1) {
            Vertex *relatedVertex = (Vertex *) List_getItem(edges, i);
            Person *related = (Person *) Vertex_getData(relatedVertex);
            if (related->listened == 0) {
                Person_spreadMusic(relatedVertex);
            }
        }
    }
}

int Graph_countLiked(Graph *graph) {
    int countLiked = 0;
    List *vertices = Graph_getVertices(graph);
    for (int i = 0; i < List_getSize(Graph_getVertices(graph)); i += 1) {
        Vertex *vertex = (Vertex *) List_getItem(vertices, i);
        Person *person = (Person *) Vertex_getData(vertex);
        if (person->liked) {
            countLiked += 1;
        }
    }
    return countLiked;
}

Vertex * Graph_searchPersonVertexById(Graph *graph, int id) {
    List *vertices = Graph_getVertices(graph);
    for (int i = 0; i < List_getSize(Graph_getVertices(graph)); i += 1) {
        Vertex *vertex = (Vertex *) List_getItem(vertices, i);
        Person *person = (Person *) Vertex_getData(vertex);
        if (person->id == id) {
            return vertex;
        }
    }
    return NULL;
}

int main() {
    int n, m, i;
    scanf("%d %d", &n, &m);

    Graph *graph = Graph_create();

    for (i = 0; i < n; i += 1) {
        int id, age;
        scanf("%d %d", &id, &age);
        Graph_insertVertex(graph, Vertex_create(Person_create(id, age)));
    }

    for (i = 0; i < m; i += 1) {
        int id1, id2;
        scanf("%d %d", &id1, &id2);
        Vertex_setEdge(
            Graph_searchPersonVertexById(graph, id1),
            Graph_searchPersonVertexById(graph, id2),
            0
        );
    }

    int firstId;
    scanf("%d", &firstId);

    Person_spreadMusic(Graph_searchPersonVertexById(graph, firstId));

    printf("%d\n", Graph_countLiked(graph));

    List *vertices = Graph_getVertices(graph);
    for (int i = 0; i < List_getSize(vertices); i += 1) {
        Vertex *vertex = (Vertex *) List_getItem(vertices, i);
        Person *person = (Person *) Vertex_getData(vertex);
        Person_destroy(person);
    }

    Graph_destroy(graph);

    return 0;
}