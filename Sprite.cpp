#include "Sprite.h"
#include "TileMap.h"
#include "BearLibTerminal.h"

Sprite::Sprite(): spriteTileCode(0xF000), spriteTileOffset(0), worldX(0), worldY(0), posX(0.0f), posY(0.0f), veloX(0.0f), veloY(0.0f), facing(DOWN), isMoving(false), renderLayer(8), animationFrame(0) {
	//this->spriteTileCode = spriteTileCode;
	//this->spriteTileOffset = spriteTileOffset;
}

Sprite::Sprite(int x): spriteTileOffset(x) {}

void Sprite::render() {
	terminal_layer(renderLayer);
	terminal_put_ext(worldX, worldY, 0, 0, spriteTileCode);
}

void Sprite::move(MOVEMENT_DIR direction, TileMap& map) {
}

void Sprite::setXY(int x, int y) {
	this->worldX = x;
	this->worldY = y;
}

bool Sprite::canMove(MOVEMENT_DIR tryDirection, TileMap& map) {
	if(tryDirection == UP) {
		if(!map.getCollision(worldX, --worldY)) return true;
		else return false;
	}else if(tryDirection == DOWN) {
		if(!map.getCollision(worldX, ++worldY)) return true;
		else return false;
	}else if(tryDirection == LEFT) {
		if(!map.getCollision(--worldX, worldY)) return true;
		else return false;
	}else if(tryDirection == RIGHT) {
		if(!map.getCollision(++worldX, worldY)) return true;
		else return false;
	}else{
		//don't move, error case
		return false;
	}
}

int Sprite::getX() const {
	return worldX;
}

int Sprite::getY() const {
	return worldY;
}
