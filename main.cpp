#include <BearLibTerminal.h>
#include <cstring>

using namespace std;

int main() {
	terminal_open();
	terminal_set("window: size=40x20, title='Terminal Trainers'");

	int x = 10;
	int y = 10;

	int mapHeight = 20;
	int mapLength = 40;
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

	while (running) {
		terminal_clear();
		
		terminal_print_ext(0, 0, 40, 20, TK_ALIGN_LEFT, map);
		terminal_put(x, y, 0x20AC);

		terminal_put_array(int x, int y, int w, int h, const uint8_t *data, int row_stride, int column_stride, const void *layout, int char_size)

		terminal_refresh();

		int key = terminal_read();
		if (key == TK_ESCAPE) running = false;
		else if (key == TK_UP || key == TK_W) y--;
		else if (key == TK_DOWN || key == TK_S) y++;
		else if (key == TK_LEFT || key == TK_A) x--;
		else if (key == TK_RIGHT || key == TK_D) x++;
	}

	terminal_close();
	return 0;
}
