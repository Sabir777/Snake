#include "Animation.h"

//определение контрола консоли
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

//настройка цвета курсора и заливки
void color(int i_text, int i_fill)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((i_fill << 4) | i_text));
}

//установить позицию курсора
void Position(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hStdOut, coord);
}

Fill::Fill(int x1, int x2, int y1, int y2)
	: x1(x1), x2(x2), y1(y1), y2(y2) {}

//закрасить область
void print_fill(Fill f, int i) {
	color(i, i);
	for (int y = f.y1; y <= f.y2; y++) {
		Position(f.x1, y);
		for (int x = f.x1; x <= f.x2; x++)
			std::cout << " ";
	}
	Position(0, 24);
}