#include "base.h"

int def_start(void **avgs)
{
    dzlog_info("This is def_start");
}

int def_stop(void **avgs)
{
    dzlog_info("This is def_stop");
}

int def_run(void **avgs)
{
    dzlog_info("This is def_run");
}

struct opt def_opt = {
    .stop = def_stop,
    .run = def_run,
    .start = def_start,
};

void base_init(struct base* c_base, struct opt* c_opt)
{
    memset(c_base, 0, sizeof(struct base));

    // Set the default function.
    c_base->def_opt_ = c_opt;
    if (!c_base->def_opt_->run) {
        c_opt->run = def_run;
    }

    if (!c_base->def_opt_->start) {
        c_opt->start = def_start;
    }

    if (!c_base->def_opt_->stop) {
        c_opt->stop = def_stop;
    }

    return;
}

void base_regest(struct base* c_base)
{
    // struct child_op *op = to_child(c_base);
    // op->test();
}