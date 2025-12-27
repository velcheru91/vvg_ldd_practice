#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VVG");
MODULE_DESCRIPTION("First hello world character driver");

static int sample_module_init(void)
{
	printk("Hello driver world\n");
	return 0;
}

static void sample_module_exit(void)
{
	printk("Exiting driver\n");
}

module_init(sample_module_init);
module_exit(sample_module_exit);
