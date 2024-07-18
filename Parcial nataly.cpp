#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int width = 40;
const int height = 20;
int x, y; // Posición de la nave
int enemyX, enemyY; // Posición del enemigo
int score = 0;
int lives = 3; // Vidas del jugador

bool gameOver;

enum eDirection { STOP = 0, LEFT, RIGHT };
eDirection dir;

struct Bullet {
    int x, y;
    bool active;
};

Bullet bullet;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height - 1;
    enemyX = rand() % width;
    enemyY = 0;
    bullet.active = false;
    score = 0; // Reiniciar el puntaje
    lives = 3; // Reiniciar las vidas
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";

            if (i == y && j == x)
                cout << "N"; // Caracter que representa la nave
            else if (i == enemyY && j == enemyX)
                cout << "%"; // Caracter que representa al enemigo
            else if (bullet.active && i == bullet.y && j == bullet.x)
                cout << "|"; // Caracter que representa el disparo
            else
                cout << " ";

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << "   Lives: " << lives << endl;
    cout << "Press 'r' to restart" << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case ' ':
            // Disparar cuando se presiona la tecla de espacio
            bullet.active = true;
            bullet.x = x;
            bullet.y = y - 1; // Posición inicial del disparo
            break;
        case 'r':
            Setup(); // Reiniciar el juego al presionar 'r'
            break;
        }
    }
    else // Si no se presiona ninguna tecla de movimiento, detener la nave
    {
        dir = STOP;
    }
}

void Logic()
{
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    }

    if (x >= width)
        x = width - 1;
    else if (x < 0)
        x = 0;

    if (enemyY == y && enemyX == x)
    {
        lives--; // Restar una vida cuando la nave colisiona con el enemigo
        if (lives <= 0)
        {
            gameOver = true;
            cout << "Game Over! Your score was: " << score << endl;
        }
        else
        {
            // Si todavía quedan vidas, reiniciar la posición de la nave y el enemigo
            x = width / 2;
            y = height - 1;
            enemyY = 0;
            enemyX = rand() % width;
        }
    }

    enemyY++;
    if (enemyY == height)
    {
        enemyY = 0;
        enemyX = rand() % width;
        score++;
    }

    // Mover el disparo
    if (bullet.active)
    {
        bullet.y--;
        if (bullet.y < 0)
            bullet.active = false; // Desactivar el disparo cuando sale de la pantalla

        // Detectar colisión entre el disparo y el enemigo
        if (bullet.active && bullet.x == enemyX && bullet.y == enemyY)
        {
            score++; // Incrementar la puntuación por destruir al enemigo
            enemyY = 0; // Restablecer la posición del enemigo
            enemyX = rand() % width;
            bullet.active = false; // Desactivar el disparo
        }
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100); // Velocidad del juego
    }
    return 0;

    }
