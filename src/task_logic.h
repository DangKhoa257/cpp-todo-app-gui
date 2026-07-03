#ifndef TASK_LOGIC_H
#define TASK_LOGIC_H

#include <string>
#include <vector>

struct Task
{
    int id;
    std::string title;
    std::string description;
    bool completed;
};

extern std::vector<Task> tasks;

void loadTasks();
void saveTasks();

void addTask(const std::string& title,
             const std::string& description = "",
             bool completed = false);
bool deleteTask(int id);
bool editTask(int id,
              const std::string& title,
              const std::string& description,
              bool completed);
std::vector<Task> searchTask(const std::string& keyword);

#endif // TASK_LOGIC_H
