#include "task_logic.h"

Task tasks[MAX_TASKS];
int taskCount = 0;

void addTask(const std::string& name)
{
    if (taskCount >= MAX_TASKS)
    {
        return;
    }

    tasks[taskCount].name = name;
    tasks[taskCount].done = false;
    taskCount++;
}
