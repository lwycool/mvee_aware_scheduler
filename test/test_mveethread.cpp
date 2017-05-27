//
// Created by Prabhu Rajasekaran on 5/26/17.
//

#include <vector>
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
    pid_t master_pid=1;
    pid_t slave_id1 = 2, slave_id2=3, slave_id3=4;
    std::vector<pid_t> slave_pids;
    slave_pids.push_back(slave_id1);
    slave_pids.push_back(slave_id2);
    slave_pids.push_back(slave_id3);
//        for (int i = 1; i < 4; i++)
//        {
//            slave_pids.push_back(slave_id);
//        }
    long int amma = syscall(318, master_pid, slave_pids.data(), 3);

//         long int amma = syscall(318); // 314 is the number of sys_hello line in `syscall_64.tbl`

    printf("System call sys_hello returned %ld\n", amma);
    return 0;
}