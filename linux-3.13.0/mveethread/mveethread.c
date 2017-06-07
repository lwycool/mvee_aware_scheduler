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
    struct slave_thread *slave_pids_list;
    printk(KERN_ALERT "Received data for mvee \n");
    printk(KERN_ALERT "[[%d]] is the master pid and has [[%d]] number of slave threads \n", master_pid, len);
 //   INIT_LIST_HEAD(&slave_pids_list.list);
    slave_pids_list = (struct slave_thread *)kmalloc(sizeof(struct slave_thread), GFP_KERNEL);

    INIT_LIST_HEAD(&(slave_pids_list->list));

    printk(KERN_ALERT "inited slave pids list \n");
    for (i = 0; i < len; i++)
    {
        tmp= (struct slave_thread *)kmalloc(sizeof(struct slave_thread), GFP_KERNEL);
        printk(KERN_ALERT "returned from malloc \n");
        tmp->slave_pid=slave_pids[i];
        printk(KERN_ALERT "assigned slave pid to tmp object \n");
        list_add(&(tmp->list), &(slave_pids_list->list));
        printk(KERN_ALERT "added tmp object to the list \n");
    }

    //update the scheduler datastructure with this data
//    int ret_pid = idr_alloc(&associated_threads, (void *)slave_pids_list,master_pid, (master_pid + 1), GFP_KERNEL);
    //$TODO$ handle -ENOMEM response from ida_simple_get
    struct task_struct* master_ts = find_task_by_vpid(master_pid);
    printk(KERN_ALERT "Fetching task struct related to master_pid [[%d]] \n", master_ts->pid);
    //$TODO save the master_pid and the slave_pids_list which is associated with this master_pid into scheduler

    master_ts->slave_pids_list = slave_pids_list;
    //printk(KERN_ALERT "[[%d]] is find_task_by_vpid pid, and tgid is [[%d]] \n", master_ts->pid, master_ts->tgid);


    printk(KERN_ALERT "Thread ids set. Assigned list. Returning from syscall \n");
    return 0;
}
