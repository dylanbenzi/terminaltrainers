#include <BearLibTerminal.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Tile {
private:
	int x;
	int y;
	int tileOffset;
	int renderLayer;
	int baseTileCode = 0;
	int cellPixelsX = 8;
	int cellPixelsY = 4;
	bool collisionTile;
public:
	Tile(): x(0), y(0), tileOffset(0), renderLayer(0), collisionTile(0), baseTileCode(0) {
	}

	void renderSingle(int x, int y) {
		Tile tile;

		int xCoord = (x * cellPixelsX);
		int yCoord = (y * cellPixelsY);
		int tileCode = baseTileCode + tileOffset;

		//cout << "Tile: (" << tilesX << ", " << tilesY << "): " << tile.tileOffset << "; Layer: " << tileLayer << endl;
		terminal_layer(renderLayer);
		terminal_put_ext(xCoord, yCoord, 0, 0, tileCode); 
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	int getTileOffset() {
		return tileOffset;
	}

	int getRenderLayer() {
		return renderLayer;
	}

	bool getCollisionTile() {
		return collisionTile;
	}

	void setX(int value) {
		x = value;
	}

	void setY(int value) {
		y = value;
	}

	void setCoord(int xValue, int yValue) {
		x = xValue;
		y = yValue;
	}

	void setTileOffset(int value) {
		tileOffset = value;
	}

	void setRenderLayer(int value) {
		renderLayer = value;
	}

	void setCollisionTile(bool value) {
		collisionTile = value;
	}
};

class TileMap {
private:
	vector<Tile> tiles;
	int layers;
	int width, height;
	int baseTileCode = 0xE000;
	int cellPixelsX = 8;
	int cellPixelsY = 4;
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

					tile.setTileOffset(tileIdInt); 
					tile.setX(mapJson["layers"][layer]["tiles"][tileList]["x"]);
					//cout << "x: " << tile.x << endl;
					tile.setY(mapJson["layers"][layer]["tiles"][tileList]["y"]);
					//cout << "y: " << tile.y << endl;
					tile.setCollisionTile(tileLayersCollider);

					tiles.push_back(tile);

					cout << "tiles push ok" << endl;

					tileLayerMap[drawLayer][{tile.getX(), tile.getY()}] = tile;

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
			return tile.getCollisionTile();
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
						int xCoord = (tilesX * cellPixelsX);
						int yCoord = (tilesY * cellPixelsY);
						int tileCode = baseTileCode + tile.getTileOffset();

						//cout << "Tile: (" << tilesX << ", " << tilesY << "): " << tile.tileOffset << "; Layer: " << tileLayer << endl;
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

	Tile character;
	character.setTileOffset(0xF000);
	character.setRenderLayer(99);

	int windowX = 136;
	int windowY = 68;

	int renderX = 0;
	int renderY = 0;

	terminal_open();

	terminal_set("window.size=136x68");
	terminal_set("0xE000: ./map/spritesheet.png, size=64x64, align=top-left");
	terminal_set("0xF000: ./tiles/characters.png, size=64x64, align=top-left");

	gameMap.render(renderX, renderY, 15, 15);
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
