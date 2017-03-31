#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QtWidgets/QMainWindow>
#include "qcolor.h"
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <ctime>
#include <cstdlib>

#define WIDTH 50 //һ��ͼ�εĿ�
#define HEIGHT 50 //һ��ͼ�εĸ�
#define ROW_NUM 14
#define COL_NUM 12
#define BLANK_STATE -1 //�հ׵ķ���

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
	bool in_hor_line(int x1, int x2, int y);//����ͼƬ����ͬ��������
	bool in_ver_line(int y1, int y2, int x);//����ͼƬ����ͬ�ĺ�����
	bool check_left(int y1, int y2, int x);//������
	bool check_right(int y1, int y2, int x);//���Ҽ��
	bool check_up(int x1,int x2,int y);//���ϼ��
	bool check_down(int x1, int x2, int y);//���¼��
	bool check_hor(int x1, int x2,int y1,int y2);//�̶�����ͼƬ��Y�ᣬ�ƶ�ˮƽ��
	bool check_ver(int x1, int x2,int y1,int y2);//�̶�����ͼƬ��X�ᣬ�ƶ���ֱ��
	bool check_right_angle(int x1, int x2, int y1, int y2,int x,int y);//����ͼƬ�����߹���һ��ֱ�ǣ���ֻ��һ���սǣ�
	bool is_Link(int x1, int x2, int y1, int y2);//�ж�����ͼƬ�������ӵķ�ʽ
	bool find_pair();
	bool is_win();
	void draw_line();

private:
	int map_col;//��ͼ������
	int map_row;//��ͼ������
	int m_Y;//��ѡ�е�ͼ�ε�����
	int m_X;//��ѡ�е�ͼ�ε�����
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