#include<iostream>
#include"Tdrinks.h"
#include"Ingredient.h"
#include"CoffeMachine.h"
#include<string>
#include<vector>

using namespace std;

int main() {
	Tdrinks drink("ekspresso", 100, 100);
	drink.show();

	return 0;
}