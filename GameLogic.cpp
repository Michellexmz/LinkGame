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
	}//��ʼ����ͼ����ͼ�����еķ���Ϊ�հ׵�
	QList<int> tmpMap;//����δ�������ǰ�ĵ�ͼ
	for (int m = 0; m < 20; m++){
		QString imgstr = "./images/" + QString::number(m, 10) + ".png";
		qDebug(imgstr.toLatin1());
		QPixmap pixmap(imgstr);
		maplist.append(pixmap);
		for (int n = 0; n < 6; n++)
			tmpMap.append(m);//��ͼƬ�Ž���ͼ��
	}
	for (int x = 0; x < map_row; x++){
		for (int y = 0; y < map_col; y++){
			if (!(x == 0 || x == (map_row - 1) || y == 0 || y == (map_col - 1))){
				srand(time(0));
				int rand_num = (int(rand()*0.1 + rand()*0.01 + rand())) % tmpMap.size();//�ڵ�ͼ�������ѡһ��λ��
				map_array[x][y] = tmpMap.at(rand_num);//����λ�õ�ͼƬ����÷�����
				tmpMap.removeAt(rand_num);//�Ƴ�ԭ���ڷ����е�ͼƬ
			}
		}
	}
	update();
}

void GameLogic::draw_new_map(QPainter* paint)
{
	paint->setBrush(QBrush(Qt::gray));
	paint->drawRect(0, 0, map_col*WIDTH, map_row*HEIGHT);//Ϊ������ͼ�ӻ�ɫ�߿�
	for (int i = 0; i < map_row; i++){
		for (int j = 0; j < map_col; j++){
			if (map_array[i][j] == BLANK_STATE){
				continue;
			}
			paint->begin(this);
			paint->drawPixmap(i*WIDTH, j*HEIGHT, WIDTH, HEIGHT, maplist.at(map_array[i][j]));
		}	if (m_Y != BLANK_STATE){         //���ʱ����ͼƬ�����
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
	if ((x1 + 1) == x2) return true;//����ͼƬ��������
	else{
		for (int i = x1 + 1; i < x2; i++){
			if (map_array[i][y] != BLANK_STATE){
				flag = false;
				break;
			}//����ͼƬ֮���������ͼƬ������ֱ��������ѭ��
		}
		if (flag == true) return true;//����ͼƬֱ�������м�������ͼƬ��Ϊ�ϰ�
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
			break;//��X=x1��X=x2�ϴ�������ͼƬ������ѭ��
		flag = true;
		for (int m = x1 + 1; m < x2; m++){
			if (map_array[m][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag == true) return true;//�����ҵ�һ�У�ʹ������ͼƬ��������û������ͼƬ��Ϊ�ϰ�
		else continue;
	}
	if (flag == false) return false;//�����޷��ҵ�����Ҫ������ӷ�ʽ ʹ������ͼƬ���� ��������ͼƬ��Ϊ�ϰ�
}

bool GameLogic::check_down(int x1, int x2, int y)
{
	bool flag;
	for (int n = y + 1; n <= map_col; n++){
		if ((map_array[x1][n] != BLANK_STATE) && (map_array[x2][n] != BLANK_STATE))
			break;//��X=x1��X=x2���ϴ�������ͼƬ������ѭ��
		flag = true;
		for (int m = x1 + 1; m < x2; m++){
			if (map_array[m][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag == true) return true;//�����ҵ�һ�У�ʹ������ͼƬ��������û������ͼƬ��Ϊ�ϰ�
		else continue;
	}
	if (flag == false) return false;//�����޷��ҵ�����Ҫ������ӷ�ʽ ʹ������ͼƬ���� ��������ͼƬ��Ϊ�ϰ�
}

bool GameLogic::in_ver_line(int y1, int y2, int x)
{
	if (y1 > y2)
		return in_ver_line(y2, y1, x);
	bool flag;
	if ((y1 + 1) == y2) return true;//����ͼƬ��������
	else{
		for (int j = y1 + 1; j < y2; j++){
			if (map_array[x][j] != BLANK_STATE){
				flag = false;
				break;
			}//����ͼƬ֮���������ͼƬ������ֱ��������ѭ��
		}
		if (flag == true) return true;//����ͼƬֱ�������м�������ͼƬ��Ϊ�ϰ�
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
			break;//��Y=y1��Y=y2�ϴ�������ͼƬ������ѭ��
		flag = true;
		for (int n = y1 + 1; n < y2; n++){
			if (map_array[m][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag == true) return true;//�������ҵ�һ�У�ʹ������ͼƬ��������û������ͼƬ��Ϊ�ϰ�
		else continue;
	}
	if (flag = false) return false;//�����޷��ҵ�����Ҫ������ӷ�ʽ ʹ������ͼƬ���� ��������ͼƬ��Ϊ�ϰ�
}

bool GameLogic::check_right(int y1, int y2, int x)
{
	bool flag;
	for (int m = x + 1; m <= map_row; m++){
		if ((map_array[m][y1] != BLANK_STATE) && (map_array[m][y2] != BLANK_STATE))
			break;//��Y=y1��Y=y2���ϴ�������ͼƬ������ѭ��
		flag = true;
		for (int n = y1 + 1; n < y2; n++){
			if (map_array[m][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag == true) return true;//�����ҵ�һ�У�ʹ������ͼƬ��������û������ͼƬ��Ϊ�ϰ�
		else continue;
	}
	if (flag == false) return false;//�����޷��ҵ�����Ҫ������ӷ�ʽ ʹ������ͼƬ���� ��������ͼƬ��Ϊ�ϰ�
}

bool GameLogic::check_right_angle(int x1, int x2, int y1, int y2,int x,int y)
{
	bool flag;
	for (int m = x1 + 1; m < x2; m++){
		if (map_array[m][y] != BLANK_STATE){
			flag = false;
			break;//��Y=y�ϣ���������ͼƬ������ѭ��
		}
	}
	if (flag = true){
		for (int n = y1 + 1; n < y2; n++){
			if (map_array[x][n] != BLANK_STATE){
				flag = false;
				break;
			}
		}
		if (flag = true) return true;//����ֻ��һ���սǽ�����ͼƬ�����ķ�ʽ
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
				continue;//��X=x1�ϴ�������ͼƬ����X=x2�ϲ���������ͼƬ���˴�ѭ������������һ��ִ��
			}
			if ((flag2 == false) && (map_array[x1][n] != BLANK_STATE)){
				bool flag1 = false;
				break;//��X=x1��X=x2�ϴ�������ͼƬ������ѭ��
			}
			if ((flag1 == true) && (map_array[x2][n] != BLANK_STATE)){
				bool flag2 = false;
				continue;//��X=x2�ϴ�������ͼƬ����X=x1�ϲ���������ͼƬ���˴�ѭ������������һ��ִ��
			}
			if ((flag1 == false) && (map_array[x2][n] != BLANK_STATE)){
				bool flag2 = false;
				break;//��X=x1��X=x2�ϴ�������ͼƬ������ѭ��
			}
			flag = true;
			for (int m = x1 + 1; m < x2; m++){
				if (map_array[m][n] != BLANK_STATE){
					flag = false;
					break;
				}
			}
			if (flag == true) return true;//��Y=y1��Y=y2֮���ҵ�һ�У�ʹ������ͼƬ��������û������ͼƬ��Ϊ�ϰ�
			else continue;
		}
		if ((flag1 == false) && (flag2 == false)) return false;//��y1<Y<y2ʱ��X=x1��X=x2�Ͼ�������ͼƬ�Ĵ���
		                                                       //�򲻴������������ԣ�ֱ�ӷ���
		else if ((flag1 == false) && (flag2 == true))//��Y>y1ʱX=x1�ϴ���ͼƬ��ֻ������̽��
			return check_up(x1, x2, y1);
		else if ((flag1 == true) && (flag2 == false))//��Y<y2ʱX=x2�ϴ���ͼƬ��ֻ������̽��
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
				continue;//��X=x1�ϴ�������ͼƬ����X=x2�ϲ���������ͼƬ���˴�ѭ������������һ��ִ��
			}
			if ((flag2 == false) && (map_array[x1][n] != BLANK_STATE)){
				bool flag1 = false;
				break;//��X=x1��X=x2�ϴ�������ͼƬ������ѭ��
			}
			if ((flag1 == true) && (map_array[x2][n] != BLANK_STATE)){
				bool flag2 = false;
				continue;//��X=x2�ϴ�������ͼƬ����X=x1�ϲ���������ͼƬ���˴�ѭ������������һ��ִ��
			}
			if ((flag1 == false) && (map_array[x2][n] != BLANK_STATE)){
				bool flag2 = false;
				break;//��X=x1��X=x2�ϴ�������ͼƬ������ѭ��
			}
			flag = true;
			for (int m = x1 + 1; m < x2; m++){
				if (map_array[m][n] != BLANK_STATE){
					flag = false;
					break;
				}
			}
			if (flag == true) return true;//��Y=y1��Y=y2֮���ҵ�һ�У�ʹ������ͼƬ��������û������ͼƬ��Ϊ�ϰ�
			else continue;
		}
		if ((flag1 == false) && (flag2 == false)) return false;//��y1<Y<y2ʱ��X=x1��X=x2�Ͼ�������ͼƬ�Ĵ���
		                                                       //�򲻴������������ԣ�ֱ�ӷ���
		else if ((flag1 == false) && (flag2 == true))//��Y>y1ʱX=x1�ϴ���ͼƬ��ֻ������̽��
			return check_down(x1, x2, y1);
		else if ((flag1 == true) && (flag2 == false))//��Y<y2ʱX=x2�ϴ���ͼƬ��ֻ������̽��
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
		if ((flag1 == false)&&(flag2==false)) return false;//��x1<X<x2ʱ��Y=y1��Y=y2�ϴ�������ͼƬ������������������
		else if ((flag1 == false) && (flag2 == true))//��X>x1ʱY=y1�ϴ���ͼƬ��ֻ������̽��
			return check_left(y1, y2, x1);
		else if ((flag1 == true) && (flag2 == false))//��X<x2ʱY=y2�ϴ���ͼƬ��ֻ������̽��
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
		if ((flag1 == false) && (flag2 == false)) return false;//��x1<X<x2ʱ��Y=y1��Y=y2�ϴ�������ͼƬ������������������
		else if ((flag1 == false) && (flag2 == true))//��X>x1ʱY=y1�ϴ���ͼƬ��ֻ������̽��
			return check_right(y1, y2, x1);
		else if ((flag1 == true) && (flag2 == false))//��X<x2ʱY=y2�ϴ���ͼƬ��ֻ������̽��
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
	if (x1 == x2&&y1 != y2){//�ж�����ͼƬ�Ƿ���һ����ֱ����
		if (in_ver_line(y1, y2, x1)){
			return true;
		}//������ͼƬ��һ��ֱ���ϣ�������ȥ��·������ȥ
	}
	else if (x1 != x2&&y1 == y2){//�ж�����ͼƬ�Ƿ���һ��ˮƽ����
		if (in_hor_line(x1, x2, y1)){
			return true;
		}//������ͼƬ��һ��ˮƽ���ϣ�������ȥ��·������ȥ
	}
	else if (x1 != x2&&y1 != y2){
		bool flag1 = check_hor(x1, x2, y1, y2);//����ƶ�ˮƽ��ʱ�Ƿ�����ȥ��·��
		if (flag1 == true) return true;
		else {
			bool flag2 = check_ver(x1, x2, y1, y2);//�ƶ�ˮƽ������ȥ��·�����ƶ���ֱ��
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
	}//�жϽ������Ƿ����ͼƬ������������κ�ͼƬ�����Ӯ����Ϸ����
	return true;
}

void GameLogic::mousePressEvent(QMouseEvent *event)
{
	int x = (event->x()) / WIDTH + ((event->x()) % WIDTH ? 1 : 0) - 1;//��¼������ڷ���ĺ�����
	int y = (event->y()) / HEIGHT + ((event->y()) % HEIGHT ? 1 : 0) - 1;//��¼������ڷ����������
	if (x > 0 && x < map_row && y>0 && y < map_col && map_array[x][y] != BLANK_STATE){
		if (m_X == BLANK_STATE || m_Y == BLANK_STATE){//�жϸ÷����ǵ�һ�ε���ķ��黹�ǵڶ��ε���ķ���
			m_X = x;
			m_Y = y;//��¼��һ�ε���ķ���
		}
		else{
			if (map_array[x][y] == map_array[m_X][m_Y]){//�ж�����ͼƬ�����Ƿ����
				bool flag = is_Link(x, y, m_X, m_Y);
				if (flag == true){
					map_array[x][y] = BLANK_STATE;
					map_array[m_X][m_Y] = BLANK_STATE;
					m_X = BLANK_STATE;
					m_Y = BLANK_STATE;
				}
				else{
					m_X = BLANK_STATE;
					m_Y = BLANK_STATE;//�������ͼƬû�����ӵ�·��������ѡ��
				}
			}
			else{
				m_X = BLANK_STATE;//�������ͼƬ���ݲ���ͬ������ѡ��
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
		return false;//�����ͼ���Դ��ڿ�����Ե�ͼƬ�����޷����ĵ�ͼ
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
					int rand_num = (int(rand()*0.1 + rand()*0.01 + rand())) % alter.size();//��ԭ��ͼƬ��λ�õ��������ѡһ��λ��
					map_array[x][y] = alter.at(rand_num);//����λ�õ�ͼƬ����÷�����
					alter.removeAt(rand_num);//�Ƴ�ԭ���ڷ����е�ͼƬ
				}
			}
		}
	}
	update();
	return true;
} 

