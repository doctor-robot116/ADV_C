#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#define MIN_Y 2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10,SEED_NUMBER=3};
#define CONTROLS 3
#define PLAYERS 2
double DELAY = 0.1;

typedef struct {
    int x;
    int y;
    time_t timestamp;
    int color;
    char point;  
} Food;
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
} control_buttons;
struct control_buttons default_controls[CONTROLS] = {
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
    {115, 119, 97, 100},
    {83, 87, 65, 68 }
};
typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
    int color;
} snake_t;
typedef struct tail_t{
    int x;
    int y;
} tail_t;

struct food{
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
    int color;
} food[MAX_FOOD_SIZE];

void setColor(int objectType) {
    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));
    switch (objectType) {
    case 1: { // SNAKE1
        attron(COLOR_PAIR(1));
        break;
    }
    case 2: { // SNAKE2
        attron(COLOR_PAIR(2));
        break;
    }
    case 3: { // FOOD
        attron(COLOR_PAIR(3));
        break;
    }
    }
}

void initFood(struct food f[], size_t size)
{
    struct food init = {0,0,0,0,0};
    for(size_t i=0; i<size; i++){
        f[i] = init;}
}
void putFoodSeed(struct food *fp)
{
    setColor(fp->color);
    int max_x=0, max_y=0;
    char spoint[2] = {0};
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(fp->y, fp->x, " ");
    fp->x = rand() % (max_x - 1);
    fp->y = rand() % (max_y - 2) + 1;
    fp->put_time = time(NULL);
    fp->point = '$';
    fp->enable = 1;
    spoint[0] = fp->point;
    mvprintw(fp->y, fp->x, "%s", spoint);
}

void putFood(struct food f[], size_t number_seeds){
    for( size_t i = 0; i<number_seeds; i++){
        putFoodSeed(&f[i]);}
}
void refreshFood(struct food f[], int nfood){
    for(size_t i=0; i<nfood; i++){
        if(f[i].put_time)
        {
            if(!f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS)
            {
                putFoodSeed(&f[i]);
            }
        }
    }
}

void initTail(struct tail_t t[], size_t size)
{
    struct tail_t init_t= {0,0};
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

void initSnake(snake_t *head[], size_t size, int x, int y, int i, int color) //ver1
{
    head[i] = (snake_t*)malloc(sizeof(snake_t));
    tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head[i], x, y);
    head[i]->tail = tail;
    head[i]->tsize = size + 1;
    head[i]->color = color;
    head[i]->controls = default_controls[0]; //[0]
}

void go(struct snake_t *head)  //ver1
{
    setColor(head->color);
    char ch = '@';
    int max_x=0, max_y=0;
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(head->y, head->x," ");
    switch (head->direction)
    {
    case LEFT:
        head->x = (head->x == 0) ? max_x - 1 : head->x - 1;
        mvprintw(head->y, head->x, "%c", ch);
        break;
    case RIGHT:
        head->x = (head->x == max_x - 1) ? 0 : head->x + 1;
        mvprintw(head->y, head->x, "%c", ch);
        break;
    case UP:
        head->y = (head->y == 0) ? max_y - 1 : head->y - 1;
        mvprintw(head->y, head->x, "%c", ch);
        break;
    case DOWN:
        head->y = (head->y == max_y - 1) ? 0 : head->y + 1;
        mvprintw(head->y, head->x, "%c", ch);
        break;
    default:
        break;
    }
    refresh();
}


void changeDirection(struct snake_t* snake, const int32_t key)
{
    for (int i = 0; i < CONTROLS; i++)
    {
        if (key == default_controls[i].down)
        {
            snake->direction = DOWN;
            return;
        }
        else if (key == default_controls[i].up)
        {
            snake->direction = UP;
            return;
        }
        else if (key == default_controls[i].right)
        {
            snake->direction = RIGHT;
            return;
        }
        else if (key == default_controls[i].left)
        {
            snake->direction = LEFT;
            return;
        }
    }
}

int checkDirection(snake_t* snake, int32_t key)
{
    for (int i = 0; i < CONTROLS; i++)
    {
        if (key == default_controls[i].down && snake->direction != UP)
        {
            return 1;
        } else if (key == default_controls[i].up && snake->direction != DOWN)
        {
            return 1;
        } else if (key == default_controls[i].right && snake->direction != LEFT)
        {
            return 1;
        } else if (key == default_controls[i].left && snake->direction != RIGHT)
        {
            return 1;
        }
    }
    return 0;
}

void goTail(struct snake_t *head)
{
    setColor(head->color);
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

_Bool isCrush(snake_t* snake) {
    for (size_t i = 1; i < snake->tsize; i++) {
        if (snake->x == snake->tail[i].x && snake->y == snake->tail[i].y) {
            return 1;
        }
    }
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    if (snake->x < 0 || snake->x >= max_x || snake->y < 0 || snake->y >= max_y) {
        return 1;
    }
    return 0;
}

_Bool haveEat(struct snake_t *head, struct food f[])
{
    for (size_t i = 0; i < MAX_FOOD_SIZE; i++)
    {
        if (f[i].enable && head->x == f[i].x && head->y == f[i].y)
        {
            f[i].enable = 0;
            return 1;
        }
    }
    return 0;
}

void addTail(struct snake_t *head) {
    head->tsize++;
    head->tail = realloc(head->tail, head->tsize * sizeof(struct tail_t)); 
    if (head->tail == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for the snake tail.\n");
        exit(1); 
    }
    head->tail[head->tsize - 1] = head->tail[head->tsize - 2];
    mvprintw(head->tail[head->tsize - 1].y, head->tail[head->tsize - 1].x, "*"); 
    refresh();
}

void repairSeed(struct food f[], size_t nfood, struct snake_t *head) {
    for (size_t i = 0; i < nfood; i++) {
        for (size_t j = 0; j < head->tsize; j++) {
            if (f[i].enable && head->tail[j].x == f[i].x && head->tail[j].y == f[i].y) {
                putFoodSeed(&f[i]);
                break;
            }
        }
        for (size_t j = i + 1; j < nfood; j++) {
            if (f[i].enable && f[j].enable && f[i].x == f[j].x && f[i].y == f[j].y) {
                putFoodSeed(&f[i]);
                break;
            }
        }
    }
}
void update(struct snake_t *head, struct food f[], const int32_t key)
{
    clock_t begin = clock();
    go(head);
    goTail(head);
    if (checkDirection(head,key))
    {
        changeDirection(head, key);
    }
    refreshFood(food, SEED_NUMBER);
    if (haveEat(head,food))
    {
        addTail(head);
    }
    refresh();
    while ((double)(clock() - begin)/CLOCKS_PER_SEC<DELAY)
    {}
}

int gameMode; // Переменная для хранения выбранного режима игры
int snakeColor; // Цвет змейки
int foodColor; // Цвет еды

void startMenu(){
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    int start_y = max_y / 2 - 10;
    int start_x = max_x / 2 - 30;
    mvprintw(start_y, start_x, "Snake!");
    mvprintw(start_y + 4, start_x, "1. 1 user");
    mvprintw(start_y + 6, start_x, "2. 2 user");
    mvprintw(start_y + 8, start_x, "3. EXIT");
    int choice = 0;
    int key;
    while (1)
    {
        key = getch();
        switch (key)
        {
            case KEY_UP:
                choice = (choice == 1) ? 3 : choice - 1;
                break;
            case KEY_DOWN:
                choice = (choice == 3) ? 1 : choice + 1;
                break;
            case 32: // Используем Enter для подтверждения
                gameMode = choice; // Сохраняем выбранный режим
                break;
            default:
                break;
        }
        mvprintw(start_y + 10, start_x, "Selected mode: %d", choice);
        if (gameMode != 0) // Выход из меню, если выбран режим
        {
            break;
        }
    }
    // Выбор цвета змейки
    start_y += 12;
    mvprintw(start_y, start_x, "Choose snake color:");
    mvprintw(start_y + 2, start_x, "1. Red");
    mvprintw(start_y + 4, start_x, "2. Blue");
    mvprintw(start_y + 6, start_x, "3. Green");
    choice = 1;
    while (1)
    {
        key = getch();
        switch (key)
        {
            case KEY_UP:
                choice = (choice == 1) ? 3 : choice - 1;
                break;
            case KEY_DOWN:
                choice = (choice == 3) ? 1 : choice + 1;
                break;
            case 32:
                snakeColor = choice; // Сохраняем выбранный цвет
                break;
            default:
                break;
        }
        mvprintw(start_y + 8, start_x, "Selected color: %d", choice);
        if (snakeColor != 0) // Выход из меню, если выбран цвет
        {
            break;
        }
    }
    // Выбор цвета еды
    start_y += 10;
    mvprintw(start_y, start_x, "Choose food color:");
    mvprintw(start_y + 2, start_x, "1. Red");
    mvprintw(start_y + 4, start_x, "2. Blue");
    mvprintw(start_y + 6, start_x, "3. Green");
    choice = 1;
    while (1)
    {
        key = getch();
        switch (key)
        {
            case KEY_UP:
                choice = (choice == 1) ? 3 : choice - 1;
                break;
            case KEY_DOWN:
                choice = (choice == 3) ? 1 : choice + 1;
                break;
            case 32:
                foodColor = choice; // Сохраняем выбранный цвет
                break;
            default:
                break;
        }
        mvprintw(start_y + 8, start_x, "Selected color: %d", choice);
        if (foodColor != 0) // Выход из меню, если выбран цвет
        {
            break;
        }
    }
    // Очистка экрана
    clear();
}

int main() {
    snake_t* snakes[PLAYERS];
    // Инициализация цветов
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK); // Цвет первой змейки
    init_pair(5, COLOR_BLUE, COLOR_BLACK); // Цвет второй змейки
    init_pair(6, COLOR_GREEN, COLOR_BLACK); // Цвет еды
    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);
    startMenu();
    // Инициализация змей в зависимости от выбранного режима
    if (gameMode == 1) {
        initSnake(snakes, START_TAIL_SIZE, 10, 10, 0, snakeColor);
    } else if (gameMode == 2) {
        initSnake(snakes, START_TAIL_SIZE, 10, 10, 0, snakeColor);
        initSnake(snakes, START_TAIL_SIZE, 20, 20, 1, snakeColor);
    } else {
        endwin();
        return 0; // Выход из игры, если выбран режим "Выход"
    }
    
    mvprintw(0, 0, "Use arrows or WASD for control. Press 'F10' for EXIT");
    timeout(0);
    initFood(food, MAX_FOOD_SIZE);
    for (int i = 0; i < MAX_FOOD_SIZE; i++)
    {
        food[i].color = foodColor;
    }
    putFood(food, SEED_NUMBER);
    int key_pressed=0 ;
    int max_x = 0, max_y = 0;
    while( key_pressed != STOP_GAME )
    {
        key_pressed = getch();
        for (int i = 0; i < gameMode; i++) // Играем только с теми змейками, которые нужны в выбранном режиме
        {
            update(snakes[i], food, key_pressed);
            repairSeed(food, SEED_NUMBER, snakes[i]);
            if (isCrush(snakes[i]))
            {
                getmaxyx(stdscr, max_y, max_x);
                mvprintw(max_y / 2, max_x / 2, "Game Over!");
                refresh();
                sleep(3);
                key_pressed = STOP_GAME;
                break;
            }
        }
    }
    for (int i = 0; i < gameMode; i++) // Освобождаем память только для тех змей, которые были созданы
    {
        free(snakes[i]->tail);
        free(snakes[i]);
    }
    endwin();
    return 0;
}
