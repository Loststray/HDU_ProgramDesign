const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 30;
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
int16_t Menu();
void Topos(int ,int);
void Help();
void About();
void InitMAP();
bool Move_Snake();
bool Check();
void Speed_Control();
void Generate_Food();
void Hide();
