#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VVG");
MODULE_DESCRIPTION("Basic read loadable kernel module");

static struct proc_dir_entry *this_proc_node;

static ssize_t	ldd_proc_read(struct file *file_ptr,
                      char *user_space_buffer,
                      size_t count,
                      loff_t *offset)
{

	char msg[] = "Ack!\n";
	size_t len = strlen(msg);
	int result;
	printk("ldd1_read\n");
	if(*offset >= len)
		return 0;

	result = copy_to_user(user_space_buffer, msg, len);
	*offset += len;

	return len;
}

struct proc_ops driver_proc_ops = {
	.proc_read = ldd_proc_read
};
static int ldd1_init(void)
{
	printk("ldd1_init: entry\n");
	this_proc_node = proc_create("ldd1_drvr",//const char *name,
				   0, //umode_t mode,
				   NULL,//stuct proc_dir_entry *parent,
				   &driver_proc_ops);//const struct proc_ops *proc_ops);
	if(!this_proc_node){
		return -1;
	}
	printk("ldd1_init: exit\n");
	return 0;
}

static void ldd1_exit(void)
{
	printk("ldd1_exit: entry\n");
	proc_remove(this_proc_node);
	printk("ldd1_exit: exit\n");
}

module_init(ldd1_init);
module_exit(ldd1_exit);
