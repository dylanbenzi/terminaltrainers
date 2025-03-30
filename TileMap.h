#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <map>
#include <string>
#include "Tile.h"

using namespace std;

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
	TileMap();

	bool loadMapJson(const string& filename);
	bool getTile(int x, int y, int layer, Tile& returnTile) const;
	bool getCollision(int x, int y, int layer) const;

	//TODO
	bool hasCollisionAt(int x, int y) const;
	bool isInBounds(int x, int y) const;
	bool canMoveTo(int x, int y) const;

	void render(int x, int y, int viewWidth, int viewHeight);
	void render(int x, int y, int viewWidth, int viewHeight, int xOffset, int yOffset);

	int getWidth() const;
	int getHeight() const;
};
#endif
