#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task_logic.h"

#include <QColor>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadTasks();
    refreshUI();

    connect(ui->btnAdd, &QPushButton::clicked,
            this, &MainWindow::onAddClicked);
    connect(ui->taskNameEdit, &QLineEdit::returnPressed,
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
        QString mark;
        if (tasks[i].done)
        {
            mark = QString(QChar(0x2611)) + " ";
        }
        else
        {
            mark = QString(QChar(0x2610)) + " ";
        }

        QString line = mark + QString::fromStdString(tasks[i].name);

        QListWidgetItem *item = new QListWidgetItem(line);
        if (tasks[i].done)
        {
            item->setForeground(QColor("#15803d"));
        }
        else
        {
            item->setForeground(QColor("#111827"));
        }

        ui->taskList->addItem(item);
    }

    updateStatistics();
}

void MainWindow::updateStatistics()
{
    int doneCount = 0;

    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i].done)
        {
            doneCount++;
        }
    }

    int remainingCount = taskCount - doneCount;

    ui->totalLabel->setText("Total: " + QString::number(taskCount));
    ui->doneLabel->setText("Done: " + QString::number(doneCount));
    ui->remainingLabel->setText("Remaining: " + QString::number(remainingCount));
}

void MainWindow::onAddClicked()
{
    QString name = ui->taskNameEdit->text().trimmed();

    if (name.isEmpty())
    {
        QMessageBox::warning(this, "Todo App",
                             QString::fromUtf8("Vui l\303\262ng nh\341\272\255p t\303\252n c\303\264ng vi\341\273\207c!"));
        ui->taskNameEdit->setFocus();
        return;
    }

    addTask(name.toStdString());
    saveTasks();

    ui->taskNameEdit->clear();
    ui->taskNameEdit->setFocus();
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
