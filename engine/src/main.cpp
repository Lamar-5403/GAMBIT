bool testBoard();
bool testRank();
bool testFile();
bool testStartingPosition();
bool testFileRankToSquare();
bool testMakeMove();
bool testForwardPawnMove();

int main() {
    bool passed = true;

    passed &= testBoard();
    passed &= testFile();
    passed &= testRank();
    passed &= testStartingPosition();
    passed &= testFileRankToSquare();
    passed &= testMakeMove();
    passed &= testForwardPawnMove();

    return passed ? 0 : 1;
}