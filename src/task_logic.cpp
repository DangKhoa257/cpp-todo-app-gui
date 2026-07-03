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

void deleteTask(int index)
{
    if (index < 0 || index >= taskCount)
    {
        return;
    }

    // Shift all tasks after "index" one slot to the left
    for (int i = index; i < taskCount - 1; i++)
    {
        tasks[i] = tasks[i + 1];
    }

    taskCount--;
}

void markDone(int index)
{
    if (index < 0 || index >= taskCount)
    {
        return;
    }

    tasks[index].done = true;
}
