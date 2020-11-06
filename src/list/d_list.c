#include "d_list.h"

bool d_list_insert(struct d_node *list, const int val)
{
    struct d_node *head = list;
    struct d_node *pre = NULL;

    if (!list) {
        dzlog_error("double list is null");
        return false;
    }

    while (head->next_) {
        head = head->next_;
    }

    pre = head;
    head->next_ = (struct d_node *)malloc(sizeof(struct d_node));
    if (!head->next_) {
        dzlog_error("double list insert malloc failed");
        return false;
    }
    
    head = head->next_;
    head->pre_ = pre;
    head->val_.value = val;
    head->next_ = NULL;
    
    return true;

}

bool d_list_iterate(struct d_node *list)
{
    struct d_node *head = list;

    if (!list) {
        dzlog_error("list is null");
        return false;
    }  

    while (head) {
        dzlog_info("Data Value: %d", head->val_.value);
        head = head->next_;
    }

    return true;

}