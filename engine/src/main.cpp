bool testBoard();
bool testRank();
bool testFile();

int main() {
    if (testBoard() && testFile() && testRank()) {
        return 0;
    }

    return 1;
}