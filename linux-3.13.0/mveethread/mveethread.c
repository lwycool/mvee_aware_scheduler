#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/sched.h>

/*-----------------------------------------------------------------------------
    struct for associated mvee thread ids which will be used by the scheduler
-----------------------------------------------------------------------------*/


asmlinkage long sys_mveethread(pid_t master_pid, pid_t* slave_pids, int len) {
    //@joe - master_pid here is the thread/task id of the master thread and list of slave_pids will contain one or more related slave thread/task ids
    int i;
    struct slave_thread *tmp;
    struct slave_thread slave_pids_list;
    printk(KERN_ALERT "Received data for mvee \n");
    printk(KERN_ALERT "[[%d]] is the master pid and has [[%d]] number of slave threads", master_pid, len);
    INIT_LIST_HEAD(&slave_pids_list.list);
    printk(KERN_ALERT "inited slave pids list");
    for (i = 0; i < len; i++)
    {
        tmp= (struct slave_thread *)kmalloc(sizeof(struct slave_thread), GFP_KERNEL);
        printk(KERN_ALERT "returned from malloc");
        tmp->slave_pid=slave_pids[i];
        printk(KERN_ALERT "assigned slave pid to tmp object");
        list_add(&(tmp->list), &(slave_pids_list.list));
        printk(KERN_ALERT "added tmp object to the list");
    }

    //update the scheduler datastructure with this data
//    int ret_pid = idr_alloc(&associated_threads, (void *)slave_pids_list,master_pid, (master_pid + 1), GFP_KERNEL);
    //$TODO$ handle -ENOMEM response from ida_simple_get
    printk(KERN_ALERT "[[%d]] is the map key returned by pid of the current task", current_thread_info()->task->pid);
    //$TODO save the master_pid and the slave_pids_list which is associated with this master_pid into scheduler
    current_thread_info()->task->slave_pids_list = &slave_pids_list;
    printk(KERN_ALERT "[[%d]] current_thread_info pid, tgid [[%d]] ",current_thread_info()->task->pid, current_thread_info()->task->tgid);

    printk(KERN_ALERT "The loop has finished. Returning from syscall");
    return 0;
}