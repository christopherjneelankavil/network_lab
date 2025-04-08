#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#define WIDTH 40
#define HEIGHT 20
#define SNAKE_MAX_LENGTH 100

// Direction enumeration
enum Direction {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Snake structure
struct Snake {
    int x[SNAKE_MAX_LENGTH];
    int y[SNAKE_MAX_LENGTH];
    int length;
    enum Direction dir;
};

// Game state
struct GameState {
    struct Snake snake;
    int fruitX;
    int fruitY;
    int score;
    bool gameOver;
};

// Function prototypes
void setup(struct GameState *game);
void draw(struct GameState *game);
void input(struct GameState *game);
void logic(struct GameState *game);
void gotoxy(int x, int y);
void hideCursor();
void showCursor();

int main() {
    struct GameState game;
    
    // Hide the cursor for better gameplay
    hideCursor();
    
    // Initialize the game
    setup(&game);
    
    // Main game loop
    while (!game.gameOver) {
        draw(&game);
        input(&game);
        logic(&game);
        Sleep(100); // Control game speed
    }
    
    // Show the cursor again
    showCursor();
    
    // Game over message
    gotoxy(WIDTH / 2 - 5, HEIGHT / 2);
    printf("Game Over!");
    gotoxy(WIDTH / 2 - 10, HEIGHT / 2 + 1);
    printf("Final Score: %d", game.score);
    gotoxy(0, HEIGHT + 2);
    
    return 0;
}

void setup(struct GameState *game) {
    // Initialize snake
    game->snake.length = 1;
    game->snake.x[0] = WIDTH / 2;
    game->snake.y[0] = HEIGHT / 2;
    game->snake.dir = STOP;
    
    // Initialize fruit position
    game->fruitX = rand() % (WIDTH - 2) + 1;
    game->fruitY = rand() % (HEIGHT - 2) + 1;
    
    // Initialize score
    game->score = 0;
    
    // Game is not over
    game->gameOver = false;
}

void draw(struct GameState *game) {
    // Clear the screen
    system("cls");
    
    // Draw top wall
    for (int i = 0; i < WIDTH; i++) {
        gotoxy(i, 0);
        printf("#");
    }
    
    // Draw bottom wall
    for (int i = 0; i < WIDTH; i++) {
        gotoxy(i, HEIGHT - 1);
        printf("#");
    }
    
    // Draw left wall
    for (int i = 0; i < HEIGHT; i++) {
        gotoxy(0, i);
        printf("#");
    }
    
    // Draw right wall
    for (int i = 0; i < HEIGHT; i++) {
        gotoxy(WIDTH - 1, i);
        printf("#");
    }
    
    // Draw snake
    for (int i = 0; i < game->snake.length; i++) {
        gotoxy(game->snake.x[i], game->snake.y[i]);
        if (i == 0) {
            printf("O"); // Head
        } else {
            printf("o"); // Body
        }
    }
    
    // Draw fruit
    gotoxy(game->fruitX, game->fruitY);
    printf("*");
    
    // Draw score
    gotoxy(WIDTH + 2, 2);
    printf("Score: %d", game->score);
}

void input(struct GameState *game) {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (game->snake.dir != RIGHT) {
                    game->snake.dir = LEFT;
                }
                break;
            case 'd':
                if (game->snake.dir != LEFT) {
                    game->snake.dir = RIGHT;
                }
                break;
            case 'w':
                if (game->snake.dir != DOWN) {
                    game->snake.dir = UP;
                }
                break;
            case 's':
                if (game->snake.dir != UP) {
                    game->snake.dir = DOWN;
                }
                break;
            case 'x':
                game->gameOver = true;
                break;
        }
    }
}

void logic(struct GameState *game) {
    // Save previous positions
    int prevX = game->snake.x[0];
    int prevY = game->snake.y[0];
    int prev2X, prev2Y;
    
    // Move head
    switch (game->snake.dir) {
        case LEFT:
            game->snake.x[0]--;
            break;
        case RIGHT:
            game->snake.x[0]++;
            break;
        case UP:
            game->snake.y[0]--;
            break;
        case DOWN:
            game->snake.y[0]++;
            break;
        default:
            break;
    }
    
    // Move body
    for (int i = 1; i < game->snake.length; i++) {
        prev2X = game->snake.x[i];
        prev2Y = game->snake.y[i];
        game->snake.x[i] = prevX;
        game->snake.y[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    // Check for collision with walls
    if (game->snake.x[0] <= 0 || game->snake.x[0] >= WIDTH - 1 ||
        game->snake.y[0] <= 0 || game->snake.y[0] >= HEIGHT - 1) {
        game->gameOver = true;
    }
    
    // Check for collision with self
    for (int i = 1; i < game->snake.length; i++) {
        if (game->snake.x[0] == game->snake.x[i] && game->snake.y[0] == game->snake.y[i]) {
            game->gameOver = true;
        }
    }
    
    // Check if snake ate the fruit
    if (game->snake.x[0] == game->fruitX && game->snake.y[0] == game->fruitY) {
        game->score += 10;
        game->snake.length++;
        
        // Generate new fruit position
        game->fruitX = rand() % (WIDTH - 2) + 1;
        game->fruitY = rand() % (HEIGHT - 2) + 1;
        
        // Make sure fruit doesn't appear on snake
        for (int i = 0; i < game->snake.length; i++) {
            if (game->fruitX == game->snake.x[i] && game->fruitY == game->snake.y[i]) {
                game->fruitX = rand() % (WIDTH - 2) + 1;
                game->fruitY = rand() % (HEIGHT - 2) + 1;
                i = -1; // Restart the loop
            }
        }
    }
}

// Utility functions
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
} 