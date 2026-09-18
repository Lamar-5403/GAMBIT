# G.A.M.B.I.T.
Game Analysis through Machine-learning, Branching, Integration, and Tactics.

---

## Overview
G.A.M.B.I.T. is a hybrid chess engine developed from the ground up in C++. The project focuses on building a complete chess-playing system while emphasizing efficient board representation, deterministic move generation, search, and eventually machine learning.

The engine is being developed incrementally, beginning with the underlying board and position representations before progressing through move generation, legal move validation, game-state management, search, evaluation, and machine learning.

---

## Architecture
G.A.M.B.I.T. is organized into several major subsystems:

### Board Representation

- Represents the chessboard using 64-bit bitboards
- Maps chess squares to individual bits
- Provides square, rank, and file conversion utilities
- Provides bitboard manipulation operations
- Provides occupancy information for individual colors and the complete position

### Position

- Maintains the complete state of a chess position
- Stores piece locations by color and piece type
- Tracks side to move
- Tracks castling rights
- Tracks the en passant square
- Tracks the half-move clock and full-move number
- Initializes positions according to the standard starting position
- Supports initialization from Forsyth-Edwards Notation (FEN)

### Move System

- Represents individual chess moves
- Applies moves to a position
- Reverts previously applied moves
- Represents quiet moves, captures, double pawn pushes, en passant, castling, and pawn promotions
- Provides the foundation for move generation and game-state transitions

### Move Generation

Implemented functionality includes:

- Pseudo-legal pawn move generation
- Pawn captures and double pushes
- En passant
- Pawn promotions and promotion captures
- Knight move generation
- Bishop, rook, and queen sliding move generation
- King move generation
- Castling

Pseudo-legal move generation does not filter ordinary moves based on whether they leave the moving side's king in check. Legal move generation will perform this validation.

Planned functionality includes:

- Legal move generation
- Checkmate and stalemate detection
- Complete game-state transition handling for all move types

### Search and Evaluation

Planned functionality includes:

- Position evaluation
- Minimax search
- Alpha-beta pruning
- Iterative deepening
- Quiescence search
- Move ordering
- Zobrist hashing
- Transposition tables

### Machine Learning

A machine learning component is planned as a later stage of development.

Potential functionality includes:

- Position evaluation using a neural network
- Self-play training
- Training-data generation
- Model evaluation
- Strength progression tracking

---

## Board Representation

G.A.M.B.I.T. uses a bitboard representation in which each chess square corresponds to one bit of a 64-bit integer.

```
A8 B8 C8 D8 E8 F8 G8 H8   
A7 B7 C7 D7 E7 F7 G7 H7   
A6 B6 C6 D6 E6 F6 G6 H6   
A5 B5 C5 D5 E5 F5 G5 H5   
A4 B4 C4 D4 E4 F4 G4 H4   
A3 B3 C3 D3 E3 F3 G3 H3   
A2 B2 C2 D2 E2 F2 G2 H2   
A1 B1 C1 D1 E1 F1 G1 H1   
```

The least significant bit represents A8, while the most significant bit represents H1.

For example:

`A8 = 0x0000000000000001`   
`E4 = 0x0000001000000000`   
`H1 = 0x8000000000000000`   

Piece locations are stored independently by color and piece type.

pieces[color][piece]

This allows operations such as finding all white pawns or manipulating a specific piece set using efficient bitwise operations.

---

## Move Model

Moves are represented as structured objects containing the information necessary to transition between positions.

```text
Move
|-- source
|-- destination
|-- piece
|-- color
|-- type
|-- promotionPiece
```

Move types include:

- QUIET
- CAPTURE
- DOUBLE_PAWN_PUSH
- EN_PASSANT
- CASTLE
- PROMOTION
- PROMOTION_CAPTURE

---

## Elo Progression

Engine strength will be evaluated throughout development using repeatable games against previous versions, reference engines, and eventually through self-play.

The Elo graph will be updated as significant engine versions are evaluated.

```text
Elo
^
|
|
|
|
|
|
|
|
+--------------------------------------------------------> Version
 v0.1	v0.2   v0.3    v0.4    v0.5    v0.6    v0.7    v0.8
```

As the engine matures, this section will be replaced with measured Elo data from controlled evaluation matches.

The objective is not simply to maximize Elo, but to track how architectural and algorithmic improvements affect playing strength.

---

## Testing

G.A.M.B.I.T. uses automated tests to validate core engine functionality as development progresses.

Current tests cover:

- Square-to-bitboard conversion
- Square-to-rank conversion
- Square-to-file conversion
- File/rank-to-square conversion
- Bitboard manipulation and occupancy detection
- Starting-position initialization
- FEN parsing
- Position state access
- Move representation
- Basic move application and reversal
- Pawn, knight, bishop, rook, queen, and king move generation
- Castling
- En passant
- Pawn promotion and promotion captures
- Pawn, knight, and king attack tables
- Sliding attack rays
- First-blocker detection
- Ray truncation
- Square attack detection
- Check detection

Additional test coverage will be added alongside each major subsystem.

---

## Repository Structure

```
/docs
	/01_architecture.md

/engine
	/include/gambit
		attack.h
		board.h
		move.h
		position.h
	/src
		attack.cpp
		board.cpp
		main.cpp
		move.cpp
		position.cpp
	/tests
		test_attacks.cpp
		test_board.cpp
		test_move.cpp
		test_position.cpp

.gitignore
CMakeLists.txt
README.md
```

---

## Development Principles

G.A.M.B.I.T. is being developed with an emphasis on:

- Clear separation of responsibilities
- Deterministic and testable behavior
- Efficient data representation
- Correctness before optimization
- Incremental validation
- Rigorous automated testing
- Reproducible performance measurements
- Maintainable C++ architecture
- Measurable improvements in playing strength
- Optimization based on measured behavior rather than premature complexity

---

## Status

G.A.M.B.I.T. is under active development.

The board and position foundations are implemented and tested, including FEN parsing and position-state management. Attack-generation infrastructure and pseudo-legal move generation are also implemented and tested, including pawn movement, captures, promotions, en passant, sliding pieces, knights, kings, and castling.

The current development stage is legal move generation, including king-safety validation and the completion of game-state transition handling.