#include "Snake.h"

Coord::Coord(int x, int y) : x(x), y(y) {}

Snake::Snake() {
	body.push_back(Coord(39, 12));
	body.push_back(Coord(40, 12));
	body.push_back(Coord(41, 12));
}

Snake& Snake::operator=(Snake&& other) {
	body = other.body;
	imax = 2;
	dir = RIGHT;
	prev_dir = RIGHT;
	speed_period = 250;
	time = other.time;
	return *this;
}

void Snake::direction(Game &gm) {
	switch (gm.get_key()) {
	case 37:  //влево
		if (dir != RIGHT) dir = LEFT; //запрет : задний ход
		break;
	case 39:  //вправо
		if (dir != LEFT) dir = RIGHT; //запрет : задний ход
		break;
	case 38:  //вверх
		if (dir != DOWN) dir = UP; //запрет : задний ход
		break;
	case 40:  //вниз
		if (dir != UP) dir = DOWN; //запрет : задний ход
		break;
	}
}

bool Snake::grow_body(Snake_food &fd, Game &gm) {
	if (fd.check_ate(body[imax + 1].x, body[imax + 1].y)) {
		++imax;
		if (speed_period > hi_speed) --speed_period;
		gm.set_score();
		return true;
	}
	return false;
}

void Snake::body_make(Snake_food &fd, Game &gm) {
	int x, y;
	switch (dir) {
	case LEFT:  //влево
		x = (body[imax].x == 1) ? 78 : (body[imax].x) - 1;
		body.push_back(Coord(x, body[imax].y)); //добовл¤ю последний элемент(голова)
		break;
	case RIGHT:  //вправо
		x = (body[imax].x == 78) ? 1 : (body[imax].x) + 1;
		body.push_back(Coord(x, body[imax].y)); //добовл¤ю последний элемент(голова)
		break;
	case UP:  //вверх
		y = (body[imax].y == 1) ? 23 : (body[imax].y) - 1;
		body.push_back(Coord(body[imax].x, y)); //добовл¤ю последний элемент(голова)
		break;
	case DOWN:  //вниз
		y = (body[imax].y == 23) ? 1 : (body[imax].y) + 1;
		body.push_back(Coord(body[imax].x, y)); //добовл¤ю последний элемент(голова)
		break;
	}

	//прорисовка и проверка
	//если зме¤ не выросла закрашиваю хвост
	if (!grow_body(fd, gm)) { 
		Position(body[0].x, body[0].y);
		color(0, 0);
		std::cout << " "; //закрашиваю хвост
		Position(0, 24);
		body.erase(body.begin(), body.begin() + 1);
		//удал¤ю первый элемент из массива(хвост)
	}
	Position(body[imax].x, body[imax].y);
	color(14, 0);
	std::cout << "*"; //рисую голову
	Position(0, 24);
}

void Snake::show_game_over() {
	color(4, 0);
	for (size_t i = 0; i < body.size(); ++i) {
		Coord b = body[i];
		Position(b.x, b.y);
		std::cout << "*";
	}
	Position(0, 24);
}

bool Snake::check_crash(Game &gm) { //проверка столкновени¤ с собой
	int x = body[imax].x; int y = body[imax].y;
	for (int i = 0; i < imax; ++i)
		if (x == body[i].x && y == body[i].y) {
			gm.set_game_over();
			return true;
		}
	return false;
}

bool Snake::check_no_body(int x, int y) {
	for (int i = 0; i <= imax; ++i)
		if (body[i].x == x && body[i].y == y)
			return true; //в данной точке тело есть
	return false; //в данной точке тела нет
}

void Snake::time_reset() {
	if (flag_time_reset && time.duration() >= period_time_reset) {
		flag_time_reset = false;
		time.set_time_point();
	}
}

void Snake::run(Game &gm, Snake_food &fd) {
	if (gm.get_state() == GAME) {
		direction(gm);
		time_reset();
		if (dir != prev_dir) {
			prev_dir = dir;
			body_make(fd, gm);
			time.set_time_point();
			flag_time_reset = true;
			if (check_crash(gm))
				show_game_over();
		}
		else if (time.duration() >= speed_period) {
			body_make(fd, gm);
			time.set_time_point();
			if (check_crash(gm))
				show_game_over();
		}
	}
}