#pragma once
#include "character.h"

class Relation {
public:
	Relation() = default;
	Relation(Character character);

private:
	float familiarity;
	float respect;
	float favorability;
	float trust;
	float reliability;
	float competitivity;
};