#include <iostream>
#include <string>
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
    int alien_health_;
    int alien_pos_x_, alien_pos_y_;

public:
    g_board(int dimX = 11, int dimY = 5, int alien_health = 100);
    void init(int dimX, int dimY);
    void display() const;
    bool move_alien(int x, int y);
};

g_board::g_board(int dimX, int dimY, int alien_health)
    : dimX_{dimX}, dimY_{dimY}, alien_health_{alien_health}, alien_pos_x_{dimX / 2}, alien_pos_y_{dimY / 2}
{
    init(dimX, dimY);
}

void g_board::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
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
            if (i == alien_pos_y_ && j == alien_pos_x_)
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
        int zombieHealth = rand() % 3;
        zombieHealth = (zombieHealth == 0) ? 100 : ((zombieHealth == 1) ? 150 : 200);
        map_[randY][randX] = ZOMBIE;
        map_[randY][randX + 1] = to_string(zombieHealth)[0];
        map_[randY][randX + 2] = to_string(zombieHealth)[1];
        map_[randY][randX + 3] = to_string(zombieHealth)[2];
    }
}

void g_board::display() const
{
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
    cout << endl;

    // Display Alien's health
    cout << endl;
    cout << "Alien: life=" << alien_health_ << endl;

    

    // Display Zombie's health and damage range
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            if (map_[i][j] == 'Z')
            {
                int health = (map_[i][j + 1] - '0') * 100 + (map_[i][j + 2] - '0') * 10 + (map_[i][j + 3] - '0');
                int damageRange = (health > 0 && health <= 50) ? 1 : ((health > 50 && health <= 100) ? 2 : 3);
                cout << "Zombie" << i + 1 << ": health=" << health << ", damage range=" << damageRange << endl;
            }
        }
    }
}

void test1_1()
{
    g_board g_board;
    g_board.display();
}
int main()
{
    int dimX = 11, dimY = 5;
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
    return 0;

    srand(time(NULL)); // try this for random map
    test1_1();
}