#include "test3.h"

test3::test3(Controller controller, QWidget *parent)
    : QMainWindow(parent), controller{controller}
{
    ui.setupUi(this);
    this->populateList();
}

test3::~test3()
{}

void test3::populateList()
{
    this->ui.itemsListWidget->clear();
    for(auto currentItem:controller.getAllItems())
    { 
        this->ui.itemsListWidget->addItem(QString::fromStdString(currentItem.toString()));
    }
}

void test3::searchItem()
{
    std::string searchedString = this->ui.nameLineEdit->text().toStdString();
    std::vector<Item> searchedItems = this->controller.searchItem(searchedString);
    this->ui.itemsListWidget->clear();
    for (auto currentItem : searchedItems)
    {
        this->ui.itemsListWidget->addItem(QString::fromStdString(currentItem.toString()));
    }
}

void test3::filterItems()
{
    std::string category = this->ui.categoryLineEdit->text().toStdString();
    std::vector<Item> filteredItems = this->controller.filterByCategory(category);
    this->ui.filteredListWidget->clear();
    for (auto currentItem : filteredItems)
    {
        this->ui.filteredListWidget->addItem(QString::fromStdString(currentItem.toString()));
    }
}
