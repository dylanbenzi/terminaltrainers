#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

using namespace std;

class TerminalTrainers: public olc::PixelGameEngine {
public:
	TerminalTrainers() {
		sAppName = "Terminal Trainers";
	}
private:
	wstring testLevel;
	int mapWidth;
	int mapHeight;
	olc::vi2d tileSize = { 16, 16 };

	int playerTileX = 1;
	int playerTileY = 1;

	float moveTimer = 0.0f;
	float moveDuration = 0.2f;

	olc::vi2d moveOffset = { 0, 0 };
	olc::vi2d moveDirection = { 0, 0 };

	bool isMoving = false;

	float cameraX = 0.0f;
	float cameraY = 0.0f;

	olc::Sprite *backgroundSprite = nullptr;
	olc::Sprite *characterSprite = nullptr;
	olc::Sprite *pokemonSprite = nullptr;
	
protected:
	bool OnUserCreate() override {
		backgroundSprite = new olc::Sprite("./assets/background.png");
		characterSprite = new olc::Sprite("./assets/characters.png");
		pokemonSprite = new olc::Sprite("./assets/pokemon/pokemon151.png");

		mapWidth = 20;
		mapHeight = 20;
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L".............#......";
		testLevel += L".............#......";
		testLevel += L".....#########......";
		testLevel += L"....................";
		testLevel += L"##.#############..#.";
		testLevel += L"##...............#..";
		testLevel += L"##..#############...";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L"....................";
			
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		auto getTile = [&](int x, int y) {
			if(x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
				return testLevel[y * mapWidth + x];
			}else{
				return L' ';
			}
		};

		auto setTile = [&](int x, int y, wchar_t c) {
			if(x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
				testLevel[y * mapWidth + x] = c;
			}
		};
		//SetPixelMode(olc::Pixel::MASK);
		//DrawPartialSprite(0, 0, pokemonSprite, 16, 0, 16, 16, 4);
		//SetPixelMode(olc::Pixel::NORMAL);

		if(IsFocused()) {
			if(GetKey(olc::Key::ESCAPE).bPressed) {
				delete backgroundSprite;
				delete characterSprite;
				delete pokemonSprite;

				return false;
			}

			if(!isMoving) {
				if(GetKey(olc::Key::W).bHeld) moveDirection = { 0, -1 };
				else if(GetKey(olc::Key::S).bHeld) moveDirection = { 0, 1 };
				else if(GetKey(olc::Key::D).bHeld) moveDirection = { 1, 0 };
				else if(GetKey(olc::Key::A).bHeld) moveDirection = { -1, 0 };
				else moveDirection = { 0, 0 };

				if(moveDirection != olc::vi2d{ 0, 0 }) {
					int targetX = playerTileX + moveDirection.x;
					int targetY = playerTileY + moveDirection.y;
					if(getTile(targetX, targetY) == L'.') {
						isMoving = true;
						moveTimer = 0.0f;
					}
				}
			}


			if(isMoving) {
				moveTimer += fElapsedTime;
				float t = moveTimer / moveDuration;
				
				if(t >= 1.0f) {
					playerTileX += moveDirection.x;
					playerTileY += moveDirection.y;
					moveOffset = { 0, 0 };
					isMoving = false;
				}else{
					moveOffset.x = moveDirection.x * t * tileSize.x;
					moveOffset.y = moveDirection.y * t * tileSize.y;
				}
			}

			if(GetKey(olc::Key::SPACE).bPressed) {
				//interactions
			}
		}


		//collisions
		
		cameraX = playerTileX + (float)moveOffset.x / tileSize.x;
		cameraY = playerTileY + (float)moveOffset.y / tileSize.y;

		int visibleTilesX = ScreenWidth() / tileSize.x;
		int visibleTilesY = ScreenHeight() / tileSize.y;

		float offsetX = cameraX - (float)visibleTilesX / 2.0f;
		float offsetY = cameraY - (float)visibleTilesY / 2.0f;

		if(offsetX < 0) offsetX = 0;
		if(offsetY < 0) offsetY = 0;
		if(offsetX > mapWidth - visibleTilesX) offsetX = mapWidth - visibleTilesX;
		if(offsetY > mapHeight - visibleTilesY) offsetY = mapHeight - visibleTilesY;

		int nOffsetX = (int)offsetX;
		int nOffsetY = (int)offsetY;
		float tileOffsetX = (offsetX - (int)offsetX) * tileSize.x;
		float tileOffsetY = (offsetY - (int)offsetY) * tileSize.y;

		for(int x = -1; x < visibleTilesX + 1; x++){
			for(int y = -1; y < visibleTilesY +1; y++){
				wchar_t tileID = getTile(x + nOffsetX, y + nOffsetY);
				int tileX = x * tileSize.x - tileOffsetX;
				int tileY = y * tileSize.y - tileOffsetY;
				switch(tileID) {
					case L'.':
						FillRect(tileX, tileY, tileSize.x, tileSize.y, olc::DARK_BLUE);
						break;
					case L'#':
						FillRect(tileX, tileY, tileSize.x, tileSize.y, olc::GREEN);
						break;
				}
			}
		}

		int drawX = (playerTileX - nOffsetX) * tileSize.x + moveOffset.x - tileOffsetX;
		int drawY = (playerTileY - nOffsetY) * tileSize.y + moveOffset.y - tileOffsetY;

		//FillRect((playerX - offsetX) * tileSize.x, (playerY - offsetY) * tileSize.x, (playerX - offsetX + 1.0f) * tileSize.x, (playerY - offsetY + 1.0f) * tileSize.y, olc::RED);
		FillRect(drawX, drawY, tileSize.x, tileSize.y, olc::RED);

		cout << "Player (" << playerTileX << ", " << playerTileY << ")" << endl;
		return true;
	}
};

int main() {
	TerminalTrainers demo;
	if(demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}
