#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <conio.h> 
using namespace std;

struct Cell {
    bool wTop = true;
    bool wRight = true;
    bool wBottom = true;
    bool wLeft = true;
    bool visited = false;
};

struct Position {
    int row;
    int col;

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};

struct SolveResult {
    vector<Position> path;
    int stepsExplored;
};

class Maze; 

SolveResult solveBFS(const Maze& maze, Position start, Position end);
SolveResult solveDFS(const Maze& maze, Position start, Position end);

class Maze {
public:
    Maze(int rows, int cols);

    void generate();

    bool canMove(Position from, char direction) const;
    Position move(Position from, char direction) const;
    void playGame() const;
    vector<Position> getNeighbors(Position p) const;

    void print(Position playerPos = { -1, -1 }, const vector<Position>& path = {}, Position endPos = { -1, -1 }) const;

    int getRows() const;
    int getCols() const;

private:
    int rows, cols;
    vector<vector<Cell>> grid;

    vector<Position> getUnvisitedGridNeighbors(Position p) const;
    void carve(Position current);
    void removeWall(Position a, Position b);
};

void displayBFS(const Maze& maze, Position start, Position end);
void solveDFSVisual(const Maze& maze, Position start, Position end);
void compareSolvers(const Maze& maze, Position start, Position end);
void getDifficulty(int& rows, int& cols);

void Menu();