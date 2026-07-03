# Todo App - Final

## Project overview

This is a simple university Todo List application built with C++ and Qt Widgets. The project uses a `struct Task`, a fixed array, functions, `fstream`, and `QListWidget`.

Tasks are saved in `task.txt` and loaded again when the application starts.

## Features

- Add a new task
- Delete the selected task
- Mark the selected task as done
- Press Enter to add a task
- Save and load tasks from `task.txt`
- Show total, done, and remaining task statistics
- Simple Qt Widgets interface with `QListWidget`

## Screenshot

Add screenshot here:

![Todo App Final screenshot](docs/final.png)

## Build instructions

Open with Qt Creator:

1. Open `src/CMakeLists.txt`.
2. Select a Qt 6 kit.
3. Click Configure Project.
4. Build and run the application.

Command line build:

```bash
cmake -S src -B build
cmake --build build
```

Release build on Windows:

```bash
cmake -S src -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
windeployqt build/Release/TodoApp.exe
```

## GitHub repository

Add your GitHub repository link here:

```text
https://github.com/your-username/cpp-todo-app-gui
```
