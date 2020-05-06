//Coder: Abdullah Al Nomaan Nafi
//Dept. of I.C.T. Islamic University, Kushtia

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

#define SIZE 3

using namespace std;

class Game{
private:
	char grid[SIZE][SIZE];

public:

	int count = 0;

	void create_grid(){

		int number = 1;

		for(int i=0; i<SIZE; ++i)
		{
			for(int j=0; j<SIZE; ++j)
			{
				grid[i][j] = to_string(number).c_str()[0];
				number++;
			}
		}
	}

	void show_grid(){

		printf(" -------------\n");
		for(int i=0; i<SIZE; ++i)
		{
			printf(" |");
			for(int j=0; j<SIZE; ++j)
			{
				printf(" %c |", grid[i][j]);
			}
			printf("\n -------------\n");
		}
	}

	void ask_position()
	{
		string input;

		puts("Where you want to play?  ");
		start:
		getline(cin,input);

		if(input != "")
		{
			char position = input.c_str()[0];
			if(position>='1' && position <='9')
			{
				int pos = position - '0' - 1;
				int row = pos / SIZE;
				int col = pos % SIZE;

				if(grid[row][col] == 'O' || grid[row][col] == 'X')
				{
					puts("This grid is already taken!");
					goto start;
				}
				else
				{
					grid[row][col] = 'X';
					count++;
				}
			}
			else
			{
				puts("You have to play in range 1 to 9!\n");
			}
		}
		else 
		{
			puts("You must enter something!\n");
		}
	}

	void computer_choice()
	{
		while(true)
		{
			int position = rand() % 9 + 1;

			int row = (position-1) / SIZE;
			int col = (position-1) % SIZE;

			if(count == 9)
			{
				show_grid();
				if(!check_win())
				{
					puts("*******************************");
					puts("!!!!!!!!! Match Drawn !!!!!!!!!");
					puts("*******************************");
				}
				exit(1);
			}

			if(grid[row][col] == 'X' || grid[row][col] == 'O')
				continue;
			else
			{	
				printf("Computer will play at position %d\n",position);
				grid[row][col] = 'O';
				count++;
				show_grid();
				break;
			}
		}
	}

	bool check_win()
	{
		const char* winning_moves[8] = {
			"123",
			"456",
			"789",
			"147",
			"258",
			"369",
			"159",
			"357"
		};
		bool winner;
		char privious_grid;

		for(int i=0; i<8; ++i)
		{
			privious_grid = '0';
			winner = true;

			for(int j=0; j<SIZE; ++j)
			{
				int pos = winning_moves[i][j] - '0' - 1;
				int row = pos / SIZE;
				int col = pos % SIZE;

				char grid_char = grid[row][col];
				
				if(privious_grid == '0')
				{
					privious_grid = grid_char;
				}
				else if(privious_grid == grid_char)
				{
					continue;
				}
				else
				{
					winner = false;
					break;
				}
			}

			if(winner == true)
			{
				puts("*******************************");
				if(privious_grid=='X')
				{
					puts("****** WE HAVE A WINNER! ******");
					printf("   Congratulations! You won!\n");
				}
				else
					printf("      Sorry! You lose!\n");
				puts("*******************************");

				return true;
			}
		}

		return false;

	}

	Game()
	{
		create_grid();
		show_grid();
		while( true )
		{
			ask_position();
			computer_choice();
			if(check_win())
			{
				break;
			}
		} 
	}

};

int main()
{
	srand(time(0));
	Game ttt;

	return 0;
}