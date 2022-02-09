//Mai shani - ID 316551613
//snake game - the user should move the snake by the keys ( up, down, left, right, esc to exit).
//the snake is grown any time it eats. If the snake tough the frame or himself - game over

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h> /*for clrscr()*/

typedef struct {
	int rows;
	int cols;
}size;

typedef struct {
	int place_rows;
	int place_cols;
}point;

#define UP 72  // Up Arrow 
#define DOWN 80 // Down Arrow 
#define LEFT 75  // Left Arrow 
#define RIGHT 77  // Right Arrow 
#define ESC 27  // Escape Key
#define EXIT 0 //finish game
#define ROWS 25
#define COLS 75
#define MAX_SIZE_OF_SNAKE 20 //size needed to win

void gotoxy(int y, int x);
int getKey();
int print_menu();// function to print the main menu
size do_user_choice(int user_choice, char frame[][COLS]);// function that print the board according to the user choice (or exit the game)
void print_frame(char frame[ROWS][COLS]);//print the frame
void insert_food(size size_of_board, char frame[][COLS]);//insert food in the game
bool game(size size_board, point snake_place[], int size_of_snake, char frame[][COLS]);//scan the user's activities
void build_frame(char frame[ROWS][COLS]);//build the array of frame
void move_array(point snake_place_arr[], int cur_counter_place, int size_of_snake);//move snake, fix the array in case of eating


void main()
{
	bool keep_playing = true;

	while (keep_playing)
	{
		bool won_game;
		int user_choice;
		size size_of_board = { -1,-1 };
		int size_of_snake = 10;
		point snake_place_arr[20];
		char frame[ROWS][COLS];

		printf("Hello, welcome to the SNAKE !\n");

		while (size_of_board.cols == -1) {

			user_choice = print_menu();// print the menu
			size_of_board = do_user_choice(user_choice, frame);

			if (size_of_board.cols == EXIT) // if the user chose to exit - stop the program, else the board is printed 
				return;
		}

		build_frame(frame);

		insert_food(size_of_board, frame);//put a food in the game

		won_game = game(size_of_board, snake_place_arr, size_of_snake, frame);

		if (won_game == true) {// if won - print
			system("cls");
			printf("***********************************\nCongratulations, you won!!\n***********************************\n\n");
		}

		else {//if lose
			printf("***********************************\nGAME OVER!!!\n***********************************\n\n");
		}
	}
}

bool game(size size_board, point snake_place_arr[], int size_of_snake, char frame[][COLS]) {

	char c = '\0', temp = '\0';
	int counter_place_in_array = 0;//to know when did I full the array of places
	int counter_size_of_snake = 0;//size of snake right now
	int x, y;

	////middle of screen///////
	x = ROWS / 2;
	y = COLS / 2;

	while (size_of_snake < MAX_SIZE_OF_SNAKE)
	{
		gotoxy(y, x);

		////if the snake hit himself or the frame - finish the game - game over
		if (frame[x][y] == '#') {
			system("cls");
			printf("The snake hit the frame !!\n");
			return false;
		}

		if (frame[x][y] == '@') {
			system("cls");
			printf("The snake hit itself !!\n");
			return false;
		}

		if (counter_place_in_array == size_of_snake)//init the counter place to re-use the array of place - insert the new points
			counter_place_in_array = 0;

		if (c != '\0') {

			if (frame[x][y] != '#' && frame[x][y] != '@') {//the snake in he wat to eat

				if (frame[x][y] == '$') {//if he arrived to the food

					move_array(snake_place_arr, counter_place_in_array, size_of_snake);
					printf("@");
					frame[x][y] = '@';//insert snake body to array (to know if the snake hit himself)
					size_of_snake++;//the snake has grown
					counter_size_of_snake++;//the snake have 1 more part in his body on screen
					snake_place_arr[counter_place_in_array].place_cols = y;//insert the place on board that the @ was print
					snake_place_arr[counter_place_in_array].place_rows = x;
					counter_place_in_array++;

					gotoxy(COLS + 10, ROWS + 10);

					if (size_of_snake == MAX_SIZE_OF_SNAKE)
						return true;
					else
						insert_food(size_board, frame);// insert another food
				}

				else {// there is " " ...

					if (counter_size_of_snake < size_of_snake) {//the snake is not in his size yet
						printf("@");
						frame[x][y] = '@';
						counter_size_of_snake++;
						snake_place_arr[counter_place_in_array].place_cols = y;//save the point in array
						snake_place_arr[counter_place_in_array].place_rows = x;
						counter_place_in_array++;
						gotoxy(COLS + 10, ROWS + 10);
					}

					else//counter size of snake is like the size of snake
					{
						printf("@");
						frame[x][y] = '@';

						//take out the point from the array
						frame[snake_place_arr[counter_place_in_array].place_rows][snake_place_arr[counter_place_in_array].place_cols] = ' ';
						gotoxy(snake_place_arr[counter_place_in_array].place_cols, snake_place_arr[counter_place_in_array].place_rows);
						printf(" ");
						snake_place_arr[counter_place_in_array].place_cols = y;//save the point in array
						snake_place_arr[counter_place_in_array].place_rows = x;
						counter_place_in_array++;
						gotoxy(COLS + 10, ROWS + 10);
					}
				}

			}
		}

		Sleep(50);
		// only if a key was hit we read what key code it was
		if (_kbhit())// if any key was hit
			temp = getKey();

		if (temp == ESC || temp == RIGHT || temp == LEFT || temp == UP || temp == DOWN)
			c = temp;

		switch (c)
		{
		case RIGHT:
			y++;
			break;
		case DOWN:
			x++;
			break;
		case LEFT:
			y--;
			break;
		case UP:
			x--;
			break;
		case ESC:
			system("cls");
			return false;
		case 0:
			break;
		}

	}
	return true;
	printf("You won!!!!!!!\n");
}
//This function change the places of the points in the arrat after eating (because the snake is grown 
void move_array(point snake_place_arr[], int cur_counter_place, int size_of_snake) {

	int i;

	for (i = size_of_snake; i > cur_counter_place; i--)
		snake_place_arr[i] = snake_place_arr[i - 1];
}
//This function print the menu
int print_menu() {

	int user_choice;

	printf("*****************************************************\n\n");
	printf("Please choose one of the options below:\n\n");
	printf(" 0 - Exit\n 1 - Basic Level\n\n");
	printf("*****************************************************\n");

	scanf("%d", &user_choice);

	return user_choice;
}
//this function do what the user chose in main menu
size do_user_choice(int user_choice, char frame[][COLS])
{
	size size_board = { -1,-1 };

	switch (user_choice)
	{
	case 0://want to finish game
		printf("Thank you!");
		size_board.cols = size_board.rows = EXIT;
		return size_board;
	case 1:
		system("cls"); /*clear output screen*/
		size_board.cols = COLS;
		size_board.rows = ROWS;
		print_frame(frame);
		return size_board;
	default:
		system("cls"); /*clear output screen*/
		printf("Invalid choice - choose again\n\n");
		return size_board;
	}
}
//This function build the frame array in order to know if the snake hit the frame (or hinself)
void build_frame(char frame[ROWS][COLS]) {

	int i, j;

	for (i = 0; i < COLS; i++)
		frame[0][i] = '#';

	for (j = 1; j < ROWS - 1; j++) {
		frame[j][0] = '#';
		for (i = 1; i < COLS - 1; i++)
			frame[j][i] = ' ';
		frame[j][COLS - 1] = '#';
	}

	for (i = 0; i < COLS; i++)
		frame[ROWS - 1][i] = '#';
}
//This function print the frame
void print_frame(char frame[ROWS][COLS]) {

	int x_frame = 0, y_frame = 0;

	for (x_frame; x_frame < COLS - 1; x_frame++) {
		gotoxy(x_frame, y_frame);
		printf("#");
	}
	for (y_frame; y_frame < ROWS - 1; y_frame++) {
		gotoxy(x_frame, y_frame);
		printf("#");
	}
	for (x_frame; x_frame > -1; x_frame--) {
		gotoxy(x_frame, y_frame);
		printf("#");
	}
	for (y_frame; y_frame > -1; y_frame--) {
		gotoxy(x_frame, y_frame);
		printf("#");
	}
}
//This function add one piece of food  
void insert_food(size size_of_board, char frame[][COLS]) {

	srand(time(NULL));
	int x, y;

	x = rand() % (ROWS - 2);//choose a random point
	y = rand() % (COLS - 2);

	x = x + 1;//choose a random point
	y = y + 1;

	frame[x][y] = '$';

	gotoxy(y, x);
	printf("$");
}
// This function moves the cursor to the line y and column x , (0,0) is the upper left corner of the screen.
void gotoxy(int y, int x) {
	printf("\x1b[%d;%df", x + 1, y + 1);
}
// This function gets keyCodes for special keys such as arrows , escape and others
// It returns the Key code such as 72 for arrow up, 27 for Escape... 
int getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}