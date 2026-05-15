#pragma once
#include <iostream>
#include <string>

class Ingredient
{
public:
    Ingredient();
    Ingredient(std::string name, int amount, int capacity, int minThreshold);

    std::string getName();
    int getAmount();
    int getCapacity();
    int getMinThreshold();
    bool isEnough();
    void consume(int value);
    void refill(int value);

private:
    std::string name;
    int amount;
    int capacity;
    int minThreshold;
};