#include "CoffeMachine.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

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
    QSqlQuery query;
    query.prepare("SELECT 1 FROM coffemachine LIMIT 1");
    if (query.exec())
    {
        if (!query.next())
        {
            water = Ingredient("Water", maxWaterCapacity/2, maxWaterCapacity, waterMinThreshold);
            beans = Ingredient("Beans", maxBeansCapacity/2, maxBeansCapacity, beansMinThreshold);
            milk = Ingredient("Milk", maxMilkCapacity/2, maxMilkCapacity, milkMinThreshold);

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
    else
    {
       qDebug() << "Error connecting to coffee machine database:" << query.lastError().text();
    }

    loadDrinksToVector();
    loadHistoryFromDatabase();
}

void CoffeMachine::cleanMachine() 
{
	isClean = true;
	cupsSinceLastCleaning = 0;
	std::cout << "Maszyna zostala wyczyszczona\n";
    std::string historyEntry = ("Machine cleaned");
    history.push_back(historyEntry);

    updateDatebase();
    updateHistoryDatebase(historyEntry);
}

void CoffeMachine::addWater(int amount) 
{
	water.refill(amount);
	updateMachineStatus();
    std::string historyEntry = "Added " + std::to_string(amount) + "ml of water";
    history.push_back(historyEntry);

    updateDatebase();
    updateHistoryDatebase(historyEntry);
}

void CoffeMachine::addBeans(int amount) 
{
	beans.refill(amount);
	updateMachineStatus();
    std::string historyEntry = "Added " + std::to_string(amount) + "g of beans";
    history.push_back(historyEntry);

    updateDatebase();
    updateHistoryDatebase(historyEntry);
}

void CoffeMachine::addMilk(int amount) 
{
	milk.refill(amount);
	updateMachineStatus();
    std::string historyEntry = "Added " + std::to_string(amount) + "ml of milk";
    history.push_back(historyEntry);

    updateDatebase();
    updateHistoryDatebase(historyEntry);
}

void CoffeMachine::descaling() 
{
	isOperational = true;
    std::string historyEntry = "Machine descaled";
    history.push_back(historyEntry);

    updateMachineStatus();
    updateDatebase();
    updateHistoryDatebase(historyEntry);
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

bool CoffeMachine::makeCoffee(Tdrinks drink) {
    //Tdrinks* base_drink = Tdrinks::getDrinkByName(drink.getName());  // wskaźnik
    /*if (Tdrinks::getDrinkByName(drink.getName()) == nullptr) {
		std::cout << "Nie ma takiego napoju\n\n";
		return false;
	}
    */

    if (rand() % 100 == 0) {
        isOperational = false;
        std::string historyEntry = "Machine malfunction";
        history.push_back(historyEntry);
        updateDatebase();
        updateHistoryDatebase(historyEntry);
        std::cout << "Maszyna sie zepsula\n";
        return false;
    }

    if (!checkIngredientsFor(drink)) {
		updateMachineStatus();
		std::cout << "Kawa nie zostala przygotowana z powodu niewystarczajacych skladnikow\n\n";
		return false;
	}

	if (cupsSinceLastCleaning >= 10) {
		isClean = false;
		std::cout << "Maszyna wymaga czyszczenia po " << cupsSinceLastCleaning << " kawach!\n";
	}

    drink.show();
    water.consume(drink.getVolumeOfWater());
    beans.consume(drink.getAmountOfCoffee());
    milk.consume(drink.getVolumeOfMilk());

	cupsServed++;
	cupsSinceLastCleaning++;

    std::string historyEntry="Made " + drink.getName() + " (Cup #" + std::to_string(cupsServed) + ")";
    history.push_back(historyEntry);

    updateMachineStatus();
    updateDatebase();
    updateHistoryDatebase(historyEntry);

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
    for (Tdrinks* drink : drinks)
    {
        delete drink;
    }

    drinks.clear();

    QSqlQuery query;
    query.prepare("SELECT name, volume, volumeofMilk, power FROM drinks");

    if (query.exec())
    {
        while (query.next())
        {
            if (!query.value("name").isNull())
            {
                std::string nativeString = query.value("name").toString().toStdString();
                float volume             = query.value("volume").toFloat();
                float volumeofMilk       = query.value("volumeofMilk").toFloat();
                int power                = query.value("power").toInt();

                Tdrinks* drink = new Tdrinks(nativeString, volume, volumeofMilk, power);
                drinks.push_back(drink);
            }
        }
    }
    else
    {
        qDebug() << "Error loading drinks:" << query.lastError().text();
    }
}

CoffeMachine machine;

void CoffeMachine::updateDatebase() {
    QSqlQuery query;

    query.prepare("UPDATE coffemachine SET "
                  "water = :water, "
                  "milk = :milk, "
                  "beans = :beans, "
                  "cupsServed = :cupsServed, "
                  "cupsSinceLastCleaning = :cupsSinceLastCleaning, "
                  "isOperational = :isOperational, "
                  "isClean = :isClean");

    query.bindValue(":water", water.getAmount());
    query.bindValue(":milk", milk.getAmount());
    query.bindValue(":beans", beans.getAmount());
    query.bindValue(":cupsServed", cupsServed);
    query.bindValue(":cupsSinceLastCleaning", cupsSinceLastCleaning);
    query.bindValue(":isOperational", isOperational);
    query.bindValue(":isClean", isClean);

    if (!query.exec()) {
        qDebug() << "Error updating coffee machine database:" << query.lastError().text();
    } else {
        qDebug() << "Database updated successfully!";
        query.finish();
    }
}

void CoffeMachine::loadFromDatabase() {
    QSqlQuery query;
    query.prepare("SELECT water, milk, beans, cupsServed, cupsSinceLastCleaning, isOperational, isClean FROM coffemachine LIMIT 1");

    if (query.exec())
    {
        if (query.next())
        {
            float storedWater = query.value("water").toFloat();
            float storedMilk  = query.value("milk").toFloat();
            float storedBeans = query.value("beans").toFloat();

            water = Ingredient("Water", storedWater, maxWaterCapacity, waterMinThreshold);
            milk  = Ingredient("Milk", storedMilk, maxMilkCapacity, milkMinThreshold);
            beans = Ingredient("Beans", storedBeans, maxBeansCapacity, beansMinThreshold);

            cupsServed             = query.value("cupsServed").toInt();
            cupsSinceLastCleaning  = query.value("cupsSinceLastCleaning").toInt();
            isOperational          = query.value("isOperational").toBool();
            isClean                = query.value("isClean").toBool();

            qDebug() << "Successfully loaded coffee machine state from database.";
        }
    }
    else
    {
        qDebug() << "Error loading coffee machine database:" << query.lastError().text();
    }
}

void CoffeMachine::resetMachine()
{
    QSqlQuery query;
    query.prepare("DELETE FROM coffemachine");

    if (query.exec())
    {
        qDebug() << "Successfully cleared 'coffemachine' table.";

        initializeMachine();
        deleteHistory();
    }
    else
    {
        qDebug() << "Error deleting coffee machine database:" << query.lastError().text();
    }
}

void CoffeMachine::insertIntoDatebase() {
    QSqlQuery query;

    query.prepare("INSERT INTO coffemachine (water, milk, beans, cupsServed, cupsSinceLastCleaning, isOperational, isClean) "
                  "VALUES (:water, :milk, :beans, :cupsServed, :cupsSinceLastCleaning, :isOperational, :isClean)");

    query.bindValue(":water", water.getAmount());
    query.bindValue(":milk", milk.getAmount());
    query.bindValue(":beans", beans.getAmount());
    query.bindValue(":cupsServed", cupsServed);
    query.bindValue(":cupsSinceLastCleaning", cupsSinceLastCleaning);
    query.bindValue(":isOperational", isOperational);
    query.bindValue(":isClean", isClean);

    if (!query.exec()) {
        qDebug() << "Error inserting into coffee machine database:" << query.lastError().text();
    } else {
        qDebug() << "Initial coffee machine state successfully inserted into database.";
        query.finish();
    }
}

void CoffeMachine::updateHistoryDatebase(std::string HistoryEntry) {
    QSqlQuery query;

    query.prepare("INSERT INTO history (entry) VALUES (:entry)");

    query.bindValue(":entry", QString::fromStdString(HistoryEntry));

    if (!query.exec()) {
        qDebug() << "Error updating history database:" << query.lastError().text();
    } else {
        qDebug() << "History entry successfully added to database.";
        query.finish();
    }
}

void CoffeMachine::loadHistoryFromDatabase() {
    history.clear();

    QSqlQuery query;
    query.prepare("SELECT entry FROM history");

    if (query.exec())
    {
        while (query.next())
        {
            if (!query.value("entry").isNull())
            {
                std::string nativeString = query.value("entry").toString().toStdString();

                history.push_back(nativeString);
            }
        }
        qDebug() << "Successfully loaded history from database. Total entries:" << history.size();
    }
    else
    {
        qDebug() << "Error loading history from database:" << query.lastError().text();
    }
}

void CoffeMachine::deleteHistory() {
    QSqlQuery query;

    bool success = query.exec("DROP TABLE IF EXISTS history;");

    if (success) {
        QSqlQuery resetQuery;
        query.exec("CREATE TABLE history ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "entry TEXT);");
        history.clear();
        qDebug() << "History table successfully cleared.";
    } else {
        qDebug() << "Error deleting history from database:" << query.lastError().text();
    }
}