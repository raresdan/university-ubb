#include "t3_exercise2.h"

t3_exercise2::t3_exercise2(Controller controller, QWidget *parent)
    : QMainWindow(parent), controller{controller}
{
    ui.setupUi(this);
    this->populateList();
}

t3_exercise2::~t3_exercise2()
{}

void t3_exercise2::populateList()
{
    this->ui.itemListWidget->clear();
    for (auto item : this->controller.getAllItems())
    {
        this->ui.itemListWidget->addItem(QString::fromStdString(item.toString()));
    }
}

void t3_exercise2::deleteItem()
{
    QListWidgetItem* selectedItem = this->ui.itemListWidget->currentItem();
    if (selectedItem != nullptr)
    {
        int row = this->ui.itemListWidget->row(selectedItem);
        this->ui.itemListWidget->takeItem(row);
        delete selectedItem;
    }
}

void t3_exercise2::filterItems()
{
    std::string category = this->ui.categoryLineEdit->text().toStdString();
    this->controller.filterItems(category);
    this->ui.itemListWidget->clear();
    for (auto currentItem : this->controller.getAllItems())
    {
        this->ui.itemListWidget->addItem(QString::fromStdString(currentItem.toString()));
    }
}
