#include "task_logic.h"

#include <fstream>
#include <sstream>

Task tasks[MAX_TASKS];
int taskCount = 0;

namespace
{
const char* TASK_FILE = "task.txt";
}

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

void saveTasks()
{
    std::ofstream file(TASK_FILE);

    for (int i = 0; i < taskCount; i++)
    {
        file << tasks[i].name << '|'
             << (tasks[i].done ? "1" : "0") << '\n';
    }
}

void loadTasks()
{
    taskCount = 0;

    std::ifstream file(TASK_FILE);
    if (!file.is_open())
    {
        return;
    }

    std::string line;
    while (std::getline(file, line) && taskCount < MAX_TASKS)
    {
        std::stringstream ss(line);
        std::string name;
        std::string doneText;

        if (std::getline(ss, name, '|') && std::getline(ss, doneText))
        {
            tasks[taskCount].name = name;
            tasks[taskCount].done = (doneText == "1");
            taskCount++;
        }
    }
}
