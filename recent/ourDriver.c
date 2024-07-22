#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/uaccess.h>          // Required for the copy to user function
#define  DEVICE_NAME "crypto_AES"    ///< The device will appear at /dev/ebbchar using this value
#define  CLASS_NAME  "AES"        ///< The device class -- this is a character device driver

MODULE_LICENSE("GPL");            ///< The license type -- this affects available functionality
MODULE_AUTHOR("AES-256 Group");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux char driver for an emulated cryptocore");
MODULE_VERSION("0.1"); 

static int    majorNumber;                  ///< Stores the device number -- determined automatically
static struct class*  AEScharClass  = NULL; ///< The device-driver class struct pointer
static struct device* AEScharDevice = NULL; ///< The device-driver device struct pointer

static struct file_ops f_ops = {
	.owner = THIS_MODULE,
	.open = AES_open,
	.read = AES_read,
	.write = AES_write,
	.release = AES_close,
	.unlocked_ioctl = AES_ioctl,
   	.compat_ioctl = AES_ioctl
};

static long int AES_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	/*
	switch (cmd) {
		case BLINK_RATE:
			selected_register = BLINK_RATE;
			break;
		case ENABLE:
			selected_register = ENABLE;
			break;
	}
	*/
	
   	printk(KERN_INFO "AES: Executing IOCTL\n");
	
	return -1;
}

static int  AES_open(struct inode* inodep, struct file * filep) {
	/*
	selected_register = ENABLE;
	WRITE_DATA_TO_THE_HW(0);
	selected_register = BLINK_RATE;
	WRITE_DATA_TO_THE_HW(0);
	*/
	
   	printk(KERN_INFO "AES: Executing OPENRELEASE\n");
	return 0;

}

static int  AES_close(struct inode* inodep, struct file * filep) {
	/*
	selected_register = ENABLE;
	WRITE_DATA_TO_THE_HW(0);
	selected_register = BLINK_RATE;
	WRITE_DATA_TO_THE_HW(0);
	*/
	
   	printk(KERN_INFO "AES: Executing OPENRELEASE\n");
	return 0;

}

static ssize_t AES_read(struct file * filep, char * buffer, size_t len, loff_t * offset) {
	/*int data;
	READ_DATA_FROM_THE_HW (&data);
	copy_to_user(buffer, &data, 4);*/
   	printk(KERN_INFO "AES: Executing READ\n");
	return 4;
}
