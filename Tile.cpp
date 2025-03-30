#include "Tile.h"
#include "BearLibTerminal.h"

Tile::Tile(): x(0), y(0), tileOffset(0), renderLayer(0), collisionTile(0), baseTileCode(0) {
}

void Tile::renderSingle(int x, int y) {
	Tile tile;

	int xCoord = (x * cellPixelsX);
	int yCoord = (y * cellPixelsY);
	int tileCode = baseTileCode + tileOffset;

	//cout << "Tile: (" << tilesX << ", " << tilesY << "): " << tile.tileOffset << "; Layer: " << tileLayer << endl;
	terminal_layer(renderLayer);
	terminal_put_ext(xCoord, yCoord, 0, 0, tileCode); 
}

int Tile::getX() const {
	return x;
}

int Tile::getY() const {
	return y;
}

int Tile::getTileOffset() const {
	return tileOffset;
}

int Tile::getRenderLayer() const {
	return renderLayer;
}

bool Tile::getCollisionTile() const {
	return collisionTile;
}

void Tile::setX(int x) {
	this->x = x;
}

void Tile::setY(int y) {
	this->y = y;
}

void Tile::setCoord(int x, int y) {
	this->x = x;
	this->y = y;
}

void Tile::setTileOffset(int tileOffset) {
	this->tileOffset = tileOffset;
}

void Tile::setRenderLayer(int renderLayer) {
	this->renderLayer = renderLayer;
}

void Tile::setCollisionTile(bool isCollisionTile) {
	this->collisionTile = isCollisionTile;
}
