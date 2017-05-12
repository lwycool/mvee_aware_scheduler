#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/list.h>

asmlinkage long sys_mveethread(pid_t master_pid, struct list_head *slave_pids) {
    //@joe - master_pid here is the thread/task id of the master thread and list of slave_pids will contain one or more related slave thread/task ids
    printk("Received data for mvee \n");
    return 0;
}