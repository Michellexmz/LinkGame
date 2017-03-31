#include "link_game.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include "GameLogic.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Link_Game w;
	w.show();
	return a.exec();
}
