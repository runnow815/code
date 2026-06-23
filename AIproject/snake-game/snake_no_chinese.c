#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_LENGTH 100

// Direction enum
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

// Difficulty enum
enum Difficulty { EASY = 1, MEDIUM, HARD };

// Color definitions
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

// Snake structure
typedef struct {
    int x;
    int y;
} Point;

// Game state structure
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

// Set console color
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Set cursor position
void SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hide cursor
void HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Initialize game
void Setup(GameState *game) {
    game->gameOver = 0;
    game->score = 0;
    game->highScore = 0;
    game->dir = STOP;
    game->difficulty = MEDIUM;
    
    // Set speed based on difficulty
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
    
    // Initialize snake position (center of screen)
    game->length = 3;
    for (int i = 0; i < game->length; i++) {
        game->snake[i].x = WIDTH / 2 - i;
        game->snake[i].y = HEIGHT / 2;
    }
    
    // Generate first food
    srand(time(NULL));
    game->food.x = rand() % WIDTH;
    game->food.y = rand() % HEIGHT;
    
    HideCursor();
}

// Draw game interface
void Draw(GameState *game) {
    system("cls");  // Clear screen
    
    // Draw top border
    SetColor(GREEN);
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    
    // Draw game area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Draw left border
            if (j == 0) {
                SetColor(GREEN);
                printf("#");
            }
            
            // Draw snake head
            if (i == game->snake[0].y && j == game->snake[0].x) {
                SetColor(RED);
                printf("O");
            }
            // Draw food
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
            
            // Draw right border
            if (j == WIDTH - 1) {
                SetColor(GREEN);
                printf("#");
            }
        }
        printf("\n");
    }
    
    // Draw bottom border
    SetColor(GREEN);
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    
    // Display game info
    SetColor(CYAN);
    printf("Score: %d", game->score);
    printf("\tHigh Score: %d", game->highScore);
    printf("\tDifficulty: ");
    
    switch (game->difficulty) {
        case EASY:
            SetColor(GREEN);
            printf("Easy");
            break;
        case MEDIUM:
            SetColor(YELLOW);
            printf("Medium");
            break;
        case HARD:
            SetColor(RED);
            printf("Hard");
            break;
    }
    
    SetColor(WHITE);
    printf("\nControls: W-Up S-Down A-Left D-Right | P-Pause | X-Exit\n");
}

// Handle input
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
                // Pause function
                SetColor(YELLOW);
                printf("\nGame Paused. Press any key to continue...");
                _getch();
                break;
            case 'x': case 'X':
                game->gameOver = 1;
                break;
        }
    }
}

// Game logic
void Logic(GameState *game) {
    if (game->dir == STOP) return;
    
    // Save tail position
    Point prevTail = game->snake[game->length - 1];
    
    // Move snake body (update positions from tail)
    for (int i = game->length - 1; i > 0; i--) {
        game->snake[i] = game->snake[i - 1];
    }
    
    // Move snake head
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
    
    // Check if food is eaten
    if (game->snake[0].x == game->food.x && game->snake[0].y == game->food.y) {
        game->score += 10;
        
        // Update high score
        if (game->score > game->highScore) {
            game->highScore = game->score;
        }
        
        // Increase snake length
        if (game->length < MAX_LENGTH) {
            game->snake[game->length] = prevTail;
            game->length++;
        }
        
        // Generate new food
        int validFood = 0;
        while (!validFood) {
            game->food.x = rand() % WIDTH;
            game->food.y = rand() % HEIGHT;
            
            validFood = 1;
            // Ensure food doesn't spawn on snake
            for (int i = 0; i < game->length; i++) {
                if (game->snake[i].x == game->food.x && game->snake[i].y == game->food.y) {
                    validFood = 0;
                    break;
                }
            }
        }
    }
    
    // Check wall collision
    if (game->snake[0].x >= WIDTH || game->snake[0].x < 0 || 
        game->snake[0].y >= HEIGHT || game->snake[0].y < 0) {
        game->gameOver = 1;
    }
    
    // Check self collision
    for (int i = 1; i < game->length; i++) {
        if (game->snake[0].x == game->snake[i].x && game->snake[0].y == game->snake[i].y) {
            game->gameOver = 1;
            break;
        }
    }
}

// Show start menu
int ShowMenu() {
    system("cls");
    SetColor(CYAN);
    printf("=== SNAKE GAME ===\n\n");
    
    SetColor(WHITE);
    printf("1. Start Game\n");
    printf("2. Select Difficulty\n");
    printf("3. Exit Game\n\n");
    
    printf("Select (1-3): ");
    
    char choice;
    scanf(" %c", &choice);
    
    return choice - '0';
}

// Select difficulty
void SelectDifficulty(GameState *game) {
    system("cls");
    SetColor(CYAN);
    printf("=== SELECT DIFFICULTY ===\n\n");
    
    SetColor(WHITE);
    printf("1. Easy (Slow)\n");
    printf("2. Medium (Default)\n");
    printf("3. Hard (Fast)\n\n");
    
    printf("Select difficulty (1-3): ");
    
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

// Show game instructions
void ShowInstructions() {
    system("cls");
    SetColor(CYAN);
    printf("=== GAME INSTRUCTIONS ===\n\n");
    
    SetColor(WHITE);
    printf("Controls:\n");
    printf("W / Up Arrow - Move Up\n");
    printf("S / Down Arrow - Move Down\n");
    printf("A / Left Arrow - Move Left\n");
    printf("D / Right Arrow - Move Right\n");
    printf("P - Pause Game\n");
    printf("X - Exit Game\n\n");
    
    printf("Game Rules:\n");
    printf("- Control the snake to eat food (F)\n");
    printf("- Each food gives 10 points\n");
    printf("- Snake grows longer\n");
    printf("- Game over if you hit wall or yourself\n\n");
    
    printf("Press any key to continue...");
    _getch();
}

int main() {
    GameState game;
    int menuChoice;
    
    do {
        menuChoice = ShowMenu();
        
        switch (menuChoice) {
            case 1:
                Setup(&game);
                
                // Show game instructions
                ShowInstructions();
                
                while (!game.gameOver) {
                    Draw(&game);
                    Input(&game);
                    Logic(&game);
                    Sleep(game.speed);  // Control game speed
                }
                
                system("cls");
                SetColor(RED);
                printf("=== GAME OVER ===\n\n");
                SetColor(WHITE);
                printf("Final Score: %d\n", game.score);
                printf("High Score: %d\n", game.highScore);
                printf("\nPress any key to return to menu...\n");
                _getch();
                break;
                
            case 2:
                SelectDifficulty(&game);
                break;
                
            case 3:
                printf("\nThanks for playing!\n");
                break;
                
            default:
                printf("\nInvalid selection, please try again!\n");
                Sleep(1000);
                break;
        }
    } while (menuChoice != 3);
    
    return 0;
}