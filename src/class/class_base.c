#include "class_base.h"

int test_start(void **avgs)
{
    dzlog_info("This is test start");
}

int test_stop(void **avgs)
{
    dzlog_info("This is test stop");
}

int test_run(void **avgs)
{
    dzlog_info("This is test run");
}

void test()
{
    struct opt test_op = {
        .run = test_run,
        .stop = test_stop,
    };

    struct base my_base;
    base_init(&my_base, &test_op);

    void **args = NULL;

    my_base.def_opt_->run(args);
    my_base.def_opt_->start(args);
    my_base.def_opt_->stop(args);

    return;
}