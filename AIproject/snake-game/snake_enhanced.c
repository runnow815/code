#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_LENGTH 100

// 方向枚举
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

// 游戏难度
enum Difficulty { EASY = 1, MEDIUM, HARD };

// 颜色定义
enum Colors {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8
};

// 蛇的结构体
typedef struct {
    int x;
    int y;
} Point;

// 游戏状态结构体
typedef struct {
    int gameOver;
    int score;
    int highScore;
    enum Direction dir;
    enum Difficulty difficulty;
    Point snake[MAX_LENGTH];
    int length;
    Point food;
    int speed;
} GameState;

// 设置控制台颜色
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 设置光标位置
void SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 隐藏光标
void HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 设置控制台编码为UTF-8
void SetConsoleEncoding() {
    system("chcp 65001 > nul");
    SetConsoleOutputCP(65001);
}

// 初始化游戏
void Setup(GameState *game) {
    game->gameOver = 0;
    game->score = 0;
    game->highScore = 0;
    game->dir = STOP;
    game->difficulty = MEDIUM;
    
    // 根据难度设置速度
    switch (game->difficulty) {
        case EASY:
            game->speed = 150;
            break;
        case MEDIUM:
            game->speed = 100;
            break;
        case HARD:
            game->speed = 50;
            break;
    }
    
    // 初始化蛇的位置（在屏幕中间）
    game->length = 3;
    for (int i = 0; i < game->length; i++) {
        game->snake[i].x = WIDTH / 2 - i;
        game->snake[i].y = HEIGHT / 2;
    }
    
    // 生成第一个食物
    srand(time(NULL));
    game->food.x = rand() % WIDTH;
    game->food.y = rand() % HEIGHT;
    
    HideCursor();
}

// 绘制游戏界面
void Draw(GameState *game) {
    system("cls");  // 清屏
    
    // 绘制上边界
    SetColor(GREEN);
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    
    // 绘制游戏区域
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // 绘制左边界
            if (j == 0) {
                SetColor(GREEN);
                printf("#");
            }
            
            // 绘制蛇头
            if (i == game->snake[0].y && j == game->snake[0].x) {
                SetColor(RED);
                printf("O");
            }
            // 绘制食物
            else if (i == game->food.y && j == game->food.x) {
                SetColor(YELLOW);
                printf("F");
            }
            else {
                int isBodyPart = 0;
                for (int k = 1; k < game->length; k++) {
                    if (game->snake[k].x == j && game->snake[k].y == i) {
                        SetColor(GREEN);
                        printf("o");
                        isBodyPart = 1;
                        break;
                    }
                }
                if (!isBodyPart) {
                    SetColor(WHITE);
                    printf(" ");
                }
            }
            
            // 绘制右边界
            if (j == WIDTH - 1) {
                SetColor(GREEN);
                printf("#");
            }
        }
        printf("\n");
    }
    
    // 绘制下边界
    SetColor(GREEN);
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    
    // 显示游戏信息
    SetColor(CYAN);
    printf("得分: %d", game->score);
    printf("\t最高分: %d", game->highScore);
    printf("\t难度: ");
    
    switch (game->difficulty) {
        case EASY:
            SetColor(GREEN);
            printf("简单");
            break;
        case MEDIUM:
            SetColor(YELLOW);
            printf("中等");
            break;
        case HARD:
            SetColor(RED);
            printf("困难");
            break;
    }
    
    SetColor(WHITE);
    printf("\n控制: W-上 S-下 A-左 D-右 | P-暂停 | X-退出\n");
}

// 处理输入
void Input(GameState *game) {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'a': case 'A':
                if (game->dir != RIGHT) game->dir = LEFT;
                break;
            case 'd': case 'D':
                if (game->dir != LEFT) game->dir = RIGHT;
                break;
            case 'w': case 'W':
                if (game->dir != DOWN) game->dir = UP;
                break;
            case 's': case 'S':
                if (game->dir != UP) game->dir = DOWN;
                break;
            case 'p': case 'P':
                // 暂停功能
                SetColor(YELLOW);
                printf("\n游戏暂停，按任意键继续...");
                _getch();
                break;
            case 'x': case 'X':
                game->gameOver = 1;
                break;
        }
    }
}

// 游戏逻辑
void Logic(GameState *game) {
    if (game->dir == STOP) return;
    
    // 保存蛇尾位置
    Point prevTail = game->snake[game->length - 1];
    
    // 移动蛇身（从尾部开始更新位置）
    for (int i = game->length - 1; i > 0; i--) {
        game->snake[i] = game->snake[i - 1];
    }
    
    // 移动蛇头
    switch (game->dir) {
        case LEFT:
            game->snake[0].x--;
            break;
        case RIGHT:
            game->snake[0].x++;
            break;
        case UP:
            game->snake[0].y--;
            break;
        case DOWN:
            game->snake[0].y++;
            break;
    }
    
    // 检查是否吃到食物
    if (game->snake[0].x == game->food.x && game->snake[0].y == game->food.y) {
        game->score += 10;
        
        // 更新最高分
        if (game->score > game->highScore) {
            game->highScore = game->score;
        }
        
        // 增加蛇的长度
        if (game->length < MAX_LENGTH) {
            game->snake[game->length] = prevTail;
            game->length++;
        }
        
        // 生成新食物
        int validFood = 0;
        while (!validFood) {
            game->food.x = rand() % WIDTH;
            game->food.y = rand() % HEIGHT;
            
            validFood = 1;
            // 确保食物不会生成在蛇身上
            for (int i = 0; i < game->length; i++) {
                if (game->snake[i].x == game->food.x && game->snake[i].y == game->food.y) {
                    validFood = 0;
                    break;
                }
            }
        }
    }
    
    // 检查是否撞墙
    if (game->snake[0].x >= WIDTH || game->snake[0].x < 0 || 
        game->snake[0].y >= HEIGHT || game->snake[0].y < 0) {
        game->gameOver = 1;
    }
    
    // 检查是否撞到自己
    for (int i = 1; i < game->length; i++) {
        if (game->snake[0].x == game->snake[i].x && game->snake[0].y == game->snake[i].y) {
            game->gameOver = 1;
            break;
        }
    }
}

// 显示开始菜单
int ShowMenu() {
    system("cls");
    SetColor(CYAN);
    printf("=== 贪吃蛇游戏 ===\n\n");
    
    SetColor(WHITE);
    printf("1. 开始游戏\n");
    printf("2. 选择难度\n");
    printf("3. 退出游戏\n\n");
    
    printf("请选择 (1-3): ");
    
    char choice;
    scanf(" %c", &choice);
    
    return choice - '0';
}

// 选择难度
void SelectDifficulty(GameState *game) {
    system("cls");
    SetColor(CYAN);
    printf("=== 选择难度 ===\n\n");
    
    SetColor(WHITE);
    printf("1. 简单 (速度慢)\n");
    printf("2. 中等 (默认)\n");
    printf("3. 困难 (速度快)\n\n");
    
    printf("请选择难度 (1-3): ");
    
    char choice;
    scanf(" %c", &choice);
    
    switch (choice) {
        case '1':
            game->difficulty = EASY;
            game->speed = 150;
            break;
        case '2':
            game->difficulty = MEDIUM;
            game->speed = 100;
            break;
        case '3':
            game->difficulty = HARD;
            game->speed = 50;
            break;
        default:
            game->difficulty = MEDIUM;
            game->speed = 100;
            break;
    }
}

// 显示游戏说明
void ShowInstructions() {
    system("cls");
    SetColor(CYAN);
    printf("=== 游戏说明 ===\n\n");
    
    SetColor(WHITE);
    printf("控制键:\n");
    printf("W / ↑ - 向上移动\n");
    printf("S / ↓ - 向下移动\n");
    printf("A / ← - 向左移动\n");
    printf("D / → - 向右移动\n");
    printf("P - 暂停游戏\n");
    printf("X - 退出游戏\n\n");
    
    printf("游戏规则:\n");
    printf("- 控制蛇吃掉食物(F)\n");
    printf("- 每吃一个食物得10分\n");
    printf("- 蛇会变长\n");
    printf("- 撞墙或撞到自己游戏结束\n\n");
    
    printf("按任意键返回...");
    _getch();
}

int main() {
    // 设置控制台编码为UTF-8，解决中文乱码问题
    SetConsoleEncoding();
    
    GameState game;
    int menuChoice;
    
    do {
        menuChoice = ShowMenu();
        
        switch (menuChoice) {
            case 1:
                Setup(&game);
                
                // 显示游戏说明
                ShowInstructions();
                
                while (!game.gameOver) {
                    Draw(&game);
                    Input(&game);
                    Logic(&game);
                    Sleep(game.speed);  // 控制游戏速度
                }
                
                system("cls");
                SetColor(RED);
                printf("=== 游戏结束 ===\n\n");
                SetColor(WHITE);
                printf("最终得分: %d\n", game.score);
                printf("最高分: %d\n", game.highScore);
                printf("\n按任意键返回主菜单...\n");
                _getch();
                break;
                
            case 2:
                SelectDifficulty(&game);
                break;
                
            case 3:
                printf("\n感谢游戏！\n");
                break;
                
            default:
                printf("\n无效选择，请重新选择！\n");
                Sleep(1000);
                break;
        }
    } while (menuChoice != 3);
    
    return 0;
}