#ifndef SPRITE_H
#define SPRITE_H

#include "TileMap.h"

enum MOVEMENT_DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Sprite {
private:
	int worldX;
	int worldY;

	float posX;
	float posY;
	float veloX;
	float veloY;

	MOVEMENT_DIR facing;
	bool isMoving;

	int spriteTileCode;
	int spriteTileOffset;
	int renderLayer;
	int animationFrame;
public:
	Sprite();
	Sprite(int x);

	void render();
	void move(MOVEMENT_DIR direction, TileMap& map);

	bool canMove(MOVEMENT_DIR tryDirection, TileMap& map);

	void setXY(int x, int y);

	int getX() const;
	int getY() const;
	int getAnimFrame() const;
	float getPosX() const;
	float getPosY() const;
	float getVeloX() const;
	float getVeloY() const;
	MOVEMENT_DIR getDirection() const;
	bool getIsMoving() const;
};


#endif
