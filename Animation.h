#pragma once
#include <windows.h>
#include <iostream>

//область заливки:координаты
struct Fill {
	Fill(int x1, int x2, int y1, int y2);
	int x1;
	int x2;
	int y1;
	int y2;
};

void color(int i_text, int i_fill);
void Position(int x, int y);
void print_fill(Fill f, int i);