#include "Pokemon.h"
#include "olcPixelGameEngine.h"

olc::vi2d tilesheetTiles = { 14, 11 };
olc::vi2d tileSize = { 16, 16 };

Pokemon::Pokemon(int id, string name) {
	this->id = id;
	this->name = name;
	this->worldPos = { 0, 0 };
};

Pokemon::Pokemon(int id, string name, olc::vi2d worldPos) {
	this->id = id;
	this->name = name;
	this->worldPos = worldPos;
};

olc::vi2d Pokemon::getCoordinate() {
	int y = (id / tilesheetTiles.x) * tileSize.x;
	int x = (id % tilesheetTiles.x) * tileSize.y;

	return { x, y };
};

int Pokemon::getRandomPokemonId() {
	return (rand() % 151 + 1);
};

void Pokemon::draw(olc::PixelGameEngine *pge, olc::Sprite *pokemonSprite, int nOffsetX, int nOffsetY, float tileOffsetX, float tileOffsetY) {
	int screenX = (worldPos.x - nOffsetX) * tileSize.x - tileOffsetX;
	int screenY = (worldPos.y - nOffsetY) * tileSize.y - tileOffsetY;

	if(screenX > 0 && screenY > 0 && screenX < pge->ScreenWidth() && screenY < pge->ScreenHeight()) {
		olc::vi2d spritesheetCoord = getCoordinate();
		pge->SetPixelMode(olc::Pixel::MASK);
		pge->DrawPartialSprite(screenX, screenY, pokemonSprite, spritesheetCoord.x, spritesheetCoord.y, tileSize.x, tileSize.y);
		pge->SetPixelMode(olc::Pixel::MASK);
	}
}

void Pokemon::drawPokemon(olc::PixelGameEngine *pge, olc::Sprite *pokemonSprite, olc::vi2d worldPos) {
	olc::vi2d spritesheetCoord = getCoordinate();
	this->worldPos = worldPos;
	olc::vi2d tileXY = {worldPos.x * tileSize.x, worldPos.y * tileSize.y};

	pge->SetPixelMode(olc::Pixel::MASK);
	pge->DrawPartialSprite(tileXY.x, tileXY.y, pokemonSprite, spritesheetCoord.x, spritesheetCoord.y, tileSize.x, tileSize.y);
	pge->SetPixelMode(olc::Pixel::NORMAL);
};

void Pokemon::drawPokemon(olc::PixelGameEngine *pge, olc::Sprite *pokemonSprite, float tileOffsetX, float tileOffsetY) {
	olc::vi2d spritesheetCoord = getCoordinate();
	int tileX = worldPos.x * tileSize.x - tileOffsetX;
	int tileY = worldPos.y * tileSize.y - tileOffsetY;

	pge->SetPixelMode(olc::Pixel::MASK);
	pge->DrawPartialSprite(tileX, tileY, pokemonSprite, spritesheetCoord.x, spritesheetCoord.y, tileSize.x, tileSize.y);
	pge->SetPixelMode(olc::Pixel::NORMAL);
};

void Pokemon::drawPokemon(olc::PixelGameEngine *pge, olc::Sprite *pokemonSprite, int &tileX, int &tileY) {
	olc::vi2d spritesheetCoord = getCoordinate();

	pge->SetPixelMode(olc::Pixel::MASK);
	pge->DrawPartialSprite(tileX, tileY, pokemonSprite, spritesheetCoord.x, spritesheetCoord.y, tileSize.x, tileSize.y);
	pge->SetPixelMode(olc::Pixel::NORMAL);
};

vector<Pokemon> allPokemon = {
	{1, "Bulbasaur", {1, 1}},
	{2, "Ivysaur"},
	{3, "Venusaur"},
	{4, "Charmander"},
	{5, "Charmeleon"},
	{6, "Charizard"},
	{7, "Squirtle"},
	{8, "Wartortle"},
	{9, "Blastoise"},
	{10, "Caterpie"},
	{11, "Metapod"},
	{12, "Butterfree"},
	{13, "Weedle"},
	{14, "Kakuna"},
	{15, "Beedrill"},
	{16, "Pidgey"},
	{17, "Pidgeotto"},
	{18, "Pidgeot"},
	{19, "Rattata"},
	{20, "Raticate"},
	{21, "Spearow"},
	{22, "Fearow"},
	{23, "Ekans"},
	{24, "Arbok"},
	{25, "Pikachu"},
	{26, "Raichu"},
	{27, "Sandshrew"},
	{28, "Sandslash"}, 
	{29, "Nidoran"}, 
	{30, "Nidorina"}, 
	{31, "Nidoqueen"}, 
	{32, "Nidoran"},
	{33, "Nidorino"},
	{34, "Nidoking"},
	{35, "Clefairy"},
	{36, "Clefable"},
	{37, "Vulpix"},
	{38, "Ninetales"},
	{39, "Jigglypuff"},
	{40, "Wigglytuff"},
	{41, "Zubat"},
	{42, "Golbat"},
	{43, "Oddish"},
	{44, "Gloom"},
	{45, "Vileplume"},
	{46, "Paras"},
	{47, "Parasect"},
	{48, "Venonat"},
	{49, "Venomoth"},
	{50, "Diglett"},
	{51, "Dugtrio"},
	{52, "Meowth"},
	{53, "Persian"},
	{54, "Psyduck"},
	{55, "Golduck"},
	{56, "Mankey"},
	{57, "Primeape"},
	{58, "Growlithe"},
	{59, "Arcanine"},
	{60, "Poliwag"},
	{61, "Poliwhirl"},
	{62, "Poliwrath"},
	{63, "Abra"},
	{64, "Kadabra"},
	{65, "Alakazam"},
	{66, "Machop"},
	{67, "Machoke"},
	{68, "Machamp"},
	{69, "Bellsprout"},
	{70, "Weepinbell"},
	{71, "Victreebel"},
	{72, "Tentacool"},
	{73, "Tentacruel"},
	{74, "Geodude"},
	{75, "Graveler"},
	{76, "Golem"},
	{77, "Ponyta"},
	{78, "Rapidash"},
	{79, "Slowpoke"},
	{80, "Slowbro"},
	{81, "Magnemite"},
	{82, "Magneton"},
	{83, "Farfetch'd"},
	{84, "Doduo"},
	{85, "Dodrio"},
	{86, "Seel"},
	{87, "Dewgong"},
	{88, "Grimer"}, 
	{89, "Muk"},
	{90, "Shellder"},
	{91, "Cloyster"},
	{92, "Gastly"},
	{93, "Haunter"},
	{94, "Gengar"},
	{95, "Onix"},
	{96, "Drowzee"},
	{97, "Hypno"},
	{98, "Krabby"}, 
	{99, "Kingler"},
	{100, "Voltorb"},
	{101, "Electrode"},
	{102, "Exeggcute"},
	{103, "Exeggutor"},
	{104, "Cubone"}, 
	{105, "Marowak"},
	{106, "Hitmonlee"},
	{107, "Hitmonchan"},
	{108, "Lickitung"}, 
	{109, "Koffing"},
	{110, "Weezing"},
	{111, "Rhyhorn"},
	{112, "Rhydon"},
	{113, "Chansey"},
	{114, "Tangela"},
	{115, "Kangaskhan"},
	{116, "Horsea"},
	{117, "Seadra"},
	{118, "Goldeen"},
	{119, "Seaking"},
	{120, "Staryu"},
	{121, "Starmie"},
	{122, "Mr. Mime"},
	{123, "Scyther"},
	{124, "Jynx"},
	{125, "Electabuzz"},
	{126, "Magmar"},
	{127, "Pinsir"},
	{128, "Tauros"},
	{129, "Magikarp"},
	{130, "Gyarados"},
	{131, "Lapras"},
	{132, "Ditto"},
	{133, "Eevee"},
	{134, "Vaporeon"},
	{135, "Jolteon"},
	{136, "Flareon"},
	{137, "Porygon"},
	{138, "Omanyte"},
	{139, "Omastar"},
	{140, "Kabuto"},
	{141, "Kabutops"},
	{142, "Aerodactyl"},
	{143, "Snorlax"},
	{144, "Articuno"},
	{145, "Zapdos"},
	{146, "Moltres"},
	{147, "Dratini"},
	{148, "Dragonair"},
	{149, "Dragonite"},
	{150, "Mewtwo"},
	{151, "Mew"},
};
