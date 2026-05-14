#include "Ingredient.h"

Ingredient::Ingredient()
{
    this->name = "";
    this->amount = 0;
    this->capacity = 0;
    this->minThreshold = 0;
}

Ingredient::Ingredient(std::string name, int amount, int capacity, int minThreshold)
{
    this->name = name;
    this->amount = amount;
    this->capacity = capacity;
    this->minThreshold = minThreshold;
}

std::string Ingredient::getName() { return name; }
int Ingredient::getAmount() { return amount; }
int Ingredient::getCapacity() { return capacity; }
int Ingredient::getMinThreshold() { return minThreshold; }

bool Ingredient::isEnough()
{
    return amount > minThreshold;
}

void Ingredient::consume(int value)
{
    amount -= value;
    if (amount < 0) {
        amount = 0;
    }
}

void Ingredient::refill(int value)
{
    amount += value;
    if (amount > capacity) {
        amount = capacity;
		std::cout<< "Przekroczono pojemnosc skladnika " << name << ". Ilosc zostala uzupelniona do maksymalnej pojemnosci.\n";
    }
}