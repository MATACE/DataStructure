#include "class_child.h"

int ch_start(void **avgs)
{
    dzlog_info("TXX START.");
}

int ch_stop(void **avgs)
{
    dzlog_info("TXX STOP.");
}

int ch_run(void **avgs)
{
    dzlog_info("TXX RUN.");
}

int ch_test()
{
    dzlog_info("The class child test to.");
}

void child_test()
{
    struct child_op ch_ax = {
        .run = ch_run,
        .test = ch_test,
    };

    struct child test_child;
    child_init(&test_child, &ch_ax);

    void **args = NULL;
    
    test_child.def_op_->run(args);
    test_child.def_op_->start(args);
    test_child.def_op_->stop(args);
    test_child.def_op_->test(args);

    test_child.def_op_->c_base.def_opt_->run(args);
    test_child.def_op_->c_base.def_opt_->start(args);
    test_child.def_op_->c_base.def_opt_->stop(args);

    get_from_base(&test_child.def_op_->c_base);

    return;
}

void get_from_base(struct base* c_base)
{
    struct child_op* test_op = to_child(c_base);
    test_op->test();
}