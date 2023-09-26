#pragma once

#include <QWidget>
#include "ui_GenesGUI.h"
#include "Gene.h"
#include <vector>

class GenesGUI : public QWidget
{
	Q_OBJECT

public:
	GenesGUI(const std::vector<Gene>& genes, QWidget *parent = nullptr);
	~GenesGUI();

private:
	std::vector<Gene> genes;
	Ui::GenesGUIClass ui;

	void populateList();
	void onVariantsEdit();
};
