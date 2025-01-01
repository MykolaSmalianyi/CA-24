#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>
#include <linux/ktime.h>

struct event_list {
    struct list_head list;
    ktime_t event_time;
};

void print_hello(void);
void cleanup_events(void);

#endif // HELLO1_H
