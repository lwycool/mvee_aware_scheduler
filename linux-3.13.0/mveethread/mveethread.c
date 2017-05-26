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
    printk("Received data for mvee \n");
    printk("[[%d]] is the master pid", master_pid);
    INIT_LIST_HEAD(&slave_pids_list.list);
    printk("inited slave pids list");
    for (i = 0; i < len; i++)
    {
        tmp= (struct slave_thread *)kmalloc(sizeof(struct slave_thread), GFP_KERNEL);
        printk("returned from malloc");
        tmp->slave_pid=slave_pids[i];
        printk("assigned slave pid to tmp object");
        list_add(&(tmp->list), &(slave_pids_list.list));
        printk("added tmp object to the list");
    }

    //update the scheduler datastructure with this data
//    int ret_pid = idr_alloc(&associated_threads, (void *)slave_pids_list,master_pid, (master_pid + 1), GFP_KERNEL);
    //$TODO$ handle -ENOMEM response from ida_simple_get
    printk("[[%d]] is the map key returned by pid of the current task", current_thread_info()->task->pid);
    //$TODO save the master_pid and the slave_pids_list which is associated with this master_pid into scheduler
    current_thread_info()->task->slave_pids_list = &slave_pids_list;
    printk("The loop has finished. Returning from syscall");
    return 0;
}