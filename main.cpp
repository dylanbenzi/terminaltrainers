#include <BearLibTerminal.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Tile {
	int x;
	int y;
	int tileOffset;
	bool collisionTile;
};

class TileMap {
private:
	vector<Tile> tiles;
	int layers;
	int width, height;
	int baseTileCode = 0xE000;
	int cellPixelsX = 8;
	int cellPixelsY = 4;
	//map<tuple<int, int, int>, Tile> tilesByPosition;
	vector<map<pair<int, int>, Tile>> tileLayerMap;
public:
	TileMap(): width(0), height(0), layers(0) {
		tileLayerMap.resize(10);
	}

	bool loadMapJson(const string& filename) {
		try {
			ifstream file(filename);
			
			if(!file.is_open()) return false;

			json mapJson;
			file >> mapJson;

			width = mapJson["mapWidth"];
			height = mapJson["mapHeight"];
			int globalTileSize = mapJson["tileSize"];

			auto mapLayer = mapJson["layers"];
			layers = mapLayer.size();
			
			tileLayerMap.resize(layers);
			cout << mapJson["layers"].size() << endl;

			int drawLayer = 0;

			for(int layer = layers - 1; layer >= 0; layer--) {
				string tileLayersName = mapLayer[layer]["name"];
				cout << tileLayersName << endl;
				bool tileLayersCollider = mapLayer[layer]["collider"];
				cout << tileLayersCollider << endl;
				
				auto mapLayerArr = mapLayer[layer]["tiles"];

				for(int tileList = 0; tileList < mapLayerArr.size(); tileList++) {
					auto mapLayerTilesArr = mapLayerArr[tileList];

					Tile tile;

					cout << "[" << layer << ", " << tileList << "]" << endl;

					string tileIdStr = mapLayerTilesArr["id"];

					cout << tileIdStr << endl;
					
					int tileIdInt = stoi(tileIdStr);

					//cout << "Tile: (" << tile.x << ", " << tile.y << "): " << tile.tileOffset << "; Layer: " << tile.tileLayer << endl;

					tile.tileOffset = tileIdInt;
					tile.x = mapJson["layers"][layer]["tiles"][tileList]["x"];
					cout << "x: " << tile.x << endl;
					tile.y = mapJson["layers"][layer]["tiles"][tileList]["y"];
					cout << "y: " << tile.y << endl;
					tile.collisionTile = tileLayersCollider;

					tiles.push_back(tile);

					cout << "tiles push ok" << endl;

					tileLayerMap[drawLayer][{tile.x, tile.y}] = tile;

					cout << "layer map push ok" << endl;
				}

				drawLayer++;
				
			}
			
			return true;
		}catch(exception& e){
			cout << e.what() << endl;

			return false;			
		}
	}

	bool getTile(int x, int y, int layer, Tile& returnTile) const {
		Tile tile;
		auto findTile = tileLayerMap[layer].find({x, y});

		//cout << findTile->second.tileOffset;

		if(findTile != tileLayerMap[layer].end()) {
			returnTile = findTile -> second;
			return true;
		}else{
			return false;
		}
	}

	bool getCollision(int x, int y, int layer) const {
		Tile tile;
		
		if(getTile(x, y, layer, tile)) {
			return tile.collisionTile;
		}else{
			return false;
		}
	}

	void render(int x, int y, int viewWidth, int viewHeight) {
		for(int tileLayer = 0; tileLayer < layers; tileLayer++) {
			for(int tilesX = 0; tilesX < viewWidth; tilesX++) {
				for(int tilesY = 0; tilesY < viewHeight; tilesY++) {
					Tile tile;

					if(getTile(x + tilesX, y + tilesY, tileLayer, tile)) {
						int xCoord = (tilesX * cellPixelsX) + x;
						int yCoord = (tilesY * cellPixelsY) + y;
						int tileCode = baseTileCode + tile.tileOffset;

						cout << "Tile: (" << tilesX << ", " << tilesY << "): " << tile.tileOffset << "; Layer: " << tileLayer << endl;
						terminal_layer(tileLayer);
						terminal_put_ext(xCoord, yCoord, 0, 0, tileCode); 
					}
				}
			}
		}
	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}

};

int main() {
	TileMap gameMap;

	Tile tile;
	if(!gameMap.loadMapJson("./map/map.json")) {
		cout << "Map error";
		return 1;
	};

	//if(!gameMap.getTile(0, 0, 0, tile)) {
	//	cout << "Tile error";
	//	return 1;
	//};

	int windowX = 136;
	int windowY = 68;

	int renderX = 0;
	int renderY = 0;

	//int cellPixelsX = 8;
	//int cellPixelsY = 4;

	//int windowXCenter = (windowX / 2) - (cellPixelsX / 2);
	//int windowYCenter = (windowY / 2) - (cellPixelsY / 2);

	//int baseBackground = 0xE000;
	//int grassTile = baseBackground + 45;
	//int oneRedFlower = baseBackground + 7;

	//int baseCharacter = 0xF000;
	//int guyCharacter = baseCharacter + 4;

	terminal_open();

	terminal_set("window.size=136x68");

	bool running = true;
	
	while (running) {
		terminal_set("0xE000: ./map/spritesheet.png, size=64x64, align=top-left");

		//terminal_set("0xE000: ./tiles/background.png, size=64x64, align=top-left");
		//terminal_set("0xF000: ./tiles/characters.png, size=64x64, align=top-left");

		//for(int i = 0; i <= windowY; i+=cellPixelsY){
		//	for(int j = 0; j <= windowX; j+=cellPixelsX){
		//		int tileCode = grassTile;
		//
		//		terminal_put_ext(j, i, 0, 0, tileCode);
		//	}
		//}

		//terminal_layer(1);
		//terminal_put_ext(windowXCenter, windowYCenter, 0, 0, guyCharacter);

		gameMap.render(renderX, renderY, 15, 15);

		int key = terminal_read();
		if(key == TK_ESCAPE) {
			running = false;
		}



		terminal_refresh();
	}

	terminal_close();
	return 0;
}
