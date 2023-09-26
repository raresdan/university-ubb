#include "t3_exercise1.h"

using namespace std;

t3_exercise1::t3_exercise1(Controller& controller, QWidget *parent)
    : QMainWindow(parent), controller{controller}
{
    ui.setupUi(this);
    this->populateList();
}

t3_exercise1::~t3_exercise1()
{}

void t3_exercise1::populateList()
{
    this->ui.tasksListWidget->clear();

    vector<Task> allTasks = this->controller.getAllTasks();
    for (Task& currentTask : allTasks)
    {
        QListWidgetItem* currentItem = new QListWidgetItem(QString::fromStdString(currentTask.toString()));
        if (currentTask.getPriority() == 1)
        {
            QFont font = currentItem->font();
            font.setBold(true);
            currentItem->setFont(font);
        }
        this->ui.tasksListWidget->addItem(currentItem);
    }

}

void t3_exercise1::totalDuration()
{
    int priority = ui.priorityLineEdit->text().toInt();
    int totalDuration = controller.showDuration(priority);
    QString message = "Total duration for priority " + QString::number(priority) + ": " + QString::number(totalDuration);
    QFont font;
    font.setPointSize(12); 
    statusBar()->setFont(font);
    statusBar()->showMessage(message);
}