#include "Game.h"
#include "Diver.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

const int INVALID = -1;
const int MAX_MENU = 6;

const int TOO_MANY_UNIQUE = -10;

const int DISPLAY_MAT = 1;
const int SEARCH_RAW = 2;
const int MERGE_MAT = 3;
const int SEE_SCORE = 4;
const int QUIT = 5;
const int FIRST_ELM = 17;

const int LUBRICANT = 28;
const int SILICONE_RUBBER = 30;

const string UNIQUE_MAT = "unique";
const string SPCASE = "Creepvine Seed Cluster";


Game::Game() {
    string newName = "";
    LoadMaterials();
    cout << "MAKE SURE TO DELETE ONE-SEC FUNCT WHEN DONE" << endl;
    cout << "50 materials loaded..." << endl;
    cout << "What is the name of your diver?: ";
    cin >> newName;
    cout << "Hello " << newName << ", welcome to..." << endl;
    m_myDiver.SetName(newName);
}

void Game::LoadMaterials() {
    string name = "";
    string matType = "";
    string matMk1 = "";
    string matMk2 = "";
    int quant = 0;
    int depth = 0;
    string item = "";

    ifstream getItem;
    getItem.open(PROJ2_DATA);
    for (int i = 0; i < PROJ2_SIZE; i++) {
        getline(getItem, item, ',');
        name = item;
        getline(getItem, item, ',');
        matType = item;
        getline(getItem, item, ',');
        matMk1 = item;
        getline(getItem, item, ',');
        matMk2 = item;
        getline(getItem, item, '\n');
        depth = stoi(item);

        //This goes to m_materials
        m_materials[i] = Material(name, matType, matMk1, matMk2, quant, depth);
        //This goes to m_mymaterial
        m_myDiver.AddMaterial(Material(name, matType, matMk1, matMk2, quant, depth));
    }
    getItem.close();
}

void Game::StartGame() {
    GameTitle();
    int usrInpt = 0;
    int count_ = 0;
    int setCount = 0;
    cout << "How many times to you want items?: ";
    cin >> setCount;
    do
    {
        if (count_ < setCount) {
            usrInpt = 2;
        }
        else {
            usrInpt = MainMenu();
        }
        switch (usrInpt)
        {
        case DISPLAY_MAT:
            DisplayMaterials();
            break;
        case SEARCH_RAW:
            OneSec(20000);
            SearchMaterials();
            break;
        case MERGE_MAT:
            CombineMaterials();
            break;
        case SEE_SCORE:
            CalcScore();
            break;
        case QUIT:
            break;
        default:
            usrInpt = INVALID;
            break;
        }
        count_++;
        cout << endl;
    } while (usrInpt != QUIT);
    cout << "Thanks for playing " << m_myDiver.GetName() << "!" << endl;
}

void Game::DisplayMaterials() {
    cout << m_myDiver.GetName() << " displays current materials!" << endl;
    for (int i = 0; i < PROJ2_SIZE; i++) {
        cout << i + 1 << ". " << m_materials[i].m_name;
        cout << " " << m_materials[i].m_quantity << endl;
    }
}

int Game::MainMenu() {
    int userNum = -1;
    int currentDepth = m_myDiver.CalcDepth();
    cout << "Current Score is: " << currentDepth << endl;
    if (currentDepth < MAX_DEPTH) {
        cout << "What would " << m_myDiver.GetName() << " like to do?" << endl;
        cout << "1. Display your Diver's Materials" << endl;
        cout << "2. Search for Raw Materials" << endl;
        cout << "3. Attempt to Merge Materials" << endl;
        cout << "4. See Score" << endl;
        cout << "5. Quit" << endl;
        cin >> userNum;
        if (userNum < 1 || userNum > MAX_MENU) {
            cout << "Invalid Input" << endl;
            userNum = INVALID;
        }
    }

    else {
        cout << "Winner!" << endl;
        userNum = QUIT;
    }
    return userNum;
}

void Game::SearchMaterials() {
    srand(time(NULL));
    int randIndex = rand() % 17;

    cout << m_materials[randIndex].m_name << " found!" << endl;
    cout << m_myDiver.GetName() << " added " << m_materials[randIndex].m_name;
    cout << " to " << m_myDiver.GetName() << "'s materials!" << endl;
    
    // Incremants the m_mymaterials list
    m_myDiver.IncrementQuantity(m_materials[randIndex]);

    // Increments the m_materials list  
    m_materials[randIndex].m_quantity += 1;
}

void Game::CombineMaterials() {
    int item_a = INVALID;
    int item_b = INVALID;
    int item_c = INVALID;

    // This checks if the user imputed a value between 1-50
    while (item_a < 0) {
        RequestMaterial(item_a);
    }
    while (item_b < 0) {
        RequestMaterial(item_b);
    }

    // Stores the names of the two materials in two variables 
    string aName = m_myDiver.GetMaterial(item_a).m_name;
    string bName = m_myDiver.GetMaterial(item_b).m_name;


    // Checks if the quantities are all good for both materials 
    bool hasMaterials = m_myDiver.CheckQuantity(m_materials[item_a], m_materials[item_b]);

    // Checks if there is a valid recipe
    item_c = SearchRecipes(aName, bName);
    
    if (item_c == TOO_MANY_UNIQUE) {
        cout << m_myDiver.GetName() << " has already made this unique material!" << endl;
    }
    else if (item_c == INVALID) {
        cout << "There's no recipe for " << aName << " and " << bName << "!" << endl;
    }
    else if (hasMaterials == false) {
        cout << m_myDiver.GetName() << " doesn't have enough materials to make ";
        cout << m_myDiver.GetMaterial(item_c).m_name << "!" << endl;
    }
    else if ((item_c != INVALID && hasMaterials) || (item_c != TOO_MANY_UNIQUE)) {
         if (item_c == LUBRICANT) {
             cout << m_myDiver.GetName() << " tries to use " << aName << "!" << endl;
            if (m_materials[item_a].m_quantity - 1 >= 0) {

                // Only decrement quantity for m_material
                m_materials[item_a].m_quantity -= 1;

                // Increment quantity for new material for m_material and and m_mymaterial
                m_myDiver.IncrementQuantity(m_materials[item_c]);
                m_materials[item_c].m_quantity += 1;

                // Display the successful merge 
                cout << m_myDiver.GetName() << " has crafted " << m_myDiver.GetMaterial(item_c).m_name;
                cout << " (+" << m_myDiver.GetMaterial(item_c).m_depth << " depth added)!" << endl;
            }
         }
        
        else if ((m_materials[item_a].m_quantity - 1 >= 0) && item_c != LUBRICANT) {
             cout << m_myDiver.GetName() << " tries to combine " << aName << " and " << bName << "!" << endl;
            // Only decrement quantity for m_material
            m_materials[item_a].m_quantity -= 1;
            if (m_materials[item_b].m_quantity - 1 >= 0) {

                // Only decrement quantity for m_material
                m_materials[item_b].m_quantity -= 1;

                // Increment quantity for new material for m_material and and m_mymaterial
                m_myDiver.IncrementQuantity(m_materials[item_c]);
                m_materials[item_c].m_quantity += 1;

                // Display the successful merge 
                cout << m_myDiver.GetName() << " has crafted " << m_myDiver.GetMaterial(item_c).m_name;
                cout << " (+" << m_myDiver.GetMaterial(item_c).m_depth << " depth added)!" << endl;
            }
            else {
                m_materials[item_a].m_quantity += 1;
                cout << m_myDiver.GetName() << " doesn't have enough materials to make ";
                cout << m_myDiver.GetMaterial(item_c).m_name << "!" << endl;
            }
         }
    }
}

void Game::RequestMaterial(int& choice) {
    cout << "Which materials would you like to merge?" << endl;
    cout << "To list known materials, enter -1" << endl;
    cin >> choice;
    if (choice == INVALID) {
        
        m_myDiver.DisplayMaterials();
        //DisplayMaterials();
    }
    else if (choice <= 0 || choice > PROJ2_SIZE) {
        choice = INVALID;
    }
    // Makes the value index friendly
    --choice;
}


int Game::SearchRecipes(string itemA, string itemB) {
    if (itemA == SPCASE && itemB == SPCASE) {
        int choice = INVALID;
        cout << "It appears that " << m_myDiver.GetName();
        cout << " can craft either Lubricant or Silicone Rubber!" << endl;
        cout << "Which material would " << m_myDiver.GetName() << " like to craft (enter 1 for Lubricant or 2 for Silicone Rubber)?: ";
        cin >> choice;
        while (choice != 1 && choice != 2) {
            cout << "Which would material" << m_myDiver.GetName() << " like to craft (enter 1 for Lubricant or 2 for Silicone Rubber)?: ";
            cin >> choice;
        }
        if (choice == 1) {
            return LUBRICANT;
        }
        else {
            return SILICONE_RUBBER;
        }
    }
    for (int index = FIRST_ELM; index < PROJ2_SIZE; index++) {
        string testMatA = m_myDiver.GetMaterial(index).m_material1;
        string testMatB = m_myDiver.GetMaterial(index).m_material2;
        int itemQuant = m_myDiver.GetMaterial(index).m_quantity;
        string itemType = m_myDiver.GetMaterial(index).m_type;
        if ((((itemA == testMatA && itemB != testMatA) || (itemA == testMatB && itemB != testMatB))
            && ((itemB == testMatA && itemA != testMatA) || (itemB == testMatB && itemA != testMatB))) ||
            ((itemA == itemB) && (itemA == testMatA && itemB == testMatB))) {
            if (itemType == UNIQUE_MAT && itemQuant == 0) {
                return index;
            }
            
            else if (itemType == UNIQUE_MAT && itemQuant > 0) {
                return TOO_MANY_UNIQUE;
            }
            else if (itemType != UNIQUE_MAT) {
                return index;
            }

        }
    }
    return INVALID;
}

void Game::CalcScore() {
    int currentDepth = m_myDiver.CalcDepth();
    cout << "Current Depth: " << currentDepth << endl;
}


void Game::OneSec(int len) {
    for (int x = 0; x < len; x++) {
        for (int y = 0; y < len; y++) {
            {}
        }
    }

}
