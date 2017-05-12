//
// Created by Prabhu Rajasekaran on 5/11/17.
//
#include <linux/kernel.h>

asmlinkage long sys_hello(void)
{
    printk("Hello world\n");
    return 0;
}



