#include "Snake_food.h"

Snake_food& Snake_food::operator=(Snake_food&& other) {
	food = other.food;
	time = other.time;
	return *this;
}

bool Snake_food::check_ate(int x, int y) {
	auto it = food.begin();
	for (; it != food.end(); ++it)
		if ((*it).x == x && (*it).y == y) {
			food.erase(it, it + 1); //змейка съела еду
			return true; //еда была
		}
	return false; //еды не было
}

bool Snake_food::check_no_food(int x, int y) {
	for (size_t i = 0; i < food.size(); ++i)
		if (food[i].x == x && food[i].y == y)
			return true;
	return false;
}

void Snake_food::generate(Snake &sn) {
	if (time.duration() >= period) {
		Coord_food next_food;
		int x, y;
		do {
			x = 1 + rand() % 78;
			y = 1 + rand() % 23;

		} while (sn.check_no_body(x, y) || check_no_food(x, y));
		next_food.x = x;
		next_food.y = y;
		next_food.time.set_time_point();
		food.push_back(next_food);
		time.set_time_point();
		show(ch_food, 3 , x, y);
	}
}

void Snake_food::delete_food() {
	auto it = food.begin();

	for (; it != food.end(); ++it) {
		switch ((*it).flag) {
		case 0:
			if ((*it).time.duration() >= period_2 / 4) {
				show(ch_food, 10, (*it).x, (*it).y);
				++(*it).flag;
			}
			break;
		case 1:
			if ((*it).time.duration() >= period_2 / 2) {
				show(ch_food, 12, (*it).x, (*it).y);
				++(*it).flag;
			}
			break;
		case 2:
			if ((*it).time.duration() >= (3 * period_2) / 4) {
				show(ch_food, 5, (*it).x, (*it).y);
				++(*it).flag;
			}
			break;
		case 3:
			if ((*it).time.duration() >= period_2) { //еда испортилась
				show(' ', 0, (*it).x, (*it).y);
				food.erase(it, it + 1);
				return;
			}
		}
	}
}

void Snake_food::show(char ch, int col, int x, int y){
	Position(x, y);
	color(col, 0);
	std::cout << ch;
	Position(0, 24);
}

void Snake_food::run(Game &gm, Snake &sn) {
	if (gm.get_state() == GAME) {
		generate(sn);
		delete_food();
	}
}