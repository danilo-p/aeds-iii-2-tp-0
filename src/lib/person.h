#include "graph.h"

#ifndef PERSON_H
#define PERSON_H

#define MAX_ID_LENGTH 256

typedef struct person Person;

Person * Person_create(char *id, int age);

void Person_destroy(void *person);

Vertex * Graph_searchPersonVertexById(Graph *graph, char *id);

void Person_spreadMusic(Vertex *vertex, int* counter);

void Graph_destroyPeople(Graph *graph);

void Graph_sortVerticesByPersonId(Graph *graph);

#endif