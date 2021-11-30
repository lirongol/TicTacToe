#include <iostream>
#include <vector>
#include <algorithm>

void play_game();
void print_board(std::vector<char> board);
char check_winner(std::vector<char> board);
int find_best_move(std::vector<char> board);
int minimax(std::vector<char> _board, bool o_turn);

const std::vector<std::vector<int>> patterns = {
	{0,1,2},
	{3,4,5},
	{6,7,8},
	{0,3,6},
	{1,4,7},
	{2,5,8},
	{0,4,8},
	{2,4,6}
};

int main()
{
	while (true)
	{
		int option;
		std::cout << "menu:\n1.play game\n2.exit" << std::endl;
		std::cin >> option;
		switch (option)
		{
		case 1:
			play_game();
			break;
		case 2:
			return 0;
		}
	}
}

void play_game()
{
	std::vector<char> board = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	bool x_turn = true;
	std::cout << "you will play as X" << std::endl;
	print_board(board);
	while (true)
	{
		if (x_turn)
		{
			int index;
			std::cout << "your move: ";
			std::cin >> index;
			if (index >= 0 && index < 9)
			{
				if (board[index] == ' ')
				{
					board[index] = 'X';
					print_board(board);
					x_turn = false;
				}
				else
				{
					std::cout << index << " is taken, choose another index" << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "please enter index between 0-8" << std::endl;
				continue;
			}
		}
		else
		{
			std::cout << "ai move:" << std::endl;
			board[find_best_move(board)] = 'O';
			print_board(board);
			x_turn = true;
		}

		if (check_winner(board) == 'D')
		{
			std::cout << "Draw!" << std::endl;
			break;
		}
		else if (check_winner(board) == 'X')
		{
			std::cout << "X is the winner!" << std::endl;
			break;
		}
		else if (check_winner(board) == 'O')
		{
			std::cout << "O is the winner" << std::endl;
			break;
		}
		else continue;
	}
}

int find_best_move(std::vector<char> board)
{
	std::vector<char> _board = board;
	int best_score = -1;
	int best_move;

	for (int i = 0; i < 9; i++)
	{
		if (_board[i] == ' ')
		{
			_board[i] = 'O';
			int score = minimax(_board, false);
			_board[i] = ' ';
			if (score > best_score)
			{
				best_score = score;
				best_move = i;
			}
		}
	}
	return best_move;
}

int minimax(std::vector<char> _board, bool o_turn)
{
	char winner = check_winner(_board);
	if (winner != 'N')
	{
		if (winner == 'O') return 1;
		if (winner == 'X') return -1;
		if (winner == 'D') return 0;
	}

	if (o_turn)
	{
		int best_score = -1;
		int best_move;
		for (int i = 0; i < 9; i++)
		{
			if (_board[i] == ' ')
			{
				_board[i] = 'O';
				int score = minimax(_board, false);
				_board[i] = ' ';
				if (score > best_score)
				{
					best_score = score;
					best_move = i;
				}
			}
		}
		return best_score;
	}
	else
	{
		int best_score = 1;
		int best_move;
		for (int i = 0; i < 9; i++)
		{
			if (_board[i] == ' ')
			{
				_board[i] = 'X';
				int score = minimax(_board, true);
				_board[i] = ' ';
				if (score < best_score)
				{
					best_score = score;
					best_move = i;
				}
			}
		}
		return best_score;
	}
}

char check_winner(std::vector<char> board)
{
	for (int i = 0; i < 8; i++)
	{
		char symbol = board[patterns[i][0]];
		if (symbol != ' ')
		{
			if (board[patterns[i][1]] == symbol &&
				board[patterns[i][2]] == symbol)
			{
				if (symbol == 'X') return 'X';
				if (symbol == 'O') return 'O';
			}
		}
	}

	if (!std::count(board.begin(), board.end(), ' '))
	{
		return 'D';
	}

	return 'N';
}

void print_board(std::vector<char> board)
{
	std::cout << "\n";
	for (int i = 0; i < 9; i += 3)
	{
		std::cout << "\t" <<
			board[i] << " | " <<
			board[i+1] << " | " << 
			board[i+2] << std::endl;
		if (i < 4) std::cout << "\t---------" << std::endl;
	}
	std::cout << "\n";
}