#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>


MODULE_AUTHOR("Smalianyi Mykola IO-21");
MODULE_DESCRIPTION("Lab 4");
MODULE_LICENSE("Dual BSD/GPL");


static unsigned int N = 1; //Default meaning
module_param(N, uint, S_IRUGO);
MODULE_PARM_DESC(N, "How many times to print Hello, World");


struct event_list {
	struct list_head list;
	ktime_t event_time;
};

static struct list_head event_list_head;
static LIST_HEAD(event_list_head);
void new_event(void);
	static int __init hello_init(void) {
		if (N == 0 || (N >= 5 && N <= 10)) {
			printk(KERN_WARNING "Warning! The parameter is between 5 and 10");
			}
		if (N > 10) {
			printk(KERN_ERR "Error! The parameter is greater than 10");
			return -EINVAL;
		}
		int i;
		for (i = 0; i < N; i++) {
			printk(KERN_EMERG "Hello, World!\n");
			new_event();
		}
	return 0;
}
static void __exit hello_exit(void) {
	struct event_list *md, *tmp;
	list_for_each_entry_safe(md, tmp, &event_list_head, list) {
		printk(KERN_EMERG "Time: %lld\n", md->event_time);
		list_del(&md->list);
		kfree(md);
	}
}
void new_event(void) {
	struct event_list *element = NULL;
	element = kmalloc(sizeof(struct event_list), GFP_KERNEL);
	element->event_time = ktime_get();
	list_add_tail(&element->list, &event_list_head);
}
module_init(hello_init);
module_exit(hello_exit);