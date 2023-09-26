#include "Gui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QDialog>
#include <QInputDialog>
#include <warning.h>
#include <qmessagebox.h>
#include <iostream>
#include <QGroupBox>


Gui::Gui(AdministratorService initialAdminService, UserService initialUserService, int initialArgumentCount, char** initialArgumentVector)
	: administratorService{ initialAdminService }, userService{ initialUserService }, argumentCount{ initialArgumentCount }, argumentVector{ initialArgumentVector }
{
}

int Gui::startScreen()
{
	QApplication application(argumentCount, argumentVector);

	QWidget window{};
	window.setStyleSheet("background-color: #186A3B; color: white;");
	window.setWindowTitle("C++ Turorials");

	QVBoxLayout* mainLayout = new QVBoxLayout{};
	QHBoxLayout* buttonLayout = new QHBoxLayout{};
	QLabel* titleLabel = new QLabel("C++ Tutorials Application");
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("font-size: 30px; font-weight: bold; margin-bottom: 20px;");

	QPushButton* adminButton = new QPushButton("Administrator Mode");
	QPushButton* userButton = new QPushButton("User Mode");

	adminButton->setStyleSheet("background-color:  darkgreen; color: white;");
	userButton->setStyleSheet("background-color:  darkgreen; color: white;");

	connect(adminButton, &QPushButton::clicked, this, &Gui::printAdminMenu);
	connect(userButton, &QPushButton::clicked, this, &Gui::printUserMenu);

	buttonLayout->addWidget(adminButton);
	buttonLayout->addWidget(userButton);

	mainLayout->addWidget(titleLabel);
	mainLayout->addLayout(buttonLayout);

	window.setLayout(mainLayout);
	window.resize(500, 250);
	window.show();
	return application.exec();
}

int Gui::printAdminMenu()
{
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white; font-size: 20px;");
	QVBoxLayout layout{};
	QListWidget list;
	QLabel title("Admin mode");
	title.setAlignment(Qt::AlignCenter);
	QListWidgetItem* element1 = new QListWidgetItem("1. Add a new tutorial", &list);
	QListWidgetItem* element2 = new QListWidgetItem("2. Delete a tutorial", &list);
	QListWidgetItem* element3 = new QListWidgetItem("3. Update a tutorial", &list);
	QListWidgetItem* element4 = new QListWidgetItem("4. Display all tutorials", &list);
	layout.addWidget(&title);
	layout.addWidget(&list);
	window.setLayout(&layout);
	window.show();
	window.resize(500, 450);
	connect(&list, &QListWidget::itemClicked, this, &Gui::handleAdminMode);
	return popup->exec();
}

int Gui::printUserMenu()
{
	QStringList options;
	options << "HTML" << "CSV";
	bool ok;
	QString selectedOption = QInputDialog::getItem(nullptr, "Save Watchlist", "Choose file format:", options, 0, false, &ok);
	if (!ok)
	{
		return 0;
	}
	this->userService.setWatchlist(selectedOption.toStdString());
	if (this->userService.getWatchlist() == nullptr)
	{
		QMessageBox::critical(nullptr, "Error", "Watchlist is nullptr!");
		return 0;
	}
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white; font-size: 20px;");
	QVBoxLayout layout{};
	QListWidget list;
	QLabel title("User mode");
	title.setAlignment(Qt::AlignCenter);
	QListWidgetItem* element1 = new QListWidgetItem("1. Search tutorials", &list);
	QListWidgetItem* element2 = new QListWidgetItem("2. Remove tutorial from watchlist", &list);
	QListWidgetItem* element3 = new QListWidgetItem("3. Display watchlist", &list);
	QListWidgetItem* element4 = new QListWidgetItem("4. Save watchlist", &list);
	QListWidgetItem* element5 = new QListWidgetItem("5. Open watchlist", &list);
	layout.addWidget(&title);
	layout.addWidget(&list);
	window.setLayout(&layout);
	window.show();
	window.resize(500, 450);
	connect(&list, &QListWidget::itemClicked, this, &Gui::handleUserMode);
	return popup->exec();
}

int Gui::addTutorial()
{
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Add a new tutorial");
	label.setAlignment(Qt::AlignCenter);
	QLabel titleLabel("Title ");
	QLabel presenterLabel("Presenter ");
	QLabel likesLabel("Likes ");
	QLabel durationLabel("Duration ");
	QLabel linkLabel("Link ");

	QLineEdit* titleInput = new QLineEdit();
	titleInput->setObjectName("title");
	titleLabel.setBuddy(titleInput);

	QLineEdit* presenterInput = new QLineEdit();
	presenterInput->setObjectName("presenter");
	presenterLabel.setBuddy(presenterInput);

	QLineEdit* likesInput = new QLineEdit();
	likesInput->setObjectName("likes");
	likesLabel.setBuddy(likesInput);

	QLineEdit* durationInput = new QLineEdit();
	durationInput->setObjectName("duration");
	durationLabel.setBuddy(durationInput);

	QLineEdit* linkInput = new QLineEdit();
	linkInput->setObjectName("link");
	linkLabel.setBuddy(linkInput);

	formLayout->addRow(&label);
	formLayout->addRow(&titleLabel, titleInput);
	formLayout->addRow(&presenterLabel, presenterInput);
	formLayout->addRow(&likesLabel, likesInput);
	formLayout->addRow(&durationLabel, durationInput);
	formLayout->addRow(&linkLabel, linkInput);
	QPushButton addButton("Add");
	formLayout->addRow(&addButton);
	connect(&addButton, &QPushButton::clicked, this, &Gui::on_addAdminButton_clicked);
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int Gui::removeTutorialFromAdmin()
{
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Remove a tutorial");
	label.setAlignment(Qt::AlignCenter);
	QLabel titleLabel("Title ");
	QLabel presenterLabel("Presenter ");

	QLineEdit* titleInput = new QLineEdit();
	titleInput->setObjectName("title");
	titleLabel.setBuddy(titleInput);
	QLineEdit* presenterInput = new QLineEdit();
	presenterInput->setObjectName("presenter");
	presenterLabel.setBuddy(presenterInput);
	formLayout->addRow(&label);
	formLayout->addRow(&titleLabel, titleInput);
	formLayout->addRow(&presenterLabel, presenterInput);

	QPushButton removeBtn("Remove");
	formLayout->addRow(&removeBtn);
	connect(&removeBtn, &QPushButton::clicked, this, &Gui::on_removeAdminButton_clicked);
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int Gui::updateTutorial()
{
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Update a tutorial");
	label.setAlignment(Qt::AlignCenter);

	QLabel oldTitleLabel("Old Title ");
	QLabel oldPresenterLabel("Old Presenter ");
	QLabel newTitleLabel("New Title ");
	QLabel newPresenterLabel("New Presenter ");
	QLabel newLikesLabel("New likes ");
	QLabel newDurationLabel("New duration ");
	QLabel newLinkLabel("New link ");

	QLineEdit* oldTitleInput = new QLineEdit();
	oldTitleInput->setObjectName("oldTitle");
	oldTitleLabel.setBuddy(oldTitleInput);
	QLineEdit* oldPresenterInput = new QLineEdit();
	oldPresenterInput->setObjectName("oldPresenter");
	oldPresenterLabel.setBuddy(oldPresenterInput);

	QLineEdit* newTitleInput = new QLineEdit();
	newTitleInput->setObjectName("newTitle");
	newTitleLabel.setBuddy(newTitleInput);
	QLineEdit* newPresenterInput = new QLineEdit();
	newPresenterInput->setObjectName("newPresenter");
	newPresenterLabel.setBuddy(newPresenterInput);
	QLineEdit* newLikesInput = new QLineEdit();
	newLikesInput->setObjectName("newLikes");
	newLikesLabel.setBuddy(newLikesInput);
	QLineEdit* newDurationInput = new QLineEdit();
	newDurationInput->setObjectName("newDuration");
	newDurationLabel.setBuddy(newDurationInput);
	QLineEdit* newLinkInput = new QLineEdit();
	newLinkInput->setObjectName("newLink");
	newLinkLabel.setBuddy(newLinkInput);

	formLayout->addRow(&label);
	formLayout->addRow(&oldTitleLabel, oldTitleInput);
	formLayout->addRow(&oldPresenterLabel, oldPresenterInput);
	formLayout->addRow(&newTitleLabel, newTitleInput);
	formLayout->addRow(&newPresenterLabel, newPresenterInput);
	formLayout->addRow(&newLikesLabel, newLikesInput);
	formLayout->addRow(&newDurationLabel, newDurationInput);
	formLayout->addRow(&newLinkLabel, newLinkInput);

	QPushButton updateBtn("Update");
	formLayout->addRow(&updateBtn);
	connect(&updateBtn, &QPushButton::clicked, this, &Gui::on_updateAdminButton_clicked);
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int Gui::displayAllTutorials()
{
	QDialog* popup = new QDialog();
	QTableWidget* table = new QTableWidget(popup);
	table->setRowCount(administratorService.getAllTutorials().size());
	table->setColumnCount(5);

	table->setStyleSheet("background-color: #186A3B; color: white; font-size: 15px;");
	QStringList headerLabels;
	headerLabels << "Title" << "Presenter" << "Likes" << "Duration" << "Link";
	table->setHorizontalHeaderLabels(headerLabels);

	int rowIndex = 0;
	for (const auto& currentTutorial : administratorService.getAllTutorials())
	{
		QTableWidgetItem* titleItem = new QTableWidgetItem(currentTutorial.getTitle().c_str());
		QTableWidgetItem* presenterItem = new QTableWidgetItem(currentTutorial.getPresenter().c_str());
		QTableWidgetItem* likesItem = new QTableWidgetItem(QString::number(currentTutorial.getLikes()));
		QTableWidgetItem* durationItem = new QTableWidgetItem(QString::number(currentTutorial.getDuration().minutes) + ":00");
		QTableWidgetItem* linkItem = new QTableWidgetItem(currentTutorial.getLink().c_str());

		table->setItem(rowIndex, 0, titleItem);
		table->setItem(rowIndex, 1, presenterItem);
		table->setItem(rowIndex, 2, likesItem);
		table->setItem(rowIndex, 3, durationItem);
		table->setItem(rowIndex, 4, linkItem);

		rowIndex++;
	}
	QHeaderView* header = table->horizontalHeader();
	header->setStyleSheet("color: #186A3B;");
	QHeaderView* verticalHeader = table->verticalHeader();
	verticalHeader->setStyleSheet("color: #186A3B;");
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);

	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	table->resize(750, 500);
	table->show();
	return popup->exec();
}

int Gui::searchTutorialsByPresenter()
{
	QDialog dialog;
	QVBoxLayout layout(&dialog);
	dialog.setStyleSheet("background-color: #186A3B; color: white;");
	QLabel searchLabel("Search a presenter:");
	QLineEdit presenterLineEdit;
	QPushButton searchButton("Search");
	QGroupBox tutorialGroupBox("Details");
	QVBoxLayout tutorialLayout(&tutorialGroupBox);
	QLabel tutorialLabel;
	QPushButton addButton("Add to Watchlist");
	QPushButton nextButton("Next");
	searchButton.setStyleSheet("background-color:  darkgreen; color: white;");
	addButton.setStyleSheet("background-color:  darkgreen; color: white;");
	nextButton.setStyleSheet("background-color:  darkgreen; color: white;");
	QHBoxLayout searchLayout;
	searchLayout.addWidget(&searchLabel);
	searchLayout.addWidget(&presenterLineEdit);
	searchLayout.addWidget(&searchButton);

	layout.addLayout(&searchLayout);
	layout.addWidget(&tutorialGroupBox);
	layout.addWidget(&addButton);
	layout.addWidget(&nextButton);

	std::vector<Tutorial> searchedTutorials;
	int currentIndex = 0;

	QObject::connect(&searchButton, &QPushButton::clicked, [&]() {
		QString searchedPresenter = presenterLineEdit.text();

		int currentIndex = 0;
		searchedTutorials = this->userService.getTutorialsOfGivenPresenter(
			this->administratorService.getAllTutorials(), searchedPresenter.toStdString());

		if (searchedTutorials.empty()) {
			QMessageBox::warning(&dialog, "Invalid search", "Please enter a valid presenter!");
			return;
		}

		this->detailsOfTutorial(searchedTutorials[currentIndex], tutorialLabel);
		});

	QObject::connect(&addButton, &QPushButton::clicked, [&]() {
		if (currentIndex < searchedTutorials.size()) {
			this->userService.addTutorialToWatchlist(searchedTutorials[currentIndex]);
			currentIndex++;
			if (currentIndex < searchedTutorials.size()) {
				this->detailsOfTutorial(searchedTutorials[currentIndex], tutorialLabel);
			}
			else {
				currentIndex = 0;
			}
		}
		});

	QObject::connect(&nextButton, &QPushButton::clicked, [&]() {
		currentIndex++;

		if (currentIndex < searchedTutorials.size()) {
			this->detailsOfTutorial(searchedTutorials[currentIndex], tutorialLabel);
		}
		else {
			currentIndex = 0;
		}
		});
	tutorialLayout.addWidget(&tutorialLabel);
	dialog.resize(600, 400);
	return dialog.exec();
}

void Gui::detailsOfTutorial(const Tutorial& tutorial, QLabel& tutorialLabel)
{
	Duration currentDuration = tutorial.getDuration();
	QString title = QString::fromStdString(tutorial.getTitle());
	QString presenter = QString::fromStdString(tutorial.getPresenter());
	QString minutes = QString::number(currentDuration.minutes);
	QString seconds = QString::number(currentDuration.seconds);
	QString likes = QString::number(tutorial.getLikes());
	QString link = QString::fromStdString(tutorial.getLink());

	QString message = QString("<b>Title:</b> %1<br>"
		"<b>Presenter:</b> %2<br>"
		"<b>Duration:</b> %3:%4<br>"
		"<b>Likes:</b> %5<br>"
		"<b>Link:</b> %6<br>")
		.arg(title)
		.arg(presenter)
		.arg(minutes, seconds)
		.arg(likes)
		.arg(link);

	tutorialLabel.setText(message);
	tutorialLabel.setAlignment(Qt::AlignTop);
	tutorialLabel.setWordWrap(true);
	tutorialLabel.setOpenExternalLinks(true);
	tutorialLabel.setTextInteractionFlags(Qt::TextBrowserInteraction);
	tutorialLabel.setStyleSheet(" color: white; font-size: 20pt;");
}


int Gui::removeTutorialFromWatchlist()
{
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Remove a tutorial");
	label.setAlignment(Qt::AlignCenter);
	QLabel titleLabel("Title ");
	QLabel presenterLabel("Presenter ");

	QLineEdit* titleInput = new QLineEdit();
	titleInput->setObjectName("title");
	titleLabel.setBuddy(titleInput);
	QLineEdit* presenterInput = new QLineEdit();
	presenterInput->setObjectName("presenter");
	presenterLabel.setBuddy(presenterInput);
	formLayout->addRow(&label);
	formLayout->addRow(&titleLabel, titleInput);
	formLayout->addRow(&presenterLabel, presenterInput);

	QPushButton removeBtn("Remove");
	formLayout->addRow(&removeBtn);
	connect(&removeBtn, &QPushButton::clicked, this, [&]() {
		std::string title = sender()->parent()->findChild<QLineEdit*>("title")->text().toStdString();
		std::string presenter = sender()->parent()->findChild<QLineEdit*>("presenter")->text().toStdString();
		try
		{
			userService.removeTutorialFromWatchlist(title, presenter);
			std::cout << "Successful remove\n";

		}
		catch (const std::exception& e)
		{
			displayError(e.what());
			QWidget* parentW = qobject_cast<QWidget*>(sender()->parent());
			parentW->close();
		}
		QWidget* parentW = qobject_cast<QWidget*>(sender()->parent()->parent());
		parentW->close();
		});
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int Gui::displayWatchlist()
{
	QDialog* popup = new QDialog();
	QTableWidget* table = new QTableWidget(popup);
	table->setRowCount(userService.getWatchlist()->getAllTutorials().size());
	table->setColumnCount(5);

	table->setStyleSheet("background-color: #186A3B; color: white; font-size: 15px;");
	QStringList headerLabels;
	headerLabels << "Title" << "Presenter" << "Likes" << "Duration" << "Link";
	table->setHorizontalHeaderLabels(headerLabels);

	int rowIndex = 0;
	for (const auto& currentTutorial : userService.getWatchlist()->getAllTutorials())
	{
		QTableWidgetItem* titleItem = new QTableWidgetItem(currentTutorial.getTitle().c_str());
		QTableWidgetItem* presenterItem = new QTableWidgetItem(currentTutorial.getPresenter().c_str());
		QTableWidgetItem* likesItem = new QTableWidgetItem(QString::number(currentTutorial.getLikes()));
		QTableWidgetItem* durationItem = new QTableWidgetItem(QString::number(currentTutorial.getDuration().minutes) + ":00");
		QTableWidgetItem* linkItem = new QTableWidgetItem(currentTutorial.getLink().c_str());

		table->setItem(rowIndex, 0, titleItem);
		table->setItem(rowIndex, 1, presenterItem);
		table->setItem(rowIndex, 2, likesItem);
		table->setItem(rowIndex, 3, durationItem);
		table->setItem(rowIndex, 4, linkItem);

		rowIndex++;
	}
	QHeaderView* header = table->horizontalHeader();
	header->setStyleSheet("color: #186A3B;");
	QHeaderView* verticalHeader = table->verticalHeader();
	verticalHeader->setStyleSheet("color: #186A3B;");
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);


	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	table->resize(750, 500);
	table->show();
	return popup->exec();
}

int Gui::saveWatchlistToFile()
{
	this->userService.saveWatchlist();
	QMessageBox validationMessage;
	validationMessage.setStyleSheet("background-color: #186A3B; color: white;");
	validationMessage.setText("Watchlist saved successfully!");
	return validationMessage.exec();
}

int Gui::openWatchlist()
{
	this->userService.openWatchlist();
	return 0;
}

void Gui::displayError(const char* message)
{
	if (strcmp(message, "invalid stoi argument") == 0)
		message = "Invalid input";
	QDialog* popup = new QDialog();
	QLabel label(message, popup);
	popup->setStyleSheet("background-color: #186A3B; color: white;");
	label.setAlignment(Qt::AlignCenter);
	label.setFont(QFont("Courier", 15, 10));
	label.resize(300, 200);
	label.show();
	popup->exec();
}

void Gui::on_addAdminButton_clicked()
{
	std::string title = sender()->parent()->findChild<QLineEdit*>("title")->text().toStdString();
	std::string presenter = sender()->parent()->findChild<QLineEdit*>("presenter")->text().toStdString();
	std::string likes = sender()->parent()->findChild<QLineEdit*>("likes")->text().toStdString();
	std::string duration = sender()->parent()->findChild<QLineEdit*>("duration")->text().toStdString();
	std::string link = sender()->parent()->findChild<QLineEdit*>("link")->text().toStdString();

	try
	{
		administratorService.addTutorial(title, presenter, { stoi(duration), 0 }, stoi(likes), link);
		std::cout << "Successful add\n";

	}
	catch (const std::exception& e)
	{
		displayError(e.what());
		QWidget* parentWindow = qobject_cast<QWidget*>(sender()->parent());
		parentWindow->close();
	}
	QWidget* parentWindow = qobject_cast<QWidget*>(sender()->parent()->parent());
	parentWindow->close();
}

void Gui::on_removeAdminButton_clicked()
{
	std::string title = sender()->parent()->findChild<QLineEdit*>("title")->text().toStdString();
	std::string presenter = sender()->parent()->findChild<QLineEdit*>("presenter")->text().toStdString();
	try
	{
		administratorService.removeTutorial(title, presenter);
		std::cout << "Successful remove\n";

	}
	catch (const std::exception& e)
	{
		displayError(e.what());
		QWidget* parentW = qobject_cast<QWidget*>(sender()->parent());
		parentW->close();
	}
	QWidget* parentW = qobject_cast<QWidget*>(sender()->parent()->parent());
	parentW->close();
}

void Gui::on_updateAdminButton_clicked()
{
	std::string oldTitle = sender()->parent()->findChild<QLineEdit*>("oldTitle")->text().toStdString();
	std::string oldPresenter = sender()->parent()->findChild<QLineEdit*>("oldPresenter")->text().toStdString();
	std::string newTitle = sender()->parent()->findChild<QLineEdit*>("newTitle")->text().toStdString();
	std::string newPresenter = sender()->parent()->findChild<QLineEdit*>("newPresenter")->text().toStdString();
	std::string newLikes = sender()->parent()->findChild<QLineEdit*>("newLikes")->text().toStdString();
	std::string newDuration = sender()->parent()->findChild<QLineEdit*>("newDuration")->text().toStdString();
	std::string newLink = sender()->parent()->findChild<QLineEdit*>("newLink")->text().toStdString();
	try {
		administratorService.updateTutorial(oldTitle, oldPresenter, newTitle, newPresenter, { std::stoi(newDuration),0 }, std::stoi(newLikes), newLink);
		std::cout << "Successful update\n";
	}
	catch (std::exception& e)
	{
		displayError(e.what());
		QWidget* parentW = qobject_cast<QWidget*>(sender()->parent());
		parentW->close();
	}
	QWidget* parentWidget = qobject_cast<QWidget*>(sender()->parent()->parent());
	parentWidget->close();
}

void Gui::handleUserMode()
{
	QListWidget* item = qobject_cast<QListWidget*>(QObject::sender()); // Get the clicked item
	QString text = item->currentItem()->text();
	try {
		if (text.startsWith("1"))
			this->searchTutorialsByPresenter();
		if (text.startsWith("2"))
			this->removeTutorialFromWatchlist();
		if (text.startsWith("3"))
			this->displayWatchlist();
		if (text.startsWith("4"))
			this->saveWatchlistToFile();
		if (text.startsWith("5"))
			this->openWatchlist();
	}
	catch (std::exception& e) {

	}
}

void Gui::handleAdminMode()
{
	QListWidget* item = qobject_cast<QListWidget*>(QObject::sender()); // Get the clicked item
	QString text = item->currentItem()->text();
	try {
		if (text.startsWith("1"))
			this->addTutorial();
		if (text.startsWith("2"))
			this->removeTutorialFromAdmin();
		if (text.startsWith("3"))
			this->updateTutorial();
		if (text.startsWith("4"))
			this->displayAllTutorials();
	}
	catch (std::exception& e) {

	}

}
