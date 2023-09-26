#pragma once
#include <qwidget.h>
#include <vector>
#include "Gene.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class GenesGUI :
    public QWidget
{
    Q_OBJECT

private:
    std::vector<Gene> genes;

public:
    GenesGUI(const std::vector<Gene>& genes, QWidget* parent = 0);

    void initGUI();

private:
    QListWidget* genesList;
    QLineEdit* nameEdit;
    QLineEdit* organismEdit;
    QLineEdit* sequenceEdit;
    QPushButton* addButton;
    QPushButton* removeButton;

    void populateList();
    void connectSignalsAndSlots();

    void listItemChanged();
    int getSelectedIndex();

signals:
    void mySignal();
};

