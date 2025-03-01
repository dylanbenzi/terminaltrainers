#include <BearLibTerminal.h>
#include <cstring>

using namespace std;

int main() {
	terminal_open();
	terminal_set("window: size=225x65, title='Terminal Trainers'");



	int x = 20;
	int y = 20;

	int mapHeight = 100;
	int mapLength = 100;
	int mapSize = mapHeight * mapLength;

	char map[mapSize + mapHeight];

	strcat(map, "#######################################\n");
	strcat(map, "#                                     #\n");
	strcat(map, "#    *       *             *          #\n");
	strcat(map, "#        *      *     *          *    #\n");
	strcat(map, "#   *         *            *          #\n");
	strcat(map, "#         *        *   *              #\n");
	strcat(map, "#             *      *     *     *    #\n");
	strcat(map, "#  *    *                  *          #\n");
	strcat(map, "#       *        *    *         *     #\n");
	strcat(map, "#            *       *               ##\n");
	strcat(map, "##   *                 *    *         #\n");
	strcat(map, "#             *    *         *        #\n");
	strcat(map, "#     *   *       *     *             #\n");
	strcat(map, "#          *  *            *     *    #\n");
	strcat(map, "#    *           *   *               ##\n");
	strcat(map, "##        *               *           #\n");
	strcat(map, "#     *        *    *          *      #\n");
	strcat(map, "#         *           *     *         #\n");
	strcat(map, "#                                     #\n");
	strcat(map, "#######################################\n");


	bool running = true;
	terminal_refresh();
	
	terminal_set("0xE000: characters.png, size=16x16, spacing=0x0, resize=32x32, transparent=#EBEBEB");

	terminal_put(x, y, 0xE001);

	while (running) {
		terminal_refresh();
		terminal_clear();
		

		//terminal_print_ext(0, 0, mapLength, mapHeight, TK_ALIGN_LEFT, map);
		// terminal_put(x, y, 0x20AC);

		//terminal_put(x, y, 0xE000);

		int key = terminal_read();
		if (key == TK_ESCAPE) {
			running = false;
		}else if (key == TK_UP || key == TK_W) {
			y--;

			terminal_put(x, y, 0xE001);
			terminal_refresh();
		}else if (key == TK_DOWN || key == TK_S) {
			y++;

			terminal_put(x, y, 0xE000);
			terminal_refresh();
		}else if (key == TK_LEFT || key == TK_A) {
			x--;

			terminal_put(x, y, 0xE002);
		}else if (key == TK_RIGHT || key == TK_D) {
			x++;

			terminal_put(x, y, 0xE002);
		}
	}

	terminal_close();
	return 0;
}
