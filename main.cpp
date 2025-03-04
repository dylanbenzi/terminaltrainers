#include <BearLibTerminal.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Tile {
	int tileSize;
	int x;
	int y;
	int tileOffset;
	int tileLayer;
	string layerName;
	bool collisionTile;
};

class TileMap {
private:
	vector<Tile> tiles;
	map<pair<int, int>, Tile> tilesByPosition;
	int width, height;

public:
	bool loadMapJson(string& filename) {
		try {
			ifstream file(filename);
			
			if(!file.is_open()) return false;

			json mapJson;
			file >> mapJson;

			tiles.clear();
			tilesByPosition.clear();
			
			width = mapJson["mapWidth"];
			height = mapJson["mapHeight"];
			
			int layer = 0;
			int globalTileSize = mapJson["tileSize"];

			for(auto& tileLayers : mapJson["layers"]) {
				string tileLayersName = tileLayers["name"];
				bool tileLayersCollider = tileLayers["collider"];
				
				for(auto& tilesArr : tileLayers["tiles"]) {
					Tile tile;

					tile.tileOffset = tilesArr["id"];
					tile.x = tilesArr["x"];
					tile.y = tilesArr["y"];
					tile.layerName = tileLayersName;
					tile.collisionTile = tileLayersCollider;
					tile.tileSize = globalTileSize;

					tiles.push_back(tile);
					tilesByPosition[{tile.x, tile.y}] = tile;
				}
				
			}

			return true;
		}catch(exception& e){
			return false;			
		}
	}

	bool getTile(int x, int y, Tile& returnTile) const {
		Tile tile;
		auto findTile = tilesByPosition.find({x, y});

		if(findTile != tilesByPosition.end()) {
			returnTile = findTile -> second;
			return true;
		}else{
			return false;
		}
	}

	bool getCollision(int x, int y) {
		Tile tile;
		
		if(getTile(x, y, tile)) {
			return tile.collisionTile;
		}else{
			return false;
		}
	}

	void render() {

	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}

};

int main() {
	TileMap map;

	int windowX = 136;
	int windowY = 68;

	int cellPixelsX = 8;
	int cellPixelsY = 4;

	int windowXCenter = (windowX / 2) - (cellPixelsX / 2);
	int windowYCenter = (windowY / 2) - (cellPixelsY / 2);

	int baseBackground = 0xE000;
	int grassTile = baseBackground + 45;
	int oneRedFlower = baseBackground + 7;

	int baseCharacter = 0xF000;
	int guyCharacter = baseCharacter + 4;

	terminal_open();

	terminal_set("window.size=136x68");

	bool running = true;
	
	while (running) {

		terminal_set("0xE000: ./tiles/background.png, size=64x64, align=top-left");
		terminal_set("0xF000: ./tiles/characters.png, size=64x64, align=top-left");

		for(int i = 0; i <= windowY; i+=cellPixelsY){
			for(int j = 0; j <= windowX; j+=cellPixelsX){
				int tileCode = grassTile;

				terminal_put_ext(j, i, 0, 0, tileCode);
			}
		}

		terminal_layer(1);
		terminal_put_ext(windowXCenter, windowYCenter, 0, 0, guyCharacter);

		int key = terminal_read();
		if(key == TK_ESCAPE) {
			running = false;
		}

		if(key == TK_W) {}


		terminal_refresh();
	}

	terminal_close();
	return 0;
}
