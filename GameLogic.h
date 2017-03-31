#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QtWidgets/QMainWindow>
#include "qcolor.h"
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <ctime>
#include <cstdlib>

#define WIDTH 50 //一个图形的宽
#define HEIGHT 50 //一个图形的高
#define ROW_NUM 14
#define COL_NUM 12
#define BLANK_STATE -1 //空白的方块

class GameLogic:public QWidget
{
	Q_OBJECT

public:
	GameLogic(QWidget *parent=0);
	~GameLogic();
	void draw_new_map(QPainter* paint);
	enum Shape{ Line, Rectangle, Pixmap };
	void setShape(Shape);
	void setBrush(QBrush);
	void setPen(QPen);
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *event);
	bool in_hor_line(int x1, int x2, int y);//两张图片有相同的纵坐标
	bool in_ver_line(int y1, int y2, int x);//两张图片有相同的横坐标
	bool check_left(int y1, int y2, int x);//向左检查
	bool check_right(int y1, int y2, int x);//向右检查
	bool check_up(int x1,int x2,int y);//向上检查
	bool check_down(int x1, int x2, int y);//向下检查
	bool check_hor(int x1, int x2,int y1,int y2);//固定两张图片的Y轴，移动水平线
	bool check_ver(int x1, int x2,int y1,int y2);//固定两张图片的X轴，移动垂直线
	bool check_right_angle(int x1, int x2, int y1, int y2,int x,int y);//两张图片的连线构成一个直角（即只有一个拐角）
	bool is_Link(int x1, int x2, int y1, int y2);//判断两张图片有无连接的方式
	bool find_pair();
	bool is_win();
	void draw_line();

private:
	int map_col;//地图的列数
	int map_row;//地图的行数
	int m_Y;//被选中的图形的列数
	int m_X;//被选中的图形的行数
	int map_array[ROW_NUM][COL_NUM];
	int* m_map;
	QList<QPixmap> maplist;
	Shape shape;
	QBrush brush;
	QPen pen;
	
protected slots:
void start_new_game();
bool card_shuffled();


};

#endif//GAMELOGIC_H