#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include "hello1.h"

static LIST_HEAD(event_list_head);

void print_hello(void) {
    struct event_list *element = kmalloc(sizeof(*element), GFP_KERNEL);
    if (!element) {
        pr_err("Memory allocation failed\n");
        return;
    }
    element->event_time = ktime_get();
    pr_info("Hello, World!\n");
    list_add_tail(&element->list, &event_list_head);
}

void cleanup_events(void) {
    struct event_list *entry, *tmp;
    list_for_each_entry_safe(entry, tmp, &event_list_head, list) {
        pr_info("Event time: %lld\n", entry->event_time);
        list_del(&entry->list);
        kfree(entry);
    }
}

EXPORT_SYMBOL(print_hello);
EXPORT_SYMBOL(cleanup_events);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Smalianyi Mykola");
MODULE_DESCRIPTION("Lab 5");
