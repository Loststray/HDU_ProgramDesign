#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "snake.h"
typedef std::pair<int32_t ,int32_t > pos;
int32_t G[MAP_HEIGHT + 2][MAP_WIDTH + 2];
class SNAKE
{
public:
    int32_t speed,len;
    char dir = 'd';
    std::deque<pos> q;
    SNAKE(int s,int l) { speed = s,len = l; }
    void init()
    {
        len = 3;
        while(!q.empty())
            q.pop_front();
        dir = 'd';
    }
    bool push_pos(int x,int y)
    {
        if (G[x][y] == 1 || x <= 0 || x >= MAP_WIDTH || y <= 0 || y >= MAP_HEIGHT)
            return false;
        if (q.size())
        {
            auto pre = q.back();
            Topos(pre.first,pre.second);
            std::cout << 'o';
        }
        q.emplace_back(x,y);
        if (G[x][y])
        {
            G[x][y] = 1;
            Topos(x,y);
            std::cout << '@';
            len++;
            Generate_Food();
        }
        else
        {
            G[x][y] = 1;
            Topos(x,y);
            std::cout << '@';
        }
        if (q.size() > len)
        {
            auto tail = q.front();
            G[tail.first][tail.second] = 0;
            Topos(tail.first,tail.second);
            std::cout << ' ';
            q.pop_front();
        }
        return true;
    }

}s(250,3);
int main() {
    //std::ios::sync_with_stdio(false);
    srand((uint32_t) time(nullptr));
    while(true)
    {
        int16_t res = Menu();
        switch (res)
        {
            case 1:
                InitMAP();
                while(Move_Snake());
                break;
            case 2:
                Help();
                break;
            case 3:
                About();
                break;
            default:
                exit(0);
        }
    }
}
void Topos(const int16_t x,const int16_t y)
{
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = {x, y};
    SetConsoleCursorPosition(stdHandle, cursorPosition);
}
void Hide()
{
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CurInfo = {1,0};
    SetConsoleCursorInfo(stdHandle, &CurInfo);
}
int16_t Menu()
{
    Topos(40,12);
    std::cout << "我超贪吃蛇";
    Topos(43,14);
    std::cout << "1.开始游戏";
    Topos(43,16);
    std::cout << "2.帮助";
    Topos(43,18);
    std::cout << "3.关于";
    Topos(43,20);
    std::cout << "4.";
    Hide();
    char ch = _getch();
    system("cls");
    return ch - '0';
}
void About()
{
    Topos(40,12);
    std::cout << "test2";
    Hide();
    char ch;
    ch = _getch();
    system("cls");
}
void Help()
{
    Topos(40,12);
    std::cout << "test3";
    Hide();
    char ch;
    ch = _getch();
    system("cls");
}
void Generate_Food()
{
    while(true)
    {
        int32_t x = rand() % (MAP_HEIGHT - 2) + 1, y = rand() % (MAP_WIDTH - 2) + 1;
        if (!G[x][y])
        {
            G[x][y] = 2;
            Topos(x,y);
            std::cout << 'F';
            return ;
        }
    }
}
void InitMAP()
{
    Hide();
    memset(G,0,sizeof(G));
    int32_t x = MAP_HEIGHT / 2 + 1 , y = MAP_WIDTH / 2 + 1;
    s.init();
    s.push_pos(x,y);
    for(int32_t i = 0 ;i < MAP_WIDTH; i++)
    {
        Topos(0,i);
        std::cout << '|';
        Topos(MAP_HEIGHT,i);
        std::cout << '|';
    }
    for(int32_t i = 1;i < MAP_HEIGHT;i++)
    {
        Topos(i,0);
        std::cout << '-';
        Topos(i,MAP_WIDTH);
        std::cout << '-';
    }
    Generate_Food();
    Topos(5,40);
    std::cout << "SCORE : ";
}
void Speed_Control()
{
    if (s.len <= 30)
    s.speed = 240 - (s.len / 3) * 20;
}
bool Move_Snake()
{
    int32_t x = s.q.back().first,y = s.q.back().second;
    Topos(x,y);
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
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case RIGHT:
            x++;
            break;
        case LEFT:
            x--;
            break;
        default:
            break;
    }
    if (!s.push_pos(x,y))
    {
        system("cls");
        Topos(45,14);
        std::cout << "FINAL SCORE:" << s.len - 3;
        Topos(45,16);
        std::cout << "ded";
        char tmp = _getch();
        system("cls");
        return false;
    }
    Topos(40,5);
    std::cout << "SCORE :" << s.len - 3;
    Speed_Control();
    Sleep(s.speed);
    return true;
}
