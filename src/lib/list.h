#ifndef LIST_H
#define LIST_H

/**
 * @brief Cell structure
 *
 * Structure for a cell. This is used to implement the linked list.
 */
typedef struct cell {
    /** Next cell on the list */
    struct cell *next;
    /** Stored data */
    void *data;
} Cell;

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
Cell * Cell_create(void *data);

/**
 * @brief Destroy a Cell
 *
 * This function destroys the given cell. Pass the appropriated
 * destructor for destroying the stored data.
 *
 * Complexity: O(1)
 *
 * @param cell The cell
 * @param[in] destructor  The destructor for the cell data
 */
void Cell_destroy(Cell *cell, void (* destructor)(void *));

/**
 * @brief Print a cell
 *
 * Complexity: O(1)
 *
 * @param cell The cell
 * @param[in] print  The function for printing the cell data
 */
void Cell_print(Cell *cell, void (* print)(void *));

/**
 * @brief List structure
 *
 * This will be the structure of the list.
 */
typedef struct list {
    /** Pointer to the first item on the list. */
    Cell *first;
    /** Pointer to the last item on the list. */
    Cell *last;
    /** Used to store the current size of the list. */
    int size;
} List;

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
List * List_create();

/**
 * @brief Destroy the given list
 * 
 * Destroy all cells and free the space of the list. Pass the
 * appropriated destructor for the cells data.
 *
 * n: the list size
 * Complexity: O(n²). The loop will execute the List_removeCell "n" times,
 * that is O(n).
 *
 * @param list The list
 * @param[in] destructor  The destructor for the cells data
 */
void List_destroy(List *list, void (* destructor)(void *));

/**
 * @brief Insert a Cell on the given List
 *
 * This function will insert a cell in a determined position of the given list.
 *
 * n: the cell position
 * Complexity: O(n)
 *
 * @param list List to insert the given cell
 * @param cell The cell
 * @param[in] position Position that the cell will be inserted. It can be
 * positive or negative. Negative numbers will be interpreted as positions at
 * the end of the list.
 *
 * @return The position (positive) that the cell was inserted
 */
int List_insertCell(List *list, Cell *cell, int position);

/**
 * @brief Removes a Cell from the given List
 *
 * This function will remove a cell in a determined position of the
 * given list.
 *
 * n: the cell position
 * Complexity: O(n)
 *
 * @param list The list
 * @param[in] position The position of the cell to be removed. It can be
 * positive or negative. Negative numbers will be interpreted as positions at
 * the end of the list.
 *
 * @return The removed cell
 */
Cell * List_removeCell(List *list, int position);

/**
 * @brief Print a List
 *
 * This function will print the content of a list. It prints the
 * position and the data of each cell.
 *
 * n: the list size
 * Complexity: O(n).
 *
 * @param[in] list Pointer to the list
 * @param[in] print The function for printing the cell data
 */
void List_print(List *list, void (* print)(void *));

/**
 * @brief Search for a cell
 * 
 * n: the position of the cell. In the worst case, the cell was not found, and n
 * becomes the size of the list.
 * Complexity: O(n).
 * 
 * This function will try to find a cell that pass on the given check function.
 * If no cell was found, NULL is returned.
 */
Cell * List_searchCell(List *list, int (* check)(void *));

#endif
