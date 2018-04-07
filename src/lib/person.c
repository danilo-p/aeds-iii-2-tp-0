#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"
#include "graph.h"
#include "list.h"

/**
 * @brief Person structure.
 */
struct person {
    /** The person id */
    char *id;
    /** The person age */
    int age;
    /** Flag indicating if the person listened to the music. */
    int listened;
};

/**
 * @brief Creates a new person with the given id and age
 * 
 * Complexity: O(1).
 * 
 * @param id The person id.
 * @param age The person age
 * @return Person* A pointer to the new person.
 */
Person * Person_create(char *id, int age) {
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
    free(((Person *) person)->id);
    free(person);
}

/**
 * @brief Recursivelly searches the vertex with the desired person using the
 * binary search approach.
 * 
 * n: The length of the vertices array
 * Complexity: O(log(n))
 * 
 * @param vertices The vertices array.
 * @param length The vertices array length.
 * @param id The person id.
 * @return Vertex* The vertex found
 */
static Vertex * Graph_binarySearchPersonVertexById(
    Vertex **vertices,
    int length,
    char *id
) {
    if (length == 0) {
        return NULL;
    }

    int middle = length / 2;
    Person *middle_person = (Person *) Vertex_getData(vertices[middle]);
    char *middle_person_id = middle_person->id;

    if (strcmp(id, middle_person_id) == 0) {
        return vertices[middle];
    }

    if (strcmp(id, middle_person_id) > 0) {
        // Right side of the array
        return Graph_binarySearchPersonVertexById(vertices + middle,
            length - middle, id);
    }

    // Left side of the array
    return Graph_binarySearchPersonVertexById(vertices, length - middle, id);
}

/**
 * @brief Search the person's vertex given the person id.
 * 
 * n: The length of the vertices array
 * Complexity: O(log(n))
 * 
 * @param graph The graph.
 * @param id The person's id.
 * @return Vertex* The person's vertex.
 */
Vertex * Graph_searchPersonVertexById(Graph *graph, char *id) {
    return Graph_binarySearchPersonVertexById(Graph_getVertices(graph),
        Graph_getVerticesNumber(graph), id);
}

/**
 * @brief Spread the music hit given the first person's vertex.
 * 
 * It uses the Deep First Search strategy to recursively navigate on the graph,
 * marking the people who liked the music and spreading to it's family.
 * 
 * V: The graph's vertices number (program input "n")
 * E: The graph's edges number (program input "m")
 * Complexity: O(V+E).
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
        Vertex_destroy(vertex);
    }
}

/**
 * @brief Recursivelly sort an array of vertices based on the person id that
 * each one has stored.
 * 
 * n: vertices length
 * Complexity: O(n*log(n))
 * 
 * @param vertices The vertices array
 * @param length The length of the vertices array
 */
static void Graph_quickSortVerticesByPersonId (Vertex **vertices, int length) {
    if (length > 1) {
        int i, j;
        char *first = ((Person *) Vertex_getData(vertices[0]))->id;
        char *last = ((Person *) Vertex_getData(vertices[length - 1]))->id;
        char *middle = ((Person *) Vertex_getData(vertices[length / 2]))->id;
        char *pivot = (strcmp(first, last) > 0) ?
                    (strcmp(middle, first) > 0 ? first : middle):
                    (strcmp(middle, last) > 0 ? last : middle);

        for (i = 0, j = length - 1;; i++, j--) {
            Person *person_i = person_i = (Person *) Vertex_getData(vertices[i]);
            Person *person_j = person_j = (Person *) Vertex_getData(vertices[j]);

            while (strcmp(person_i->id, pivot) < 0) {
                i++;
                person_i = (Person *) Vertex_getData(vertices[i]);
            }

            while (strcmp(person_j->id, pivot) > 0) {
                j--;
                person_j = (Person *) Vertex_getData(vertices[j]);
            }

            if (i >= j) break;

            Vertex_setData(vertices[i], person_j);
            Vertex_setData(vertices[j], person_i);
        }

        Graph_quickSortVerticesByPersonId(vertices, i);
        Graph_quickSortVerticesByPersonId(vertices + i, length - i);
    }
}

/**
 * @brief Sort the vertices array based on the people id
 * 
 * n: vertices length
 * Complexity: O(n*log(n))
 * 
 * @param vertices The vertices array
 * @param length The length of the vertices array
 */
void Graph_sortVerticesByPersonId(Graph *graph) {
    Graph_quickSortVerticesByPersonId(Graph_getVertices(graph),
        Graph_getVerticesNumber(graph));
}