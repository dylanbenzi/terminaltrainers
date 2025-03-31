#ifndef SPRITE_H
#define SPRITE_H

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

	int spriteOffset;
	int renderLayer;
	int animationFrame;
public:
	Sprite();

	void render();
	void move();

	void tryMove(int newX, int newY);

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
