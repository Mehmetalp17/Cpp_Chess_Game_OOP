#include "chesslib.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

ChessBoard :: ChessBoard(int S): size(S),Turn(Piece::Color::White){
    boardVec.resize(size);
    // Set up Black pieces (top row)
    boardVec[0].push_back(Piece('r'));
    boardVec[0].push_back(Piece('n'));
    boardVec[0].push_back(Piece('b'));
    boardVec[0].push_back(Piece('q'));
    boardVec[0].push_back(Piece('k'));
    boardVec[0].push_back(Piece('b'));
    boardVec[0].push_back(Piece('n'));
    boardVec[0].push_back(Piece('r'));

    // Set up Black pawns
    for(int i = 0; i<size; i++){
        boardVec[1].push_back(Piece('p'));
    }

    // Set up empty squares
    for(int i = 2; i<size-2; i++){
        for(int a=0; a<size; a++){
            boardVec[i].push_back(Piece('e'));
        }
    }

    // Set up White pawns
    for(int i = 0; i<size; i++){
        boardVec[size-2].push_back(Piece('P'));
    }


    // Set up White pieces (bottom row)
    boardVec[size-1].push_back(Piece('R'));
    boardVec[size-1].push_back(Piece('N'));
    boardVec[size-1].push_back(Piece('B'));
    boardVec[size-1].push_back(Piece('Q'));
    boardVec[size-1].push_back(Piece('K'));
    boardVec[size-1].push_back(Piece('B'));
    boardVec[size-1].push_back(Piece('N'));
    boardVec[size-1].push_back(Piece('R'));


}

void ChessBoard :: print_board(){
    // Loop through each row to print the board
    for(int row = 0; row < get_size(); row ++){
        // Print row number and left border
        cout << get_size()-row << " |";
        // Loop through each column to print each square
        for(int col = 0; col < get_size(); col++){
            // If the square is empty, print a dot
            if(boardVec[row][col].get_Type() == 'e'){
                cout << " .";
            }
            else{
                // Otherwise, print the piece type
                cout << " " << boardVec[row][col].get_Type();
            }
        }
        // End of row, move to next line
        cout << "\n";
    }

    // Print horizontal border below the board
    cout << "    ";
    for(int a = 0 ; a<get_size()*2; a++){
        cout << "-";
    }
    cout << endl;

    // Print column labels (a-h)
    cout << "    ";
    char ch = 97;
    for(int i = 0; i<get_size(); i++){
        cout << ch << " ";
        ch +=1; 
    }
    cout << endl;
}

void ChessBoard :: move(string _move){
    int Pcol =(_move[0] - 'a');
    int Prow =(size)-(_move[1]-48);
    int Mcol = (_move[2] - 'a');
    int Mrow = (size)-(_move[3]-48);

    boardVec[Mrow][Mcol].set_Type(boardVec[Prow][Pcol].get_Type());
    boardVec[Mrow][Mcol].set_color(boardVec[Prow][Pcol].get_color());
    boardVec[Prow][Pcol].set_Type('e');
    boardVec[Prow][Pcol].set_color(Piece::Color::Empty);
}

Piece :: Piece (char Type) : type(Type){
    if (type == 'p' || type == 'r' || type == 'n' || type == 'b' 
        || type == 'q' || type == 'k'){
            Pcolor = Black;
        }
    else if(type == 'e'){
        Pcolor = Empty;
    }
    else{
        Pcolor = White;
    }

}


const bool ChessBoard :: is_Legal_Input(string _move){
    if(_move[0]>='a' && _move[0]<='h' && _move[1]>='1' && _move[1] <= '8'
            && _move[2]>='a' && _move[2]<='h' && _move[3]>='1' && _move[3] <= '8'
                && !(_move[0] == _move[2] && _move[1] == _move[3])){

                    return true;
    } 
    return false;
}

const bool  Piece :: Bishop_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const{
    int Pcol =(_move[0] - 'a');
    int Prow =(size)-(_move[1]-48);
    int Mcol = (_move[2] - 'a');
    int Mrow = (size)-(_move[3]-48);



    if(abs(Pcol - Mcol) != abs(Prow - Mrow)){
        return false;
    }
    if(boardVec[Mrow][Mcol].Pcolor ==  boardVec[Prow][Pcol].Pcolor){
        return false;
    }
    int distance = Prow-Mrow;
    int dirX = Mrow > Prow ? 1 : -1;
    int dirY = Mcol > Mrow ? 1 : -1;
    for(int i=1; i < abs(distance); i++){
        if(boardVec[Prow +  i*dirX][Pcol + i*dirY].type != 'e'){
            return false;
        }
    }
    return true;
    
}


const bool  Piece :: Rook_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const{
    int Pcol =(_move[0] - 'a')  , Prow =(size)-(_move[1]-48);
    int Mcol = (_move[2] - 'a') , Mrow =(size)-(_move[3]-48);

    if(Mrow != Prow && Pcol != Mcol){
        return false;
    }
    if(boardVec[Mrow][Mcol].Pcolor ==  boardVec[Prow][Pcol].Pcolor){
        return false;
    }
    int dir ;
    if(Mcol == Pcol){
        dir = Mrow > Prow ? 1 : -1;
        for(int i = 1; i< abs(Mrow - Prow) ; i++){
             if(boardVec[Prow + i*dir][Pcol].type != 'e'){
                return false;
            }
        }
    }
    if(Mrow == Prow){
        dir = Mcol > Pcol ? 1 : -1;
        for(int i = 1; i< abs(Mrow - Prow) ; i++){
            if(boardVec[Prow][Pcol + i*dir].type != 'e'){
                return false;
            }
        }
    }
    return true;

}

const bool  Piece :: Knight_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const{
    int Pcol =(_move[0] - 'a')  , Prow =(size)-(_move[1]-48);
    int Mcol = (_move[2] - 'a') , Mrow =(size)-(_move[3]-48);

    if(boardVec[Mrow][Mcol].Pcolor ==  boardVec[Prow][Pcol].Pcolor){
        return false;
    }

    int rowDiff = abs(Mrow - Prow);
    int colDiff = abs(Mcol - Pcol);

    return (rowDiff == 1 && colDiff == 2) || (rowDiff == 2 && colDiff == 1);
}


const bool  Piece :: King_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const{
    int Pcol =(_move[0] - 'a')  , Prow =(size)-(_move[1]-48);
    int Mcol = (_move[2] - 'a') , Mrow =(size)-(_move[3]-48);
    Color attacking_color = (boardVec[Prow][Pcol].Pcolor==Color::White) ? Color::Black : Color::White;
    
    if((abs(Pcol-Mcol)==1 || abs(Prow-Mrow) == 1) 
            && (boardVec[Prow][Pcol].Pcolor!=boardVec[Mrow][Mcol].Pcolor) ){
        
        return true;
    }
  
    return false;
}

const bool  Piece :: Queen_Rule(const vector<vector<Piece> >& boardVec,string _move, const int size)const{
   if(Bishop_Rule(boardVec,_move,size) || Rook_Rule(boardVec,_move,size)){
        return true;
    }
    else{
        return false;
   }

}

const bool  Piece :: is_legal_move(const vector<vector<Piece> >& boardVec,string _move, const int& size,Piece::Color turn)const{
    char piece_type = type;
    if(Pcolor != turn){
        return false;
    }

    switch(piece_type){
        case 'r':
        case 'R':
            return Rook_Rule(boardVec,_move,size);
        case 'n':
        case 'N':
            return Knight_Rule(boardVec,_move,size);
        case 'Q':
        case 'q':
            return Queen_Rule(boardVec,_move,size);
        case 'b':
        case 'B':
            return Bishop_Rule(boardVec,_move,size);
        case 'K':
        case 'k':
            if(King_Rule(boardVec,_move,size)){
               ChessBoard temp(8);
               temp.setBoardVect(boardVec);
               temp.move(_move);
               if(!temp.isKingInCheck(turn))
               {
                return true;
               }
            } 
            return false;

        case 'P':
        case 'p':
            return Pawn_Rule(boardVec,_move,size);

        case 'e':
            return false;
    }
    return false;
}

 const bool Piece :: Pawn_Rule(const vector<vector<Piece> >& boardVec, string _move, const int size)const {
        int Pcol = (_move[0] - 'a'), Prow = (size) - (_move[1] - 48);
        int Mcol = (_move[2] - 'a'), Mrow = (size) - (_move[3] - 48);

       int direction =(boardVec[Prow][Pcol].Pcolor == Piece::Color::White) ? -1 : 1;

        if (Prow + direction == Mrow && Pcol == Mcol && boardVec[Mrow][Mcol].type == 'e') {
            return true;
        }if (Prow + 2 * direction == Mrow && Pcol == Mcol && (Prow == 1 || Prow == 6) && boardVec[Mrow][Mcol].type == 'e') {
            // Initial move: advancing two squares
            return true;
        }

        // Capturing diagonally
        if (abs(Pcol - Mcol) == 1 && Prow + direction == Mrow && boardVec[Mrow][Mcol].type != 'e' && boardVec[Prow][Pcol].Pcolor!=boardVec[Mrow][Mcol].Pcolor) {
            return true;
        }
        

        return false;
}




// Set the piece's type (e.g., 'P' for pawn, 'R' for rook)
void Piece :: set_Type(char Type){ type = Type;}
// Get the piece's type
char Piece :: get_Type()const { return type; }
// Set the piece's color
void Piece :: set_color(Color pcolor){Pcolor = pcolor;}
// Get the piece's color
Piece :: Color Piece :: get_color()const {return Pcolor;}



// Main game loop: handles turns, move validation, and checks for game over
void ChessBoard::playGame() {
    Piece :: Color turn = Turn;
    bool gameIsOver = false;
    while (!gameIsOver) {
        print_board();
        cout << "Turn: " << (turn == Piece ::Color::White ? "White" : "Black") << endl;
        cout << "Enter move (e.g., a2a4) or type 'suggest': ";
        string _move;
        cin >> _move;

        if (_move == "suggest") {
            string suggestedMove = Next_Move();
            cout << "Suggested move: " << suggestedMove << endl;
            cout << "Enter move (e.g., a2a4): ";
            cin >> _move;
        }

        if (is_Legal_Input(_move)) {
            int Pcol = _move[0] - 'a';
            int Prow = size - (_move[1] - '0');

            if (boardVec[Prow][Pcol].get_color() == turn) {
                if (boardVec[Prow][Pcol].is_legal_move(boardVec, _move, size, turn) ) {
                    move(_move);
                    this->saveGame("savegame.txt",turn);
                    Piece :: Color opponentColor = (turn == Piece :: Color::White) ? Piece::Color::Black : Piece::Color::White;
                    if (this ->Is_Game_Over(opponentColor)) {
                        gameIsOver = true;
                        cout << (turn == Piece::Color::White ? "White" : "Black") << " wins!" << endl;
                    }
                    // Switch turn to the other player
                    turn = (turn == Piece :: Color::White) ? Piece::Color::Black : Piece::Color::White;
                    this->Turn = turn;
                } else {
                    cout << "Illegal move! Try again." << endl;
                }
            } else {
                cout << "It's not your piece! Try again." << endl;
            }
        } else {
            cout << "Invalid input! Please enter a valid move." << endl;
        }
    }
}

// Check if the king of a given color is currently under threat
bool ChessBoard::isKingInCheck(Piece ::Color kingColor) const {
    // Find the king's position
    int kingRow = -1, kingCol = -1;
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (toupper(boardVec[row][col].get_Type()) == 'K' && boardVec[row][col].get_color() == kingColor) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1) {
            break;
        }
    }
    Piece :: Color opponentColor = (kingColor == Piece::Color::White) ? Piece::Color::Black : Piece::Color::White;
    // Iterate through opponent's pieces to check for legal moves to the king's position
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (boardVec[row][col].get_color() == opponentColor) {
                string _move;
                _move += col + 'a';
                _move += (size-row) + '0';
                _move += kingCol + 'a';
                _move += (size -kingRow) + '0';
                if (boardVec[row][col].is_legal_move(boardVec, _move, size, boardVec[row][col].get_color())) {
                    // There is a legal move to capture the king
                    return true;
                }
            }
        }
    }

    // No legal moves found, king is not in check
    return false;
}

// Check if the king of the given color is in checkmate.
// It verifies if the king is currently in check and cannot escape to any adjacent square.
// Returns true if checkmate is detected, otherwise false.
const bool ChessBoard :: Check_Mate(Piece :: Color kingColor){
    int kingRow = -1, kingCol = -1;
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (toupper(boardVec[row][col].get_Type()) == 'K' && boardVec[row][col].get_color() == kingColor) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1) {
            break;
        }
    }
    vector<vector<int> > moves = {{1,1},{1,0},{0,1},{-1-1},{-1,0},{0,-1},{1,-1},{-1,1}};

    if(isKingInCheck(kingColor)){
        for(int i = 0; i < 8; i++){
            string _move;
            _move += kingCol + 'a';
            _move += (size-kingRow) + '0';
            _move += kingCol+moves[i][0] + 'a';
            _move += (size - kingRow) + moves[i][1] + '0';
            if(this->is_Legal_Input(_move)){
                if(boardVec[kingRow][kingCol].King_Rule(boardVec,_move,size)){
                    ChessBoard temp(8);
                    temp.setBoardVect(boardVec);
                    temp.move(_move);
                if(!temp.isKingInCheck(kingColor))
                    {
                    return false;
                }
            } 
            }
        }
        return true;
    }
    return false;
}

const bool ChessBoard :: Is_Game_Over(Piece::Color turnn){
    if(Check_Mate(turnn)){
        return true;
    }

    return false;
}

void ChessBoard::saveGame(const string& filename, Piece :: Color turn) const {
    ofstream file(filename);
    if (file.is_open()) {
        // Save the game state to the file
        // Write each piece's information (type, color, position) to the file
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                const Piece& piece = boardVec[row][col];
                file << piece.get_Type();
            }
            file << endl;
        }
        if(turn == Piece :: Color::White){
            file << "White";
        }else{
            file << "Black";
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}


// Constructor that loads a saved game from a file.
// Initializes the board from a given filename and sets the turn accordingly.
ChessBoard :: ChessBoard(string filename,int Size): size(Size){
    ifstream file(filename);
    if (file.is_open()) {
        boardVec.resize(Size);
        char typ;
        for(int i = 0; i <8 ; i++){
            for(int j = 0 ; j < 8; j++){
                file >> typ;
                boardVec[i].push_back(Piece(typ));
            }
        }
        string colour;
        file >> colour;
        if(colour == "White"){
            Turn = Piece :: Color :: Black;
        }else{
            Turn = Piece :: Color :: White;
        }
        cout << "Game loaded from " << filename << endl;
        file.close();
    }else{
        cerr << "Unable to open file: " << filename << endl;
    }
}

int ChessBoard :: score(){
    int ovrlpts = 0 ;
    Piece :: Color opponentColor  = (Turn == Piece::Color::White) ? Piece :: Color ::White : Piece :: Color ::Black;
      for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if(boardVec[i][j].get_color() == Turn){
                    int point;
                    switch (tolower(boardVec[i][j].get_Type())) {
                        case 'p':
                            point += 1;
                            break;
                        case 'n':
                            point += 3;
                            break;
                        case 'b':
                            point += 3;
                            break;
                        case 'r':
                            point += 5;
                            break;
                        case 'q':
                            point += 9;
                            break;
                        // You can add more cases as needed
                    }
                    if(boardVec[i][j].Is_Under_Attack(boardVec,i,j,opponentColor,size)){
                        point /=2;
                    }
                    ovrlpts +=point;
            }
    }
}
 return ovrlpts;
}

const bool Piece :: Is_Under_Attack(const vector<vector<Piece> >& boardVec ,int Targetrow,int Targetcol,Piece::Color attackingColor,const int size)const {
    Color turnColor = (attackingColor == Color :: White) ? Color :: Black : Color ::White;
     for (int row = 0; row < boardVec.size(); ++row) {
        for (int col = 0; col < boardVec[row].size(); ++col) {
            const Piece& piece = boardVec[row][col];
            if (piece.Pcolor == attackingColor) {
                string _move; 
                _move += Targetcol + 'a';
                _move += (size-Targetrow) + '0';
                _move += col + 'a';
                _move += (size -row) + '0';
                if (piece.is_legal_move(boardVec,_move,size,attackingColor)) {
                    return true;
                }
            }
        }
    }

    return false;
}

string ChessBoard :: Next_Move(){
    int bestScore = -1;
    string bestMove = "";
    
    for (int row = 0; row < boardVec.size(); ++row) {
        for (int col = 0; col < boardVec[row].size(); ++col){
            if (boardVec[row][col].get_color() == Turn){
                char fromCol = col + 'a';
                char fromRow = (size - row) + '0';
                
                for (int toRow = 0; toRow < size; ++toRow) {
                    for (int toCol = 0; toCol < size; ++toCol) {
                        if (row == toRow && col == toCol) continue;
                        
                        char toColChar = toCol + 'a';
                        char toRowChar = (size - toRow) + '0';
                        string moveStr = {fromCol, fromRow, toColChar, toRowChar};
                        
                        if (is_Legal_Input(moveStr) &&
                            boardVec[row][col].is_legal_move(boardVec, moveStr, size, Turn)) {
                            
                            ChessBoard temp(*this);
                            temp.move(moveStr);
                            int sc = temp.score();
                            
                            if (sc > bestScore) {
                                bestScore = sc;
                                bestMove = moveStr;
                            }
                        }
                    }
                }
            }
        }
    }   
    return bestMove;   
}
