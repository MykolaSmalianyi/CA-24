#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

static unsigned int N = 1;
module_param(N, uint, S_IRUGO);
MODULE_PARM_DESC(N, "Number of hello calls");

static int __init hello2_init(void) {
    int i;
    if (N == 0 || (N >= 5 && N <= 10)) {
        pr_warn("Parameter N is between 5 and 10\n");
    } else if (N > 10) {
        pr_err("Parameter N exceeds 10\n");
        return -EINVAL;
    }
    for (i = 0; i < N; i++) {
        print_hello();
    }
    return 0;
}


static void __exit hello2_exit(void) {
    cleanup_events();
}

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Smalianyi Mykola");
MODULE_DESCRIPTION("Lab 5");
