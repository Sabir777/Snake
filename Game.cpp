#include "Game.h"

void Game::init() {
	print_fill(Fill(0, 79, 0, 24), 6);
	print_fill(Fill(1, 78, 1, 23), 0);
	Position(35, 0); //счет
	color(4, 6);
	std::cout << "Счет: 000";
	Position(65, 24); //пауза
	color(1, 6);
	std::cout << "Esc - пауза";
	color(14, 0);
	Position(39, 12);
	std::cout << "***";
	Position(0, 24);
}

int Game::get_key_press() {
	if (GetAsyncKeyState(37)) return 37; //влево
	if (GetAsyncKeyState(39)) return 39; //вправо
	if (GetAsyncKeyState(38)) return 38; //вверх
	if (GetAsyncKeyState(40)) return 40; //вниз
	if (GetAsyncKeyState(27)) return 27; //Esc
	if (GetAsyncKeyState(13)) return 13; //Enter
	return 0;
}

int Game::get_key() {
	return key_press;
}

State Game::get_state() {
	return state;
}

void Game::set_score() {
	++score;
}

void Game::set_game_over() {
	state = GAME_OVER;
	color(4, 0);
	Position(15, 12);
	std::cout << "Вы умерли. Для того чтобы начать игру нажмите Enter";
	Position(0, 24);
}

void Game::print_score() {
	if (prev_score != score) {
		int n1, n2, n3;
		n3 = score % 10;
		n2 = (score % 100) / 10;
		n1 = (score % 1000) / 100;
		color(4, 6);
		Position(41, 0);
		std::cout << n1;
		Position(42, 0);
		std::cout << n2;
		Position(43, 0);
		std::cout << n3;
		Position(0, 24);
		prev_score = score;
	}
}

void Game::run(Snake &sn, Snake_food &fd) {
	key_press = get_key_press();
	switch (state) {
	case GAME:
		if (prev_key_press == 27 && !key_press) {
			state = PAUSE;
			break;
		}

		print_score();
		break;

	case PAUSE:
		if (prev_key_press == 27 && !key_press) {
			state = GAME;
			break;
		}

	case GAME_OVER:
		if (key_press == 13) { //новая игра - Enter
			sn = Snake();
			fd = Snake_food();
			init();
			score = prev_score = 0;
			state = GAME;
		}
	}
	prev_key_press = key_press;
}