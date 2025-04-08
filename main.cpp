#define OLC_PGE_APPLICATION

#include "olcPixelGameEngine.h"
#include "Pokemon.h"
#include <cstdlib>
#include <ctime>

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

olc::vi2d getRandomEmptyTile(wstring s, olc::vi2d mapDim, olc::vi2d playerPos) {
	int randX = (rand() % mapDim.x);
	int randY = (rand() % mapDim.y);
	olc::vi2d returnXY = { randX, randY };

	if(s[randY * mapDim.x + randX] == '.' && randX != playerPos.x && randY != playerPos.y) {
		return returnXY;
	}else{
		return getRandomEmptyTile(s, mapDim, playerPos);
	}
}

class TerminalTrainers: public olc::PixelGameEngine {
public:
	TerminalTrainers() {
		sAppName = "Terminal Trainers";
	}
private:
	//level map
	wstring levelStr;
	olc::vi2d mapDim = { 20, 20 };
	olc::vi2d tileSize = { 16, 16 };

	//hard-coded x,y positions for background spritesheet
	int backgroundGrassX = 5 * tileSize.x;
	int backgroundGrassY = 5 * tileSize.y;
	int backgroundFlowerX = 0;
	int backgroundFlowerY = 5 * tileSize.y;

	//player movement
	const float moveDuration = 0.25f;
	bool isMoving = false;
	olc::vi2d playerPos = { 1, 1 };
	olc::vi2d moveOffset = { 0, 0 };
	olc::vi2d moveDirection = { 0, 0 };
	float t;
	float moveTimer = 0.0f;

	//player animation
	int characterAnimationFrame = 0;
	int characterAnimationRow = 0;
	MOVEMENT_DIR characterFacing = DOWN;

	//camera position
	float cameraX = 0.0f;
	float cameraY = 0.0f;

	//randomized pokemon
	int randPokemon = getRandomPokemonId();
	olc::vi2d randPokemonXY = { 2, 1 };
	int pokemonCaptured = false;

	//tilesheets
	olc::Sprite *backgroundSprite = nullptr;
	olc::Sprite *characterSprite = nullptr;
	olc::Sprite *pokemonSprite = nullptr;
	
protected:
	bool OnUserCreate() override {
		backgroundSprite = new olc::Sprite("./assets/background.png");
		characterSprite = new olc::Sprite("./assets/characters.png");
		pokemonSprite = new olc::Sprite("./assets/pokemon/pokemon151.png");

		//hardcoded level map 
		//can be improved to be procedurally generated
		//or imported from a tile map creation program
		levelStr += L"..............######";
		levelStr += L".................###";
		levelStr += L"...................#";
		levelStr += L"....................";
		levelStr += L".#########..........";
		levelStr += L"....................";
		levelStr += L".............#......";
		levelStr += L".............#......";
		levelStr += L".....#########......";
		levelStr += L"....................";
		levelStr += L"##.#############..#.";
		levelStr += L"##...............#..";
		levelStr += L"##..#############...";
		levelStr += L"....................";
		levelStr += L"....................";
		levelStr += L"#####..............#";
		levelStr += L"#####..............#";
		levelStr += L"#####..............#";
		levelStr += L"#............#######";
		levelStr += L"#....###############";

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		//lambda getter and setter functions for tiles
		auto getTile = [&](int x, int y) {
			if(x >= 0 && x < mapDim.x && y >= 0 && y < mapDim.y) {
				return levelStr[y * mapDim.x + x];
			}else{
				return L' ';
			}
		};

		auto setTile = [&](int x, int y, wchar_t c) {
			if(x >= 0 && x < mapDim.x && y >= 0 && y < mapDim.y) {
				levelStr[y * mapDim.x + x] = c;
			}
		};

		setTile(randPokemonXY.x, randPokemonXY.y, 'p');
		
		//regenerate randomized pokemon and location if captured
		if(pokemonCaptured) {
			setTile(randPokemonXY.x, randPokemonXY.y, '.');
			randPokemon = getRandomPokemonId();
			randPokemonXY = getRandomEmptyTile(levelStr, mapDim, playerPos);
			pokemonCaptured = false;
		}

		//only process inputs if terminal window is focused
		if(IsFocused()) {
			if(GetKey(olc::Key::ESCAPE).bPressed) {
				delete backgroundSprite;
				delete characterSprite;
				delete pokemonSprite;

				return false;
			}

			//movement direction cannot be changed while already moving
			//mimicking pokemon game movement
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
					int targetX = playerPos.x + moveDirection.x;
					int targetY = playerPos.y + moveDirection.y;
					if(getTile(targetX, targetY) == L'.') {
						isMoving = true;
						moveTimer = 0.0f;
					}
				}

				//capture pokemon if next to and facing pokemon
				if(GetKey(olc::Key::SPACE).bPressed) {
					int targetX = playerPos.x;
					int targetY = playerPos.y;

					if(characterFacing == UP) targetY--;
					if(characterFacing == DOWN) targetY++;
					if(characterFacing == RIGHT) targetX++;
					if(characterFacing == LEFT) targetX--;

					if(getTile(targetX, targetY) == L'p') {
						pokemonCaptured = true;
					}
				}
			}

			//process movement animation
			if(isMoving) {
				moveTimer += fElapsedTime;
				t = moveTimer / moveDuration;
				
				if(t >= 1.0f) {
					playerPos.x += moveDirection.x;
					playerPos.y += moveDirection.y;
					moveOffset = { 0, 0 };
					isMoving = false;
				}else{
					moveOffset.x = moveDirection.x * t * tileSize.x;
					moveOffset.y = moveDirection.y * t * tileSize.y;
				}
			}
		}

		//calculations to determine what tiles to render on the screen
		cameraX = playerPos.x + (float)moveOffset.x / tileSize.x;
		cameraY = playerPos.y + (float)moveOffset.y / tileSize.y;

		int visibleTilesX = ScreenWidth() / tileSize.x;
		int visibleTilesY = ScreenHeight() / tileSize.y;

		//offset allows for subtile smooth movement
		float offsetX = cameraX - (float)visibleTilesX / 2.0f;
		float offsetY = cameraY - (float)visibleTilesY / 2.0f;

		//clamp offset from 0 to visible tile map width
		if(offsetX < 0) offsetX = 0;
		if(offsetY < 0) offsetY = 0;
		if(offsetX > mapDim.x - visibleTilesX) offsetX = mapDim.x - visibleTilesX;
		if(offsetY > mapDim.y - visibleTilesY) offsetY = mapDim.y - visibleTilesY;

		//additional offsets used in rendering calculations
		int nOffsetX = (int)offsetX;
		int nOffsetY = (int)offsetY;
		float tileOffsetX = (offsetX - (int)offsetX) * tileSize.x;
		float tileOffsetY = (offsetY - (int)offsetY) * tileSize.y;


		//render tile function
		//renders one tile padding around visible area to account for any delay in drawing to screen
		for(int x = -1; x < visibleTilesX + 1; x++){
			for(int y = -1; y < visibleTilesY +1; y++){
				wchar_t tileID = getTile(x + nOffsetX, y + nOffsetY);
				int tileX = x * tileSize.x - tileOffsetX;
				int tileY = y * tileSize.y - tileOffsetY;

				//always draw grass tiles
				DrawPartialSprite(tileX, tileY, backgroundSprite, backgroundGrassX, backgroundGrassY, tileSize.x, tileSize.y);

				switch(tileID) {
					//flower collision tile
					case L'#':
						SetPixelMode(olc::Pixel::MASK);
						DrawPartialSprite(tileX, tileY, backgroundSprite, backgroundFlowerX, backgroundFlowerY, tileSize.x, tileSize.y);
						SetPixelMode(olc::Pixel::NORMAL);
						break;
					//pokemon collision sprite
					case L'p':
						olc::vi2d pokemonXY = allPokemon[randPokemon].getCoordinate();
						SetPixelMode(olc::Pixel::MASK);
						DrawPartialSprite(tileX, tileY, pokemonSprite, pokemonXY.x, pokemonXY.y, tileSize.x, tileSize.y);
						SetPixelMode(olc::Pixel::NORMAL);
				}

			}
		}

		//player x and y position to render
		int drawX = (playerPos.x - nOffsetX) * tileSize.x + moveOffset.x - tileOffsetX;
		int drawY = (playerPos.y - nOffsetY) * tileSize.y + moveOffset.y - tileOffsetY;

		//calculate animation frame based on movement time
		//clamps between 0 and 3
		characterAnimationFrame = (int)(t / moveDuration);
		if(characterAnimationFrame < 0 || characterAnimationFrame > 3) characterAnimationFrame = 0;

		//player render animations
		//based on facing direction and movement time
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
