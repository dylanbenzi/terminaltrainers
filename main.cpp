#include <BearLibTerminal.h>
#include <cstdlib>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
	int windowX = 136;
	int windowY = 68;

	int cellPixelsX = 8;
	int cellPixelsY = 4;

	int windowXCenter = (windowX / 2) - (cellPixelsX / 2);
	int windowYCenter = (windowY / 2) - (cellPixelsY / 2);

	int baseBackground = 0xE000;
	int grassTile = baseBackground + 45;
	int oneRedFlower = baseBackground + 7;

	terminal_open();

	terminal_set("window.size=136x68");

	bool running = true;
	
	while (running) {
		terminal_set("0xE000: ./tiles/background.png, size=64x64, align=top-left");

		for(int i = 0; i <= windowY; i+=cellPixelsY){
			for(int j = 0; j <= windowX; j+=cellPixelsX){
				int tileCode = grassTile;

				terminal_put_ext(j, i, 0, 0, tileCode);
			}
		}

		terminal_put_ext(windowXCenter, windowYCenter, 0, 0, oneRedFlower);

		terminal_refresh();

		int key = terminal_read();
		if (key == TK_ESCAPE) {
			running = false;
		}

	}

	terminal_close();
	return 0;
}
