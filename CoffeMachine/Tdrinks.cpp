#include <iostream>
#include <string>
#include <vector>
#include "Tdrinks.h"
#include <msclr/marshal_cppstd.h>
using namespace std;
using namespace System;
using namespace System::Data::SQLite;
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
			cout << "Nie znaleziono napoju o podanej nazwie: \"" << name << "\"!\n";
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

void Tdrinks::addDrink(std::string name, float volume, float volumeOfMilk, int power) {
	drinks.push_back(new Tdrinks(name, volume, volumeOfMilk, power));
	System::String^ connectionString = "Data Source=coffemachine.db;Version=3;";

	System::String^ sql = "INSERT INTO drinks (name, volume, volumeofMilk, power, favourite) VALUES (@name, @volume, @volumeOfMilk, @power, @favourite)";

	try
	{
		System::Data::SQLite::SQLiteConnection connection(connectionString);
		connection.Open();

		System::Data::SQLite::SQLiteCommand^ command = gcnew System::Data::SQLite::SQLiteCommand(sql, % connection);

		System::String^ managedName = gcnew System::String(name.c_str());

		command->Parameters->AddWithValue("@name", managedName);
		command->Parameters->AddWithValue("@volume", volume);
		command->Parameters->AddWithValue("@volumeOfMilk", volumeOfMilk);
		command->Parameters->AddWithValue("@power", power);
		command->Parameters->AddWithValue("@favourite", 0); // Domyœlnie ustawiamy na 0 (nie ulubiony)

		command->ExecuteNonQuery();
	}
	catch (System::Exception^ ex)
	{
		std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
		std::cout << "Error adding drink: " << errorMsg << "\n";
	}
}

void Tdrinks::removeDrink(std::string name) {
	int _id = getDrinkId (name);
	if (_id > 26) {
		System::String^ connectionString = "Data Source=coffemachine.db;Version=3;";
		System::String^ sql = "DELETE FROM drinks WHERE name = @name";

		try
		{
			System::Data::SQLite::SQLiteConnection connection(connectionString);
			connection.Open();

			System::Data::SQLite::SQLiteCommand^ command = gcnew System::Data::SQLite::SQLiteCommand(sql, % connection);

			System::String^ managedName = gcnew System::String(name.c_str());
			command->Parameters->AddWithValue("@name", managedName);

			command->ExecuteNonQuery();
		}
		catch (System::Exception^ ex)
		{
			std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
			std::cout << "Error removing drink: " << errorMsg << "\n";
		}

		for (int i = 0; i < drinks.size(); i++) {
			if (drinks[i]->getName() == name) {
				delete drinks[i];
				drinks.erase(drinks.begin() + i);
				return;
			}
		}
	}
	else 
	{
		std::cout << "Nie mo¿na usun¹æ tego napoju, poniewa¿ jest to jeden z domyœlnych napojów (ID <= 26).\n";
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

vector<Tdrinks*> drinks;

// funkcja do znajdywania napoju po nazwie
Tdrinks* Tdrinks::getDrinkByName(std::string name) {
	int count = drinks.size();
	for (int i = 0; i < count; i++) 
	{
		if (drinks[i]->getName() == name)
		{
			return drinks[i];
		}
	}
	return nullptr;  
}
/*
void Tdrinks::LoadDrinksToVector() 
{
	String^ connectionString = "Data Source=coffemachine.db;Version=3;";
	String^ sql = "SELECT * FROM drinks"; 

	try
	{
		SQLiteConnection connection(connectionString);
		connection.Open();

		SQLiteCommand^ command = gcnew SQLiteCommand(sql, % connection);
		SQLiteDataReader^ reader = command->ExecuteReader();

		while (reader->Read())
		{
			if (reader["name"] != DBNull::Value)
			{
				String^ managedString = reader["name"]->ToString();

				float volume = Convert::ToSingle(reader["volume"]);
				float volumeofMilk = Convert::ToSingle(reader["volumeofMilk"]);
				int power = Convert::ToSingle(reader["power"]);
				std::string nativeString = msclr::interop::marshal_as<std::string>(managedString);
				Tdrinks drink=Tdrinks(nativeString, volume, volumeofMilk, power);
				Tdrinks::drinks.push_back(drink);
			}
		}

		reader->Close();
	}
	catch (Exception^ ex)
	{
		std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
		cout << "Error loading drinks: " << errorMsg << endl;
	}
}
*/