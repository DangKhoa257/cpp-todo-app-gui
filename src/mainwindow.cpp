#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task_logic.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Version 3: load tasks from task.txt when the app starts
    loadTasks();
    refreshUI();

    connect(ui->btnAdd, &QPushButton::clicked,
            this, &MainWindow::onAddClicked);
    connect(ui->btnDelete, &QPushButton::clicked,
            this, &MainWindow::onDeleteClicked);
    connect(ui->btnComplete, &QPushButton::clicked,
            this, &MainWindow::onCompleteClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshUI()
{
    ui->taskList->clear();

    for (int i = 0; i < taskCount; i++)
    {
        QString mark = tasks[i].done ? "[x] " : "[ ] ";
        QString line = mark + QString::fromStdString(tasks[i].name);
        ui->taskList->addItem(line);
    }
}

void MainWindow::onAddClicked()
{
    QString name = ui->taskNameEdit->text().trimmed();

    if (name.isEmpty())
    {
        return;
    }

    addTask(name.toStdString());
    saveTasks();

    ui->taskNameEdit->clear();
    refreshUI();
}

void MainWindow::onDeleteClicked()
{
    int index = ui->taskList->currentRow();

    if (index < 0)
    {
        QMessageBox::information(this, "Todo App", "Hay chon mot task can xoa.");
        return;
    }

    deleteTask(index);
    saveTasks();
    refreshUI();
}

void MainWindow::onCompleteClicked()
{
    int index = ui->taskList->currentRow();

    if (index < 0)
    {
        QMessageBox::information(this, "Todo App", "Hay chon mot task can hoan thanh.");
        return;
    }

    markDone(index);
    saveTasks();
    refreshUI();
}
