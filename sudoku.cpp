#include<string>
#include <iostream>
using namespace std;

bool FindUnassignedLocation(int table[9][9],
	int& row, int& column)
{
	for (row = 0; row < 9; row++)
		for (column = 0; column < 9; column++)
			if (table[row][column] == 0)
				return 1;
	return 0;
}


bool UsedInRow(int table[9][9], int row, int number)
{
	for (int column = 0; column < 9; column++)
		if (table[row][column] == number)
			return 1;
	return 0;
}

bool UsedInCol(int table[9][9], int column, int number)
{
	for (int row = 0; row < 9; row++)
		if (table[row][column] == number)
			return 1;
	return 0;
}

bool UsedInBox(int table[9][9], int boxStartRow, int boxStartCol, int number)
{
	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++)
			if (table[row + boxStartRow][column + boxStartCol] == number)
				return 1;
	return 0;
}

bool isSafe(int table[9][9], int row, int column, int number)//is box/row/column has this number 
{
	return !UsedInRow(table, row, number)
		&& !UsedInCol(table, column, number)
		&& !UsedInBox(table, row - row % 3, column - column % 3, number)
		&& table[row][column] == 0;
}

bool solve(int table[9][9])
{
	int row, column;

	if (!FindUnassignedLocation(table, row, column))
		return 1;

	for (int number = 1; number <= 9; number++)
	{
		if (isSafe(table, row, column, number))
		{
			table[row][column] = number;
			if (solve(table))
				return 1;
			table[row][column] = 0;
		}
	}
	return 0;
}

void drawTable(int table[9][9])
{
	string answer = "";
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
			answer += to_string(table[row][column]) + "\t";
		answer += "\n";
	}
	cout << answer;
}

int main()
{
	int table[9][9];
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			table[i][j] = 0;
	{
		char whichInput;
		cout << "0 for input full sudoku (0 for no number),\n 1 for input by each filled cell: ";
		cin >> whichInput;
		if (whichInput == '0')
			for (int i = 0; i < 9; ++i)
				for (int j = 0; j < 9; ++j)
					cin >> table[i][j];
		else if (whichInput == '1')
		{

			cout << " x,y,number x, y in 0-8, number in 1-9\nprint 0 0 0 to end entery: ";
			while (1)
			{
				int a, b, c;
				cin >> a >> b >> c;
				if (a == 0 && b == 0 && c == 0)
				{
					cout << "ending input\n";
					break;
				}
				table[a][b] = c;
			}
		}
	}
	if (solve(table))
		drawTable(table);
	else
		cout << "no solves";
}
