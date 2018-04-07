#include <stdio.h>
#include <stdlib.h>
#include "lib/list.h"
#include "lib/graph.h"
#include "lib/person.h"

/**
 * @brief Main funcition.
 * 
 * It will create and destroy the graph, the vertices and the edges given the
 * user entries, and it will calculate how many people liked the music hit after
 * the spread.
 * 
 * Final complexity: O(E*log(V)), being V = "n" and E = "m". The most expensive
 * part is the edges input processing, because of the search that have to be
 * done to find the two persons on the graph vertices.
 * 
 * @return int Program's exit status code.
 */
int main() {
    int n, m, i;
    scanf("%d %d", &n, &m);

    Graph *graph = Graph_create(n);

    // Complexity for create all vertices is O(V), being V = "n".
    for (i = 0; i < n; i += 1) {
        char *id = (char *) malloc(sizeof(char) * MAX_ID_LENGTH);
        int age;
        scanf("%s %d", id, &age);
        Graph_insertVertex(graph, Vertex_create(Person_create(id, age)), i);
    }

    Graph_sortVerticesByPersonId(graph);

    char *id1 = (char *) malloc(sizeof(char) * MAX_ID_LENGTH);
    char *id2 = (char *) malloc(sizeof(char) * MAX_ID_LENGTH);
    // Complexity for set all edges is O(E*log(V)), being V = "n",and E = "m".
    for (i = 0; i < m; i += 1) {
        scanf("%s %s", id1, id2);
        Vertex_setEdge(
            Graph_searchPersonVertexById(graph, id1),
            Graph_searchPersonVertexById(graph, id2),
            0
        );
    }

    char *first_id = (char *) malloc(sizeof(char) * MAX_ID_LENGTH);
    int counter = 0;
    scanf("%s", first_id);
    Person_spreadMusic(Graph_searchPersonVertexById(graph, first_id), &counter);
    printf("%d\n", counter);

    free(id1);
    free(id2);
    free(first_id);
    Graph_destroyPeople(graph);
    Graph_destroy(graph);

    return 0;
}