#include <linux/init.h>
#include <linux/kern_levels.h>
#include <linux/module.h>
#include <linux/sched.h>

#define DRIVER_AUTHOR "John Gentile <johncgentile17@gmail.com>"
#define DRIVER_DESC   "A hello world kernel module!"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

static int __init hello_init(void)
{
	printk(KERN_ALERT "Hello, world from process \"%s\" (pid %i)\n",
			current->comm,
			current->pid);
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
