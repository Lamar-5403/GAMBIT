bool testBoard();
bool testRank();
bool testFile();
bool testStartingPosition();
bool testFileRankToSquare();
bool testMakeMove();
bool testForwardPawnMove();
bool testStartingPositionFromFEN();
bool testPositionFromFEN();
bool testPseudoLegalPawnMoves();

int main() {
    bool passed = true;

    passed &= testBoard();
    passed &= testFile();
    passed &= testRank();
    passed &= testStartingPosition();
    passed &= testFileRankToSquare();
    passed &= testMakeMove();
    passed &= testForwardPawnMove();
    passed &= testStartingPositionFromFEN();
    passed &= testPositionFromFEN();
    passed &= testPseudoLegalPawnMoves();
    return passed ? 0 : 1;
}