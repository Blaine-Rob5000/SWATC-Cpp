# SWATC-Cpp
C++ Final Project

Sudoku Solver version 1.0
created by Robin G. Blaine on 6/23/2017 using C++


Sudoku is a Japanese puzzle consisting of 81 squares arranged in a nine-by-nine grid.  This grid is further subdivided into 9 three-by-three regions.  The object of the game is to place the numbers 1 through 9 in each of the squares such that no number is duplicated in any row, column, or region.  Puzzles start with a number of the squares (called clues) already filled. This program allows the user to enter clues and guesses into a puzzle and lets the user know when they have solved the puzzle.  It also allows the user to save their progress on a puzzle, including any clues and guesses.  Finally, the program can solve a puzzle for the user.


# Code Example (puzzle solver algorithm):  This is the section of the program that searches through the puzzle and finds the solution.

	//solve the puzzle
	counter = firstGuess;
	while ((counter >= firstGuess) && (counter <= lastGuess))
	{
		if (tempPuzzle[counter][1] != 0)		//cell is not a clue
		{
			if (tempPuzzle[counter][0] < 9)		//cell value is not maxed
			{
				tempPuzzle[counter][0] += 1;	//increase the cell value by one
				if (checkForDuplicate(counter, tempPuzzle[counter][0], tempPuzzle) == 0)
					counter += 1;
								//end if
			}
			else					//cell value maxed, reset to 0 & go back 1 cell
			{
				tempPuzzle[counter][0] = 0;
				counter -= 1;
			}					//end if
		}
		else						//cell is a clue, go to next cell
		{
			counter += 1;
		}						//end if
	}							//end while


# Motivation:

This is the final project for my C++ introductory programming class.  Its purpose is to showcase my understanding of the basic concepts introduced in the course.  Future updates to the program will add graphic elements including a graphical user interface.


# API:

The main menu of the program allows you to select from the following options:

1) Enter Puzzle Clues
	The user can enter the clues (squares with predetermined, fixed values) by entering the coordinates for the square by the row letter (A, B, C, D, E, F, G, H, or I) and the column number (1, 2, 3, 4, 5, 6, 7, 8, or 9).  For example, the first square of the puzzle is A1 and the last square is I9.  Letters may be entered in upper or lower case.

	After selecting a square, the user either enters a clue value for that square (ranging from 1 to 9) or 0 to clear the square.  The program will not allow the user to enter duplicate clues.  If a clue would 

	The program displays the number of clues entered for the puzzle.  Note that no puzzle with fewer than 17 clues can have a unique solution.

	Once the user has finished entering clues, she may return to the main menu by entering the letter X (upper or lower case) for the square coordinates.

	The user may return later to add additional clues as desired.

2) Attempt to Solve Puzzle
	The user enters guesses into squares in the puzzle that do not contain guesses.  The program flags these squares as either a guess (?) or a duplicate (!).  If the user fills all of the free squares with non-duplicate numbers, the puzzle is solved.

3) Save Puzzle
	The program saves the puzzle (including all clues and guesses entered by the user) so that the user may continue working on it at a later point.

	The puzzle is saved in the text file, "SudokuPuzzle.txt".

4) Load Puzzle
	The program loads a previously saved puzzle so that the user can continue working on it.

	If the "SudokuPuzzle.txt" file does not contain the appropriate amount of data, the puzzle will not be loaded.

5) Have the Computer Attempt to Solve the Puzzle
	The program will solve the puzzle and display the answer.  For puzzles with a fewer number of clues, this may take some time. Only clues are taken into account when solving the puzzle; any guesses entered by the user are not considered. However, if the user is certain of the values for any numbers, they may be entered as clues and will be considered.

	The algorithm used to solve the puzzle is a "brute force" method called backtracking. It places a value of 1 in the first open square and checks to see if that value is legal.  If it is legal, it moves on to the next open square.  If it is not legal, it increments to the next value and checks it. If no value is legal, it moves back to the previous open square and increments its value by 1.

0) Quit Program
	This option exits the program.

~~~
# Puzzle Legend:
	A blank square with a ? after it is empty.
	A square with a number not followed by any cell is a clue. (A1)
	A square with a number followed by a ? is a guess. (D2)
	A square with a number followed by a ! is a duplicate number. (A4)

   | 1   2   3   | 4   5   6   | 7   8   9   |  < Column number
----------------------------------------------
 A | 5    ?   ?  | 5!   ?   ?  |  ?   ?   ?  |
 B |  ?   ?   ?  |  ?   ?   ?  |  ?   ?   ?  |
 C |  ?   ?   ?  |  ?   ?   ?  |  ?   ?   ?  |
----------------------------------------------
 D |  ?  4?   ?  |  ?   ?   ?  |  ?   ?   ?  |
 E |  ?   ?   ?  |  ?   ?   ?  |  ?   ?   ?  |
 F |  ?   ?   ?  |  ?   ?   ?  |  ?   ?   ?  |
----------------------------------------------
 G |  ?   ?   ?  |  ?   ?   ?  |  ?   ?   ?  |
 H |  ?   ?   ?  |  ?   ?   ?  |  ?   ?   ?  |
 I |  ?   ?   ?  |  ?   ?   ?  |  ?   ?   ?  |
----------------------------------------------

 ^
 Row letter
 ~~~

# Tests
	Tests may be run by entering a number of clues and guesses, saving the puzzle, and having the program search for a solution.  This may take a while (upwards of 900,000 cycles) for puzzles with fewer numbers of clues.  For a quicker test, more clues should be added.


# Contributers
Contributers can find out more about the algorithm at the following sites:
	https://en.wikipedia.org/wiki/Sudoku_solving_algorithms
	https://stackoverflow.com/questions/16675248/sudoku-solving-algorithm-c
