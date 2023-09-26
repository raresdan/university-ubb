#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Genes_stub.h"

class Genes_stub : public QMainWindow
{
    Q_OBJECT

public:
    Genes_stub(QWidget *parent = nullptr);
    ~Genes_stub();

private:
    Ui::Genes_stubClass ui;
};
