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
    char dir = 'D';
    std::deque<pos> q;
    SNAKE(int s,int l) { speed = s,len = l; }
    bool push_pos(int x,int y)
    {
        if (G[x][y] == 1)
            return false;
        auto pre = q.back();
        Topos(pre.first,pre.second);
        std::cout << 'o';
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
    std::ios::sync_with_stdio(0);
    srand((uint32_t) time(0));
    while(1)
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
    std::cout << "test1";
    Topos(43,14);
    std::cout << "1.";
    Topos(43,16);
    std::cout << "2.";
    Topos(43,18);
    std::cout << "3.";
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
    s.push_pos(x,y);
    for(int32_t i =0 ;i < MAP_WIDTH; i++)
    {
        Topos(0,i);
        std::cout << '-';
        Topos(MAP_HEIGHT,i);
        std::cout << '-';
    }
    for(int32_t i = 0;i < MAP_HEIGHT - 1;i++)
    {
        Topos(i,0);
        std::cout << '|';
        Topos(i,MAP_WIDTH);
        std::cout << '|';
    }
    Generate_Food();
    Topos(5,50);
    std::cout << "SCORE : ";
}
void Speed_Control()
{

}
bool Move_Snake()
{
    int32_t x = s.q.front().first,y = s.q.front().second;
    auto tail = s.q.back();
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
            x--;
            break;
        case DOWN:
            x++;
            break;
        case RIGHT:
            y++;
            break;
        case LEFT:
            y--;
            break;
        default:
            break;
    }
    if (!s.push_pos(x,y))
    {
        system("cls");
        std::cout << "FIN";
    }
}
