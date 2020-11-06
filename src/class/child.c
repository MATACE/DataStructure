#include "child.h"

int c_def_start(void **avgs)
{
    dzlog_info("The default child start.");
}

int c_def_stop(void **avgs)
{
    dzlog_info("This default child stop.");
}

int c_def_run(void **avgs)
{
    dzlog_info("This default child run.");
}

int c_def_test()
{
    dzlog_info("The default child test.");
}

void child_init(struct child *c_child, struct child_op* c_child_op)
{
    memset(c_child, 0, sizeof(*c_child));
    c_child->def_op_ = c_child_op;

    if (!c_child->def_op_->run) {
        c_child_op->run = c_def_run;
    }

    if (!c_child->def_op_->start) {
        c_child_op->start = c_def_start;
    }

    if (!c_child->def_op_->stop) {
        c_child_op->stop = c_def_stop;
    }

    if (!c_child->def_op_->test) {
        c_child_op->test = c_def_test;
    }

    c_child->def_op_->c_opt.run = c_child_op->run;
    c_child->def_op_->c_opt.start = c_child_op->start;
    c_child->def_op_->c_opt.stop = c_child_op->stop;

    base_init(&c_child->def_op_->c_base, &c_child->def_op_->c_opt);
    base_regest(&c_child->def_op_->c_base);

    return;
}