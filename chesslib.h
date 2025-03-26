#ifndef CHESSLIB_H
#define CHESSLIB_H

#include <iostream>
#include <vector>
using namespace std;

class Piece {
public:
    enum Color{
       Black,White,Empty
    };
    Piece(char Type); // Constructor to initialize piece with a type
    void set_Type(char Type); // Set the type of the piece
    char get_Type()const ; // Get the type of the piece
    void set_color(Color pcolor); // Set the color of the piece
    Color get_color()const; // Get the color of the piece
    const bool Bishop_Rule(const vector<vector<Piece> >& boardVec,string _move,const int size)const; // Check if the move is valid for a bishop
    const bool  Rook_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const; // Check if the move is valid for a rook
    const bool  Knight_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const; // Check if the move is valid for a knight
    const bool  King_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const; // Check if the move is valid for a king
    const bool  Queen_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const; // Check if the move is valid for a queen
    const bool  Pawn_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const; // Check if the move is valid for a pawn
    const bool  is_legal_move(const vector<vector<Piece> >& boardVec,string _move, const int& size,Color team)const; // Check if a move is legal for a piece
    const bool Is_Under_Attack(const vector<vector<Piece> >& boardVec ,int row,int col,Piece::Color attackingColor,const int size)const ; // Check if a square is under attack

private:
    char type; // Piece type (e.g., 'P' for pawn)
    Color Pcolor; // Color of the piece
};

class ChessBoard {
public:
    ChessBoard(int Size); // Constructor for a new board
    ChessBoard(string Filename,int Size); // Constructor to load board from file
    void print_board(); // Display the current board
    int get_size(){ return size; } // Get board size
    void move(string _move); // Execute a move
    const bool is_Legal_Input(string move); // Check format validity of input move
    void Switch_Player(); // Switch the current player's turn
    void playGame(); // Run the game loop
    bool is_game_over(Piece::Color turn) const; // Check if the game is over for a given color
    bool isKingInCheck(Piece :: Color kingColor) const ; // Check if the king of the given color is in check
    void setBoardVect(vector<vector<Piece> > b){boardVec = b;} // Replace current board vector
    vector<vector<Piece> > getBoardVec()const{return boardVec;} // Get a copy of the board vector
    const bool Check_Mate(Piece :: Color kingColor); // Check if the king is in checkmate
    const bool Is_Game_Over(Piece::Color turn); // Determine if the game is over
    void saveGame(const string& filename,Piece :: Color turn) const; // Save the game to a file
    int score(); // Evaluate the board score
    string Next_Move(); // Suggest the best move for the current player

private:
    int size; // Board size (usually 8)
    vector<vector<Piece> > boardVec; // 2D board of pieces
    Piece::Color Turn; // Current turn's color
};

#endif