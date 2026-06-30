#define _HAS_STD_BYTE 0
#include <windows.h>


#include "structures.h"
#include <stack>
#include <queue>
#include <algorithm>

SolveResult solveBFS(const Maze& maze, Position start, Position end)
{
	int rows = maze.getRows();
	int cols = maze.getCols();

	vector<vector<bool>> visited(rows, vector<bool>(cols, false));
	vector<vector<Position>> parent(rows, vector<Position>(cols));

	queue<Position> q;
	q.push(start);
	visited[start.row][start.col] = true;

	int stepsExplored = 0;
	bool found = false;

	while (!q.empty())
	{
		Position current = q.front();
		q.pop();
		stepsExplored++;

		if (current == end)
		{
			found = true;
			break;
		}

		for (Position neighbor : maze.getNeighbors(current))
		{
			if (!visited[neighbor.row][neighbor.col])
			{
				visited[neighbor.row][neighbor.col] = true;
				parent[neighbor.row][neighbor.col] = current;
				q.push(neighbor);
			}
		}
	}

	SolveResult result;
	result.stepsExplored = stepsExplored;

	if (!found)
		return result;

	vector<Position> path;
	Position p = end;
	while (p != start)
	{
		path.push_back(p);
		p = parent[p.row][p.col];
	}
	path.push_back(start);
	reverse(path.begin(), path.end());

	result.path = path;
	return result;
}

SolveResult solveDFS(const Maze& maze, Position start, Position end)
{
	int rows = maze.getRows();
	int cols = maze.getCols();

	vector<vector<bool>> visited(rows, vector<bool>(cols, false));
	vector<vector<Position>> parent(rows, vector<Position>(cols));

	stack<Position> stk;
	stk.push(start);
	visited[start.row][start.col] = true;

	int stepsExplored = 0;
	bool found = false;

	while (!stk.empty())
	{
		Position current = stk.top();
		stk.pop();
		stepsExplored++;

		if (current == end)
		{
			found = true;
			break;
		}

		for (Position neighbor : maze.getNeighbors(current))
		{
			if (!visited[neighbor.row][neighbor.col])
			{
				visited[neighbor.row][neighbor.col] = true;
				parent[neighbor.row][neighbor.col] = current;
				stk.push(neighbor);
			}
		}
	}

	SolveResult result;
	result.stepsExplored = stepsExplored;

	if (!found)
		return result;

	vector<Position> path;
	Position p = end;
	while (p != start)
	{
		path.push_back(p);
		p = parent[p.row][p.col];
	}
	path.push_back(start);
	reverse(path.begin(), path.end());

	result.path = path;
	return result;
}



void solveDFSVisual(const Maze& maze, Position start, Position end)
{
	int rows = maze.getRows();
	int cols = maze.getCols();

	vector<vector<bool>> visited(rows, vector<bool>(cols, false));
	stack<Position> stk;
	vector<Position> currentPath;   // mô phỏng đúng nội dung của stack, dùng để vẽ

	stk.push(start);
	visited[start.row][start.col] = true;
	currentPath.push_back(start);

	while (!stk.empty())
	{
		Position current = stk.top();

		system("cls");
		maze.print(current, currentPath, end);
		cout << "DFS dang duyet... do dai hien tai: " << currentPath.size() << "\n";
		Sleep(100);   // ms — chỉnh nhanh/chậm tùy ý

		if (current == end)
			break;

		// Tìm 1 neighbor chưa thăm để đi tới (chỉ 1, đúng kiểu DFS từng bước)
		vector<Position> neighbors = maze.getNeighbors(current);
		bool moved = false;

		for (Position neighbor : neighbors)
		{
			if (!visited[neighbor.row][neighbor.col])
			{
				visited[neighbor.row][neighbor.col] = true;
				stk.push(neighbor);
				currentPath.push_back(neighbor);
				moved = true;
				break;
			}
		}

		if (!moved)
		{
			stk.pop();
			currentPath.pop_back();   // backtrack rút khỏi đường đi hiển thị
		}
	}

	system("cls");
	maze.print(currentPath.empty() ? Position{ -1, -1 } : currentPath.back(), currentPath,end);
	cout << "DFS hoan thanh! Do dai duong di cuoi cung: " << currentPath.size() << "\n";
}

void compareSolvers(const Maze& maze, Position start, Position end)
{
	SolveResult bfsResult = solveBFS(maze, start, end);
	SolveResult dfsResult = solveDFS(maze, start, end);

	cout << "===== SO SANH BFS vs DFS =====\n\n";

	cout << "BFS:\n";
	cout << "  Do dai duong di: " << bfsResult.path.size() << " o\n";
	cout << "  So o da duyet:   " << bfsResult.stepsExplored << "\n\n";

	cout << "DFS:\n";
	cout << "  Do dai duong di: " << dfsResult.path.size() << " o\n";
	cout << "  So o da duyet:   " << dfsResult.stepsExplored << "\n\n";

	if (bfsResult.path.size() < dfsResult.path.size())
		cout << "=> BFS tim duong NGAN HON DFS.\n";
	else if (bfsResult.path.size() > dfsResult.path.size())
		cout << "=> DFS tim duong NGAN HON BFS.\n";
	else
		cout << "=> Hai duong di co DO DAI BANG NHAU.\n";
}