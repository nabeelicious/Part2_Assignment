#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void startGame()
{
    cout << "Starting game..." << endl;
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

    ofstream file("players.txt", ios::app);// to save new data

    file << name << endl; //writes the value stored in the name variable to the file,
    file.close(); //closes the file, releasing any resources associated with it and ensuring that all the data has been written to disk.

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

int main()
{
    int choice;
    bool gameOn = true;

    while (gameOn)
    {
        cout << "***********\n";
        cout << " 1 - Start the game.\n";
        cout << " 2 - Create new player.\n";
        cout << " 3 - Continue as existing player.\n";
        cout << " 4 - Exit.\n";
        cout << " Enter your choice and press return: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                startGame();
                break;
            case 2:
                createNewPlayer();
                break;
            case 3:
                continueAsExistingPlayer();
                break;
            case 4:
                quitGame();
                gameOn = false;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    }

    return 0;
}