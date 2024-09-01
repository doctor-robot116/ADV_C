/* Алексеев Дмитрий
 * 
 * 
 * Доработайте функционал игры змейка. Реализуйте в игре ситуацию, когда змея врезается сама в себя.
 * Выход за границы экрана
 * */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#define MIN_Y  2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};


// Здесь храним коды управления змейкой
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
}control_buttons;

struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */
typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
} snake_t;

/*
 Хвост это массив состоящий из координат x,y
 */
typedef struct tail_t
{
    int x;
    int y;
} tail_t;

void initTail(struct tail_t t[], size_t size)
{
    struct tail_t init_t={0,0};
    for(size_t i=0; i<size; i++)
    {
        t[i]=init_t;
    }
}
void initHead(struct snake_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y)
{
    tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size + 1; // Установка размера хвоста + 1 (голова)
    head->controls = default_controls;
}

/*
 Движение головы с учетом текущего направления движения
 */
void go(struct snake_t *head)
{
    char ch = '@';                      // Символ для отображения головы змейки (в данном случае '@')
    int max_x=0, max_y=0;               // Объявляем переменные для хранения ширины (max_x) и высоты (max_y) терминала
    getmaxyx(stdscr, max_y, max_x);     // Получаем размеры текущего терминала с помощью функции getmaxyx() и сохраняем их в переменные max_y и max_x. 
    mvprintw(head->y, head->x, " ");    // Очищаем предыдущее положение головы змейки на экране,заменяя символ головы пробелом (" ").
    switch (head->direction)            // Выбор действия в зависимости от направления движения змейки
    {
        case LEFT:                      // Движение влево
            head->x = (head->x == 0) ? max_x - 1 : head->x - 1;             // Если голова змейки находится на левой границе (head->x == 0),
                                                                            // то переносим ее на правую границу (max_x - 1), иначе сдвигаем на один символ влево.
            mvprintw(head->y, head->x, "%c", ch);                           // Отрисовываем голову змейки на новой позиции.
            break;
        case RIGHT:                     // Движение вправо
            head->x = (head->x == max_x - 1) ? 0 : head->x + 1;             // Если голова змейки находится на правой границе (head->x == max_x - 1), 
                                                                            // то переносим ее на левую границу (0), иначе сдвигаем на один символ вправо.
            mvprintw(head->y, head->x, "%c", ch);                           // Отрисовываем голову змейки на новой позиции.
            break;
        case UP: // Движение вверх
            head->y = (head->y == 0) ? max_y - 1 : head->y - 1;             // Если голова змейки находится на верхней границе (head->y == 0),
                                                                            // то переносим ее на нижнюю границу (max_y - 1), иначе сдвигаем на один символ вверх.
            mvprintw(head->y, head->x, "%c", ch);                           // Отрисовываем голову змейки на новой позиции.
            break;
        case DOWN: // Движение вниз
            head->y = (head->y == max_y - 1) ? 0 : head->y + 1;             // Если голова змейки находится на нижней границе (head->y == max_y - 1),
                                                                            // то переносим ее на верхнюю границу (0), иначе сдвигаем на один символ вниз.
            mvprintw(head->y, head->x, "%c", ch);                           // Отрисовываем голову змейки на новой позиции.
            break;
        default:
            break;
    }
    refresh();                          // Обновляем содержимое экрана, чтобы изменения стали видны
}

void changeDirection(struct snake_t* snake, const int32_t key)
{
    if (key == snake->controls.down)
        snake->direction = DOWN;
    else if (key == snake->controls.up)
        snake->direction = UP;
    else if (key == snake->controls.right)
        snake->direction = RIGHT;
    else if (key == snake->controls.left)
        snake->direction = LEFT;
}

/*
 Движение хвоста с учетом движения головы
 */
void goTail(struct snake_t *head)
{
    char ch = '*';
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
    for(size_t i = head->tsize-1; i>0; i--)
    {
        head->tail[i] = head->tail[i-1];
        if( head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}

int check_collision(snake_t* snake) {
    for (size_t i = 1; i < snake->tsize; i++) {
        if (snake->x == snake->tail[i].x && snake->y == snake->tail[i].y) {
            return 1; // Столкновение!
        }
    }
    return 0; // Столкновения нет
}

int main()
{
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    initSnake(snake, START_TAIL_SIZE, 10, 10); // Используем START_TAIL_SIZE
    initscr();
    keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
    raw();                // Откдючаем line buffering
    noecho();            // Отключаем echo() режим при вызове getch
    curs_set(FALSE);    //Отключаем курсор
    mvprintw(0, 0,"Use arrows for control. Press 'F10' for EXIT");
    timeout(0);    //Отключаем таймаут после нажатия клавиши в цикле
    int key_pressed=0;
    int max_x = 0, max_y = 0; // Объявляем max_x и max_y
    while( key_pressed != STOP_GAME )
    {
        key_pressed = getch(); // Считываем клавишу
        go(snake);
        goTail(snake);
        if (check_collision(snake)) {
            getmaxyx(stdscr, max_y, max_x); // Получение размеров терминала
            mvprintw(max_y / 2, max_x / 2, "Game Over!");
            refresh(); // Обновляем экран, чтобы сообщение стало видно
            sleep(3);   // Задержка на 3 секунды
            //~ timeout(1000);
            //~ getch();
            break; // Выход из цикла при столкновении
        }
        timeout(100); // Задержка при отрисовке
        changeDirection(snake, key_pressed);
    }
    free(snake->tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
