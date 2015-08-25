// Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

// The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

// A partially filled sudoku which is valid.

// Note:
// A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isValidSudoku(char( *board)[9], int boardRowSize, int boardColSize) {
	int i, j, m, n;
	int Hash[10] = {0};

	for (i = 0; i < boardRowSize; ++i)
	{
		memset(Hash, 0, 10 * sizeof(int));
		for (j = 0; j < boardColSize; ++j)
		{
			if (board[i][j] != '.')
			{
				if (Hash[board[i][j] - '0'] != 0)
					return 0;
				else
					++Hash[board[i][j] - '0'];
			}
		}
	}

	for (i = 0; i < boardRowSize; ++i)
	{
		memset(Hash, 0, 10 * sizeof(int));
		for (j = 0; j < boardColSize; ++j)
		{
			if (board[j][i] != '.')
			{
				if (Hash[board[j][i] - '0'] != 0)
					return 0;
				else
					++Hash[board[j][i] - '0'];
			}
		}
	}

	for (i = 0; i < boardRowSize; i += 3)
	{
		for (j = 0; j < boardColSize; j += 3)
		{
			memset(Hash, 0, 10 * sizeof(int));
			for (m = i; m < i + 3; ++m)
			{
				for (n = j; n < j + 3; ++n)
				{
					if (board[m][n] != '.')
					{
						if (Hash[board[m][n] - '0'] != 0)
							return 0;
						else
							++Hash[board[m][n] - '0'];
					} 
				}
			}
		}
	}
	
	return 1;
}

int main(int argc, char const *argv[])
{
	// char board2[3][3] = {
	// 	{'3', '2', '1'},
	// 	{'1', '3', '.'},
	// 	{'2', '1', '2'}
	// };

	char board2[3][3] = {
		{'1', '.', '.'},
		{'.', '.', '.'},
		{'.', '.', '.'}
	};

	char board[][9] = {
	 "....5..1.",
	 ".4.3.....",
	 ".....3..1",
	 "8......2.",
	 "..2.7....",
	 ".15......",
	 ".....2...",
	 ".2.9.....",
	 "..4......"
	};

	// char board[][9] = {
	// 	"..5.....6",
	// 	"....14...",
	// 	".........",
	// 	".....92..",
	// 	"5....2...",
	// 	".......3.",
	// 	"...54....",
	// 	"3.....42.",
	// 	"...27.6.."
	// };

	// char **board;
	// int i, j;

	// board = malloc(sizeof(char*) * 3);
	// for (i = 0; i < 3; ++i)
	// {
	// 	board[i] = malloc(sizeof(char) * 3);
	// 	for (j = 0; j < 3; ++j)
	// 		board[i][j] = board2[i][j];
	// }

	printf("%d\n", isValidSudoku(board, 9, 9));
	return 0;
}