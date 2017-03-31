#ifndef LINK_GAME_H
#define LINK_GAME_H

#include <QtWidgets/QMainWindow>
#include "ui_link_game.h"

class Link_Game : public QMainWindow
{
	Q_OBJECT

public:
	Link_Game(QWidget *parent = 0);
	~Link_Game();
	
private:
	Ui::Link_GameClass ui;	
};

#endif // LINK_GAME_H
