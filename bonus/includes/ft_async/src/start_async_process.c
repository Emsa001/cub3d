#include "../includes/ft_async.h"
#include "../../cub3d.h"

static void run_async_loop(t_async *current)
{
    while (1)
    {
        if (current->stopped || (current->time_elapsed >= current->time && current->time != -1))
            break;

        usleep(current->process_time * 1000);

        if (current->process)
            current->process(current);
        
        if(current->time != -1)
            current->time_elapsed += current->process_time;
    }
}


void start_async_process(t_async *async) {
    pid_t pid = fork();
    if(pid == 0) { // Child process
        if (async->process)
            async->process(async);

        exit(0);  // Child process exits
    } else if (pid > 0) { // Parent process
        if (async->start)
            async->start(async);


        if (async->end)
            async->end(async);

        // Optional: Wait for the child process (blocking) if needed
        // waitpid(pid, NULL, 0);
    }
}