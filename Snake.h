#pragma once
#include <vector>
#include "Animation.h"
#include "Timer.h"
#include "Game.h"
#include "Snake_food.h"

class Game;
class Snake_food;

struct Coord {
	Coord() = default;
	Coord(int x, int y);
	int x;
	int y;
};

enum Direction { LEFT, RIGHT, UP, DOWN };

class Snake {
public:
	Snake();
	Snake& operator=(Snake&& other);
	void direction(Game &gm);
	void body_make(Snake_food &fd, Game &gm);
	bool grow_body(Snake_food &fd, Game &gm);
	void show_game_over();
	bool check_crash(Game &gm);
	bool check_no_body(int x, int y);
	void time_reset();
	void run(Game &gm, Snake_food &fd);

private:
	std::vector<Coord> body;
	int imax = 2;
	Direction dir = RIGHT;
	Direction prev_dir = RIGHT;
	Timer time;
	int speed_period = 250;
	const int hi_speed = 150;
	bool flag_time_reset = false;
	int period_time_reset = 90;
};