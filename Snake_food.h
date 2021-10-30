#pragma once
#include <vector>
#include "Animation.h"
#include "Timer.h"
#include "Game.h"
#include "Snake.h"

class Game;
class Snake;

struct Coord_food {
	int x;
	int y;
	int flag = 0;
	Timer time;
};

class Snake_food {
public:
	Snake_food() = default;
	Snake_food& operator=(Snake_food&& other);
	bool check_ate(int x, int y);
	bool check_no_food(int x, int y);
	void generate(Snake &sn);
	void delete_food();
	void show(char ch, int color, int x, int y);
	void run(Game &gm, Snake &sn);

private:
	std::vector<Coord_food> food;
	Timer time;
	char ch_food = '#';
	const int period = 6000;
	const int period_2 = 15000;
};
