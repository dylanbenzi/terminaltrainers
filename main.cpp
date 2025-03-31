#include <BearLibTerminal.h>
#include <iostream>
#include "json.hpp"
#include "Tile.h"
#include "TileMap.h"

using json = nlohmann::json;
using namespace std;


int main() {
	TileMap gameMap;

	Tile tile;
	if(!gameMap.loadMapJson("./assets/map.json")) {
		cout << "Map error";
		return 1;
	};

	Tile character;
	character.setTileOffset(0xF000);
	character.setRenderLayer(99);

	int windowX = 136;
	int windowY = 68;

	int renderX = 0;
	int renderY = 0;

	terminal_open();

	terminal_set("window.size=136x68");
	terminal_set("0xE000: ./assets//spritesheet.png, size=64x64, align=top-left");
	terminal_set("0xF000: ./assets/characters.png, size=64x64, align=top-left");
	terminal_set("input.filter={keyboard}");
	terminal_set("input.repeat-delay=100");
	terminal_set("input.repeat-rate=10");

	gameMap.render(0, 0, 15, 15, renderX, renderY);
	character.renderSingle(7, 7);

	terminal_refresh();

	bool running = true;
	
	while (running) {
		terminal_clear();
		//terminal_set("0xE000: ./map/spritesheet.png, size=64x64, align=top-left");
		//terminal_set("0xF000: ./tiles/characters.png, size=64x64, align=top-left");

		//gameMap.render(renderX, renderY, 15, 15);

		int key = terminal_read();
		if(key == TK_ESCAPE) {
			running = false;
		}

		if(key == TK_D) {
			renderX++;
		}

		if(key == TK_A) {
			renderX--;
		}

		if(key == TK_W) {
			renderY--;
		}

		if(key == TK_S) {
			renderY++;
		}

		gameMap.render(renderX, renderY, 15, 15);
		character.renderSingle(7, 7);
		
		terminal_refresh();
	}

	terminal_close();
	return 0;
}
