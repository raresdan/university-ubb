#pragma once

#include <QMainWindow>
#include "ui_ChatWindow.h"
#include "Observer.h"
#include "ChatSession.h"

using namespace std;

class ChatWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	ChatWindow(ChatSession& session, std::string user, QWidget *parent = nullptr);
	~ChatWindow();

	void update();

public slots:
	void sendMessage();

private:
	Ui::ChatWindowClass ui;

	ChatSession& session;
	string user;
};
