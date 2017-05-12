#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/list.h>

/*-----------------------------------------------------------------------------
    struct for associated mvee thread ids which will be used by the scheduler
-----------------------------------------------------------------------------*/
struct slave_thread {
    struct list_head list;
    pid_t slave_pid;
};

asmlinkage long sys_mveethread(pid_t master_pid, void* slave_pids, size_t size, int len) {
    //@joe - master_pid here is the thread/task id of the master thread and list of slave_pids will contain one or more related slave thread/task ids
    printk("Received data for mvee \n");
    struct slave_thread *tmp;
    struct slave_thread slave_pids_list;
    INIT_LIST_HEAD(&slave_pids_list.list);
    for (int i = 0; i < len; i++)
    {
        void* ptr = (slave_pids + (i*size));
        pid_t thispid = *(pid_t*)ptr;
        &tmp->slave_pid=thispid;
        list_add(&(tmp->list), &(slave_pids_list.list));
    }
    //$TODO save the master_pid and the slave_pids_list which is associated with this master_pid into scheduler
    return 0;
}