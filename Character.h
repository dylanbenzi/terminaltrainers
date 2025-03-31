#ifndef CHARACTER_H
#define CHARACTER_H

enum MOVEMENT_DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Character {
private:
	int worldX;
	int worldY;

	float posX;
	float posY;

	MOVEMENT_DIR facing;

	int spriteOffset;
	int renderLayer;
};

void charMove(MOVEMENT_DIR dir, int *pCharX, int *pCharY);

#endif
