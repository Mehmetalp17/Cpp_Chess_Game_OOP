#include "chesslib.h"
#include <iostream>
using namespace std;

int main(){
    // Display the main menu options
    cout << "=== Chess Game Menu ===" << endl;
    cout << "1 - Start New Game" << endl;
    cout << "2 - Load Saved Game" << endl;
    cout << "=======================" << endl;

    int option;

    // Prompt the user for input until a valid option is selected
    while (true) {
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1 || option == 2)
            break;

        cout << "Invalid option. Please try again." << endl;
    }

    string Filename = "savegame.txt";

    // Start a new game or load a saved one based on user choice
    if (option == 1) {
        ChessBoard Board(8); // Create a new 8x8 chess board
        Board.playGame();    // Start the game loop
    } else {
        ChessBoard Board(Filename, 8); // Load a board from the save file
        Board.playGame();              // Start the game loop
    }

    return 0;
}