# ♟️ C++ Terminal Chess Game

This is a terminal-based chess game developed in C++ using Object-Oriented Programming principles.  
It simulates a full chess game between two players with support for move validation, game state persistence (saving and loading), and a simple AI move suggestion system.

---

## 🧩 Project Overview

This project was designed to simulate a playable chess game directly in the terminal.  
It includes:

- A fully initialized 8x8 chess board
- Turn-based gameplay between White and Black
- Full implementation of chess rules for each piece
- Detection of check and checkmate conditions
- A simple AI that suggests the best move based on board scoring
- Saving/loading game state from a file

---

## 🛠 Technologies Used

- **Language**: C++17
- **Paradigm**: Object-Oriented Programming (classes for `ChessBoard` and `Piece`)
- **Tools**: VS Code, g++

---

## 🎮 Features

- ✅ Legal move checking for each piece (rook, knight, bishop, queen, king, pawn)
- ♻️ Turn handling (White and Black alternate turns)
- 🛡 Check and checkmate detection
- 💾 Game auto-saves to `savegame.txt` after each move
- 🧠 AI-based move suggestion based on a scoring function
- ⌨️ Simple input format: `a2a4` (from-to)

---

## 📂 File Structure
├── chesslib.h        # Declarations for Piece and ChessBoard classes
├── chesslib.cpp      # All game logic and rule enforcement
├── mychess.cpp       # Entry point and menu handling
├── savegame.txt      # Automatically created when the game is saved
└── README.md         # You’re reading it :)

💡 How to Play
	1.	Choose 1 for a new game or 2 to load from save.
	2.	Move format: a2a4 (move from a2 to a4).
	3.	Type suggest for an AI-recommended move.
	4.	Game ends on checkmate.

💾 Save System
The game automatically saves the board and the current turn to savegame.txt after every move.
You can resume the game by choosing “Load Game” at the menu.

🚀 How to Initialize the Game

    1. Open Terminal, Navigate to the project directory.
    2. Run the Game by typing 'make'.



📌 Known Limitations
	•	Castling, en passant, and pawn promotion are not yet implemented.
	•	No visual UI; runs only in the terminal.
	•	Move suggestion is basic (greedy score-based AI).

📈 Future Improvements
	•	Implement castling and pawn promotion
	•	Add PGN move logging
	•	Create a graphical interface using SDL or SFML
	•	Improve AI with Minimax or Alpha-Beta pruning

👨‍💻 Author
    Mehmet Alp Atay
    Computer Engineering Student at Gebze Technical University


