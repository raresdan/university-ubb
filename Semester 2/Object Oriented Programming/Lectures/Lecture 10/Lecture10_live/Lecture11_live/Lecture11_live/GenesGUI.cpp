#include "GenesGUI.h"

GenesGUI::GenesGUI(const std::vector<Gene>& genes, QWidget *parent)
	: QWidget(parent), genes{genes}
{
	ui.setupUi(this);
	this->populateList();
	QObject::connect(ui.addButton, &QPushButton::clicked,
		this, [&]() {
			//
		});

	QObject::connect(ui.variantsEdit, &QLineEdit::textChanged,
		this, &GenesGUI::onVariantsEdit);
}

GenesGUI::~GenesGUI()
{}

void GenesGUI::populateList()
{
	ui.genesList->clear();

	for (Gene& g : this->genes)
		ui.genesList->addItem(QString::fromStdString(g.toString()));

	ui.genesList->setCurrentRow(0);
}

void GenesGUI::onVariantsEdit()
{
	QVBoxLayout* vLayout = new QVBoxLayout{};
	ui.variantsWidget->setLayout(vLayout);

	vLayout->addWidget(new QLabel{ "Variant1" });
	vLayout->addWidget(new QLabel{ "Variant2" });
	vLayout->addWidget(new QLabel{ "Variant3" });
}
