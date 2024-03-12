// csvFileGenerator.cpp : 
// Generates csv files that I will use as dummy data for mySQL database
// Generates 4 csv files with headers:
//      -customerData.csv: Customer ID, First Name, Last Name, Street Address, City Name
//      -itemPrice.csv: Product ID, Item Size, Item Name, Item Price
//      -itemSuppliers.csv: Supply ID, Product ID, Item Size, Item Name, Item Supplier
//      -salesLog.csv: Sale ID, Customer ID, Product ID, Quantity Purchased, Date Purchased



#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const int NUM_CUSTOMERS = 500; // Number of customer records to generate.
const int STREET_NUM = 99; // Max street number for customer addresses.
const int SMOL_MULT = 1; // Multiplier to base price for small version of an item.
const int REGULAR_MULT = 3; // Multiplier to base price for medium version of an item.
const int HYOOGE_MULT = 5; // Multiplier to base price for large version of an item. 
const int MAX_PRICE = 10; // Max price for base item.
const int MAX_CUST_ID = 5000; // Modulus used to create customer ID, completely arbitrary.
const int MAX_PROD_ID = 2000; // Modulus used to create product ID, completely arbitrary.
const int MAX_SUPP_ID = 200; // Modulus used to create supplier ID, completelyl arbitrary.
const int MAX_SALE_ID = 9000; // Modulus used to create supplier ID, completely arbitrary.
const int MAX_SOLD_ITEMS = 5; // Max quantity of any one item sold.
const int NUM_SOLD_RECORDS = 5000; // Number of sold item records to generate.

int makeCustomerCSV(int custID, vector<string>& custFirstName, vector<string>& custLastName , vector<string> custStreetName, vector<string> custStreetType, vector<string> custCityName, vector<string> custCityType);
int makePriceTableCSV(int prodID, vector<string>& priceItemSize, vector<string>& priceItemName, vector<int>& itemPriceMultiplier);
int makeSupplierSheetCSV(int suppID, int prodID, vector<string>& priceItemSize, vector<string>& priceItemName, vector<string>& itemDistributorName);
int makeSalesLogCSV(int saleID, int custID, int prodID, int productCount);

int main()
{
    //Identifying Customer Information
    vector<string> firstName = { "Rocket", "Joplin", "Mack", "Lucy", "Murphy", "Yang", "Oliver", "Riley", "Willow", "Charlie", "Buddy", "Chelsea", "Buddy II", "Chloe", "Nora", "Brenda", "Nala", "Drax", "Finn", "Petey", "Meatballs", "Noodles", "Stinky Boy", "Curly Tail", "Mr. Pup", "Mr. Puppy", "Mr. Dog", "Rocco", "LuLu", "Jops", "Macky Poo", "Murphy Poo" }; // Names and nicknames for the dogs in my life (past and present)
    vector<string> lastName = { "Barksalot", "Snifferson", "Digsby", "McPetme", "Snuffleski", "Howler", "Sleeperson", "Bonesly", "Toughguy", "Crapperson", "McBeggsly", "Noseston", "Sitstayski", "Goodboi", "Floppyearston", "Pointersly", "Ruffalo" }; // Some stupid last names
    vector<string> streetName = { "Bark", "Sniff", "Dig", "Ruff", "Bone", "Ear Flop", "Waggy Tail", "Fire Hydrant", "Neighbors Bush", "Pile of Socks", "Old Shoes", "Ball", "Open Field", "Squirrel", "Chaser", "Sir Dogton", "Rabbit Chase" };
    vector<string> streetType = { "Rd", "Ave", "St", "Rt", "Circ", "Blvd" };
    vector<string> cityName = { "Pup", "Dog"};
    vector<string> cityType = { "ville", "burg", " City", " Township", " Villiage", "ton"};
    // No zip, state or country because it needlessly complicated things, and frankly didn't add anything of interest to the data. 

    //Item Identification
    vector<string> itemSize = { "Smol", "Regular", "Hyooge" };
    vector<string> itemName = { "Ball", "Used Socks", "Raw Hide", "Bone", "Human Food", "Treats", "Stuffies", "Tug Toy", "Phallic Chew Toy", "Canned Dog Food", "Used Tissues", "Auto-petter", "Love and Affection", "Chicken Jerky", "Pig Ears" };
    vector<int> priceMultiplier = {SMOL_MULT, REGULAR_MULT, HYOOGE_MULT};
    vector<string> distributorName = { "Trash Can", "Small Child", "Nefarious Mailman", "It Just Shows Up" };

    cout << "It's doing stuff" << endl << endl;

    srand(time(0));

    int randCustID = (rand() % MAX_CUST_ID);
    cout << "Customer ID starts at: " << randCustID << endl;
    makeCustomerCSV(randCustID, firstName , lastName , streetName, streetType, cityName, cityType);

    int randProdID = (rand() % MAX_PROD_ID);
    cout << "Product ID starts at: " << randProdID << endl;
    makePriceTableCSV(randProdID, itemSize, itemName, priceMultiplier);

    int randSuppID = (rand() % MAX_SUPP_ID);
    cout << "Supplier ID starts at: " << randSuppID << endl;
    makeSupplierSheetCSV(randSuppID, randProdID, itemSize, itemName, distributorName);

    int randSaleID = (rand() % MAX_SALE_ID);
    cout << "Sale ID starts at: " << randSaleID << endl;
    makeSalesLogCSV(randSaleID, randCustID, randProdID, (itemSize.size() * itemName.size()));

    cout << endl << "Now it's done!" << endl;
}

int makeCustomerCSV(int custID, vector<string>& custFirstName, vector<string>& custLastName, vector<string> custStreetName, vector<string> custStreetType, vector<string> custCityName, vector<string> custCityType) {
    ofstream customerFile;

    customerFile.open("customerData.csv");
    customerFile << "\"Cust_ID\",\"First_Name\",\"Last_Name\",\"Street_Address\",\"City_Name\"\n";

    srand(time(0));

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        string writeString = "";
        
        // Customer ID
        writeString += "\"CUST" + to_string(custID + i) + "\",";

        // First Name
        writeString += "\"" + custFirstName[(rand() % (custFirstName.size()))] + "\",";

        // Last Name
        writeString += "\"" + custLastName[(rand() % (custLastName.size()))] + "\",";

        // Street Number
        writeString += "\"" + to_string(rand() % STREET_NUM + 1) + " ";

        // Street Name
        writeString += custStreetName[(rand() % (custStreetName.size()))] + " ";

        // Street Type
        writeString += custStreetType[(rand() % (custStreetType.size()))] + "\",";

        //City Name
        writeString += "\"" + custCityName[(rand() % (custCityName.size()))];

        //City Type
        writeString += custCityType[(rand() % (custCityType.size()))] + "\"";

        writeString += "\n";
        customerFile << writeString;
    }

    customerFile.close();
    return 0;
}

int makePriceTableCSV(int prodID, vector<string>& priceItemSize, vector<string>& priceItemName, vector<int>& itemPriceMultiplier) {
    ofstream itemPriceFile;

    itemPriceFile.open("itemPrice.csv");
    itemPriceFile << "\"Prod_ID\",\"Item_Size\",\"Item_Name\",\"Item_Price\"\n";

    srand(time(0));

    for (int i = 0; i < priceItemName.size(); i++) {
        string writeString = "";
        int basePrice = (rand() % MAX_PRICE) + 1;

        for (int j = 0; j < priceItemSize.size(); j++) {
            writeString += "\"PROD" + to_string(prodID++) + "\","; // PROD ID
            writeString += "\"" + priceItemSize[j] + "\","; // SIZE
            writeString += "\"" + priceItemName[i] + "\","; // ITEM
            writeString += "\"" + to_string((itemPriceMultiplier[j] * basePrice)) + "\""; // PRICE
            writeString += "\n";
        }
        itemPriceFile << writeString;
    }

    itemPriceFile.close();
    return 0;
}

int makeSupplierSheetCSV(int suppID, int prodID, vector<string>& priceItemSize, vector<string>& priceItemName, vector<string>& itemDistributorName) {
    ofstream supplierFile;

    supplierFile.open("itemSuppliers.csv");
    supplierFile << "\"Supp_ID\",\"Prod_ID\",\"Item_Size\",\"Item_Name\",\"Item_Supplier\"\n";

    srand(time(0));

    for (int i = 0; i < priceItemName.size(); i++) {
        string writeString = "";

        for (int j = 0; j < priceItemSize.size(); j++) {
            writeString += "\"SUPP" + to_string(suppID++) + "\","; // SUPPLIER ID
            writeString += "\"PROD" + to_string(prodID++) + "\","; // PRODUCT ID
            writeString += "\"" + priceItemSize[j] + "\","; // SIZE
            writeString += "\"" + priceItemName[i] + "\","; // ITEM
            writeString += "\"" + itemDistributorName[(rand() % (itemDistributorName.size()))] + "\""; // PRICE
            writeString += "\n";
        }
        supplierFile << writeString;
    }


    supplierFile.close();
    return 0;
}

int makeSalesLogCSV(int saleID, int custID, int prodID, int productCount) {
    ofstream salesLogFile;

    salesLogFile.open("salesLog.csv");
    salesLogFile << "\"Sale_ID\",\"Cust_ID\",\"Prod_ID\",\"Qty_Purchased\",\"Date_Purchased\"\n";

    srand(time(0));

    for (int i = 0; i < NUM_SOLD_RECORDS ;i++) {
        string writeString = "";

        writeString += "\"SALE" + to_string(saleID) + "\","; // SALE ID

        // Determine customer ID
        int randCustID = (rand() % NUM_CUSTOMERS) + custID;
        writeString += "\"CUST" + to_string(randCustID) + "\",";

        // Determine product ID
        int randProdID = (rand() % productCount) + prodID;
        writeString += "\"PROD" + to_string(randProdID) + "\",";

        // Deterine qty purchased
        writeString += "\"" + to_string((rand() % MAX_SOLD_ITEMS) + 1) + "\",";

        // Determine date purchased
        int randMonth = (rand() % 12) + 1;
        int randDay = rand();
        if (randMonth == 2) {
            randDay = randDay % 28;
        }
        else if (randMonth == 1 || randMonth == 3 || randMonth == 5 || randMonth == 7 || randMonth == 9 || randMonth == 10 || randMonth == 12) {
            randDay = randDay % 31;
        }
        else {
            randDay = randDay % 30;
        }
        randDay++;
        writeString += "\"2024/" + to_string(randMonth) + "/" + to_string(randDay) + "\"";

        writeString += "\n";
        salesLogFile << writeString;
    }

    salesLogFile.close();
    return 0;
}