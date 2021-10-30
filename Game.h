#pragma once
#include "Animation.h"
#include "Timer.h"
#include "Snake.h"
#include "Snake_food.h"

class Snake;
class Snake_food;

enum State { GAME, PAUSE, GAME_OVER };

class Game {
public:
	void init();
	int get_key_press();
	int get_key();
	State get_state();
	void set_score();
	void set_game_over();
	void print_score();
	void run(Snake &sn, Snake_food &fd);

private:
	int key_press;
	int prev_key_press;
	State state = GAME;
	int score = 0;
	int prev_score = 0;
};
