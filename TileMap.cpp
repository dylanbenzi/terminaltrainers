#include <fstream>
#include <iostream>
#include "BearLibTerminal.h"
#include "TileMap.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;
TileMap::TileMap(): width(0), height(0), layers(0) {
	tileLayerMap.resize(10);
}

bool TileMap::loadMapJson(const string& filename) {
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
		//cout << mapJson["layers"].size() << endl;

		int drawLayer = 0;

		for(int layer = layers - 1; layer >= 0; layer--) {
			string tileLayersName = mapLayer[layer]["name"];
			//cout << tileLayersName << endl;
			bool tileLayersCollider = mapLayer[layer]["collider"];
			//cout << tileLayersCollider << endl;
			
			auto mapLayerArr = mapLayer[layer]["tiles"];

			for(int tileList = 0; tileList < mapLayerArr.size(); tileList++) {
				auto mapLayerTilesArr = mapLayerArr[tileList];

				Tile tile;

				//cout << "[" << layer << ", " << tileList << "]" << endl;

				string tileIdStr = mapLayerTilesArr["id"];

				//cout << tileIdStr << endl;
				
				int tileIdInt = stoi(tileIdStr);

				tile.setTileOffset(tileIdInt); 
				tile.setX(mapJson["layers"][layer]["tiles"][tileList]["x"]);
				//cout << "x: " << tile.x << endl;
				tile.setY(mapJson["layers"][layer]["tiles"][tileList]["y"]);
				//cout << "y: " << tile.y << endl;
				tile.setCollisionTile(tileLayersCollider);

				tiles.push_back(tile);

				//cout << "tiles push ok" << endl;

				tileLayerMap[drawLayer][{tile.getX(), tile.getY()}] = tile;

				//cout << "layer map push ok" << endl;
			}

			drawLayer++;
			
		}
		
		return true;
	}catch(exception& e){
		//cout << e.what() << endl;

		return false;			
	}
}

bool TileMap::getTile(int x, int y, int layer, Tile& returnTile) const {
	Tile tile;
	auto findTile = tileLayerMap[layer].find({x, y});

	if(findTile != tileLayerMap[layer].end()) {
		returnTile = findTile -> second;
		return true;
	}else{
		return false;
	}
}

bool TileMap::getCollision(int x, int y, int layer) const {
	Tile tile;
	
	if(getTile(x, y, layer, tile)) {
		return tile.getCollisionTile();
	}else{
		return false;
	}
}

void TileMap::render(int x, int y, int viewWidth, int viewHeight) {
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

void TileMap::render(int x, int y, int viewWidth, int viewHeight, int xOffset, int yOffset) {
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
					terminal_put_ext(xCoord, yCoord, xOffset, yOffset, tileCode); 
				}
			}
		}
	}
}

int TileMap::getWidth() const {
	return width;
}

int TileMap::getHeight() const {
	return height;
}

