

/*
 * uPR24drv - uPR24drv legacy prototype
 */

#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

/* Device major umber */
static int major;

/*
 * Methods
 */

static ssize_t uPR24drv_read(struct file *filp,
			   char __user *buf, size_t count, loff_t *ppos)
{
	pr_info("return EOF\n");

	return 0;
}

static ssize_t uPR24drv_write(struct file *filp,
			    const char __user *buf, size_t count, loff_t *ppos)
{
	pr_info("got %ld bytes\n", count);

	*ppos += count;	
	return count;
}

static int uPR24drv_open(struct inode *inode, struct file *filp)
{
	pr_info("uPR24drv opened\n");

	return 0;
}

static int uPR24drv_release(struct inode *inode, struct file *filp)
{
	pr_info("uPR24drv released\n");

	return 0;
}

static struct file_operations uPR24drv_fops = {
	.owner		= THIS_MODULE,
	.read		= uPR24drv_read,
	.write		= uPR24drv_write,
	.open		= uPR24drv_open,
	.release	= uPR24drv_release
};

/*
 * Module stuff
 */

static int __init uPR24drv_init(void)
{
	int ret;

	ret = register_uPR24drv(0, "uPR24drv", &uPR24drv_fops);
	if (ret < 0) {
		pr_err("unable to register char device! Error %d\n", ret);
		return ret;
	}
	major = ret;
	pr_info("got major %d\n", major);

	return 0;
}

static void __exit uPR24drv_exit(void)
{
	unregister_uPR24drv(major, "uPR24drv");
}

module_init(uPR24drv_init);
module_exit(uPR24drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anton Pavlov");
MODULE_DESCRIPTION("uPR24 radar");