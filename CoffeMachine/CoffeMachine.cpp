#include "CoffeMachine.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Data::SQLite;


CoffeMachine::CoffeMachine() {
}
void CoffeMachine::updateMachineStatus() {
	// Implementation to return the current status of the machine


	hasMilk = milk.isEnough();
	hasWater = water.isEnough();
	hasBeans = beans.isEnough();
	
	if (!hasMilk) std::cout << "Dolej mleka\n";
	else if (!hasWater) std::cout << "Dolej wode\n";
	else if (!hasBeans) std::cout << "Dosyp ziarna\n";
	else std::cout << "Wystarczajace skladniki\n";
}


void CoffeMachine::initializeMachine() 
{
	{
		System::String^ connectionString = "Data Source=coffemachine.db;Version=3;";
		System::String^ sql = "SELECT 1 FROM coffemachine LIMIT 1";

		try
		{
			System::Data::SQLite::SQLiteConnection connection(connectionString);
			connection.Open();

			System::Data::SQLite::SQLiteCommand^ command = gcnew System::Data::SQLite::SQLiteCommand(sql, % connection);
			System::Object^ result = command->ExecuteScalar();

			if (result == nullptr)
			{
				water = Ingredient("Water", maxWaterCapacity / 2, maxWaterCapacity, waterMinThreshold);
				beans = Ingredient("Beans", maxBeansCapacity / 2, maxBeansCapacity, beansMinThreshold);
				milk = Ingredient("Milk", maxMilkCapacity / 2, maxMilkCapacity, milkMinThreshold);

				isOperational = true;
				isClean = true;
				cupsServed = 0;
				cupsSinceLastCleaning = 0;



				insertIntoDatebase();
				
			}

			else
			{
				loadFromDatabase();
			}
		}
		catch (System::Exception^ ex)
		{
			std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
			std::cout << "Error connecting to coffe machine database: " << errorMsg << "\n";
		}
	}


	loadDrinksToVector();
}

void CoffeMachine::cleanMachine() 
{
	isClean = true;
	cupsSinceLastCleaning = 0;
	std::cout << "Maszyna zostala wyczyszczona\n";
	history.push_back("Machine cleaned");

	updateDatebase();
}

void CoffeMachine::addWater(int amount) 
{
	water.refill(amount);
	updateMachineStatus();
	history.push_back("Added " + std::to_string(amount) + "ml of water");

	updateDatebase();
}

void CoffeMachine::addBeans(int amount) 
{
	beans.refill(amount);
	updateMachineStatus();
	history.push_back("Added " + std::to_string(amount) + "g of beans");

	updateDatebase();
}

void CoffeMachine::addMilk(int amount) 
{
	milk.refill(amount);
	updateMachineStatus();
	history.push_back("Added " + std::to_string(amount) + "ml of milk");

	updateDatebase();
}

void CoffeMachine::descaling() 
{
	isOperational = true;
	history.push_back("Machine descaled");

	updateDatebase();
}

bool CoffeMachine::checkIngredientsFor(Tdrinks drink) 
{
	return water.getAmount() >= drink.getVolume()
		&& milk.getAmount() >= drink.getVolumeOfMilk()
		&& beans.getAmount() >= drink.getAmountOfCoffee();
}


void CoffeMachine::printStatus()
{
	std::cout << "Machine Status:\n";
	std::cout << "Water: " << water.getAmount() << "ml\n";
	std::cout << "Beans: " << beans.getAmount() << "g\n";
	std::cout << "Milk: " << milk.getAmount() << "ml\n";
	std::cout << "Cups Served: " << cupsServed << "\n";
	std::cout << "Operational: " << (isOperational ? "Yes" : "No") << "\n";
	std::cout << "Cups Since Last Cleaning: " << cupsSinceLastCleaning << "\n";
	std::cout << "Clean: " << (isClean ? "Yes" : "No") << "\n";
	std::cout << "\n\n\n";
}

bool CoffeMachine::makeCoffee(std::string drinkName) {
	Tdrinks* drink = Tdrinks::getDrinkByName(drinkName);  // wskaźnik
	if (drink == nullptr) {
		std::cout << "Nie ma takiego napoju\n\n";
		return false;
	}

	if (!checkIngredientsFor(*drink)) {  
		updateMachineStatus();
		std::cout << "Kawa nie zostala przygotowana z powodu niewystarczajacych skladnikow\n\n";
		return false;
	}

	if (cupsSinceLastCleaning >= 10) {
		isClean = false;
		std::cout << "Maszyna wymaga czyszczenia po " << cupsSinceLastCleaning << " kawach!\n";
	}

	drink->show();  
	water.consume(drink->getVolumeOfWater());  
	beans.consume(drink->getAmountOfCoffee());  
	milk.consume(drink->getVolumeOfMilk());     

	cupsServed++;
	cupsSinceLastCleaning++;

	history.push_back("Made " + drink->getName() + " (Cup #" + std::to_string(cupsServed) + ")");  

	updateMachineStatus();
	updateDatebase();

	return true;
}

void CoffeMachine::printHistory()
{
	std::cout << "\n=== HISTORIA MASZYNY ===\n";

	if (history.empty()) {
		std::cout << "Brak historii.\n";
		return;
	}

	for (int i = 0; i < history.size(); i++) {
		std::cout << i + 1 << ". " << history[i] << "\n";
	}
	std::cout << "========================\n";
}


void CoffeMachine::loadDrinksToVector()
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
				Tdrinks drink = Tdrinks(nativeString, volume, volumeofMilk, power);
				Tdrinks::drinks.push_back(drink);
			}
		}

		reader->Close();
	}
	catch (Exception^ ex)
	{
		std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
		std::cout << "Error loading drinks: " << errorMsg << "\n";
	}
}


void CoffeMachine::updateDatebase() {
	System::String^ connectionString = "Data Source=coffemachine.db;Version=3;";
	System::String^ sql = "UPDATE coffemachine SET water = @water, milk = @milk, beans = @beans, cupsServed = @cupsServed, cupsSinceLastCleaning = @cupsSinceLastCleaning, isOperational = @isOperational, isClean = @isClean";
	try
	{
		System::Data::SQLite::SQLiteConnection connection(connectionString);
		connection.Open();
		System::Data::SQLite::SQLiteCommand^ command = gcnew System::Data::SQLite::SQLiteCommand(sql, % connection);
		command->Parameters->AddWithValue("@water", water.getAmount());
		command->Parameters->AddWithValue("@milk", milk.getAmount());
		command->Parameters->AddWithValue("@beans", beans.getAmount());
		command->Parameters->AddWithValue("@cupsServed", cupsServed);
		command->Parameters->AddWithValue("@cupsSinceLastCleaning", cupsSinceLastCleaning);
		command->Parameters->AddWithValue("@isOperational", isOperational);
		command->Parameters->AddWithValue("@isClean", isClean);
		command->ExecuteNonQuery();
	}
	catch (System::Exception^ ex)
	{
		std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
		std::cout << "Error updating coffe machine database: " << errorMsg << "\n";
	}
}

void CoffeMachine::loadFromDatabase() {
	System::String^ connectionString = "Data Source=coffemachine.db;Version=3;";
	System::String^ sql = "SELECT * FROM coffemachine LIMIT 1";
	try
	{
		System::Data::SQLite::SQLiteConnection connection(connectionString);
		connection.Open();
		System::Data::SQLite::SQLiteCommand^ command = gcnew System::Data::SQLite::SQLiteCommand(sql, % connection);
		System::Data::SQLite::SQLiteDataReader^ reader = command->ExecuteReader();
		if (reader->Read())
		{
			float storedWater = System::Convert::ToSingle(reader["water"]);
			float storedMilk = System::Convert::ToSingle(reader["milk"]);
			float storedBeans = System::Convert::ToSingle(reader["beans"]);
			water = Ingredient("Water", storedWater, maxWaterCapacity, waterMinThreshold);
			milk = Ingredient("Milk", storedMilk, maxMilkCapacity, milkMinThreshold);
			beans = Ingredient("Beans", storedBeans, maxBeansCapacity, beansMinThreshold);
			cupsServed = System::Convert::ToInt32(reader["cupsServed"]);
			cupsSinceLastCleaning = System::Convert::ToInt32(reader["cupsSinceLastCleaning"]);
			isOperational = System::Convert::ToBoolean(reader["isOperational"]);
			isClean = System::Convert::ToBoolean(reader["isClean"]);
		}
		reader->Close();
	}
	catch (System::Exception^ ex)
	{
		std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
		std::cout << "Error loading coffe machine database: " << errorMsg << "\n";
	}
}

void CoffeMachine::resetMachine()
{
	System::String^ connectionString = "Data Source=coffemachine.db;Version=3;";
	System::String^ sql = "DELETE FROM coffemachine";

	try
	{ 
		System::Data::SQLite::SQLiteConnection connection(connectionString);
		connection.Open();

		System::Data::SQLite::SQLiteCommand^ command = gcnew System::Data::SQLite::SQLiteCommand(sql, % connection);

		command->ExecuteNonQuery();

		initializeMachine();
	}
	catch(System::Exception^ ex)
	{ 
		std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
		std::cout << "Error deleting coffe machine database: " << errorMsg << "\n";
	}
}

void CoffeMachine::insertIntoDatebase() {
	System::String^ connectionString = "Data Source=coffemachine.db;Version=3;";
	System::String^ sql = "INSERT INTO coffemachine (water, milk, beans, cupsServed, cupsSinceLastCleaning, isOperational, isClean) VALUES (@water, @milk, @beans, @cupsServed, @cupsSinceLastCleaning, @isOperational, @isClean)";
	try
	{
		System::Data::SQLite::SQLiteConnection connection(connectionString);
		connection.Open();
		System::Data::SQLite::SQLiteCommand^ command = gcnew System::Data::SQLite::SQLiteCommand(sql, % connection);
		command->Parameters->AddWithValue("@water", water.getAmount());
		command->Parameters->AddWithValue("@milk", milk.getAmount());
		command->Parameters->AddWithValue("@beans", beans.getAmount());
		command->Parameters->AddWithValue("@cupsServed", cupsServed);
		command->Parameters->AddWithValue("@cupsSinceLastCleaning", cupsSinceLastCleaning);
		command->Parameters->AddWithValue("@isOperational", isOperational);
		command->Parameters->AddWithValue("@isClean", isClean);
		command->ExecuteNonQuery();
	}
	catch (System::Exception^ ex)
	{
		std::string errorMsg = msclr::interop::marshal_as<std::string>(ex->Message);
		std::cout << "Error inserting into coffe machine database: " << errorMsg << "\n";
	}
}