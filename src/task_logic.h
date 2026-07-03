#ifndef TASK_LOGIC_H
#define TASK_LOGIC_H

#include <string>

struct Task
{
    std::string name;
    bool done;
};

const int MAX_TASKS = 100;

extern Task tasks[MAX_TASKS];
extern int taskCount;

void addTask(const std::string& name);
void deleteTask(int index);
void markDone(int index);

#endif // TASK_LOGIC_H
