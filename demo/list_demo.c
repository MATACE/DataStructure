#include "list.h"
#include "d_list.h"

int main(int argc, char const *argv[])
{
    // struct node list;
    // list.next_ = NULL;
    // list.d_val_.value = 3;

    struct d_node d_list;
    d_list.val_.value = 3;
    d_list.next_ = NULL;
    d_list.pre_ = NULL;

    /* Init the zlog. */
    dlog_init();
    
    // list_insert(&list, 15);

    // list_iterate(&list);

    d_list_insert(&d_list, 14);
    
    d_list_iterate(&d_list);

    return 0;
}
