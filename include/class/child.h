#ifndef CHILD_H
#define CHILD_H

#include <stdio.h>
#include <string.h>

#include "base.h"
#include "s_mber.h"
#include "set_dzlog.h"

#define to_child(x) (container_of((x), struct child_op, c_base))

struct child_op {
    int (*start)(void **avgs);
    int (*stop)(void **avgs);
    int (*run)(void **avgs);
    int (*test)();
    struct base c_base;
    struct opt c_opt;
};

struct child_inf {
    const char name_;
    unsigned int size_;
};

struct child {
    struct child_op* def_op_;
    struct child_inf* def_inf_;
};

static int c_def_start(void **avgs);
static int c_def_stop(void **avgs);
static int c_def_run(void **avgs);
static int c_def_test();

void child_init(struct child *c_child, struct child_op* c_child_op);

#endif // CHILD_H