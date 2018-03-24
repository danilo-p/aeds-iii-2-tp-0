#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Cell * Cell_create(void *data) {
    Cell *cell = malloc(sizeof(Cell));

    cell->next = NULL;
    cell->data = data;

    return cell;
}

void Cell_destroy(Cell *cell, void (* destructor)(void *)) {
    if(cell->data) { 
        destructor(cell->data);
    }
    free(cell);
}

void Cell_print(Cell *cell, void (* print)(void *)) {
    print(cell->data);
}

List * List_create() {
    List *list = malloc(sizeof(List));

    list->first = NULL;
    list->size = 0;

    return list;
}

void List_destroy(List *list, void (* destructor)(void *)) {
    for (int i = list->size; i > 0; i--) {
        Cell_destroy(List_removeCell(list, i-1), destructor);
    }
    free(list);
}

int List_calculateCellPosition(int position, int size) {
    /**
     * If the position is negative, it will be interpreted that the cell have to
     * be inserted on the x position before the end of the list.
     */
    if (position < 0) {
        position = size + position;
    }

    /**
     * If the given position is greater than the size of the list, it will be
     * reassigned to the end of the list.
     */
    if(size < position) {
        position = size;
    }

    return position;
}

int List_insertCell(List *list, Cell *cell, int position) {
    int counter = 0;
    Cell *previous = NULL, *current = NULL;

    position = List_calculateCellPosition(position, list->size);

    current = list->first;

    /*
     * This loop will search the given position over the list iterating on the
     * cells. Once it arrive to the position, the "current" pointer will be
     * pointing to the cell that is on the given position.
     */
    while (counter < position) {
        previous = current;
        current = current->next;
        counter++;
    }

    /*
     * There are 3 cases to be treated. The first, last or middle position.
     *
     * First position: current will point to the first cell and previous will be
     * NULL. list->first will be set to the new cell and if the list size is
     * greater than 0, the cell->next have to point to the old first cell.
     *
     * Last position: current will be NULL and previous to the last element.
     * previous->next have to be set to cell. As cell->next is NULL by default,
     * nothing will be done.
     *
     * Middle position: current and previous will be pointing to cells on the
     * list. previous->next have to point to cell. cell->next have to point to
     * current.
     */

    /* First position */
    if(previous == NULL) {
        list->first = cell;

        /*
         * If the list is empty, current will be NULL. So assigning it to
         * cell->next will work the same way.
         */
        cell->next = current;
    }
    /* Last position */
    else if(previous != NULL && current == NULL) {
        previous->next = cell;
    }
    /* The list has 2 or more items */
    else {
        previous->next = cell;
        cell->next = current;
    }

    list->size++;

    return position;
}

Cell * List_removeCell(List *list, int position) {
    int counter = 0;
    Cell *previous = NULL, *current = NULL;

    position = List_calculateCellPosition(position, list->size);

    /*
     * If the position is equal to the size, it will be trying to remove a cell
     * that dont exist. With that, we can presume that the cell to be removed is
     * the last.
     */
    if(position == list->size) {
        position = list->size - 1;
    }

    current = list->first;

    /* 
     * This loop will search the given position over the list iterating on the
     * cells. Once it arrive to the position, the "current" pointer will be
     * pointing to the cell that is on the given position.
     */
    while (counter < position) {
        previous = current;
        current = current->next;
        counter++;
    }

    /*
     * There are 3 cases to be treated. The first, last or middle position.
     *
     * First position: current will point to the first cell and previous will be
     * NULL. list->first will be set to the current->next.
     *
     * Last position: The difference of the last position to the insertCell
     * function is that here, if the size of the list is x, you cant remove the
     * cell that is on the position x. On insert funciton, it would be a valid
     * position, because it would sign that the cell have to be the last cell.
     * Here, last position means the x-1 position. In this case, current will
     * be pointing to the last cell of the list. With that, current->next will
     * be NULL. previous->next have to be set to NULL.
     *
     * Middle position: current and previous will be pointing to cells on the
     * list. previous->next have to point to current->next.
     */


    /* First position */
    if(previous == NULL) {
        /*
         * If the list is empty, current will be NULL. If is that the case, the
         * list have no cells to be removed and nothing have to be done.
         */
        if(current != NULL) {
            list->first = current->next;
        }
    }
    /* Last position */
    else if(previous != NULL && current != NULL && current->next == NULL) {
        previous->next = NULL;
    }
    /* The list has 2 or more items */
    else {
        previous->next = current->next;
    }

    /* 
     * If the list is empty, there is no reason to decrease the size, because
     * any cell was removed.
     */
    if(list->size > 0) {
        list->size--;
    }

    return current;
}

void List_print(List *list, void (* print)(void *)) {
    int counter = 0;

    printf("%d Cells\n\n", list->size);

    if(list) {
        Cell *current = list->first;
        while (counter < list->size) {
            printf("Cell %d\n", counter);
            Cell_print(current, print);
            current = current->next;
            counter++;
            printf("\n");
        }
    }
}

Cell * List_searchCell(List *list, int (* check)(void *)) {
    Cell *current = list->first;
    while (current != NULL) {
        if(check(current->data)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}