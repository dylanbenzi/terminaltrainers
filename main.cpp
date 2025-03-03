#include <BearLibTerminal.h>
#include <cstdlib>

using namespace std;

int main() {
	int windowX = 128;
	int windowY = 64;

	int cellPixelsX = 8;
	int cellPixelsY = 4;

	int windowRenderX = windowX + cellPixelsX;
	int windowRenderY = windowY + cellPixelsY;

	terminal_open();

	terminal_set("window.size=128x64");

	int x = 32;
	int y = 32;

	int baseBackground = 0xF000;
	int grassTile = baseBackground + 45;
	int oneRedFlower = baseBackground + 7;

	bool running = true;
	
	while (running) {
		terminal_set("0xF000: ./tiles/background.png, size=64x64, align=top-left");

		for(int i = 0; i <= windowY; i+=4){
			for(int j = 0; j <= windowX; j+=8){
				int randNum = (rand() % 10) + 1;

				int tileCode = grassTile;

				if(randNum == 10) tileCode = oneRedFlower;

				terminal_put_ext(j, i, 0, 0, tileCode);
			}
		}

		terminal_refresh();

		int key = terminal_read();
		if (key == TK_ESCAPE) {
			running = false;
		}

	}

	terminal_close();
	return 0;
}
