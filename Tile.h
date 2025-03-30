#ifndef TILE_H
#define TILE_H

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
	Tile();

	void renderSingle(int x, int y);

	int getX() const;
	int getY() const;
	int getTileOffset() const;
	int getRenderLayer() const;
	bool getCollisionTile() const;

	void setX(int x);
	void setY(int y);
	void setCoord(int x, int y);
	void setTileOffset(int tileOffset);
	void setRenderLayer(int renderLayer);
	void setCollisionTile(bool isCollisionTile);
};

#endif
