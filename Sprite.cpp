#include "Sprite.h"
#include "TileMap.h"

Sprite::Sprite(): worldX(0), worldY(0), posX(0.0f), posY(0.0f), veloX(0.0f), veloY(0.0f), facing(DOWN), isMoving(false), spriteOffset(0x0000), renderLayer(8), animationFrame(0) {}

void Sprite::render() {

}

void Sprite::move(MOVEMENT_DIR direction, TileMap& map) {
}

bool Sprite::canMove(MOVEMENT_DIR tryDirection, TileMap&& map) {
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
