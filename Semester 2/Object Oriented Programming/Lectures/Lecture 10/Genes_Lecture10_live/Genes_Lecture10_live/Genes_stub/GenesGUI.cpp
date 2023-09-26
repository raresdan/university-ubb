#include "GenesGUI.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <qlabel.h>

GenesGUI::GenesGUI(const std::vector<Gene>& genes, QWidget* parent):
		QWidget{parent}, genes{genes}
{
	this->initGUI();
	this->populateList();
	this->connectSignalsAndSlots();
}

void GenesGUI::initGUI()
{
	QHBoxLayout* layout = new QHBoxLayout{ this };
	genesList = new QListWidget{};

	layout->addWidget(genesList);

	QVBoxLayout* genesDataLayout = new QVBoxLayout{};

	layout->addLayout(genesDataLayout);

	QFormLayout* geneInfoLayout = new QFormLayout{};
	QLabel* nameLabel = new QLabel{"&Name"};
	nameEdit = new QLineEdit{};
	nameLabel->setBuddy(nameEdit);

	QLabel* organismLabel = new QLabel{ "&Organism" };
	organismEdit = new QLineEdit{};
	organismLabel->setBuddy(organismEdit);

	QLabel* sequenceLabel = new QLabel{ "&Sequence" };
	sequenceEdit = new QLineEdit{};
	sequenceLabel->setBuddy(sequenceEdit);

	geneInfoLayout->addRow(nameLabel, nameEdit);
	geneInfoLayout->addRow(organismLabel, organismEdit);
	geneInfoLayout->addRow(sequenceLabel, sequenceEdit);

	genesDataLayout->addLayout(geneInfoLayout);

	QHBoxLayout* buttonsLayout = new QHBoxLayout{};
	addButton = new QPushButton{"Add"};
	removeButton = new QPushButton{"Remove"};
	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(removeButton);

	genesDataLayout->addLayout(buttonsLayout);
}

void GenesGUI::populateList()
{
	genesList->clear();

	for (Gene g : genes)
		genesList->addItem(QString::fromStdString(g.toString()));

	genesList->setCurrentRow(0);
}

void GenesGUI::connectSignalsAndSlots()
{
	QObject::connect(genesList, &QListWidget::itemSelectionChanged,
					this, &GenesGUI::listItemChanged);

	QObject::connect(addButton, &QPushButton::clicked,
		this, [&]() {
			Gene g{nameEdit->text().toStdString(),
					organismEdit->text().toStdString(),
					sequenceEdit->text().toStdString() };
			genes.push_back(g);
			populateList();
			genesList->setCurrentRow(genes.size() - 1);
		});

	emit mySignal();
}

void GenesGUI::listItemChanged()
{
	int index = getSelectedIndex();
	if (index < 0)
		return;

	Gene g = genes[index];
	nameEdit->setText(QString::fromStdString(g.getName()));
	organismEdit->setText(QString::fromStdString(g.getOrganismName()));
	sequenceEdit->setText(QString::fromStdString(g.getSequence()));
}

int GenesGUI::getSelectedIndex()
{
	int currentRow = genesList->currentRow();

	return currentRow;
}
