// Управление "Змейкой" осуществляется при помощи клавиш W, A, S, D
// Для начала игры нужно нажать на одну из клавиш
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 25

// Переменные игры
int gameOver;              // Флаг окончания игры
int snakeX, snakeY;       // Координаты головы змеи
int fruitX, fruitY;       // Координаты фрукта
int tailX[200], tailY[200]; // Массивы для хранения координат хвоста змеи
int tailLength;           // Длина хвоста змеи
int speed = 200;          // Начальная скорость игры

// Направления движения
enum eDirection {
    STOP = 0, LEFT, RIGHT, UP, DOWN
};

enum eDirection direction; // Текущая направление движения змеи

// Функция для инициализации игры
void Setup() {
    gameOver = 0;                       // Игра не окончена
    direction = STOP;                   // Направление остановлено
    snakeX = WIDTH / 2;                 // Установка начальной позиции головы змеи по X
    snakeY = HEIGHT / 2;                // Установка начальной позиции головы змеи по Y
    fruitX = rand() % WIDTH;            // Генерация случайной позиции фрукта по X
    fruitY = rand() % HEIGHT;           // Генерация случайной позиции фрукта по Y
    tailLength = 0;                     // Начальная длина хвоста
}

// Функция для отрисовки игрового поля
void Draw(HANDLE hConsole) {
    COORD cursorPos = {0, 0};           // Позиция курсора
    SetConsoleCursorPosition(hConsole, cursorPos); // Установка курсора в начало

    printf("  ");
    for (int i = 0; i < WIDTH; i++) printf("#"); // Отрисовка верхней границы
    printf("\n");

    // Отрисовка игрового поля
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#"); // Отрисовка левой границы

            // Отрисовка головы змеи
            if (i == snakeY && j == snakeX)
                printf("O");
            // Отрисовка фрукта
            else if (i == fruitY && j == fruitX)
                printf("F");
            else {
                int print = 0;
                // Отрисовка хвоста змеи
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print)
                    printf(" "); // Пустое пространство
            }

            if (j == WIDTH - 1)
                printf("#"); // Отрисовка правой границы
        }
        printf("\n");
    }
    // Отрисовка нижней границы
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
}

// Функция для обработки ввода
void Input() {
    if (_kbhit()) { // Если нажата клавиша
        switch (_getch()) {
            case 'a': // Влево
                if (direction != RIGHT) direction = LEFT;
                break;
            case 'd': // Вправо
                if (direction != LEFT) direction = RIGHT;
                break;
            case 'w': // Вверх
                if (direction != DOWN) direction = UP;
                break;
            case 's': // Вниз
                if (direction != UP) direction = DOWN;
                break;
        }
    }
}

// Функция для логики игры
void Logic() {
    int prevX = tailX[0]; // Предыдущая позиция X хвоста
    int prevY = tailY[0]; // Предыдущая позиция Y хвоста
    int prev2X, prev2Y;   // Вторая предыдущая позиция для хвоста
    tailX[0] = snakeX;    // Обновление позиции хвоста
    tailY[0] = snakeY;

    // Обновление позиций хвоста
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Обработка движения змеи
    switch (direction) {
        case LEFT:
            snakeX--;
            break;
        case RIGHT:
            snakeX++;
            break;
        case UP:
            snakeY--;
            break;
        case DOWN:
            snakeY++;
            break;
    }

    // Проверка на столкновение с границей
    if (snakeX >= WIDTH || snakeX < 0 || snakeY >= HEIGHT || snakeY < 0)
        gameOver = 1;

    // Проверка на столкновение с хвостом
    for (int i = 0; i < tailLength; i++)
        if (tailX[i] == snakeX && tailY[i] == snakeY)
            gameOver = 1;

    // Проверка на поедание фрукта
    if (snakeX == fruitX && snakeY == fruitY) {
        fruitX = rand() % WIDTH; // Генерация новой позиции фрукта
        fruitY = rand() % HEIGHT;
        tailLength++; // Увеличение длины хвоста
        if (speed > 10) speed -= 10; // Увеличение скорости игры
    }
}

// Главная функция
int main(int argc, char *argv[]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Setup(); // Инициализация игры
    while (!gameOver) {
        Draw(hConsole);
        Input();
        Logic();
        Sleep(speed); // Задержка
    }
    printf("\n");
    printf("Game Over\n"); // Сообщение об окончании игры
    return 0;
}
