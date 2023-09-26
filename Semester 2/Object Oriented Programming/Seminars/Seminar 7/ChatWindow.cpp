#include "ChatWindow.h"

ChatWindow::ChatWindow(ChatSession& session, std::string user, QWidget* parent)
	: QMainWindow(parent), user(user), session(session)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(user));
}

ChatWindow::~ChatWindow()
{}

void ChatWindow::update()
{
	ui.chatList->clear();

	for (const auto& message : session.getMessages())
	{
		if (message.first == this->user)
		{
			string messageText =  message.second;
			QListWidgetItem* currentMessage = new QListWidgetItem{ QString::fromStdString(messageText) };
			currentMessage->setTextAlignment(Qt::AlignRight); 
			
			ui.chatList->addItem(currentMessage);
		}
		else
		{
			string messageText = "[" + message.first + "] : " + message.second;
			QListWidgetItem* currentMessage = new QListWidgetItem{ QString::fromStdString(messageText) };
			currentMessage->setTextAlignment(Qt::AlignLeft);
			
			ui.chatList->addItem(currentMessage);

		}

	}
}

void ChatWindow::sendMessage()
{
	string messageText = ui.messageInput->text().toStdString();
	session.addMessage(user, messageText);
	ui.messageInput->clear();
}
