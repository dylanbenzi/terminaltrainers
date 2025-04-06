#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>

using namespace std;

class TileMap {
public: 
	//3 arrays to store the converted 2D map layer data
	vector<int> background;
	vector<int> foreground;
	vector<int> collision;

	int mapWidth;
	int mapHeight;

	int getTile(int x, int y) const;
	int setTile(int x, int y, int tileID) const;

	void loadMap(string file);

};
#endif
