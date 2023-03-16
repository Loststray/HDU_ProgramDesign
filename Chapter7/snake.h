// PLEASE USE GBK
const int MAP_HEIGHT = 20;
const int MAP_WIDTH = 40;
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
void Topos(const int32_t, const int32_t);
void Help();
void About();
void Options();
void InitMAP();
bool Move_Snake();
void Speed_Control();
void Generate_blocks(const int32_t);
void Generate_Food();
void Generate_Special_Food();
void Hide();
bool bfs(int32_t, int32_t);
int16_t Menu();
