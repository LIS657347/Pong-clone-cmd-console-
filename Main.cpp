#include<windows.h>
#include<conio.h>
#include<ctime>
#include<stdio.h>
#include<math.h>

using namespace std;

unsigned int start_time;
unsigned int end_time;
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
int player_point = 0;
int enemy_point = 0;
char key = 0;
const int map_x = 320;
const int map_y = 240;
const int fps = 15;
bool game_over = false;
unsigned int frame_time = 1000 / fps;
auto mydc = GetDC(GetConsoleWindow());
const auto start_y = 40;



void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(out, coord);
}


class guard
{
public:
	guard(bool is_player)
	{
		height = 36;
		width = 10;
		this->is_player = is_player;
		if (is_player) x = map_x - 2 - width/2;
		else           x = 2 + width/2;
		y = map_y / 2 - height / 2;

	}
	void move(const char& key)
	{
		for (int _y = y - height / 2; _y < y + height / 2; ++_y) {
			for (int _x = x - width / 2; _x < x + width / 2; ++_x) {
				SetPixel(mydc, _x, _y + start_y, 789516);
			}
		}
		if (key == 'w' || key == 'W' || key == 'ö' || key == 'Ö')
		{
			if (y - 1 - height / 2 > fabs(pow(dy - a_y ,2) / r_y))
			{
				dy -= a_y;
				y += dy;
			}
		}
		if (key == 's' || key == 'S' || key == 'û' || key == 'Û')
		{
			if (map_y - 1 -y - height/2  > fabs(pow(dy+a_y,2)/r_y))
			{
				dy += a_y;
				y += dy;
			}
		}
		if (dy < 0) {
			/*for (int _y = y   + height / 2 - dy; _y > y + height / 2; --_y) {
				for (int _x = x - width / 2; _x < x + width / 2; ++_x) {
					SetPixel(mydc, _x, _y + start_y, 789516);
				}
			}
			for (int _y = y + height / 2; _y <= y - dy + height / 2; ++_y) {
				for (int _x = x - width / 2; _x < x + width / 2; ++_x) {
					SetPixel(mydc, _x, _y + start_y, RGB(is_player ? 255 : 0, 0, is_player ? 0 : 255));
				}
			}*/
			dy += r_y;
		}
		else if (dy > 0) {
			//for (int _y = y - height / 2 - dy; _y < y - height / 2; ++_y) {
			//	for (int _x = x - width / 2; _x < x + width / 2; ++_x) {
			//		SetPixel(mydc, _x, _y + start_y, 789516);
			//	}
			//}
			//for (int _y = y - height / 2; _y >= y - height / 2 - dy; --_y) {
			//	for (int _x = x - width / 2; _x < x + width / 2; ++_x) {
			//		SetPixel(mydc, _x, _y + start_y, RGB(is_player?255:0,0,is_player?0:255));
			//	}
			//}
			dy -= r_y;
	
		}
		for (int _y = y - height / 2; _y < y + height / 2; ++_y) {
			for (int _x = x - width / 2; _x < x + width / 2; ++_x) {
				SetPixel(mydc, _x, _y + start_y, RGB(is_player ? 255 : 0, 0, is_player ? 0 : 255));
			}
		}
	}
	bool are_there(int x_cord, int y_cord) const
	{
		if (x_cord == x && y_cord >= y && y_cord <= (y + height - 1)) return true;
		else                                                       return false;
	}
	inline int get_x()	 const
	{
		return x;
	}
	inline int get_y()	 const
	{
		return y;
	}
	inline int get_height() const
	{
		return height;
	}
	inline int get_width() const
	{
		return width;
	}
private:
	float x;
	float y;
	float dy;
	const float a_y = 2.5;
	const float r_y = 2.0;
	int height;
	int width;
	bool is_player;
};


class ball
{
public:
	ball()
	{
		x = map_x / 2;
		y = map_y / 2;
		dx = 1;
		srand(clock());
		dy = rand() % 25 - 12;
		dy = dy == 0 ? 12.5 : dy;
		r = 5;
	}
	void move(guard& player, guard& enemy)
	{
		for (int _y = y - r; _y < y + r; ++_y) {
			for (int _x = x - r; _x < x + r; ++_x) {
				if (pow(_x - x, 2) + pow(_y - y, 2) <= r) {
					if (_x==map_x/2 && (_y + start_y) % 20 < 15)
						SetPixel(mydc, _x, _y + start_y, RGB(255, 255, 255));
					else
						SetPixel(mydc, _x, _y + start_y, 789516);
				}
			}
		}
		y += dy;
		x += dx;
		if (y+r > map_y-2 || y-r < 1)
		{
			if (y-r > 1)
			{
				y = 2* (map_y - 2 -r) -y;
				dy += 0.5;
				dy *= -1;
			}
			else
			{
				y = 1 + r+fabs(y-r-1);
				dy -= 0.5;
				dy *= -1;
			}
			dx += dx < 0 ? -0.5 : 0.5;
		}
		if (x-r<=enemy.get_x()+enemy.get_width()/2  + 1&& y + r <= enemy.get_y() + enemy.get_height() / 2 +1&& y - r >= enemy.get_y() - enemy.get_height() / 2 - 1)
		{
			x = enemy.get_x() + enemy.get_width()+1+r;
			dx *= -1;
		}
		else if (x - r<=1)
		{
			++player_point;
			x = map_x / 2;
			y = map_y / 2;
			dx = 2.5;
			dy = rand() % 10 - 5;
			dy = dy == 0 ? 5 : dy;
		}
		else if (x + r >= player.get_x() - player.get_width() / 2 -1 && y + r <= player.get_y() + player.get_height() / 2 +1&& y - r >= player.get_y() - player.get_height() / 2 -1)
		{
			x = player.get_x() -player.get_width() - r - 1;
			dx *= -1;
		}
		else if (x + r >= map_x - 1)
		{
			++enemy_point;
			x = map_x / 2;
			y = map_y / 2;
			dx = -1;
			dy = rand() % 2 - 1;
			dy = dy == 0 ? 1 : dy;
		}
		for (int _y = y - r; _y < y+r; _y += 1) {
			for (int _x =x-r; _x < x+r; _x += 1) {
				if (pow(_x - x, 2) + pow(_y - y, 2) <= r)
					SetPixel(mydc, _x, _y + start_y, RGB(255, 255, 255));
			}
		}
	}
	bool are_there(int x_coord, int y_coord)	const
	{
		if (pow(x - x_coord, 2) + pow(y - y_coord, 2) <= r ) return true;
		else												 return false;
	}
	inline float get_y()	const
	{
		return y;
	}
	inline float get_x()	const
	{
		return x;
	}
		inline float get_r()	const
		{
			return r;
		}
	
private:
	float  x;
	float dx;
	float  y;
	float dy;
	int r;
};

void draw_title(ball& b, guard player, guard enemy)
{
	system("cls");
	for (int y = 0; y < map_y; ++y) {
		SetPixel(mydc, 0, y + start_y, RGB(255, 255, 255));
	}
	for (int x = 0; x < map_x; ++x) {
		SetPixel(mydc, x, start_y, RGB(255, 255, 255));
	}
	for (int y = 0; y < map_y; ++y) {
		SetPixel(mydc, map_x - 1, y + start_y, RGB(255, 255, 255));
	}
	for (int x = 0; x < map_x; ++x) {
		SetPixel(mydc, x, map_y - 1 + start_y, RGB(255, 255, 255));
	}
	for (int y = b.get_y() - b.get_r(); y < b.get_y() + b.get_r(); y += 1) {
		for (int x = b.get_x() - b.get_r(); x < b.get_x() + b.get_r(); x += 1) {
			if (pow(x - b.get_x(), 2) + pow(y - b.get_y(), 2) <= b.get_r())
				SetPixel(mydc, x, y + start_y, RGB(255, 255, 255));
		}
	}
	for (int y = 0; y < map_y; ++y) {
		if((y + start_y) % 20 < 15)
			SetPixel(mydc, map_x / 2, y + start_y, RGB(255, 255, 255));
	}

	for (int _y = player.get_y() - player.get_height()/2; _y < player.get_y() + player.get_height()/2; ++_y) {
		for (int _x = player.get_x() - player.get_width()/2; _x < player.get_x() + player.get_width()/2; ++_x) {
			SetPixel(mydc, _x, _y + start_y, RGB(255, 0, 0));
		}
	}
	for (int _y = enemy.get_y() - enemy.get_height()/2; _y < enemy.get_y() + enemy.get_height()/2; ++_y) {
		for (int _x = enemy.get_x() - enemy.get_width()/2; _x < enemy.get_x() + enemy.get_width()/2; ++_x) {
			SetPixel(mydc, _x, _y + start_y, RGB(0, 0, 255));
		}
	}
}


void control()
{
	if (_kbhit())
	{
		key = _getch();
	}
}

void logic(ball& b, guard& player, guard& enemy)
{
	if (b.get_y() < enemy.get_y())                                  enemy.move('w');
	else if (b.get_y() > enemy.get_y() + enemy.get_height() - 2)       enemy.move('s');
	player.move(key);
	key = 0;
	b.move(player, enemy);
}


int main()
{
	guard player(1);
	guard enemy(0);
	ball  b;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	draw_title(b, player, enemy);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(out, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(out, &structCursorInfo);

	while (!game_over)
	{
		gotoxy(0, 0);
		printf("score-->%d : %d\n", enemy_point, player_point);
		start_time = clock();
		control();
		logic(b, player, enemy);
		if (enemy_point > 10 || player_point > 10) game_over = true;
		end_time = clock();
		frame_time = end_time - start_time;
		if (frame_time < 1000 / fps)  Sleep(1000 / fps - frame_time);
	}
	printf("score-->%d : %d\n", enemy_point, player_point);
	if (enemy_point == 11) printf("Enemy Win!\n");
	else                   printf("Player win!\n");
	system("pause");
}