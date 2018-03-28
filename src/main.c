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
    person->liked = 0;
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
 * n: the graph vertices number
 * Complexity: O(n²).
 * 
 * @param graph The graph.
 * @param id The person's id.
 * @return Vertex* The person's vertex.
 */
Vertex * DinamicGraph_searchPersonVertexById(DinamicGraph *graph, int id) {
    List *vertices = DinamicGraph_getVertices(graph);
    for (int i = 0; i < List_getSize(DinamicGraph_getVertices(graph)); i += 1) {
        Vertex *vertex = (Vertex *) List_getItem(vertices, i);
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
 * n: The graph's vertices number
 * Complexity: O(n³). Given that the DFS strategy has a complexity of O(n²),
 * this function uses an O(n) function for retrieving the connected vertices.
 * 
 * @param vertex The person's first vertex who first listened the music.
 */
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

/**
 * @brief Counts how many people liked the music hit.
 * 
 * n: the graph's vertices amount.
 * Complexity: O(n²).
 * 
 * @param graph The graph
 * @return int How many people liked the music.
 */
int DinamicGraph_countLiked(DinamicGraph *graph) {
    int countLiked = 0;
    List *vertices = DinamicGraph_getVertices(graph);
    for (int i = 0; i < List_getSize(DinamicGraph_getVertices(graph)); i += 1) {
        Vertex *vertex = (Vertex *) List_getItem(vertices, i);
        Person *person = (Person *) Vertex_getData(vertex);
        if (person->liked) {
            countLiked += 1;
        }
    }
    return countLiked;
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

    DinamicGraph *graph = DinamicGraph_create();

    for (i = 0; i < n; i += 1) {
        int id, age;
        scanf("%d %d", &id, &age);
        DinamicGraph_insertVertex(graph, Vertex_create(Person_create(id, age)));
    }

    for (i = 0; i < m; i += 1) {
        int id1, id2;
        scanf("%d %d", &id1, &id2);
        Vertex_setEdge(
            DinamicGraph_searchPersonVertexById(graph, id1),
            DinamicGraph_searchPersonVertexById(graph, id2),
            0
        );
    }

    int firstId;
    scanf("%d", &firstId);

    Person_spreadMusic(DinamicGraph_searchPersonVertexById(graph, firstId));

    printf("%d\n", DinamicGraph_countLiked(graph));

    List *vertices = DinamicGraph_getVertices(graph);
    while (List_getSize(vertices) > 0) {
        Vertex *vertex = (Vertex *) List_removeItem(vertices, -1);
        Person *person = (Person *) Vertex_getData(vertex);
        Person_destroy(person);
        Vertex_destroy(vertex);
    }

    DinamicGraph_destroy(graph);

    return 0;
}