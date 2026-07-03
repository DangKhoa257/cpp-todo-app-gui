#include "task_logic.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

std::vector<Task> tasks;

namespace
{
const char* TASK_FILE = "task.txt";

int getNextId()
{
    int maxId = 0;

    for (const Task& task : tasks)
    {
        if (task.id > maxId)
        {
            maxId = task.id;
        }
    }

    return maxId + 1;
}

std::string toLower(std::string text)
{
    for (char& ch : text)
    {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    return text;
}
}

void loadTasks()
{
    tasks.clear();

    std::ifstream file(TASK_FILE);
    if (!file.is_open())
    {
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idText;
        std::string title;
        std::string description;
        std::string completedText;

        if (std::getline(ss, idText, '|') &&
            std::getline(ss, title, '|') &&
            std::getline(ss, description, '|') &&
            std::getline(ss, completedText))
        {
            Task task;
            task.id = std::stoi(idText);
            task.title = title;
            task.description = description;
            task.completed = (completedText == "1");

            tasks.push_back(task);
        }
    }
}

void saveTasks()
{
    std::ofstream file(TASK_FILE);

    for (const Task& task : tasks)
    {
        file << task.id << '|'
             << task.title << '|'
             << task.description << '|'
             << (task.completed ? "1" : "0") << '\n';
    }
}

void addTask(const std::string& title,
             const std::string& description,
             bool completed)
{
    Task task;
    task.id = getNextId();
    task.title = title;
    task.description = description;
    task.completed = completed;

    tasks.push_back(task);
    saveTasks();
}

bool deleteTask(int id)
{
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [id](const Task& task)
                           {
                               return task.id == id;
                           });

    if (it == tasks.end())
    {
        return false;
    }

    tasks.erase(it);
    saveTasks();
    return true;
}

bool editTask(int id,
              const std::string& title,
              const std::string& description,
              bool completed)
{
    for (Task& task : tasks)
    {
        if (task.id == id)
        {
            task.title = title;
            task.description = description;
            task.completed = completed;
            saveTasks();
            return true;
        }
    }

    return false;
}

std::vector<Task> searchTask(const std::string& keyword)
{
    std::vector<Task> results;
    std::string searchText = toLower(keyword);

    for (const Task& task : tasks)
    {
        std::string title = toLower(task.title);
        std::string description = toLower(task.description);

        if (title.find(searchText) != std::string::npos ||
            description.find(searchText) != std::string::npos)
        {
            results.push_back(task);
        }
    }

    return results;
}
