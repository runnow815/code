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

// 蛇的结构体
typedef struct {
    int x;
    int y;
} Point;

// 游戏状态结构体
typedef struct {
    int gameOver;
    int score;
    enum Direction dir;
    Point snake[MAX_LENGTH];
    int length;
    Point food;
} GameState;

// 初始化游戏
void Setup(GameState *game) {
    game->gameOver = 0;
    game->score = 0;
    game->dir = STOP;
    
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
}

// 绘制游戏界面
void Draw(GameState *game) {
    system("cls");  // 清屏
    
    // 绘制上边界
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    
    // 绘制游戏区域
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // 绘制左边界
            if (j == 0)
                printf("#");
            
            // 绘制蛇头
            if (i == game->snake[0].y && j == game->snake[0].x)
                printf("O");
            // 绘制蛇身
            else if (i == game->food.y && j == game->food.x)
                printf("F");
            else {
                int isBodyPart = 0;
                for (int k = 1; k < game->length; k++) {
                    if (game->snake[k].x == j && game->snake[k].y == i) {
                        printf("o");
                        isBodyPart = 1;
                        break;
                    }
                }
                if (!isBodyPart)
                    printf(" ");
            }
            
            // 绘制右边界
            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }
    
    // 绘制下边界
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    
    // 显示分数
    printf("得分: %d\n", game->score);
    printf("按 'x' 退出游戏\n");
}

// 处理输入
void Input(GameState *game) {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (game->dir != RIGHT) game->dir = LEFT;
                break;
            case 'd':
                if (game->dir != LEFT) game->dir = RIGHT;
                break;
            case 'w':
                if (game->dir != DOWN) game->dir = UP;
                break;
            case 's':
                if (game->dir != UP) game->dir = DOWN;
                break;
            case 'x':
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

int main() {
    GameState game;
    Setup(&game);
    
    printf("=== 贪吃蛇游戏 ===\n");
    printf("控制说明：\n");
    printf("W - 向上\n");
    printf("S - 向下\n");
    printf("A - 向左\n");
    printf("D - 向右\n");
    printf("X - 退出游戏\n");
    printf("按任意键开始游戏...\n");
    _getch();
    
    while (!game.gameOver) {
        Draw(&game);
        Input(&game);
        Logic(&game);
        Sleep(100);  // 控制游戏速度
    }
    
    system("cls");
    printf("=== 游戏结束 ===\n");
    printf("最终得分: %d\n", game.score);
    printf("按任意键退出...\n");
    _getch();
    
    return 0;
}