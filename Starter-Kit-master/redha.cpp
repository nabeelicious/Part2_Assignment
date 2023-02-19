#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;

class g_board
{
private:
    vector<vector<char>> map_;
    int dimX_, dimY_;

public:
    g_board(int dimX = 11, int dimY = 5);
    void init(int dimX, int dimY);
    void display() const;
    void moveAlienUp();
    void moveAlienDown();
    void moveAlienLeft();
    void moveAlienRight();
    void createNewPlayer();
    void continueAsExistingPlayer();

};

void g_board::moveAlienUp()
{
    // find the position of the alien on the game board
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            if (map_[i][j] == 'A')
            {
                // clear the current position of the alien
                map_[i][j] = '.';
                // move the alien down
                if (i > 0)
                {
                    map_[i + 1][j] = 'A';
                }
                else
                {
                    map_[0][j] = 'A';
                }
                return;
            }
        }
    }
}

void g_board::moveAlienDown()
{
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            if (map_[i][j] == 'A')
            {
                // clear the current position of the alien
                map_[i][j] = '.';
                // move the alien down
                if (i < dimY_ - 1)
                {
                    map_[i - 1][j] = 'A';
                }
                else
                {
                    map_[dimY_ + 1][j] = 'A';
                }
                return;
            }
        }
    }
}

void g_board::moveAlienLeft()
{
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            if (map_[i][j] == 'A')
            {
                // clear the current position of the alien
                map_[i][j] = '.';
                // move the alien left
                if (j > 0)
                {
                    map_[i][j - 1] = 'A';
                }
                else
                {
                    map_[i][0] = 'A';
                }
                return;
            }
        }
    }
}

void g_board::moveAlienRight()
{
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = dimX_ - 1; j >= 0; --j)
        {
            if (map_[i][j] == 'A')
            {
                // clear the current position of the alien
                map_[i][j] = '.';
                // move the alien right
                if (j < dimX_ - 1)
                {
                    map_[i][j + 1] = 'A';
                }
                else
                {
                    map_[i][dimX_ - 1] = 'A';
                }
                return;
            }
        }
    }
}

g_board::g_board(int dimX, int dimY)
    : dimX_{dimX}, dimY_{dimY}
{
    init(dimX, dimY);
}

void g_board::init(int dimX, int dimY)
{
    const char ALIEN = 'A';
    const char ZOMBIE = 'Z';
    const char POD = 'p';
    const char HEALTH = 'h';
    const char ROCK = 'r';
    const char SPACE = ' ';
    const char ARROW_UP = '^';
    const char ARROW_DOWN = 'v';
    const char ARROW_LEFT = '<';
    const char ARROW_RIGHT = '>';
    char objects[] = {SPACE, SPACE, SPACE, SPACE, ROCK, POD, ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN, ROCK, POD, HEALTH};
    int noOfObjects = 12;
    map_.resize(dimY_);
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_);
    }
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            if (i == dimY_ / 2 && j == dimX_ / 2)
            {
                map_[i][j] = ALIEN;
            }
            else
            {
                int objNo = rand() % noOfObjects;
                map_[i][j] = objects[objNo];
            }
        }
    }

    int numberOfZombies;
    cout << "Choose the number of zombies (1 or 2): ";
    cin >> numberOfZombies;
    for (int i = 0; i < numberOfZombies; ++i)
    {
        int randX = rand() % dimX_;
        int randY = rand() % dimY_;
        map_[randY][randX] = ZOMBIE;
    }
}

void g_board::display() const
{
    int dimX = 11, dimY = 5;

    cout << " --__--__--__--__--__--__--__--_" << endl;
    cout << " =       Alien VS Zombies      =" << endl;
    cout << " __--__--__--__--__--__--__--__-" << endl;
    // for each row
    for (int i = dimY_ - 1; i >= 0; --i)
    {
        // display upper border of the row
        cout << "   ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+---";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (i + 1) << " ";
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "| " << map_[i][j] << " ";
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << "   ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+---";
    }
    cout << "+" << endl;
    // display column number
    cout << "    ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) << "  ";
    }
    char choice;
    cout << "Do you want to change the default number of rows and columns (Default settings : 11x5)? (y/n): ";
    cin >> choice;
    if (choice == 'y')
    {
        cout << "Enter the number of columns: ";
        cin >> dimX;
        cout << "Enter the number of rows: ";
        cin >> dimY;
    }
    g_board gameBoard(dimX, dimY);

    gameBoard.display();

    while (true)
    {
        char direction;
        cout << "Enter direction to move the alien (u/d/l/r): ";
        cin >> direction;
        if (direction == 'u')
        {
            gameBoard.moveAlienUp();
        }
        else if (direction == 'd')
        {
            gameBoard.moveAlienDown();
        }
        else if (direction == 'l')
        {
            gameBoard.moveAlienLeft();
        }
        else if (direction == 'r')
        {
            gameBoard.moveAlienRight();
        }
        else
        {
            cout << "Invalid direction. Try again." << endl;
            continue;
        }
        gameBoard.display();
    }

    cout << endl
         << endl;
}

void showHelp()
{
    cout << "Displaying help..." << endl;
}

void quitGame()
{
    cout << "Quitting game..." << endl;
}

void createNewPlayer()
{
    string name; // to enter new players name
    cout << "Enter the name of the new player: ";
    cin >> name;

    ofstream file("players.txt", ios::app); // to save new data

    file << name << endl; // writes the value stored in the name variable to the file,
    file.close();         // closes the file, releasing any resources associated with it and ensuring that all the data has been written to disk.

    cout << "New player '" << name << "' created successfully." << endl;
}

void continueAsExistingPlayer()
{
    string name;
    cout << "Enter the name of the existing player: ";
    cin >> name;

    ifstream file("players.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        if (line == name)
        {
            found = true;
            break;
        }
    }
    file.close();

    if (found)
    {
        cout << "Continuing as player '" << name << "'." << endl;
    }
    else
    {
        cout << "Player '" << name << "' not found." << endl;
    }
}

// Function to create a new player
void createNewPlayer()
{
    string name;
    int level;
    ofstream outFile("gamers.txt", ios::app);
    if (outFile.is_open())
    {
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your level: ";
        cin >> level;
        outFile << name << " " << level << endl;
        cout << "Player created!" << endl;
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
}

// Function to continue as an existing player
void continueAsExistingPlayer()
{
    string name, line;
    int level;
    ifstream inFile("gamers.txt");
    if (inFile.is_open())
    {
        cout << "Enter your name: ";
        cin >> name;
        while (getline(inFile, line))
        {
            size_t pos = line.find(name);
            if (pos != string::npos)
            {
                level = stoi(line.substr(pos + name.length() + 1));
                cout << "Welcome back, " << name << "!" << endl;
                cout << "Your level is " << level << endl;
                inFile.close();
                return;
            }
        }
        cout << "Player not found." << endl;
        inFile.close();
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
}

// Function to display the game menu
void displayMenu()
{
    int choice;
    g_board Gameboard;

    do
    {
        cout << "\nGame Menu\n";
        cout << "1. Start Game\n";
        cout << "2. Create New Player\n";
        cout << "3. Continue as Existing Player\n";
        cout << "4. Quit Game\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            Gameboard.display();
            break;
        case 2:
            createNewPlayer();
            break;
        case 3:
            continueAsExistingPlayer();
            break;
        case 4:
            cout << "Quitting game..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 4);
}

int main()
{
    displayMenu();
    srand(time(NULL)); // try this for random map
    return 0;
}

// srand(1);          // use this for fixed map during testing
