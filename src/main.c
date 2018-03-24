#include <stdio.h>
#include <stdlib.h>
#include "lib/graph.h"

typedef struct {
    int id;
    int age;
} Person;

void Person_destroy(void *person) {
    free(person);
}

int searchPersonId = 0;
int searchPerson(void *vertex) {
    Person *person = (Person *) ((Vertex *) vertex)->data;
    return person->id == searchPersonId;
}

int main() {
    int n, m, i;
    Graph *graph = Graph_create();
    scanf("%d %d", &n, &m);

    for(i = 0; i < n; i++) {
        int id, age;
        scanf("%d %d", &id, &age);

        Person *person = (Person *) malloc(sizeof(Person));
        person->id = id;
        person->age = age;

        Vertex *vertex = Vertex_create(person);
        Graph_insertVertex(graph, vertex);
    }

    for(i = 0; i < m; i++) {
        int id1, id2;
        scanf("%d %d", &id1, &id2);

        searchPersonId = id1;
        Vertex *vertex1 = Graph_searchVertex(graph, searchPerson);

        searchPersonId = id2;
        Vertex *vertex2 = Graph_searchVertex(graph, searchPerson);

        Vertex_setEdge(vertex1, vertex2);

        Vertex_setEdge(vertex2, vertex1);
    }

    Graph_destroy(graph, Person_destroy);

    return 0;
}