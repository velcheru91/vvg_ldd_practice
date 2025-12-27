#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VVG");
MODULE_DESCRIPTION("Basic write & read loadable kernel module");

#define MAX_BUFF_LEN 80
static struct proc_dir_entry *this_proc_node;

static char ldd_msg_buff[MAX_BUFF_LEN];
static size_t buff_len = 0;

static ssize_t ldd_proc_write(struct file *file_ptr,
                              const char *usr_buffer,
                              size_t count, 
                              loff_t *offset)
{
	size_t in_len = (count > MAX_BUFF_LEN -1) ? MAX_BUFF_LEN -1 : count;

	if(copy_from_user(ldd_msg_buff, usr_buffer, in_len))
		return -EFAULT;

	ldd_msg_buff[in_len] = '\0';
	buff_len = in_len;
	return buff_len;
}

static ssize_t	ldd_proc_read(struct file *file_ptr,
                              char *usr_buffer,
                              size_t count,
                              loff_t *offset)
{
	size_t len = buff_len;

	if(*offset >= len)
		return 0;
	if(copy_to_user(usr_buffer, ldd_msg_buff, len))
		return -EFAULT;
	*offset += len;
	return len;
}

struct proc_ops driver_proc_ops = {
	.proc_read = ldd_proc_read,
	.proc_write = ldd_proc_write,
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
