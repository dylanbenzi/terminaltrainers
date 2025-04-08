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

	olc::vi2d getCoordinate();
};

//global vector of 151 pokemon
extern const vector<Pokemon> allPokemon;

#endif
