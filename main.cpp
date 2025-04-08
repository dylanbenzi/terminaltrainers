#include <cstdlib>
#include <ctime>
#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Pokemon.h"

using namespace std;

enum MOVEMENT_DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

int getRandomPokemonId() { 
	return (rand() % 151 + 1);
};

olc::vi2d getRandomEmptyTile(wstring s, int mapWidth, int mapHeight, int playerTileX, int playerTileY) {
	int randX = (rand() % mapWidth);
	int randY = (rand() % mapHeight);
	olc::vi2d returnXY = { randX, randY };

	if(s[randY * mapWidth + randX] == '.' && randX != playerTileX && randY != playerTileY) {
		return returnXY;
	}else{
		return getRandomEmptyTile(s, mapWidth, mapHeight, playerTileY, playerTileY);
	}
}

class TerminalTrainers: public olc::PixelGameEngine {
public:
	TerminalTrainers() {
		sAppName = "Terminal Trainers";
	}
private:
	wstring testLevel;
	int mapWidth = 20;
	int mapHeight = 20;
	olc::vi2d tileSize = { 16, 16 };

	int playerTileX = 1;
	int playerTileY = 1;

	float t;
	float moveTimer = 0.0f;
	const float moveDuration = 0.25f;

	olc::vi2d moveOffset = { 0, 0 };
	olc::vi2d moveDirection = { 0, 0 };

	bool isMoving = false;

	float cameraX = 0.0f;
	float cameraY = 0.0f;

	int characterAnimationFrame = 0;
	int characterAnimationRow = 0;
	MOVEMENT_DIR characterFacing = DOWN;

	int randPokemon = getRandomPokemonId();
	olc::vi2d randPokemonXY = { 2, 1 };
	int pokemonCaptured = false;

	olc::Sprite *backgroundSprite = nullptr;
	olc::Sprite *characterSprite = nullptr;
	olc::Sprite *pokemonSprite = nullptr;
	
protected:
	bool OnUserCreate() override {
		backgroundSprite = new olc::Sprite("./assets/background.png");
		characterSprite = new olc::Sprite("./assets/characters.png");
		pokemonSprite = new olc::Sprite("./assets/pokemon/pokemon151.png");

		testLevel += L"..............######";
		testLevel += L".................###";
		testLevel += L"...................#";
		testLevel += L"....................";
		testLevel += L".#########..........";
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
		testLevel += L"#####..............#";
		testLevel += L"#####..............#";
		testLevel += L"#####..............#";
		testLevel += L"#............#######";
		testLevel += L"#....###############";

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

		setTile(randPokemonXY.x, randPokemonXY.y, 'p');

		
		//SetPixelMode(olc::Pixel::MASK);
		//DrawPartialSprite(0, 0, pokemonSprite, 16, 0, 16, 16, 4);
		//SetPixelMode(olc::Pixel::NORMAL);
		
		if(pokemonCaptured) {
			setTile(randPokemonXY.x, randPokemonXY.y, '.');
			randPokemon = getRandomPokemonId();
			randPokemonXY = getRandomEmptyTile(testLevel, mapWidth, mapHeight, playerTileX, playerTileY);
			pokemonCaptured = false;
		}

		if(GetKey(olc::Key::O).bPressed) pokemonCaptured = true;

		if(IsFocused()) {
			if(GetKey(olc::Key::ESCAPE).bPressed) {
				delete backgroundSprite;
				delete characterSprite;
				delete pokemonSprite;

				return false;
			}

			if(!isMoving) {
				if(GetKey(olc::Key::W).bHeld) {
					moveDirection = { 0, -1 };
					characterFacing = UP;
				}else if(GetKey(olc::Key::S).bHeld) {
					moveDirection = { 0, 1 };
					characterFacing = DOWN;
				}else if(GetKey(olc::Key::D).bHeld) {
					moveDirection = { 1, 0 };
					characterFacing = RIGHT;
				}else if(GetKey(olc::Key::A).bHeld) {
					moveDirection = { -1, 0 };
					characterFacing = LEFT;
				}else moveDirection = { 0, 0 };

				if(moveDirection != olc::vi2d{ 0, 0 }) {
					int targetX = playerTileX + moveDirection.x;
					int targetY = playerTileY + moveDirection.y;
					if(getTile(targetX, targetY) == L'.') {
						isMoving = true;
						moveTimer = 0.0f;
					}
				}

				if(GetKey(olc::Key::SPACE).bPressed) {
					int targetX = playerTileX;
					int targetY = playerTileY;

					if(characterFacing == UP) targetY--;
					if(characterFacing == DOWN) targetY++;
					if(characterFacing == RIGHT) targetX++;
					if(characterFacing == LEFT) targetX--;

					//cout << "(" << targetX << ", " << targetY << ")" << endl;

					if(getTile(targetX, targetY) == L'p') {
						pokemonCaptured = true;
					}
				}
			}


			if(isMoving) {
				moveTimer += fElapsedTime;
				t = moveTimer / moveDuration;
				
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

		int bgTileX = 5 * tileSize.x;
		int bgTileY = 5 * tileSize.y;

		int bgTileX2 = 0;
		int bgTileY2 = 5 * tileSize.y;

		for(int x = -1; x < visibleTilesX + 1; x++){
			for(int y = -1; y < visibleTilesY +1; y++){
				wchar_t tileID = getTile(x + nOffsetX, y + nOffsetY);
				int tileX = x * tileSize.x - tileOffsetX;
				int tileY = y * tileSize.y - tileOffsetY;
				DrawPartialSprite(tileX, tileY, backgroundSprite, bgTileX, bgTileY, 16, 16);
				switch(tileID) {
					case L'.':
						//FillRect(tileX, tileY, tileSize.x, tileSize.y, olc::DARK_BLUE);
						//DrawPartialSprite(tileX, tileY, backgroundSprite, bgTileX, bgTileY, 16, 16);
						break;
					case L'#':
						//FillRect(tileX, tileY, tileSize.x, tileSize.y, olc::GREEN);
						
						//DrawPartialSprite(tileX, tileY, backgroundSprite, bgTileX, bgTileY, 16, 16);
						SetPixelMode(olc::Pixel::MASK);
						DrawPartialSprite(tileX, tileY, backgroundSprite, bgTileX2, bgTileY2, 16, 16);
						SetPixelMode(olc::Pixel::NORMAL);
						break;
					case L'p':
						olc::vi2d pokemonXY = allPokemon[randPokemon].getCoordinate();
						SetPixelMode(olc::Pixel::MASK);
						DrawPartialSprite(tileX, tileY, pokemonSprite, pokemonXY.x, pokemonXY.y, 16, 16);
						SetPixelMode(olc::Pixel::NORMAL);
				}

			}
		}
		//allPokemon[0].draw(this, pokemonSprite, nOffsetX, nOffsetX, tileOffsetX, tileOffsetY);
		//allPokemon[0].drawPokemon(this, pokemonSprite, tileOffsetX, tileOffsetY);

		int drawX = (playerTileX - nOffsetX) * tileSize.x + moveOffset.x - tileOffsetX;
		int drawY = (playerTileY - nOffsetY) * tileSize.y + moveOffset.y - tileOffsetY;

		characterAnimationFrame = (int)(t / 0.250f);
		if(characterAnimationFrame < 0 || characterAnimationFrame >= 4) characterAnimationFrame = 0;

		switch(characterFacing) {
			case UP:
				characterAnimationRow = 3;
				SetPixelMode(olc::Pixel::MASK);
				DrawPartialSprite(drawX, drawY, characterSprite, characterAnimationFrame * tileSize.x, characterAnimationRow * tileSize.y, tileSize.x, tileSize.y);
				SetPixelMode(olc::Pixel::NORMAL);
				break;
			case DOWN:
				characterAnimationRow = 0;
				SetPixelMode(olc::Pixel::MASK);
				DrawPartialSprite(drawX, drawY, characterSprite, characterAnimationFrame * tileSize.x, characterAnimationRow * tileSize.y, tileSize.x, tileSize.y);
				SetPixelMode(olc::Pixel::NORMAL);
				break;	
			case LEFT:
				characterAnimationRow = 1;
				SetPixelMode(olc::Pixel::MASK);
				DrawPartialSprite(drawX, drawY, characterSprite, characterAnimationFrame * tileSize.x, characterAnimationRow * tileSize.y, tileSize.x, tileSize.y);
				SetPixelMode(olc::Pixel::NORMAL);
				break;
			case RIGHT:
				characterAnimationRow = 2;
				SetPixelMode(olc::Pixel::MASK);
				DrawPartialSprite(drawX, drawY, characterSprite, characterAnimationFrame * tileSize.x, characterAnimationRow * tileSize.y, tileSize.x, tileSize.y);
				SetPixelMode(olc::Pixel::NORMAL);
				break;
		}

		//cout << "Player (" << playerTileX << ", " << playerTileY << "); Facing " << characterFacing << "; Timer: " << t << "; Frame: " << characterAnimationFrame << "; Poke: " << randPokemon << endl;

		//allPokemon[0].drawPokemon(this, pokemonSprite, tileOffsetX, tileOffsetY);
		//allPokemon[1].drawPokemon(this, pokemonSprite, {0, 1});

		return true;
	}
};

int main() {
	srand(time(0));
	TerminalTrainers demo;
	if(demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}
