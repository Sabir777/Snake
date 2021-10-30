#include "main.h"

using namespace std::chrono_literals;

int main() {
	system("mode con cols=80 lines=26");
	SetConsoleOutputCP(65001);
	//setlocale(LC_ALL, "");
	Game gm; Snake sn; Snake_food fd;
	gm.init();

	
	for (;;) {
		std::this_thread::sleep_for(25ms);
		gm.run(sn, fd);
		fd.run(gm, sn);
		sn.run(gm, fd);
	}
	
}