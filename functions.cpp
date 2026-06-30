#include "structures.h"
#include <stack>
#include <random>

Maze::Maze(int rows, int cols) : rows(rows), cols(cols)
{
	grid.resize(rows, vector<Cell>(cols));
}

void Maze::generate()
{
	mt19937 rng(std::random_device{}());
	stack<Position> stk;
	Position start = { 0, 0 };
	grid[start.row][start.col].visited = true;
	stk.push(start);

	while (!stk.empty())
	{
		Position current = stk.top();
		vector<Position> unvisitedNeighbors = getUnvisitedGridNeighbors(current);

		if (unvisitedNeighbors.empty())
		{
			stk.pop(); //gặp ngõ cụt quay về điểm gần nhất (backtrack)
		}
		else
		{
			//lấy số random
			uniform_int_distribution<int> dist(0, (int)unvisitedNeighbors.size() - 1);
			int random = dist(rng);
			Position next = unvisitedNeighbors[random];
			removeWall(current, next);
			grid[next.row][next.col].visited = true;
			stk.push(next);
		}
	}
	// Reset visited để BFS/DFS giải mê cung
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			grid[r][c].visited = false;
}

//getUnvisitedGridNeighbors lấy grid chưa thăm bắt kể có là tường mục đích để tạo maze
vector<Position> Maze::getUnvisitedGridNeighbors(Position p) const
{
	vector<Position> neighbor;
	int row = p.row;
	int col = p.col;
	//kiem tra top
	if (row - 1 >= 0 && grid[row - 1][col].visited == false)
	{
		neighbor.push_back({ row - 1, col });
	}
	//kiem tra left
	if (col - 1 >= 0 && grid[row][col - 1].visited == false)
	{
		neighbor.push_back({ row, col - 1 });
	}
	//kiem tra bottom
	//rows cua maze
	if (row + 1 < rows && grid[row + 1][col].visited == false)
	{
		neighbor.push_back({ row + 1, col });
	}
	//kiem tra right
	//cols cua maze
	if (col + 1 < cols && grid[row][col + 1].visited == false)
	{
		neighbor.push_back({ row, col + 1 });
	}
	return neighbor;
}
//a là vị trí đang ở và b là vị trí đang thăm, xác định hướng xóa tường bằng vị trí b so với a 
void Maze::removeWall(Position a, Position b)
{
	if (a.row > b.row)
	{
		grid[a.row][a.col].wTop = false;
		grid[b.row][b.col].wBottom = false;
	}
	if (a.row < b.row)
	{
		grid[a.row][a.col].wBottom = false;
		grid[b.row][b.col].wTop = false;
	}
	if (a.col > b.col)
	{
		grid[a.row][a.col].wLeft = false;
		grid[b.row][b.col].wRight = false;
	}
	if (a.col < b.col)
	{
		grid[a.row][a.col].wRight = false;
		grid[b.row][b.col].wLeft = false;
	}
}

void Maze::print(Position playerPos, const vector<Position>& path, Position endPos) const
{
	const int CELL_WIDTH = 4;

	vector<vector<bool>> onPath(rows, vector<bool>(cols, false));
	for (Position p : path)
		onPath[p.row][p.col] = true;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			cout << "+";
			cout << string(CELL_WIDTH - 1, grid[r][c].wTop ? '-' : ' ');
		}
		cout << "+\n";

		for (int c = 0; c < cols; c++)
		{
			cout << (grid[r][c].wLeft ? "|" : " ");

			char content = ' ';
			if (r == playerPos.row && c == playerPos.col)
				content = 'P';
			else if (r == endPos.row && c == endPos.col)
				content = 'E';
			else if (onPath[r][c])
				content = 'o';

			cout << content;
			cout << string(CELL_WIDTH - 2, ' ');
		}
		cout << (grid[r][cols - 1].wRight ? "|" : " ");
		cout << "\n";
	}

	for (int c = 0; c < cols; c++)
	{
		cout << "+";
		cout << string(CELL_WIDTH - 1, grid[rows - 1][c].wBottom ? '-' : ' ');
	}
	cout << "+\n";
}
bool Maze::canMove(Position from, char direction) const
{
	if ('w' == direction || 'W' == direction)
	{
		if (!grid[from.row][from.col].wTop) return true;
	}
	if ('a' == direction || 'A' == direction)
	{
		if (!grid[from.row][from.col].wLeft) return true;
	}
	if ('s' == direction || 'S' == direction)
	{
		if (!grid[from.row][from.col].wBottom) return true;
	}
	if ('d' == direction || 'D' == direction)
	{
		if (!grid[from.row][from.col].wRight) return true;
	}
	return false;
}

Position Maze::move(Position from, char direction) const
{
	Position next = from;
	if ('w' == direction || 'W' == direction)
	{
		next.row = from.row - 1;
	}
	if ('a' == direction || 'A' == direction)
	{
		next.col = from.col - 1;
	}
	if ('s' == direction || 'S' == direction)
	{
		next.row = from.row + 1;
	}
	if ('d' == direction || 'D' == direction)
	{
		next.col = from.col + 1;
	}
	return next;
}

void Maze::playGame() const
{
	Position player = { 0, 0 };
	Position exit = { rows - 1, cols - 1 };

	while (player != exit)
	{
		system("cls");
		print(player, {}, exit);

		char input = _getch();


		if (input == 'w' || input == 'a' || input == 's' || input == 'd' ||
			input == 'W' || input == 'A' || input == 'S' || input == 'D')
		{
			if (canMove(player, input))
				player = move(player, input);
		}
	}
	cout << "WINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN!\n";
}

vector<Position> Maze::getNeighbors(Position p) const
{
	vector<Position> neighbor;
	int row = p.row, col = p.col;

	if (!grid[row][col].wTop)
		neighbor.push_back({ row - 1, col });
	if (!grid[row][col].wBottom)
		neighbor.push_back({ row + 1, col });
	if (!grid[row][col].wLeft)
		neighbor.push_back({ row, col - 1 });
	if (!grid[row][col].wRight)
		neighbor.push_back({ row, col + 1 });

	return neighbor;
}

int Maze::getRows() const
{
	return rows;
}

int Maze::getCols() const
{
	return cols;
}

void displayBFS(const Maze& maze, Position start, Position end)
{
	SolveResult result = solveBFS(maze, start, end);

	maze.print({ -1, -1 }, result.path, end);
	cout << "BFS - duong di ngan nhat: " << result.path.size() << " o\n";
	cout << "So o da duyet: " << result.stepsExplored << "\n";
}

void getDifficulty(int& rows, int& cols)
{
	cout << "Chon do kho:\n";
	cout << "1. De     (10 x 10)\n";
	cout << "2. Trung  (20 x 20)\n";
	cout << "3. Kho    (30 x 30)\n";
	cout << "Lua chon: ";

	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1: rows = 10; cols = 10; break;
	case 2: rows = 20; cols = 20; break;
	case 3: rows = 30; cols = 30; break;
	default:
		cout << "Lua chon khong hop le, sai mac dinh 10x10\n";
		rows = 10; cols = 10;
		break;
	}
}

void Menu()
{
	int rows = 10, cols = 10;
	Maze* maze = nullptr;
	Position start = { 0, 0 };
	Position end;

	int choice;
	do
	{
		cout << "\n========== MAZE GAME ==========\n";
		cout << "1. Tao me cung ngau nhien (Recursive Backtracker)\n";
		cout << "2. Hien thi me cung ASCII\n";
		cout << "3. Choi - tu giai bang W/A/S/D\n";
		cout << "4. Tu dong giai bang BFS (duong ngan nhat)\n";
		cout << "5. Tu dong giai bang DFS (hien thi backtrack)\n";
		cout << "6. So sanh BFS vs DFS\n";
		cout << "7. Dieu chinh do kho (kich thuoc me cung)\n";
		cout << "0. Thoat\n";
		cout << "Lua chon: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			if (maze != nullptr) delete maze;
			maze = new Maze(rows, cols);
			maze->generate();
			end = { rows - 1, cols - 1 };
			cout << "Da tao me cung " << rows << "x" << cols << "\n";
			break;
		}
		case 2:
		{
			if (maze == nullptr) { cout << "Chua co me cung, chon muc 1 truoc!\n"; break; }
			maze->print({ -1, -1 }, {}, end);
			break;
		}
		case 3:
		{
			if (maze == nullptr) { cout << "Chua co me cung, chon muc 1 truoc!\n"; break; }
			maze->playGame();
			break;
		}
		case 4:
		{
			if (maze == nullptr) { cout << "Chua co me cung, chon muc 1 truoc!\n"; break; }
			displayBFS(*maze, start, end);
			break;
		}
		case 5:
		{
			if (maze == nullptr) { cout << "Chua co me cung, chon muc 1 truoc!\n"; break; }
			solveDFSVisual(*maze, start, end);
			break;
		}
		case 6:
		{
			if (maze == nullptr) { cout << "Chua co me cung, chon muc 1 truoc!\n"; break; }
			compareSolvers(*maze, start, end);
			break;
		}
		case 7:
		{
			getDifficulty(rows, cols);
			cout << "Da cap nhat do kho. Chon muc 1 de tao me cung moi.\n";
			break;
		}
		case 0:
			cout << "Tam biet!\n";
			break;
		default:
			cout << "Lua chon khong hop le.\n";
			break;
		}

	} while (choice != 0);

	if (maze != nullptr) delete maze;
}