#include "GameLogic.h"


GameLogic::GameLogic(QWidget *parent)
{
	
	map_col = COL_NUM;
	map_row = ROW_NUM;
	m_X = BLANK_STATE;
	m_Y = BLANK_STATE;
	m_map = new int[map_col*map_row];
	setFixedSize(map_row*WIDTH + 100, map_col*WIDTH + 1);
	setAutoFillBackground(true);
}

GameLogic::~GameLogic()
{
	delete[] m_map;
}

void GameLogic::start_new_game()
{
	for (int i = 0; i < map_row; i++){
		for (int j = 0; j < map_col; j++){
			map_array[i][j] = BLANK_STATE;
		}
	}//初始化地图，地图上所有的方块为空白的
	QList<int> tmpMap;//定义未随机分配前的地图
	for (int m = 0; m < 20; m++){
		QString imgstr = "./images/" + QString::number(m, 10) + ".png";
		qDebug(imgstr.toLatin1());
		QPixmap pixmap(imgstr);
		maplist.append(pixmap);
		for (int n = 0; n < 6; n++)
			tmpMap.append(m);//将图片放进地图中
	}
	for (int x = 0; x < map_row; x++){
		for (int y = 0; y < map_col; y++){
			if (!(x == 0 || x == (map_row - 1) || y == 0 || y == (map_col - 1))){
				srand(time(0));
				int rand_num = (int(rand()*0.1 + rand()*0.01 + rand())) % tmpMap.size();//在地图中随机挑选一个位置
				map_array[x][y] = tmpMap.at(rand_num);//将该位置的图片放入该方块中
				tmpMap.removeAt(rand_num);//移除原本在方块中的图片
			}
		}
	}
	update();
}

void GameLogic::draw_new_map(QPainter* paint)
{
	paint->setBrush(QBrush(Qt::gray));
	paint->drawRect(0, 0, map_col*WIDTH, map_row*HEIGHT);//为整个地图加灰色边框
	for (int i = 0; i < map_row; i++){
		for (int j = 0; j < map_col; j++){
			if (map_array[i][j] == BLANK_STATE){
				continue;
			}
			paint->begin(this);
			paint->drawPixmap(i*WIDTH, j*HEIGHT, WIDTH, HEIGHT, maplist.at(map_array[i][j]));
		}	if (m_Y != BLANK_STATE){         //点击时绘制图片的外框
			QPen myPen(Qt::red, 2, Qt::SolidLine);
			QPen ppen;
			ppen = paint->pen();
			paint->setPen(myPen);
			paint->drawLine(      m_X*WIDTH,       m_Y*HEIGHT,       m_X*WIDTH, (m_Y + 1)*HEIGHT);
			paint->drawLine(      m_X*WIDTH, (m_Y + 1)*HEIGHT, (m_X + 1)*WIDTH, (m_Y + 1)*HEIGHT);
			paint->drawLine((m_X + 1)*WIDTH, (m_Y + 1)*HEIGHT, (m_X + 1)*WIDTH,       m_Y *HEIGHT);
			paint->drawLine((m_X + 1)*WIDTH,       m_Y*HEIGHT,       m_X*WIDTH,       m_Y *HEIGHT);
			paint->setPen(ppen);
		}
	}paint->end();
}


void GameLogic::setShape(Shape s)
{
	shape = s;
	update();
}

void GameLogic::setBrush(QBrush b)
{
	brush = b;
	update();
}

void GameLogic::setPen(QPen p)
{
	pen = p;
	update();
}


void GameLogic::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	draw_new_map(&p);
}

bool GameLogic::in_hor_line(int x1, int x2, int y)
{
	if (x1 > x2) 
		return in_hor_line(x2, x1, y);
	bool flag;
	if ((x1 + 1) == x2) return true;//两张图片左右相邻
	else{
		for (int i = x1 + 1; i < x2; i++){
			if (map_array[i][y] != BLANK_STATE){
				flag = false;
				break;
			}//两张图片之间存在其他图片，不可直连，跳出循环
		}
		if (flag == true) return true;//两张图片直连，且中间无其他图片作为障碍
		else{
			bool checked=check_up(x1, x2, y);
			if (checked = true) return checked;
			else
				return checked = check_down(x1, x2, y);
		}
	}
}

bool GameLogic::check_up(int x1,int x2,int y)
{
	bool flag;
	for (int n = y - 1; n >= 0; n--){
		if ((map_array[x1][n] != BLANK_STATE) && (map_array[x2][n] != BLANK_STATE))
			break;//在X=x1或X=x2上存在其他图片，跳出循环
		flag = true;
		for (int m = x1 + 1; m < x2; m++){
			if (map_array[m][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag == true) return true;//向上找到一行，使得两张图片相连，且没有其他图片作为障碍
		else continue;
	}
	if (flag == false) return false;//向上无法找到符合要求的连接方式 使得两张图片相连 而无其他图片作为障碍
}

bool GameLogic::check_down(int x1, int x2, int y)
{
	bool flag;
	for (int n = y + 1; n <= map_col; n++){
		if ((map_array[x1][n] != BLANK_STATE) && (map_array[x2][n] != BLANK_STATE))
			break;//在X=x1或X=x2轴上存在其他图片，跳出循环
		flag = true;
		for (int m = x1 + 1; m < x2; m++){
			if (map_array[m][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag == true) return true;//向下找到一行，使得两张图片相连，且没有其他图片作为障碍
		else continue;
	}
	if (flag == false) return false;//向下无法找到符合要求的连接方式 使得两张图片相连 而无其他图片作为障碍
}

bool GameLogic::in_ver_line(int y1, int y2, int x)
{
	if (y1 > y2)
		return in_ver_line(y2, y1, x);
	bool flag;
	if ((y1 + 1) == y2) return true;//两张图片上下相邻
	else{
		for (int j = y1 + 1; j < y2; j++){
			if (map_array[x][j] != BLANK_STATE){
				flag = false;
				break;
			}//两张图片之间存在其他图片，不可直连，跳出循环
		}
		if (flag == true) return true;//两张图片直连，且中间无其他图片作为障碍
		else{
			bool checked = check_left(y1, y2, x);
			if (checked = true) return true;
			else
				return checked = check_right(y1, y2, x);
		}
	}
}

bool GameLogic::check_left(int y1, int y2, int x)
{
	bool flag;
	for (int m = x - 1; m >= 0; m--){
		if ((map_array[m][y1] != BLANK_STATE) && (map_array[m][y2] != BLANK_STATE))
			break;//在Y=y1或Y=y2上存在其他图片，跳出循环
		flag = true;
		for (int n = y1 + 1; n < y2; n++){
			if (map_array[m][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag == true) return true;//向左上找到一列，使得两张图片相连，且没有其他图片作为障碍
		else continue;
	}
	if (flag = false) return false;//向左无法找到符合要求的连接方式 使得两张图片相连 而无其他图片作为障碍
}

bool GameLogic::check_right(int y1, int y2, int x)
{
	bool flag;
	for (int m = x + 1; m <= map_row; m++){
		if ((map_array[m][y1] != BLANK_STATE) && (map_array[m][y2] != BLANK_STATE))
			break;//在Y=y1或Y=y2轴上存在其他图片，跳出循环
		flag = true;
		for (int n = y1 + 1; n < y2; n++){
			if (map_array[m][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag == true) return true;//向右找到一列，使得两张图片相连，且没有其他图片作为障碍
		else continue;
	}
	if (flag == false) return false;//向右无法找到符合要求的连接方式 使得两张图片相连 而无其他图片作为障碍
}

bool GameLogic::check_right_angle(int x1, int x2, int y1, int y2,int x,int y)
{
	bool flag;
	for (int m = x1 + 1; m < x2; m++){
		if (map_array[m][y] != BLANK_STATE){
			flag = false;
			break;//在Y=y上，存在其他图片，跳出循环
		}
	}
	if (flag = true){
		for (int n = y1 + 1; n < y2; n++){
			if (map_array[x][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag = true) return true;//存在只有一个拐角将两张图片相连的方式
	}
	return flag;
}

bool GameLogic::check_hor(int x1, int x2, int y1, int y2)
{
	if (x1 > x2)
		return check_hor(x2, x1, y2, y1);
	if (y1 < y2){
		bool flag, flag1, flag2;
		if (map_array[x2][y1] == BLANK_STATE){
			bool checkin = check_right_angle(x1, x2, y1, y2,x2,y1);
			if (checkin == true) return true;
		}
		if (map_array[x1][y2] == BLANK_STATE){
			bool checkin = check_right_angle(x1, x2, y1, y2, x1, y2);
			if (checkin == true) return true;
		}
		if (map_array[x2][y1] != BLANK_STATE) flag2 = false;
		if (map_array[x1][y2] != BLANK_STATE) flag1 = false;
		for (int n = y1+1; n < y2; n++){
			if ((flag2== true)&&(map_array[x1][n] != BLANK_STATE)){
				bool flag1 = false;
				continue;//在X=x1上存在其他图片，但X=x2上不存在其他图片，此次循环结束，向下一行执行
			}
			if ((flag2 == false) && (map_array[x1][n] != BLANK_STATE)){
				bool flag1 = false;
				break;//在X=x1与X=x2上存在其他图片，跳出循环
			}
			if ((flag1 == true) && (map_array[x2][n] != BLANK_STATE)){
				bool flag2 = false;
				continue;//在X=x2上存在其他图片，但X=x1上不存在其他图片，此次循环结束，向下一行执行
			}
			if ((flag1 == false) && (map_array[x2][n] != BLANK_STATE)){
				bool flag2 = false;
				break;//在X=x1与X=x2上存在其他图片，跳出循环
			}
			flag = true;
			for (int m = x1 + 1; m < x2; m++){
				if (map_array[m][n] != BLANK_STATE){
					flag = false;
					break;
				}
			}
			if (flag == true) return true;//向Y=y1与Y=y2之间找到一行，使得两张图片相连，且没有其他图片作为障碍
			else continue;
		}
		if ((flag1 == false) && (flag2 == false)) return false;//在y1<Y<y2时，X=x1与X=x2上均有其他图片的存在
		                                                       //则不存在其他可能性，直接返回
		else if ((flag1 == false) && (flag2 == true))//在Y>y1时X=x1上存在图片，只能向上探索
			return check_up(x1, x2, y1);
		else if ((flag1 == true) && (flag2 == false))//在Y<y2时X=x2上存在图片，只能向下探索
			return check_down(x1, x2, y2);
		else{
			bool checked = check_up(x1, x2, y1);
			if (checked == true) return true;
			else
				return check_down(x1, x2, y2);
		}
	}
	else if (y1 > y2){
		bool flag, flag1, flag2;
		if (map_array[x2][y1] == BLANK_STATE){
			bool checkin = check_right_angle(x1, x2, y1, y2, x2, y1);
			if (checkin == true) return true;
		}
		if (map_array[x1][y2] == BLANK_STATE){
			bool checkin = check_right_angle(x1, x2, y1, y2, x1, y2);
			if (checkin == true) return true;
		}
		if (map_array[x2][y1] != BLANK_STATE) flag2 = false;
		if (map_array[x1][y2] != BLANK_STATE) flag1 = false;
		for (int n = y2 + 1; n < y1; n++){
			if ((flag2 == true) && (map_array[x1][n] != BLANK_STATE)){
				bool flag1 = false;
				continue;//在X=x1上存在其他图片，但X=x2上不存在其他图片，此次循环结束，向下一行执行
			}
			if ((flag2 == false) && (map_array[x1][n] != BLANK_STATE)){
				bool flag1 = false;
				break;//在X=x1与X=x2上存在其他图片，跳出循环
			}
			if ((flag1 == true) && (map_array[x2][n] != BLANK_STATE)){
				bool flag2 = false;
				continue;//在X=x2上存在其他图片，但X=x1上不存在其他图片，此次循环结束，向下一行执行
			}
			if ((flag1 == false) && (map_array[x2][n] != BLANK_STATE)){
				bool flag2 = false;
				break;//在X=x1与X=x2上存在其他图片，跳出循环
			}
			flag = true;
			for (int m = x1 + 1; m < x2; m++){
				if (map_array[m][n] != BLANK_STATE){
					flag = false;
					break;
				}
			}
			if (flag == true) return true;//向Y=y1与Y=y2之间找到一行，使得两张图片相连，且没有其他图片作为障碍
			else continue;
		}
		if ((flag1 == false) && (flag2 == false)) return false;//在y1<Y<y2时，X=x1与X=x2上均有其他图片的存在
		                                                       //则不存在其他可能性，直接返回
		else if ((flag1 == false) && (flag2 == true))//在Y>y1时X=x1上存在图片，只能向上探索
			return check_down(x1, x2, y1);
		else if ((flag1 == true) && (flag2 == false))//在Y<y2时X=x2上存在图片，只能向下探索
			return check_up(x1, x2, y2);
		else{
			bool checked = check_down(x1, x2, y1);
			if (checked == true) return true;
			else
				return check_up(x1, x2, y2);
		}
	}
}

bool GameLogic::check_ver(int x1, int x2, int y1, int y2)
{
	if (y1 > y2)
		return check_ver(x2, x1, y2, y1);
	if (x1 < x2){
		bool flag1,flag2;
		for (int m = x1 + 1; m <= x2; m++){
			if (map_array[m][y1] != BLANK_STATE){
				flag1 = false;
				break;
			}
		}
		for (int m = x2 - 1; m >= x1; m--){
			if (map_array[m][y2] != BLANK_STATE){
				flag2 = false;
				break;
			}
		}
		if ((flag1 == false)&&(flag2==false)) return false;//在x1<X<x2时，Y=y1或Y=y2上存在其他图片，不存在其他可能性
		else if ((flag1 == false) && (flag2 == true))//在X>x1时Y=y1上存在图片，只能向左探索
			return check_left(y1, y2, x1);
		else if ((flag1 == true) && (flag2 == false))//在X<x2时Y=y2上存在图片，只能向右探索
			return check_right(y1, y2, x2);
		else{
			bool checked = check_left(y1,y2,x1);
			if (checked == true) return true;
			else
				return check_right(y1,y2,x2);
		}	
	}
	else if (x1 > x2){
		bool flag1, flag2;
		for (int m = x2 + 1; m <= x1; m++){
			if (map_array[m][y1] != BLANK_STATE){
				flag1 = false;
				break;
			}
		}
		for (int m = x1 - 1; m >= x2; m--){
			if (map_array[m][y2] != BLANK_STATE){
				flag2 = false;
				break;
			}
		}
		if ((flag1 == false) && (flag2 == false)) return false;//在x1<X<x2时，Y=y1或Y=y2上存在其他图片，不存在其他可能性
		else if ((flag1 == false) && (flag2 == true))//在X>x1时Y=y1上存在图片，只能向左探索
			return check_right(y1, y2, x1);
		else if ((flag1 == true) && (flag2 == false))//在X<x2时Y=y2上存在图片，只能向右探索
			return check_left(y1, y2, x2);
		else{
			bool checked = check_right(y1, y2, x1);
			if (checked == true) return true;
			else
				return check_left(y1, y2, x2);
		}
	}
}

bool GameLogic::is_Link(int x1, int x2, int y1, int y2)
{
	if (x1 == x2&&y1 != y2){//判断两张图片是否在一条竖直线上
		if (in_ver_line(y1, y2, x1)){
			return true;
		}//若两张图片在一条直线上，且有消去的路径，消去
	}
	else if (x1 != x2&&y1 == y2){//判断两张图片是否在一条水平线上
		if (in_hor_line(x1, x2, y1)){
			return true;
		}//若两条图片在一条水平线上，且有消去的路径，消去
	}
	else if (x1 != x2&&y1 != y2){
		bool flag1 = check_hor(x1, x2, y1, y2);//检测移动水平轴时是否有消去的路径
		if (flag1 == true) return true;
		else {
			bool flag2 = check_ver(x1, x2, y1, y2);//移动水平轴无消去的路径，移动垂直轴
			if (flag2 == true)return true;
		}
	}
	else
		return false;
}

bool GameLogic::is_win()
{
	for (int m = 0; m < map_row; m++){
		for (int n = 0; n < map_col; n++){
			if (map_array[m][n] != BLANK_STATE)
				return false;
		}
	}//判断界面上是否存在图片，如果不存在任何图片，玩家赢，游戏结束
	return true;
}

void GameLogic::mousePressEvent(QMouseEvent *event)
{
	int x = (event->x()) / WIDTH + ((event->x()) % WIDTH ? 1 : 0) - 1;//记录鼠标所在方块的横坐标
	int y = (event->y()) / HEIGHT + ((event->y()) % HEIGHT ? 1 : 0) - 1;//记录鼠标所在方块的纵坐标
	if (x > 0 && x < map_row && y>0 && y < map_col && map_array[x][y] != BLANK_STATE){
		if (m_X == BLANK_STATE || m_Y == BLANK_STATE){//判断该方块是第一次点击的方块还是第二次点击的方块
			m_X = x;
			m_Y = y;//记录第一次点击的方块
		}
		else{
			if (map_array[x][y] == map_array[m_X][m_Y]){//判断两张图片内容是否相等
				bool flag = is_Link(x, y, m_X, m_Y);
				if (flag == true){
					map_array[x][y] = BLANK_STATE;
					map_array[m_X][m_Y] = BLANK_STATE;
					m_X = BLANK_STATE;
					m_Y = BLANK_STATE;
				}
				else{
					m_X = BLANK_STATE;
					m_Y = BLANK_STATE;//如果两张图片没有连接的路径，重新选择
				}
			}
			else{
				m_X = BLANK_STATE;//如果两张图片内容不相同，重新选择
				m_Y = BLANK_STATE;
			}
		}
		update();
	}
	if (is_win()){
		QMessageBox::information(this, tr("Congratulations!"), tr("You've won the game"));

	}
}

bool GameLogic::find_pair()
{
	for (int sx = 1; sx < map_row-1; sx++){
		for (int sy = 1; sy < map_col-1; sy++){
			if (map_array[sx][sy] == BLANK_STATE)
				continue;
			else{
				for (int ex = sx; ex < map_row; ex++){
					for (int ey = 1; ey < map_col; ey++){
						if (map_array[ex][ey] == BLANK_STATE||(sx==ex&&sy==ey))
							continue;
						if (map_array[sx][sy] == map_array[ex][ey]){
							if (is_Link(sx, sy, ex, ey) == true)
								return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool GameLogic::card_shuffled()
{
	if (find_pair()){
		QMessageBox::information(this, tr("Warning"), tr("Pair Exists!"));
		return false;//如果地图上仍存在可以配对的图片，则无法更改地图
	}
	else{
		QList<int> alter;
		for (int i = 0; i < map_row; i++){
			for (int j = 0; j < map_col; j++){
				if (map_array[i][j] != BLANK_STATE)
					alter.append(map_array[i][j]);
			}
		}
		for (int x = 0; x < map_row; x++){
			for (int y = 0; y < map_col; y++){
				if (map_array[x][y]!=BLANK_STATE){
					srand(time(0));
					int rand_num = (int(rand()*0.1 + rand()*0.01 + rand())) % alter.size();//在原有图片的位置当中随机挑选一个位置
					map_array[x][y] = alter.at(rand_num);//将该位置的图片放入该方块中
					alter.removeAt(rand_num);//移除原本在方块中的图片
				}
			}
		}
	}
	update();
	return true;
} 

