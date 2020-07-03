/*
 * uPR24drv
 * https://tnsense.com
 */

#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

/* Device major number 
 * https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html#majors-and-minors
 */
static int major;

/* Functions */

/* Transfer data from the device into the user space */
static ssize_t uPR24drv_read(struct file *filp,
			   char __user *buf, size_t count, loff_t *ppos)
{
	pr_info("uPR24drv_read call\n");

	return 0;
}

/* Transfer data from the user space into the device */
static ssize_t uPR24drv_write(struct file *filp,
			    const char __user *buf, size_t count, loff_t *ppos)
{
	pr_info("uPR24drv_write call, %ld bytes\n", count);

	*ppos += count;	
	return count;
}

/* https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html#open-and-release */
static int uPR24drv_open(struct inode *inode, struct file *filp)
{
	pr_info("uPR24drv_open call\n");

	return 0;
}

static int uPR24drv_release(struct inode *inode, struct file *filp)
{
	pr_info("uPR24drv_release call\n");

	return 0;
}

/* Allowed system calls */
/* https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html#struct-file-operations */
static struct file_operations uPR24drv_fops = {
	.owner		= THIS_MODULE,
	.read		= uPR24drv_read,
	.write		= uPR24drv_write,
	.open		= uPR24drv_open,
	.release	= uPR24drv_release
};

/* Module */
static int __init uPR24drv_init(void)
{
	int ret;

	ret = register_chrdev(0, "uPR24drv", &uPR24drv_fops);
	if (ret < 0) {
		pr_err("Failure to register a char device! Error code: %d\n", ret);
		return ret;
	}
	major = ret;
	pr_info("Major: %d\n", major);

	return 0;
}

static void __exit uPR24drv_exit(void)
{
	unregister_chrdev(major, "uPR24drv");
}

module_init(uPR24drv_init);
module_exit(uPR24drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anton Pavlov");
MODULE_DESCRIPTION("uPR24 radar");