#include "Game.h"
#include "Diver.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int const INVALID = -1;
int const MAX_MENU = 6;

int const DISPLAY_MAT = 1;
int const SEARCH_RAW = 2;
int const MERGE_MAT = 3;
int const SEE_SCORE = 4;
int const QUIT = 5;
int const FIRST_ELM = 17;
string const UNIQUE_MAT = "unique";
string const SPCASE = "Creepvine Seed Cluster";
const int LUBRICANT = 28;
const int SILICONE_RUBBER = 30;

/*Things to do:
VERY IMPORTANT: CREATE A COPY OF ALL OF THESE FILES BEFORE CHANGING! THE CODE IS WORKING FINE (FOR NOW) 
1.
When using the increment-quantity function to increment m_mymaterials, ALSO increment m_materials.
NEVER DECREMENT M_MATERIALS! This will be used to calculate the TOTAL score. Apply this to the search 
materials and combine-materials functions (also check Diver.cpp I only checked Game.cpp)

2.
Tweak the displaying materials function a bit by displaying KNOWN materials (use m_materials).
IMPORTANT! This is ONLY when the comp asks for -1 to see the materials NOT when the user enters 1
for the main menu! DONT TOUCH THE DISPLAY FUNCTION WHEN THE USER ENTERS 1! You're good on that one.

3.
Change the calc score by using m_materials (Game.cpp) instead of m_mymaterials (Diver.cpp).
Calc score in Diver.cpp is when you've just obtained a score! Long story short, 
DONT GIVE A SHIT ABOUT CALC SCORE IN DIVER.CPP

4. You're gonna need to use m_materials in the search-recipes function to see if you used the same unique
material more than once. DON'T TOUCH THE BIG IF-STATEMENT! JUST change the if-statement that asks if it's unique. 

5. 
Create global constants if necessary
*/


/* Name: Game() Default Constructor
    // Desc - Builds a new game by:
    // 1. Loads all materials and their recipes into m_materials
    // 2. Asks user for their diver's name (store in m_myDiver as m_myName)
    // 3. Copies all materials from m_materials into the diver's material array
    // Preconditions - None
    // Postconditions - m_materials is populated
    */
Game::Game() {
    string newName = "";
    LoadMaterials();
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

// Name: StartGame()
    // Desc - Manages the game itself including win conditions continually
    //         calling the main menu 
    // Preconditions - Player is placed in game
    // Postconditions - Continually checks to see if player has entered 5
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
    m_myDiver.DisplayMaterials();
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
    
    m_myDiver.IncrementQuantity(m_myDiver.GetMaterial(randIndex));
}


// Name: CombineMaterials()
    // Desc - Attempts to combine known materials. If combined, quantity of material decreased
    // Preconditions - Diver is populated with materials
    // Postconditions - Increments quantity of item "made", decreases quantity of source items
void Game::CombineMaterials() {
    int item_a = INVALID;
    int item_b = INVALID;
    int item_c = INVALID;
    
    // This checks if the user imputed a value between 1-50
    while (item_a <= 0) {
        RequestMaterial(item_a);
    }
    while (item_b <= 0){
        RequestMaterial(item_b);
    }

    // Stores the names of the two materials in two variables 
    string aName = m_myDiver.GetMaterial(item_a).m_name;
    string bName = m_myDiver.GetMaterial(item_b).m_name;

    // Checks if the quantities are all good for both materials 
    bool hasMaterials = m_myDiver.CheckQuantity(m_myDiver.GetMaterial(item_a), m_myDiver.GetMaterial(item_b));

    // checks if there is a valid recipe
    item_c = SearchRecipes(aName, bName);
    if (item_c != LUBRICANT) {
        cout << m_myDiver.GetName() << " tries to combine " << aName << " and " << bName << "!" << endl;
    }
    if (item_c != INVALID && hasMaterials) {
        if (item_c == LUBRICANT) {
            if (m_myDiver.DecrementQuantity(m_myDiver.GetMaterial(item_a))) {
                m_myDiver.IncrementQuantity(m_myDiver.GetMaterial(item_c));
                // Display the successful merge 
                cout << m_myDiver.GetName() << " has crafted " << m_myDiver.GetMaterial(item_c).m_name;
                cout << " (+" << m_myDiver.GetMaterial(item_c).m_depth << " depth added)!" << endl;
            }
        }
        else if ((m_myDiver.DecrementQuantity(m_myDiver.GetMaterial(item_a))) &&
            (m_myDiver.DecrementQuantity(m_myDiver.GetMaterial(item_b)))) {

            m_myDiver.IncrementQuantity(m_myDiver.GetMaterial(item_c));

            // Display the successful merge 
            cout << m_myDiver.GetName() <<" has crafted "<< m_myDiver.GetMaterial(item_c).m_name;
            cout << " (+" << m_myDiver.GetMaterial(item_c).m_depth << " depth added)!" << endl;
        }
    }
    
    else if (item_c == INVALID) {
        cout << "There's no recipe for " << aName << " and " << bName << "!" << endl;
    }
    else if (hasMaterials == false) {
        cout << m_myDiver.GetName() << " doesn't have enough materials to make ";
        cout << m_myDiver.GetMaterial(item_c).m_name << "!" << endl;
    }
}

// Name: RequestMaterial()
    // Desc - Requests material to use to merge
    // Preconditions - Diver has materials to try and merge
    // Postconditions - Returns integer of item selected by user
void Game::RequestMaterial(int& choice) {
    cout << "Which materials would you like to merge?" << endl;
    cout << "To list known materials, enter -1" << endl;
    cin >> choice;
    if (choice == INVALID) {
        DisplayMaterials();
    }
    else if (choice <= 0 || choice > PROJ2_SIZE) {
        choice = INVALID;
    }
    // make the value index friendly
    --choice;
}


// Name: SearchRecipes()
    // Desc - Searches recipes for two strings (name of item)
    // Preconditions - m_materials is populated
    // Postconditions - Returns int index of matching recipe

//make sure that the quantity for the unique item is zero
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
        if ( ( ((itemA == testMatA && itemB != testMatA) || (itemA == testMatB && itemB != testMatB)) 
            && ((itemB == testMatA && itemA != testMatA) || (itemB == testMatB && itemA != testMatB)) ) || 
            ((itemA == itemB) && (itemA == testMatA && itemB == testMatB))) {
            if (itemType == UNIQUE_MAT && itemQuant == 0) {
                return index;
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


void Game::OneSec(int len){
    for (int x = 0; x < len; x++) {
        for (int y = 0; y < len; y++) {
            {}
        }
    }

}
/*private:
    Diver m_myDiver; Player's Diver for the game
    Material m_materials[PROJ2_SIZE]; All materials in the game (loaded from file)*/
