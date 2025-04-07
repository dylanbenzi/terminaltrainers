#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include "olcPixelGameEngine.h"

using namespace std;

class Pokemon {
public:
	string name;
	int id;

	Pokemon(int id, string name);

	void drawPokemon(int id);
	void drawPokemon(string name);

	int getID(string name);
	int getName(int it);
};

extern vector<Pokemon> allPokemon;

#endif
