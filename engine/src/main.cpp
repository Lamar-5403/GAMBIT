bool testBoard();
bool testRank();
bool testFile();
bool testStartingPosition();

int main() {
    if (testBoard() && testFile() && testRank() && testStartingPosition()) {
        return 0;
    }

    return 1;
}