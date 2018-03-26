#include <stdio.h>
#include <stdlib.h>
#include "lib/graph.h"

typedef struct {
    int id;
    int age;
    int listened;
    int liked;
} Person;

Person * Person_create(int id, int age) {
    printf("Person_create %d %d\n", id, age);
    Person *person = (Person *) malloc(sizeof(Person));
    person->id = id;
    person->age = age;
    person->listened = 0;
    person->liked = 0;
    return person;
}

void Person_destroy(void *person) {
    printf("Person_destroy %d\n", ((Person *) person)->id);
    free(person);
}

Vertex * Graph_searchVertexByPersonId(Graph *graph, int id) {
    printf("Graph_searchVertexByPersonId %d\n", id);
    Cell *current = graph->vertices->first;
    while (current != NULL) {
        Vertex *currentVertex = ((Vertex *) current->data);
        Person *person = (Person *) currentVertex->data;
        printf("Graph_searchVertexByPersonId Trying with person %d...\n", person->id);
        if (person->id == id) {
            printf("Graph_searchVertexByPersonId found!\n");
            return currentVertex;
        }
        current = current->next;
    }
    printf("Graph_searchVertexByPersonId NOT found!\n");
    return NULL;
}

void MusicHit_spread(Vertex *vertex) {
    Person *person = (Person *) vertex->data;
    person->listened = 1;

    printf("MusicHit_spread %d\n", person->id);

    if (person->age < 35) {
        printf("MusicHit_spread person liked!\n");
        person->liked = 1;

        Cell *currentEdge = vertex->edges->first;
        while (currentEdge != NULL) {
            Vertex *relatedVertex = (Vertex *) currentEdge->data;
            Person *related = (Person *) relatedVertex->data;
            printf("MusicHit_spread %d spreading to related person %d!\n", person->id, related->id);
            if (related->listened == 0) {
                MusicHit_spread(relatedVertex);
            }

            currentEdge = currentEdge->next;
        }
    }
}

int MusicHit_countLiked(Graph *graph) {
    int countLiked = 0;
    Cell *current = graph->vertices->first;
    while (current != NULL) {
        Vertex *currentVertex = ((Vertex *) current->data);
        Person *person = (Person *) currentVertex->data;
        if (person->liked) {
            countLiked += 1;
        }
        current = current->next;
    }
    return countLiked;
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

        Vertex *vertex1 = Graph_searchVertexByPersonId(graph, id1);
        Vertex *vertex2 = Graph_searchVertexByPersonId(graph, id2);

        Vertex_setEdge(vertex1, vertex2);
        Vertex_setEdge(vertex2, vertex1);
    }

    int firstPersonId;
    scanf("%d", &firstPersonId);

    MusicHit_spread(Graph_searchVertexByPersonId(graph, firstPersonId));

    printf("%d\n", MusicHit_countLiked(graph));

    Graph_destroy(graph, Person_destroy);

    return 0;
}