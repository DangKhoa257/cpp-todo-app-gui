#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task_logic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    refreshUI();

    connect(ui->btnAdd, &QPushButton::clicked,
            this, &MainWindow::onAddClicked);
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

    ui->taskNameEdit->clear();
    refreshUI();
}
