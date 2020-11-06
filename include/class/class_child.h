#ifndef CLASS_CHILD_H
#define CLASS_CHILD_H

#include <stdio.h>

#include "child.h"
#include "set_dzlog.h"

static int ch_start(void **avgs);
static int ch_stop(void **avgs);
static int ch_run(void **avgs);
static int ch_test();

void child_test();
void get_from_base(struct base* c_base);

#endif // CLASS_CHILD_H