#ifndef TDRINKS_H
#define TDRINKS_H

#pragma once
#include <string>
#include <vector>


// Czym jest kawa?
/*
Historia kawy rozpoczęła się w Etiopii (rejon Kaffa), gdzie według legendy pobudzające właściwości owoców kawowca odkrył pasterz,
obserwując ożywione kozy. Stamtąd trafiła do Jemenu (XV/XVI w.), zyskując popularność w świecie arabskim, a w XVII w. dotarła do Europy.
Od tego czasu nasze życie nie wyglądało już tak samo...
*/

class Tdrinks
{

    std::string name;
    float volume;
    float volumeOfMilk;
    int power;  // Power = (1,2,3,4,5) default = 3


public:

    Tdrinks();
    Tdrinks(std::string name, float volume, float volumeofMilk, int power);
    Tdrinks(const Tdrinks& other);
    ~Tdrinks()=default;
    static void showAll();
    std::string getName() const;
    static int getDrinkId(std::string name);
    int getPowerOfCoffe() const	;
    bool hasMilk();
    float getVolume() const;
    float getVolumeOfMilk() const;
    float getVolumeOfWater() const;
    void show();
    int getAmountOfCoffee();

    void editVolume(float newVolume);
    void editVolumeOfMilk(float newVolumeOfMilk);
    void editPower(int newPower);

    static void addDrink(std::string name, float volume, float volumeOfMilk, int power);
    static void removeDrink(std::string name);

    static void copyDrink(std::string name);

    static Tdrinks* getDrinkByName(std::string name);

};

// Declaration of the global drinks vector used across the module.
// It is defined in Tdrinks.cpp
extern std::vector<Tdrinks*> drinks;

#endif // TDRINKS_H
