#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ModelView_stub.h"

class ModelView_stub : public QMainWindow
{
    Q_OBJECT

public:
    ModelView_stub(QWidget *parent = nullptr);
    ~ModelView_stub();

private:
    Ui::ModelView_stubClass ui;
};
