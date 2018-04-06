#include <stdio.h>
#include <stdlib.h>
#include "lib/list.h"
#include "lib/graph.h"

typedef struct {
    int id;
    int age;
    int listened;
} Person;

/**
 * @brief Creates a new person with the given id and age
 * 
 * Complexity: O(1).
 * 
 * @param id The person id.
 * @param age The person age
 * @return Person* A pointer to the new person.
 */
Person * Person_create(int id, int age) {
    Person *person = (Person *) malloc(sizeof(Person));

    person->id = id;
    person->age = age;
    person->listened = 0;

    return person;
}

/**
 * @brief Destroys the given person. It simply free the allocated memory to 
 * store the data.
 * 
 * Complexity: O(1).
 * 
 * @param person The person to be destroyed.
 */
void Person_destroy(void *person) {
    free(person);
}

/**
 * @brief Search the person's vertex given the person id.
 * 
 * It performs a linear search on the graph vertices list.
 * 
 * V: the graph vertices number
 * Complexity: O(V).
 * 
 * @param graph The graph.
 * @param id The person's id.
 * @return Vertex* The person's vertex.
 */
Vertex * Graph_searchPersonVertexById(Graph *graph, int id) {
    Vertex **vertices = Graph_getVertices(graph);
    for (int i = 0; i < Graph_getVerticesNumber(graph); i += 1) {
        Vertex *vertex = vertices[i];
        Person *person = (Person *) Vertex_getData(vertex);
        if (person->id == id) {
            return vertex;
        }
    }
    return NULL;
}

/**
 * @brief Spread the music hit given the first person's vertex.
 * 
 * It uses the Deep First Search strategy to recursivelly navigate on the graph,
 * marking the people who liked the music and spreading to it's familly.
 * 
 * V: The graph's vertices number (or "graph->verticesNumber")
 * E: The graph's edges number (program input "m")
 * Complexity: O(V*E²). We consult only once each vertex and we have V vertices.
 * For each vertex, we have to dive into each related vertex, which the amount
 * of it is E. Retrieving an edge costs O(E) on the worst case (the edge is on
 * the last position of the list).
 * 
 * @param vertex The person's first vertex who first listened the music.
 */
void Person_spreadMusic(Vertex *vertex, int* counter) {
    Person *person = (Person *) Vertex_getData(vertex);
    person->listened = 1;

    if (person->age < 35) {
        *counter += 1;

        List *edges = Vertex_getEdges(vertex);
        for (int i = 0; i < List_getSize(edges); i += 1) {
            Vertex *relatedVertex = (Vertex *) List_getItem(edges, i);
            Person *related = (Person *) Vertex_getData(relatedVertex);
            if (related->listened == 0) {
                Person_spreadMusic(relatedVertex, counter);
            }
        }
    }
}

/**
 * @brief Destroy all allocated memory for storing people data
 * 
 * V: the graph's vertices number.
 * Complexity: O(V).
 * 
 * @param graph The graph
 */
void Graph_destroyPeople(Graph *graph) {
    Vertex **vertices = Graph_getVertices(graph);
    for (int i = 0; i < Graph_getVerticesNumber(graph); i += 1) {
        Vertex *vertex = vertices[i];
        Person *person = (Person *) Vertex_getData(vertex);
        Person_destroy(person);
    }
}


/**
 * @brief Main funcition.
 * 
 * It will create and destroy the graph, the vertices and the edges given the
 * user entries, and it will calculate how many people liked the music hit after
 * the spread.
 * 
 * @return int Program's exit status code.
 */
int main() {
    int n, m, i;
    scanf("%d %d", &n, &m);

    Graph *graph = Graph_create(n);

    for (i = 0; i < n; i += 1) {
        int id, age;
        scanf("%d %d", &id, &age);
        Graph_insertVertex(graph, Vertex_create(Person_create(id, age)), i);
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

    int firstId, counter = 0;
    scanf("%d", &firstId);

    Person_spreadMusic(Graph_searchPersonVertexById(graph, firstId), &counter);

    printf("%d\n", counter);

    Graph_destroyPeople(graph);
    Graph_destroy(graph);

    return 0;
}