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

	float playerX = 1.0f;
	float playerY = 1.0f;
	float playerXVelo = 0.0f;
	float playerYVelo = 0.0f;

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
		testLevel += L"....................";
		testLevel += L"....................";
		testLevel += L".....#########......";
		testLevel += L"....................";
		testLevel += L"##.#############..#.";
		testLevel += L"##...............#..";
		testLevel += L"#################...";
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
		}

		int visibleTilesX = ScreenWidth() / tileSize.x;
		int visibleTilesY = ScreenHeight() / tileSize.y;

		float offsetX = cameraX - (float)visibleTilesX / 2.0f;
		float offsetY = cameraY - (float)visibleTilesY / 2.0f;

		if(offsetX < 0) offsetX = 0;
		if(offsetY < 0) offsetY = 0;
		if(offsetX > mapWidth - visibleTilesX) offsetX = mapWidth - visibleTilesX;
		if(offsetY > mapHeight - visibleTilesY) offsetY = mapHeight - visibleTilesY;

		float tileOffsetX = (offsetX - (int)offsetX) * tileSize.x;
		float tileOffsetY = (offsetY - (int)offsetY) * tileSize.y;

		for(int x = -1; x < visibleTilesX + 1; x++){
			for(int y = -1; y < visibleTilesY +1; y++){
				wchar_t tileID = getTile(x + offsetX, y + offsetY);
				switch(tileID) {
					case L'.':
						FillRect(x * tileSize.x - tileOffsetX, y * tileSize.y - tileOffsetY, (x + 1) * tileSize.x - tileOffsetX, (y + 1) * tileSize.y - tileOffsetY, olc::DARK_BLUE);
						break;
					case L'#':
						FillRect(x * tileSize.x - tileOffsetX, y * tileSize.y - tileOffsetY, (x + 1) * tileSize.x - tileOffsetX, (y + 1) * tileSize.y - tileOffsetY, olc::GREEN);
						break;
				}
			}
		}
		return true;
	}
};

int main() {
	TerminalTrainers demo;
	if(demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}
