// PLEASE USE GBK
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <random>
#include <chrono>
#include "snake.h"

typedef std::pair<int32_t, int32_t> pos;
int32_t G[MAP_WIDTH + 2][MAP_HEIGHT + 2], step = 0; // 0 = empty 1 = Snakebody 2 or greater is value of food,use a graph to save data
pos Special_Food;
const std::string difficulty_setting[10] = { "Easy","Normal","Hard","WHATISTHIS" };
int32_t dif = 1, Difficult_Modifier = 20,Blocks = 5;
bool EASYMODE = 0;
bool BFS_vis[MAP_WIDTH + 2][MAP_HEIGHT + 2];
const int32_t direction[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count()); // 梅森旋转算法伪随机数生成器
std::uniform_int_distribution<uint64_t> dist(0, ULLONG_MAX); // 均匀化随机数
class LeaderBoard //附加功能4 排行榜类
{
private:
	struct node
	{
		std::string name;
		int val;
		node(std::string a, int b) { name = a, val = b; }
		bool operator<(const node& b) const 
		{
			if (val == b.val)
				return name < b.name;
			return val > b.val;
		}
	};
	std::vector<node> LB;
public:
	LeaderBoard(void)
	{
		//fillsth;
		LB.emplace_back( "野兽先辈",514 );
		LB.emplace_back( "田所浩二",114 );
		LB.emplace_back( "flfl",666);
		LB.emplace_back( "麦克阿瑟",42);
		LB.emplace_back( "Fiatiustitia",999 );
	}
	void ReadScore(int score,std::string &name)
	{
		LB.emplace_back(name,score);
	}
	void PrintBoard()
	{
		std::sort(LB.begin(), LB.end());
		for (int32_t i = 0; i < min(LB.size(),10); i++)
		{
			Topos(20, 10 + i * 2);
			std::cout << i + 1;
			Topos(22, 10 + i * 2);
			std::cout << LB[i].name;
			Topos(37, 10 + i * 2);
			std::cout << LB[i].val;
		}
	}
}Board;

class SNAKE
{
public:
	int32_t speed, len, Special_Food_cnt;
	char dir = 'd';
	std::deque<pos> q; //特色功能5 双端队列维护蛇，实现更优时间和空间复杂度

	SNAKE(int s, int l) { speed = s, len = l, Special_Food_cnt = 0; }

	void init()//初始化
	{
		len = 3;
		while (!q.empty())
			q.pop_front();
		Special_Food_cnt = 0;
		dir = 'd';
	}

	bool push_pos(int32_t& x, int32_t& y) //返回蛇的移动操作是否合法
	{
		if (G[x][y] == 1) // 撞到蛇身体
		{
			if (!EASYMODE)
				return false;
			while (q.front().first != x || q.front().second != y) //附加功能1 撞到蛇身截断
			{
				int xx = q.front().first, yy = q.front().second;
				G[xx][yy] = 0;
				Topos(xx, yy);
				std::cout << ' ';
				q.pop_front();
				len--;
			}
			G[x][y] = 1;
			Topos(x, y);
			std::cout << '@';
			q.pop_front();
			len--;
		}
		if (x == 0 || x == MAP_WIDTH || y == 0 || y == MAP_HEIGHT) //特色功能1 简单模式地图循环
		{
			if (EASYMODE)
			{
				if (x == 0)
					x = MAP_WIDTH - 1;
				if (x == MAP_WIDTH)
					x = 1;
				if (y == 0)
					y = MAP_HEIGHT - 1;
				if (y == MAP_HEIGHT)
					y = 1;
			}
			else
				return false;
		}
		if (!q.empty()) //蛇头前一节处理
		{
			auto &pre = q.back();
			Topos(pre.first, pre.second);
			std::cout << 'o';
		}
		q.emplace_back(x, y);
		if (G[x][y] > 1) //食物处理
		{
			len += G[x][y] - 1;
			Special_Food_cnt++;
			if (Special_Food_cnt % 2 == 0)
				Generate_Special_Food();
			if (G[x][y] <= 2)
				Generate_Food();
		}
		G[x][y] = 1;
		Topos(x, y);
		std::cout << '@';
		if (q.size() > len) // 长度超出处理
		{
			auto &tail = q.front();
			G[tail.first][tail.second] = 0;
			Topos(tail.first, tail.second);
			std::cout << ' ';
			q.pop_front();
		}
		return true;
	}

} s(250, 3);

int main()
{
	//std::ios::sync_with_stdio(false);
	while (true)
	{
		int16_t res = Menu();
		switch (res)
		{
		case 1:InitMAP();
			while (Move_Snake());
			break;
		case 2:Help();
			break;
		case 3:About();
			break;
		case 4:
			Options();
			break;
		default:exit(0);
		}
	}
}

void Topos(const int32_t x, const int32_t y) //将光标设定到指定位置
{
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPosition = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(stdHandle, cursorPosition);
}

void Hide() // 隐藏光标
{
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CurInfo = { 1, 0 };
	SetConsoleCursorInfo(stdHandle, &CurInfo);
}

int16_t Menu()
{
	Topos(40, 12);
	std::cout << "我超贪吃蛇";
	Topos(43, 14);
	std::cout << "1.开始游戏";
	Topos(43, 16);
	std::cout << "2.帮助";
	Topos(43, 18);
	std::cout << "3.关于";
	Topos(43, 20);
	std::cout << "4.设置";
	Topos(43, 22);
	std::cout << "5.退出";
	Hide();
	char ch = _getch();
	system("cls");
	return ch - '0';
}

void About()
{
	Topos(40, 12);
	std::cout << "游戏后续内容等待开发者更新！";
	Hide();
	char ch;
	ch = _getch();
	system("cls");
}

void Help()
{
	Topos(40, 12);
	std::cout << "帮助：通过键盘W、A、S、D操纵蛇上、左、下、右移动";
	Topos(40, 14);
	std::cout << "游戏分为简单、中等、困难、地狱模式";
	Topos(40, 16);
	std::cout << "简单模式下蛇撞到墙会从另一边穿出，同时自撞只截断撞到的蛇尾";
	Topos(40, 18);
	std::cout << "其余模式随难度增加速度与障碍物数量";
	Hide();
	char ch;
	ch = _getch();
	system("cls");
}
void Options()
{
	Topos(40, 12);
	std::cout << "难度设置:" << difficulty_setting[dif];
	Topos(40, 14);
	std::wcout << "按esc键退出";
	while(1)
	{
		char tmp = _getch();
		switch (tmp)
		{
		case LEFT:
			if (dif)
				dif--;
			break;
		case RIGHT:
			if (dif < 3)
				dif++;
			break;
		default:
			//do nothing
			break;
		}
		Topos(49, 12);
		std::cout << difficulty_setting[dif] << "              ";
		Difficult_Modifier = dif * 10 + 5;
		Blocks = dif * 5;
		if (!dif)
			EASYMODE = 1;
		else
			EASYMODE = 0;
		if (tmp == 27)
			break;
	}
	system("cls");
}
void Generate_Special_Food()
{
	step = 0;
	while (true)
	{
		int32_t x = dist(rnd) % 21 - 10, y = dist(rnd) % 21 - 10;
		x += s.q.back().first, y += s.q.back().second;
		if (x > 0 && x < MAP_WIDTH && y > 0 && y < MAP_HEIGHT && !G[x][y] && bfs(x, y))
		{
			G[x][y] = 6;
			Special_Food = { x, y };
			Topos(x, y);
			std::cout << '*';
			return;
		}
	}
}

void Generate_Food()
{
	while (true)
	{
		int32_t x = dist(rnd) % (MAP_WIDTH - 2) + 1, y = dist(rnd) % (MAP_HEIGHT - 2) + 1;
		if (!G[x][y] && bfs(x,y))
		{
			G[x][y] = 2;
			Topos(x, y);
			std::cout << 'F';
			return;
		}
	}
}

bool bfs(int32_t x,int32_t y) // 特色功能2，从蛇头开始必定可以到达果实
{
	std::queue<pos> q;
	q.push({ x,y });
	memset(BFS_vis, 0, sizeof(BFS_vis));
	const int32_t tx = s.q.back().first, ty = s.q.back().second;
	while(!q.empty())
	{
		auto u = q.front();
		q.pop();
		for (int i = 0; i <= 3; i++)
		{
			int xx = u.first + direction[i][0],yy = u.second + direction[i][1];
			if (xx == tx && yy == ty)
				return true;
			if (!BFS_vis[xx][yy] && G[xx][yy] != 1 && xx > 0 && xx < MAP_WIDTH && yy > 0 && yy < MAP_HEIGHT)
			{
				BFS_vis[xx][yy] = 1;
				q.push({ xx,yy });
			}
		}
	}
	return false;
}

void Generate_blocks(const int32_t numbers) //附加功能2，在场内随机生成障碍物
{
	for(int32_t i = 1;i <= numbers;i++)
	{
		int32_t x = dist(rnd) % (MAP_WIDTH - 2) + 1,y = dist(rnd) % (MAP_HEIGHT - 2) + 1;
		Topos(x, y);
		std::cout << '#';
		if (!G[x][y])
			G[x][y] = 1;
	}
}

void InitMAP()
{
	Hide();
	memset(G, 0, sizeof(G));
	int32_t x = MAP_WIDTH / 2 + 1, y = MAP_HEIGHT / 2 + 1;
	s.init();
	s.push_pos(x, y);
	for (int32_t i = 0; i <= MAP_HEIGHT; i++)
	{
		Topos(0, i);
		std::cout << '|';
		Topos(MAP_WIDTH, i);
		std::cout << '|';
	}
	for (int32_t i = 1; i <= MAP_WIDTH; i++)
	{
		Topos(i, 0);
		std::cout << '-';
		Topos(i, MAP_HEIGHT);
		std::cout << '-';
	}
	Topos(0, 0);
	std::cout << '+';
	Topos(0, MAP_HEIGHT);
	std::cout << '+';
	Topos(MAP_WIDTH, 0);
	std::cout << '+';
	Topos(MAP_WIDTH, MAP_HEIGHT);
	std::cout << '+';
	if (!EASYMODE)
		Generate_blocks(Blocks);
	Generate_Food();
}

void Speed_Control()
{
	if (240 - (s.len / 3) * Difficult_Modifier > 0)
		s.speed = 250 - (s.len / 3) * Difficult_Modifier;
}

bool Move_Snake()
{
	int32_t x = s.q.back().first, y = s.q.back().second;
	Topos(x, y);
	std::cout << 'o';
	char dir = s.dir;
	if (_kbhit())
	{
		char tmp = _getch();
		switch (tmp)
		{
		case UP:
			if (dir != DOWN)
				dir = tmp;
			break;
		case LEFT:
			if (dir != RIGHT)
				dir = tmp;
			break;
		case RIGHT:
			if (dir != LEFT)
				dir = tmp;
			break;
		case DOWN:
			if (dir != UP)
				dir = tmp;
			break;
		default:
			//??
			break;
		}
	}
	s.dir = dir;
	switch (dir)
	{
	case UP:y--;
		break;
	case DOWN:y++;
		break;
	case RIGHT:x++;
		break;
	case LEFT:x--;
		break;
	default:break;
	}
	char esc = 0;
	if (_kbhit())
		esc = _getch();
	if (!s.push_pos(x, y) || esc == 27 )
	{
		system("cls");
		Topos(45, 14);
		std::cout << "FINAL SCORE:" << s.len - 3;
		Topos(45, 16);
		std::cout << "请输入名字：";
		std::string tmp;
		std::cin >> tmp;
		Board.ReadScore(s.len - 3, tmp);
		Board.PrintBoard();
		char t = _getch();
		system("cls");
		return false;
	}
	Topos(50, 5);
	std::cout << "SCORE :" << s.len - 3;
	if (G[Special_Food.first][Special_Food.second] >= 3) //附加功能3,特色功能3，特殊食物的生成，特色食物分值随蛇走过的步数减少
	{
		step++;
		if (step % 5 == 0)
			G[Special_Food.first][Special_Food.second]--;
		Topos(50, 8);
		std::cout << "特殊果子还有" << 20 - step << "步就要逃走啦 ";
		if (step >= 20)
		{
			Topos(Special_Food.first, Special_Food.second);
			std::cout << ' ';
			Topos(50, 8);
			std::cout << "                                    ";
			G[Special_Food.first][Special_Food.second] = 0;
		}
	}
	else
	{
		Topos(50, 8);
		std::cout << "                                    ";
		step = 0;
	}
	Speed_Control();
	Sleep(s.speed);
	return true;
}
