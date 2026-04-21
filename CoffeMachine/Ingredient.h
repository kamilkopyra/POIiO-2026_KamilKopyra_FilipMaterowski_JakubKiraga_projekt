#pragma once
#include <string>


class Ingredient {
        std::string name;
        int quantity;     
        int capacity;     
    public:
        bool isEnough(int needed);
        void consume(int amount);
        void refill();
};
