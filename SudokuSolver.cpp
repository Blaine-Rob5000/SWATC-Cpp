//Final Project: Sudoku Solver (SudokuSolver.cpp)
//created by Robin G. Blaine on 6/xx/2017
//a program to enter, work on, save, load, and solve Sudoku puzzles

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//function prototypes
int displayMainMenu();
void enterClues(int puzzleArray[81][2]);
void workPuzzle(int puzzleArray[81][2]);
void savePuzzle(int puzzleArray[81][2]);
void loadPuzzle(int puzzleArray[81][2]);
void solvePuzzle(int puzzleArray[81][2]);
void displayPuzzle(int puzzleArray[81][2]);
int chooseCell();
int chooseValue();
int checkForDuplicate(int cellNumber, int cellValue, int puzzleArray[81][2]);
void flagDuplicates(int puzzleArray[81][2]);
int countClues(int puzzleArray[81][2]);
int countAnswers(int puzzleArray[81][2]);
int countDuplicates(int puzzleArray[81][2]);

//main function
int main(int argc, char *argv[])
{
	//declare variables
	double version    = 1.0;
	int puzzle[81][2] = {0};
	int menuSelection = -1;
	
	//flag all cells as guesses initially
	for (int cell = 0; cell < 81; cell++)
		puzzle[cell][1] = 1;
	
	cout << "Welcome to Robin G. Blaine's Sudoku Solver, version " << version << "!" << endl << endl;
		
	while (menuSelection != 0)
	{
		menuSelection = displayMainMenu();
		
		if (menuSelection == 1)
			enterClues(puzzle);
			//end if
		if (menuSelection == 2)
			workPuzzle(puzzle);
			//end if
		if (menuSelection == 3)
			savePuzzle(puzzle);
			//end if
		if (menuSelection == 4)
			loadPuzzle(puzzle);
			//end if
		if (menuSelection == 5)
			solvePuzzle(puzzle);
			//end if
	}	//end while
	cout << endl << endl << "Goodbye!" << endl;
	return 0;
}	//end main function

//********** function definitions **********

//displays the menu and returns a selection from 0 to 5
int displayMainMenu()
{
	//declare variables
	int selection = -1;
	
	while ((selection < 0) || (selection > 5))
	{
		cout << endl << "Main Menu:" << endl;
		cout << "1) Enter Puzzle Clues" << endl;
		cout << "2) Attempt to Solve Puzzle" << endl;
		cout << "3) Save Puzzle" << endl;
		cout << "4) Load Puzzle" << endl;
		cout << "5) Have the Computer Solve the Puzzle" << endl;
		cout << "0) Quit Program" << endl;
		cout << endl;
		cout << "Enter menu selection: ";
		cin >> selection;
		cout << endl;
		if ((selection < 0) || (selection > 5))
			cout << "Invalid Selection!" << endl;
			//end if		
	}	//end while
	
	cin.ignore(100, '\n');
	
	return selection;
}	//end displayMenu function

//enter clues (fixed values) for the puzzle
void enterClues(int puzzleArray[81][2])
{
	//declare variables
	int clueCell  = -1;
	int clueValue = -1; 
	
	while (clueCell != 100)
	{
		displayPuzzle(puzzleArray);
		
		cout << "Number of clues: " << countClues(puzzleArray);
		cout << "  (Note: At least 17 clues are needed for a puzzle with a unique solution.)" << endl << endl << endl;
	
		cout << "Select a cell to enter a clue into..." << endl;
		clueCell = chooseCell();
				
		if (clueCell != 100)
		{
			clueValue = chooseValue();

			//assign clue to puzzle if the value is legal
			if (((checkForDuplicate(clueCell, clueValue, puzzleArray)) == 0) || (clueValue == 0))
			{
					puzzleArray[clueCell][0] = clueValue;	//place clueValue in the clueCell
					if (clueValue != 0)
						puzzleArray[clueCell][1] = 0;		//flag the cell as a clue
					else
						puzzleArray[clueCell][1] = 1;		//flag the cell as a guess
			}
			else
			{
				cout << endl << "Illegal clue!" << endl;
			}	//end if
		}	//end if
	}	//end while
}	//end enterClues function

//enter guesses for the puzzle
void workPuzzle(int puzzleArray[81][2])
{
	//declare variables
	int guessCell       =  -1;
	int guessValue      = -1;
	string returnToMenu = "";
	
	while (guessCell != 100)
	{
		displayPuzzle(puzzleArray);

		cout << "Select a cell to enter a guess into..." << endl;
		guessCell = chooseCell();

		if (guessCell != 100)
		{
			if (puzzleArray[guessCell][1] != 0)
			{
				guessValue = chooseValue();
				puzzleArray[guessCell][0] = guessValue;
				puzzleArray[guessCell][1] = 1;
				flagDuplicates(puzzleArray);
			}
			else
			{
				cout << endl << endl << "That cell is a clue!  Use menu option 1 from the main menu to change clues..." << endl;
			}	//end if
		}	//end if

		//check to see if puzzle is solved
		if ((countAnswers(puzzleArray) == 81) && (countDuplicates(puzzleArray) == 0))
		{
			displayPuzzle(puzzleArray);
			cout << endl << endl << "Puzzle Solved!!!" << endl << endl;
			cout << "Press any key to return to the main menu..." << endl;
			getline(cin, returnToMenu);
			guessCell = 100;
		}	//end if
	}	//end while
	
}	//end workPuzzle function

//save the puzzle clues and guesses
void savePuzzle(int puzzleArray[81][2])
{
	//create output file object and open it
	ofstream outFile;
	outFile.open("SudokuPuzzle.txt", ios::out);
	
	//check to see if file was opened
	if (outFile.is_open())
	{
		for (int cell = 0; cell < 81; cell++)
			outFile << puzzleArray[cell][0] << '#' << puzzleArray[cell][1] << endl;
			//end for
		outFile.close();
		cout << endl << endl << "Puzzle saved!" << endl << endl;
	}
	else
	{
		cout << endl << endl << "File could not be opened!" << endl << endl;
	}	//end if
}	//end savePuzzle function

//load puzzle clues and guesses
void loadPuzzle(int puzzleArray[81][2])
{
	//declare variables
	int tempPuzzle[81][2] = {0};
	int counter = 0;
	
	//create file object and open it
	ifstream inFile;
	inFile.open("SudokuPuzzle.txt", ios::in);
	
	//determine whether or not the file was opened
	if (inFile.is_open())
	{
		//read until end of file, count the number of records read
		while (!inFile.eof())
		{
			inFile >> tempPuzzle[counter][0];
			inFile.ignore();
			inFile >> tempPuzzle[counter][1];
			inFile.ignore();
			if (!inFile.eof())
				counter += 1;
				//end if
		}	//end while
		inFile.close();

		//check to see if 81 records were read
		if (counter == 81)
		{
			//if true, transfer contents of tempPuzzle to puzzleArray
			for (int cell = 0; cell < 81; cell++)
			{
				puzzleArray[cell][0] = tempPuzzle[cell][0];
				puzzleArray[cell][1] = tempPuzzle[cell][1];
			}	//end for
			cout << endl << endl << "Puzzle loaded!" << endl << endl;
		}
		else
		{
			//if false, output an error message
			cout << endl << endl << "File corrupted! Could not load puzzle..." << endl << endl;
		}	//enf if
	}
	else
	{
		cout << endl << endl << "File cold not be opened!" << endl << endl;
	}	//end if
}	//end loadPuzzle function

//have the computer solve the puzzle
void solvePuzzle(int puzzleArray[81][2])
{
	//declare variables
	int tempPuzzle[81][2] = {0};
	int counter    = 0;
	
	//copy puzzle clues into temporary array and flag all other cells as guesses
	for (int cell = 0; cell < 81; cell++)
	{
		if (puzzleArray[cell][1] == 0)
			tempPuzzle[cell][0] = puzzleArray[cell][0];		//copy clue value
		else
			tempPuzzle[cell][1] = 1;						//flag all other cells as guesses
			//end if
	}	//end for

	//solve the puzzle
	while ((counter > -1) && (counter < 81))
	{
		if (tempPuzzle[counter][1] != 0)		//cell is not a clue
		{
			if (tempPuzzle[counter][0] < 9)		//cell is not maxed
			{
				tempPuzzle[counter][0] += 1;	//increase its value
				if (checkForDuplicate(counter, tempPuzzle[counter][0], tempPuzzle) == 0)
					counter += 1;				//new value is not a duplicate, so move on to next cell
					//end if
			}
			else
			{
				tempPuzzle[counter][0] = 0;
				counter -= 1;
				while (tempPuzzle[counter][1] == 0)
					counter -= 1;
					//end while
			}	//end if
		}
		else									//cell is a clue, go to next cell
		{
			counter += 1;
		}	//end if


//*** debug ***		
	system("clear");
	displayPuzzle(tempPuzzle);
	cout << "Counter: " << counter << endl;
//*** debug ***


		if ((countAnswers(tempPuzzle) == 81) && (countDuplicates(tempPuzzle) == 0))
			counter = 100;
		
	}	//end while
	
	//flag all cells as clues
	for (int cell = 0; cell < 81; cell++)
		tempPuzzle[cell][1] = 0;
		//end for
	
	displayPuzzle(tempPuzzle);
	
	if ((countAnswers(tempPuzzle) == 81) && (countDuplicates(tempPuzzle) == 0))
		cout << endl << "Puzzle Solved!" << endl << endl;
	else
		cout << endl << "Could not solve..." << endl << endl;
}	//end solvePuzzle function

//display the puzzle
//[N][0] = value of the Nth cell (0 = no entry)
//[N][1] = status of the value in the Nth cell (0 = clue, 1 = guess, 2 = duplicate guess)
//N is calculated as rowValue*9 + columnValue
void displayPuzzle(int puzzleArray[81][2])
{
	//delcare variables
	string regionDivider = "";
	char rowHeader[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
	
	//create the horizontal divider for regions
	regionDivider.assign(43, '-');
	
	cout << endl << "Puzzle:" << endl << endl;
	
	//display column header
	cout << endl;
	cout << "   |";
	for (int column = 0; column < 9; column++)
		{
			cout << " " << (column +1) << "  ";
			//output vertical region divider
			if ((column == 2) || (column == 5) || (column == 8))
				cout << "|";
				//end if
		}
		cout << endl << regionDivider << endl;
			
	for (int row = 0; row < 9; row++)
	{
		cout << " " << rowHeader[row] << " |";
		for (int column = 0; column < 9; column++)
		{
			cout << " ";
			
			//output an blank if the cell is unassigned (0)
			if  (puzzleArray[row * 9 + column][0] == 0)
				cout << " ";
			else
			{
				//output the cell value if it is in the 1-9 range or E otherwise
				if ((puzzleArray[row * 9 + column][0] >= 1) && (puzzleArray[row * 9 + column][0] <= 9))
					cout << puzzleArray[row * 9 + column][0];
				else
					cout << "E";
					//end if
			}	//end if
			
			//show whether the cell value is:
				//a clue (value 0, output " ")
				//a guess (value 1, output "?")
				//a duplicate guess (value 2, output "!")
			if (puzzleArray[row * 9 + column][1] == 0)
				cout << " ";
				//end if
			if (puzzleArray[row * 9 + column][1] == 1)
				cout << "?";
				//end if
			if (puzzleArray[row * 9 + column][1] == 2)
				cout << "!";
				//end if
			cout << " ";	
			
			//output vertical region divider
			if ((column == 2) || (column == 5) || (column == 8))
				cout << "|";
				//end if
		}	//end for (column)
		cout << endl;
		
		//output horizontal region divider
		if ((row == 2) || (row == 5) || (row == 8))
			cout << regionDivider << endl;
			//end if
				
	}	//end for (row)
	cout << endl;
	cout << "     ? = guess           ! = duplicate" << endl << endl;
}	//end displayPuzzle function

//return a valid cell number (0 - 80) into which to enter a clue or a guess or return 100 as a sentinel value
//cells are denoted by the row letter (A - I) followed by the column number (1 - 9) ... { examples: A1, E5, I9 }
int chooseCell()
{
	//declare variables
	string cellCoordinates = "";
	int cellRow    = -1;
	int cellColumn = -1;
	

	while ((cellRow == -1) || (cellColumn == -1))
	{
		cellRow    = -1;
		cellColumn = -1;
		
		cout << "  Enter row letter (A - I) plus column number (1 - 9) or X to return to main menu (progress will not be lost): ";
		getline(cin, cellCoordinates);
		
		if ((cellCoordinates == "X") || (cellCoordinates == "x"))
		{
			//if X was entered set sentinal values to return to main menu
			cellRow    = 10;
			cellColumn = 10;
		}
		else
		{
			//check to make sure that the string is 2 characters long
			if (cellCoordinates.length() == 2)
			{
				//assign a row based on the first character in the string
				if ((cellCoordinates.substr(0,1) == "A") || (cellCoordinates.substr(0,1) == "a"))
					cellRow = 0;
					//end if
				if ((cellCoordinates.substr(0,1) == "B") || (cellCoordinates.substr(0,1) == "b"))
					cellRow = 1;
					//end if
				if ((cellCoordinates.substr(0,1) == "C") || (cellCoordinates.substr(0,1) == "c"))
					cellRow = 2;
					//end if
				if ((cellCoordinates.substr(0,1) == "D") || (cellCoordinates.substr(0,1) == "d"))
					cellRow = 3;
					//end if
				if ((cellCoordinates.substr(0,1) == "E") || (cellCoordinates.substr(0,1) == "e"))
					cellRow = 4;
					//end if
				if ((cellCoordinates.substr(0,1) == "F") || (cellCoordinates.substr(0,1) == "f"))
					cellRow = 5;
					//end if
				if ((cellCoordinates.substr(0,1) == "G") || (cellCoordinates.substr(0,1) == "g"))
					cellRow = 6;
					//end if
				if ((cellCoordinates.substr(0,1) == "H") || (cellCoordinates.substr(0,1) == "h"))
					cellRow = 7;
					//end if
				if ((cellCoordinates.substr(0,1) == "I") || (cellCoordinates.substr(0,1) == "i"))
					cellRow = 8;
					//end if
				
				//assign a column based on the second character in the string
				if (cellCoordinates.substr(1,1) == "1")
					cellColumn = 0;
					//end if
				if (cellCoordinates.substr(1,1) == "2")
					cellColumn = 1;
					//end if
				if (cellCoordinates.substr(1,1) == "3")
					cellColumn = 2;
					//end if
				if (cellCoordinates.substr(1,1) == "4")
					cellColumn = 3;
					//end if
				if (cellCoordinates.substr(1,1) == "5")
					cellColumn = 4;
					//end if				
				if (cellCoordinates.substr(1,1) == "6")
					cellColumn = 5;
					//end if
				if (cellCoordinates.substr(1,1) == "7")
					cellColumn = 6;
					//end if
				if (cellCoordinates.substr(1,1) == "8")
					cellColumn = 7;
					//end if
				if (cellCoordinates.substr(1,1) == "9")
					cellColumn = 8;
					//end if
			}	//end if
		}	//end if
		//error message if invalide coordinates were entered
		if ((cellRow == -1) || (cellColumn == -1))
			cout << "  Invalid coordinates!  Valid examples:  A1, E5, I9 ..." << endl << endl;
	}	//end while
	
	//return the cell location (0 - 80) or 100 as a sentinel value
	return (cellRow * 9 + cellColumn);
}	//end chooseCell function

//return a valid number (1 - 9) to put in a cell or return 0 to cancel and go back to cell selection
int chooseValue()
{
	//declare variables
	string cellValue  = "";

	while (cellValue == "")
	{
		cout << "  Enter a value (1 - 9) for the cell (enter 0 to clear the cell): ";
		getline(cin, cellValue);
		
		if(!isdigit(cellValue.at(0)))
		//if ((cellValue < 0) || (cellValue > 9))
		{
			cout << endl << "  Invalid cell value!" << endl << endl;
			cellValue = "";
		}	//end if
	}	//end while

	//return the value to be assigned to the cell (1 - 9) or 0 as a sentinel value
	return atoi(cellValue.c_str());
}	//end chooseValue function

//check to see if the cellValue when entered into cellNumber duplicates a value in that row, column, or region
//returns 0 if it does not duplicate a value or 1 if it does
int checkForDuplicate(int cellNumber, int cellValue, int puzzleArray[81][2])
{
	//declare variables
	int isDuplicate = 0;
	int cellRow     = 0;
	int cellColumn  = 0;
	int regionHome  = 0;
	
	cellRow    = cellNumber/9;
	cellColumn = cellNumber%9;

	//check row
	for (int column = 0; column < 9; column++)
	{
		if ((column != cellColumn) && (puzzleArray[cellRow * 9 + column][0] == cellValue))
		{
			isDuplicate = 1;
		}	//end if
	}	//end for
	
	//check column
	for (int row = 0; row < 9; row++)
	{
		if ((row != cellRow) && (puzzleArray[row * 9 + cellColumn][0] == cellValue))
		{
			isDuplicate = 1;
		}	//end if		
	}	//end for
	
	//determine region
	if (cellRow < 3)						//upper row
	{
		if (cellColumn < 3)
			regionHome = 0;					//left column   (upper left region)
			//end if
		if ((cellColumn >2) && (cellColumn < 6))
			regionHome = 3;					//middle column (upper middle region)
			//end if
		if (cellColumn > 5)
			regionHome = 6;					//right column  (upper right region)
			//end if
	}	//end if
	
	if ((cellRow > 2) && (cellRow < 6))		//middle row
	{
		if (cellColumn < 3)
			regionHome = 27;				//left column   (middle left region)
			//end if
		if ((cellColumn >2) && (cellColumn < 6))
			regionHome = 30;				//middle column (center region)
			//end if
		if (cellColumn > 5)
			regionHome = 33;				//right column  (middle right region)
			//end if
	}	//end if
	
	if (cellRow > 5)						//lower row
	{
		if (cellColumn < 3)
			regionHome = 54;				//left column   (lower left region)
			//end if
		if ((cellColumn >2) && (cellColumn < 6))
			regionHome = 57;				//middle column (lower middle region)
			//end if
		if (cellColumn > 5)
			regionHome = 60;				//right column  (lower right region)
			//end if
	}	//end if	
		
	//check region
	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 3; column++)
		{
			if ((regionHome + row * 9 + column) != cellNumber)
			{
				if ((puzzleArray[(regionHome + row * 9) + column][0]) == cellValue)
				{
					isDuplicate = 1;
				}	//end if
			}	//end if
		}	//end for (column)
	}	//end for (row)
	
	//if the value being entered into the cell is 0 then do not flag as a duplicate
	if (cellValue == 0)
		isDuplicate = 0;
	
	return isDuplicate;
}	//end checkForDuplicate function


//flag guess cells that are duplicates
void flagDuplicates(int puzzleArray[81][2])
{
	for (int cell = 0; cell < 81; cell++)
	{
		if (puzzleArray[cell][1] != 0)
		{
			if ((checkForDuplicate(cell, puzzleArray[cell][0], puzzleArray) == 0))
			{
				puzzleArray[cell][1] = 1;	//flag as a guess if no duplication
			}
			else
			{
				puzzleArray[cell][1] = 2;	//flag as a duplicate
			}	//end if
		}	//end if
	}	//end for
}	//end flagDuplicates function


//returns the number of cells that have clues in them
int countClues(int puzzleArray[81][2])
{
	//delcare variables
	int numClues = 0;
	
	for (int count = 0; count < 81; count++)
	{
		if ((puzzleArray[count][0] != 0) && (puzzleArray[count][1] == 0))
			numClues += 1;
	}
	
	return numClues;
}	//end countAnswers function


//returns the number of cells that have answers (an answer is any value other than 0) in them
int countAnswers(int puzzleArray[81][2])
{
	//delcare variables
	int numAnswers = 0;
	
	for(int cell = 0; cell < 81; cell++)
	{
		if ((puzzleArray[cell][1] != 2) && (puzzleArray[cell][0] != 0))
			numAnswers += 1;
			//end if
	}	//end for
	return numAnswers;
}	//end countAnswers function

//returns the number of duplicates in the puzzle
int countDuplicates(int puzzleArray[81][2])
{
	//delcare variables
	int numDuplicates = 0;
	
	for (int cell  = 0; cell < 81; cell++)
	{
		if (puzzleArray[cell][1] == 2)
			numDuplicates += 1;
			//end if
	}	//end for
	
	return numDuplicates;
}	//end countDuplicates function

