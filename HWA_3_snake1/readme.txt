Изменения:
1. Реализовано, когда змея врезается сама в себя.
2. Реализован - выход за границы экрана

Макросы:
MIN_Y: минимальная координата по вертикали (используется для ограничения движения змейки).

Перечисления:
LEFT, UP, RIGHT, DOWN: перечисление направлений движения змейки.
STOP_GAME: код клавиши для завершения игры.
MAX_TAIL_SIZE: максимальный размер хвоста змейки.
START_TAIL_SIZE: начальный размер хвоста змейки.
MAX_FOOD_SIZE: максимальное количество точек еды.
FOOD_EXPIRE_SECONDS: время жизни точки еды (в секундах).

Структуры:
control_buttons: структура для хранения кодов клавиш управления змейкой.
snake_t: структура для представления головы змейки.
tail_t: структура для представления элемента хвоста змейки.
food: структура для представления точки еды.

Функции:
initTail(): инициализирует хвост змейки.
initHead(): инициализирует голову змейки.
initSnake(): инициализирует змейку.
go(): перемещает голову змейки.
changeDirection(): изменяет направление движения змейки.
goTail(): перемещает хвост змейки.
main(): основная функция программы.

Описание food:
x, y: координаты точки еды.
put_time: время установки точки еды.
point: символ для отображения точки еды.
enable: флаг, указывающий, была ли точка съедена.
