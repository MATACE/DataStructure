#include "list.h"

/**
 * @brief Insert the new list node to the list end.
 * 
 * @param list The operation list.
 * @param value The list of value.
 * @return true 
 * @return false 
 */
bool list_insert(struct node *list, const int value)
{
    struct node *head = list;

    if (!list) {
        dzlog_error("List is null.");
        return false;
    }

    /* To find the list of end. */
    while (head->next_) {
        head = head->next_;
    }

    /* Inset a node in the list of last. */
    head->next_ = (struct node *)malloc(sizeof(struct node));
    if (!head->next_) {
        dzlog_error("insert list malloc failed");
        return false;
    }
    head = head->next_;
    head->d_val_.value = value;
    head->next_ = NULL;

    return true;
}

/**
 * @brief Iter show the list of value.
 * 
 * @param list The operation list.
 * @return true 
 * @return false 
 */
bool list_iterate(struct node *list)
{  
    struct node *head = list;

    if (!list) {
        dzlog_error("List is null.");
        return false;
    }

    while (head) {
        dzlog_info("List data: %d", head->d_val_.value);
        head = head->next_;
    }

    return true;
}