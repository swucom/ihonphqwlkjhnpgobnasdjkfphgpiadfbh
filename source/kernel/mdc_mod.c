#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/sched.h>


MODULE_LICENSE("GPL");

static int major = 0; 
static int minor = 0; 
const int count = 3; 
#define DEVNAME "mdc" 
static struct cdev *mdcp = NULL; 


/*****************************************************************************
     Author : zhangqijun
       Time : 2018/03/10
 Student ID : SA16225432
Description : 打开设备
      Input : void
     Output : 0
Modify list :
----------------------------------------------------------------------------
Date    Author  Description

*****************************************************************************/
static int mdc_open(struct inode *inode, struct file *filp) 
{ 
    //get command and pid 
    printk(KERN_INFO "(%s:pid=%d), %s : %s : %d\n", current->comm, current->pid, __FILE__, __func__, __LINE__); 
    //get major and minor from inode 
    printk(KERN_INFO "(major=%d, minor=%d), %s : %s : %d\n", imajor(inode), iminor(inode), __FILE__, __func__, __LINE__); 
    return 0; 
} 

/*****************************************************************************
     Author : zhangqijun
       Time : 2018/03/10
 Student ID : SA16225432
Description : 关闭设备 
      Input : void
     Output : 0
Modify list :
----------------------------------------------------------------------------
Date    Author  Description

*****************************************************************************/
static int mdc_release(struct inode *inode, struct file *filp) 
{ 
    //get command and pid 
    printk(KERN_INFO "(%s:pid=%d), %s : %s : %d\n", current->comm, current->pid, __FILE__, __func__, __LINE__); 
    //get major and minor from inode 
    printk(KERN_INFO "(major=%d, minor=%d), %s : %s : %d\n", imajor(inode), iminor(inode), __FILE__, __func__, __LINE__); 
    return 0; 
} 

/*****************************************************************************
     Author : zhangqijun
       Time : 2018/03/10
 Student ID : SA16225432
Description : 读设备
      Input : void
     Output : 0
Modify list :
----------------------------------------------------------------------------
Date    Author  Description

*****************************************************************************/
static ssize_t mdc_read(struct file *filp, char __user *buf, size_t size, loff_t *offset) 
{
    struct inode *inode = filp->f_path.dentry->d_inode; 
    //get command and pid 
    printk(KERN_INFO "(%s:pid=%d), %s : %s : %d\n", current->comm, current->pid, __FILE__, __func__, __LINE__); 
    //get major and minor from inode 
    printk(KERN_INFO "(major=%d, minor=%d), %s : %s : %d\n", imajor(inode), iminor(inode), __FILE__, __func__, __LINE__); 
    return 0; 
} 

/*****************************************************************************
     Author : zhangqijun
       Time : 2018/03/10
 Student ID : SA16225432
Description : 写设备 
      Input : void
     Output : 0
Modify list :
----------------------------------------------------------------------------
Date    Author  Description

*****************************************************************************/
static ssize_t mdc_write(struct file *filp, const char __user *buf, size_t size, loff_t *offset) 
{ 
    struct inode *inode = filp->f_path.dentry->d_inode; 
    //get command and pid 
    printk(KERN_INFO "(%s:pid=%d), %s : %s : %d\n", current->comm, current->pid, __FILE__, __func__, __LINE__); 
    //get major and minor from inode 
    printk(KERN_INFO "(major=%d, minor=%d), %s : %s : %d\n", imajor(inode), iminor(inode), __FILE__, __func__, __LINE__); 
    return 0; 
} 

//操作方法集 
static struct file_operations fops = {
    .owner = THIS_MODULE, .open = mdc_open, 
    .release= mdc_release, 
    .read = mdc_read, 
    .write = mdc_write, 
}; 

/*****************************************************************************
     Author : zhangqijun
       Time : 2018/03/11
 Student ID : SA16225432
Description : cdev设备模块初始化 
      Input : void
     Output : 0
Modify list :
----------------------------------------------------------------------------
Date    Author  Description

*****************************************************************************/
static int __init mdc_init(void) 
{ 
    dev_t devnum; int ret; 
    //get command and pid 
    printk(KERN_INFO "(%s:pid=%d), %s : %s : %d\n", current->comm, current->pid, __FILE__, __func__, __LINE__); 
    //1. alloc cdev obj 
    mdcp = cdev_alloc(); 
    if(NULL == mdcp) { 
        return -ENOMEM; 
    }
    //2. init cdev obj
    cdev_init(mdcp, &fops);
    ret = alloc_chrdev_region(&devnum, minor, count, DEVNAME);
    if(ret){
        goto ERR_STEP;
    }
    major = MAJOR(devnum);
    //3. register cdev obj
    ret = cdev_add(mdcp, devnum, count);
    if(ret){
        goto ERR_STEP1;
    }
    //get command and pid
    printk(KERN_INFO "(%s:pid=%d), %s : %s : %d - ok.\n", current->comm, current->pid, __FILE__, __func__, __LINE__);
    return 0;

ERR_STEP1:
    unregister_chrdev_region(devnum, count);

ERR_STEP:
    cdev_del(mdcp);
    //get command and pid
    printk(KERN_INFO "(%s:pid=%d), %s : %s : %d - fail.\n", current->comm, current->pid, __FILE__, __func__, __LINE__);
    return ret;
}

/*****************************************************************************
     Author : zhangqijun
       Time : 2018/03/11
 Student ID : SA16225432
Description : 
      Input : void
     Output : 0
Modify list :
----------------------------------------------------------------------------
Date    Author  Description

*****************************************************************************/
static void __exit mdc_exit(void)
{
    //get command and pid
    printk(KERN_INFO "(%s:pid=%d), %s : %s : %d - leave.\n", current->comm, current->pid, __FILE__, __func__, __LINE__);
    unregister_chrdev_region(MKDEV(major, minor), count);
    cdev_del(mdcp);
}

module_init(mdc_init);
module_exit(mdc_exit);



