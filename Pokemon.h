#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include "olcPixelGameEngine.h"

using namespace std;

class Pokemon {
public:
	string name;
	int id;
	olc::vi2d worldPos;

	Pokemon(int id, string name);
	Pokemon(int id, string name, olc::vi2d worldPos);

	void drawPokemon(olc::PixelGameEngine *pge, olc::Sprite *pokemonSprite, olc::vi2d worldPos);
	void drawPokemon(olc::PixelGameEngine *pge, olc::Sprite *pokemonSprite, float tileOffsetX, float tileOffsetY);
	void drawPokemon(olc::PixelGameEngine *pge, olc::Sprite *pokemonSprite, int &tileX, int &tileY);
	void drawPokemon(string name);

	void draw(olc::PixelGameEngine *pge, olc::Sprite *pokemonSprite, int nOffsetX, int nOffsetY, float tileOffsetX, float tileOffsetY);

	int getRandomPokemonId();
	int getID(string name);
	int getName(int it);
	olc::vi2d getCoordinate();
};

extern vector<Pokemon> allPokemon;

#endif
