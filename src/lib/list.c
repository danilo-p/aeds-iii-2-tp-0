#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * @brief Cell structure
 *
 * Structure for a cell. This is used to implement the linked list.
 */
struct cell {
    /** Next cell on the list */
    struct cell *next;
    /** Previous cell on the list */
    struct cell *previous;
    /** Stored data */
    void *data;
};
typedef struct cell Cell;

/**
 * @brief Create a new Cell
 *
 * This function will create a new cell. The next and previous item will be set
 * to NULL and the stored data will be set to the specified data.
 *
 * Complexity: O(1)
 *
 * @param[in] data  Pointer to the data
 *
 * @return Returns a pointer to a new empty Cell.
 */
static Cell * Cell_create(void *data) {
    Cell *cell = malloc(sizeof(Cell));

    cell->next = NULL;
    cell->previous = NULL;
    cell->data = data;

    return cell;
}

/**
 * @brief Destroy a Cell
 *
 * This function destroys the given cell. Pass the appropriated
 * destructor for destroying the stored data.
 *
 * Complexity: O(1).
 *
 * @param cell The cell
 * @param[in] destructor  The destructor for the cell data
 */
static void Cell_destroy(Cell *cell) {
    free(cell);
}

/**
 * @brief List structure
 *
 * This will be the structure of the list.
 */
struct list {
    /** Pointer to the first item on the list. */
    Cell *first;
    /** Pointer to the last item on the list. */
    Cell *last;
    /** Used to store the current size of the list. */
    int size;
};


/**
 * @brief Create a List
 *
 * This function create a empty list. The first and last item and size is set
 * to NULL and 0, respectively.
 *
 * Complexity: O(1)
 *
 * @return Returns the pointer to the created list
 */
List * List_create() {
    List *list = malloc(sizeof(List));

    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

/**
 * @brief Destroy the given list
 * 
 * Destroy all cells and free the space of the list. Pass the
 * appropriated destructor for the cells data.
 *
 * n: the list size
 * Complexity: O(n²). The loop will execute the List_remove "n" times,
 * that is O(n).
 *
 * @param list The list
 * @param[in] destructor  The destructor for the cells data
 */
void List_destroy(List *list) {
    free(list);
}

/**
 * @brief Get the size of a list.
 *
 * Complexity: O(1).
 *
 * @param list The list.
 * @return Returns the size of the given list.
 */
int List_getSize(List *list) {
    return list->size;
}

/**
 * @brief Calculates the position.
 * 
 * It normalizes the given position according to the given size, allowing the
 * position to be negative and greater than the size.
 * 
 * * Complexity: O(1).
 * 
 * @param position The desired position.
 * @param size The size of the list.
 * @return int The positive position.
 */
static int List_calculatePosition(int position, int size) {
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
    if (size < position) {
        position = size;
    }

    return position;
}

/**
 * @brief Gets the cell of a list on the given position
 * 
 * n: the cell position
 * Complexity: O(n).
 * 
 * @param list The list
 * @param position The cell position
 * @return Cell* A pointer to the cell. NULL if not found.
 */
static Cell * List_getCell(List *list, int position) {
    Cell *current = NULL;
    int counter;
    position = List_calculatePosition(position, list->size);

    /*
     * If the position is more closer to the end, find the position from
     * backwards. The next step will search the given position over the list
     * iterating on the cells. Once it arrive to the position, the "current"
     * pointer will be pointing to the cell that is on the given position.
     */
    if (position > list->size / 2) {
        counter = list->size - 1;
        current = list->last;
        while (counter > position) {
            current = current->previous;
            counter--;
        }
    } else {
        counter = 0;
        current = list->first;
        while (counter < position) {
            current = current->next;
            counter++;
        }
    }

    return current;
}

/**
 * @brief Insert an item with the given data
 *
 * This function will insert a cell in a determined position of the given list,
 * containing the given data.
 *
 * n: the cell position
 * Complexity: O(n)
 *
 * @param list List to insert the given item
 * @param data The data of the item
 * @param[in] position Position that the item will be inserted. It can be
 * positive or negative. Negative numbers will be interpreted as positions at
 * the end of the list.
 *
 * @return The position (positive) that the item was inserted
 */
int List_insertItem(List *list, void *data, int position) {
    Cell *cell = Cell_create(data);
    Cell *current = List_getCell(list, position);

    /*
     * Check if the list is empty.
     */
    if (current == NULL) {
        list->first = cell;
        list->last = cell;
        list->size += 1;
        return 0;
    }

    /* The cell have to be inserted on the first position */
    if (list->first == current && position == 0) {
        list->first = cell;
        cell->next = current;
        current->previous = cell;
    }
    /* The cell have to be inserted on the last position */
    else if (list->last == current && position == -1) {
        list->last = cell;
        cell->previous = current;
        current->next = cell;
    }
    /* The cell have to be inserted on the middle of 2 others cells */
    else {
        /* If the specified position is negative, the cell have to be inserted
         * after the current cell. This way, the cell index keeps being
         * negative.
         */
        if (position < 0) {
            current->next->previous = cell;
            cell->next = current->next;
            cell->previous = current;
            current->next = cell;
        } else {
            current->previous->next = cell;
            cell->previous = current->previous;
            cell->next = current;
            current->previous = cell;
        }
    }

    list->size++;

    return position;
}

/**
 * @brief Removes a item from the given list.
 *
 * This function will remove a cell in a determined position of the
 * given list.
 *
 * n: the item position.
 * Complexity: O(n).
 *
 * @param list The list.
 * @param[in] position The position of the item to be removed. It can be
 * positive or negative. Negative numbers will be interpreted as positions at
 * the end of the list.
 *
 * @return The data of the removed item.
 */
void * List_removeItem(List *list, int position) {
    void *data;

    /*
     * Check if the list is empty.
     */
    if (list->first == NULL && list->last == NULL) {
        return NULL;
    }
    /*
     * Check if the list has just one element
     */
    else if (list->first == list->last) {
        data = list->first->data;
        Cell_destroy(list->first);
        list->first = NULL;
        list->last = NULL;
        list->size = 0;
        return data;
    }

    Cell *current = List_getCell(list, position);

    /* The cell have to be removed from the first position */
    if (list->first == current && position == 0) {
        list->first = current->next;
        list->first->previous = NULL;
    }
    /* The cell have to be removed from the last position */
    else if (list->last == current && position == -1) {
        list->last = current->previous;
        list->last->next = NULL;
    }
    /* The cell have to be removed from the middle of 2 others cells */
    else {
        current->previous->next = current->next;
        current->next->previous = current->previous;
    }

    list->size -= 1;

    data = current->data;
    Cell_destroy(current);

    return data;
}

/**
 * @brief Get the item on the given position
 * 
 * n: the item position
 * Complexity: O(n).
 * 
 * @param list The list
 * @param position The position of the item
 * @return void* The data on the item. NULL if not found.
 */
void * List_getItem(List *list, int position) {
    Cell *cell = List_getCell(list, position);
    if (cell == NULL) {
        return NULL;
    }
    return cell->data;
}
