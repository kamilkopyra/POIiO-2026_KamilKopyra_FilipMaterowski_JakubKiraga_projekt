#include <iostream>
#include <string>
#include <vector>

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "Tdrinks.h"
using namespace std;

// Constructor to initialize the name and volume of the drink
Tdrinks::Tdrinks(string name, float volume, float volumeofMilk, int power)
{
    this->name = name;
    this->volume = volume;
    this->volumeOfMilk = volumeofMilk;
    this->power = power;
}

Tdrinks::Tdrinks(const Tdrinks& other) {

    this->name = other.getName() + "_copy" + std::to_string(rand() % 1000);
    this->volume = other.getVolumeOfWater();
    this->volumeOfMilk = other.getVolumeOfMilk();
    this->power = other.getPowerOfCoffe();
}

void Tdrinks::showAll() {
    for (int i = 0; i < drinks.size(); i++) {
        std::cout << drinks[i]->getName() << endl;
    }
}

int Tdrinks::getDrinkId(string name)
{
    int count = drinks.size();
    int _id = -1;
    bool run = true;

    while (run)
    {
        _id += 1;
        string sub_name = drinks[_id]->getName();

        if (sub_name == name) run = false;

        if ((_id + 1 == count) && (run == true))
        {
            cout << "Nie znaleziono plynu o podanej nazwie: \"" << name << "\"!\n";
            run = false;
            _id = -1;
        }
    }
    return _id;
}


// Returns the name of the drink
std::string Tdrinks::getName() const
{
    return name;
}
// Returns the volume of the drink
float Tdrinks::getVolume() const
{
    return volume + volumeOfMilk;
}
float Tdrinks::getVolumeOfWater() const
{
    return volume;
}
float Tdrinks::getVolumeOfMilk() const
{
    return volumeOfMilk;
}


int Tdrinks::getPowerOfCoffe() const
{
    return power;
}

void Tdrinks::show()
{
    std::cout << "Informacje o napoju:\n";
    std::cout << "Nazwa: " << getName() << "\n";
    std::cout << "Ilosc kawy :  " << getVolume() << " ml\n";
    std::cout << "Ilosc wody:  " << getVolumeOfWater() << " ml\n";
    std::cout << "Ilosc mleka:  " << getVolumeOfMilk() << " ml\n";
    std::cout << "Moc: " << getPowerOfCoffe() << "\n";
    std::cout << "Ilosc ziaren kawy: " << getAmountOfCoffee() << " g\n";
    std::cout << "----------------------------\n";
}

void Tdrinks::editVolume(float newVolume) {
    volume = newVolume;
}
void Tdrinks::editVolumeOfMilk(float newVolumeOfMilk) {
    volumeOfMilk = newVolumeOfMilk;
}
void Tdrinks::editPower(int newPower) {
    power = newPower;
}


// zmieni³em ¿eby dodawanie by³o ³atwiejsze, napój jest dodawany bezpoœrednio do wektora po utworzeniu
void Tdrinks::addDrink(std::string name, float volume, float volumeOfMilk, int power) {
    Tdrinks(name, volume, volumeOfMilk, power);
    drinks.push_back(new Tdrinks(name, volume, volumeOfMilk, power));

    QSqlQuery query;
    query.prepare("INSERT INTO drinks (name, volume, volumeofMilk, power, favourite) "
                  "VALUES (:name, :volume, :volumeOfMilk, :power, :favourite)");

    query.bindValue(":name", QString::fromStdString(name));
    query.bindValue(":volume", volume);
    query.bindValue(":volumeOfMilk", volumeOfMilk);
    query.bindValue(":power", power);
    query.bindValue(":favourite", 0); // Domyślnie 0 (fałsz)

    if (query.exec()) {
        qDebug() << "Successfully added drink to database:" << QString::fromStdString(name);
    } else {
        qDebug() << "Error adding drink to database:" << query.lastError().text();
    }
}

void Tdrinks::removeDrink(std::string name) {
    int _id = getDrinkId(name);

    if (_id > 26) {
        QSqlQuery query;
        query.prepare("DELETE FROM drinks WHERE name = :name");
        query.bindValue(":name", QString::fromStdString(name));

        if (query.exec()) {
            qDebug() << "Successfully removed drink from database:" << QString::fromStdString(name);
        } else {
            qDebug() << "Error removing drink from database:" << query.lastError().text();
        }

        for (size_t i = 0; i < drinks.size(); i++) {
            if (drinks[i]->getName() == name) {
                delete drinks[i];
                drinks.erase(drinks.begin() + i);
                return;
            }
        }
    }
    else {
        qDebug() << "Nie można usunąć tego napoju, ponieważ jest to jeden z domyślnych napojów (ID <= 26).";
    }
}
int Tdrinks::getAmountOfCoffee() {
    float AmountPerVolume;
    switch (power) {
    case 1:
        AmountPerVolume = 8.0/250.0;
        break;
    case 2:
        AmountPerVolume = 10.0/250.0;
        break;
    case 3:
        AmountPerVolume = 14.0/250.0;
        break;
    case 4:
        AmountPerVolume = 16.0/250.0;
        break;
    case 5:
        AmountPerVolume = 18.0/250.0;
        break;
    default:
        std::cout << "Invalid power level. Setting to default (3).\n";
        power = 3;
        AmountPerVolume = 14.0 / 250.0;
        break;


    }
    return int(AmountPerVolume * volume);
}

void Tdrinks::copyDrink(std::string name) {
    for (auto& drink : drinks) {
        if (drink->getName() == name) {
            //cout << "Nie znaleziono napoju o nazwie: \" " << name << "\"!\n";
            drinks.push_back(new Tdrinks(*drink));
            cout << "Napoj \"" << name << "\" zostal skopiowany jako \"" << drinks.back()->getName() << "\"\n";
            return;
        }
    }
    cout << "Nie znaleziono napoju o nazwie: \"" << name << "\"!\n";
    return;
}
// List of drinks with their names and volumes
// (nazwa, iloœæ wody, iloœæ mleka, moc)
std::vector<Tdrinks*> drinks;


// funkcja do znajdywania napoju po nazwie
Tdrinks* Tdrinks::getDrinkByName(std::string name) {
    for (auto& drink : drinks) {
        if (drink->getName() == name) {
            return drink;
        }
    }
    return nullptr;
}