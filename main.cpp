#include <iostream>                                     
#include <string>									   
#include <fstream>

using namespace std;




class Day_Node
{
public:

	int Date;
	int Year;
	string Day_Name;
	string Month_Name;

	string Note1 = "Note not set.";
	string Note2 = "Note not set.";
	string Note3 = "Note not set.";
	string Note4 = "Note not set.";
	string Note5 = "Note not set.";

private:
};

struct Calender_Load_Package
{
	int Start;
	int Length;
	Day_Node**** Calender_Pointer;
};

// Function that fills the MonthName,MonthLength and DayName arrays with their appropriate values for later use.
void SetCalender(string* DayInput, string* MonthNames, int* MonthLengths)
{
	DayInput[0] = " S";
	DayInput[1] = " M";
	DayInput[2] = "Tu";
	DayInput[3] = " W";
	DayInput[4] = "Th";
	DayInput[5] = " F";
	DayInput[6] = "Sa";

	MonthNames[0] = "January"; MonthLengths[0] = 31;
	MonthNames[1] = "February"; MonthLengths[1] = 28;
	MonthNames[2] = "March"; MonthLengths[2] = 31;
	MonthNames[3] = "April"; MonthLengths[3] = 30;
	MonthNames[4] = "May"; MonthLengths[4] = 31;
	MonthNames[5] = "June"; MonthLengths[5] = 30;
	MonthNames[6] = "July"; MonthLengths[6] = 31;
	MonthNames[7] = "August"; MonthLengths[7] = 31;
	MonthNames[8] = "September"; MonthLengths[8] = 30;
	MonthNames[9] = "October"; MonthLengths[9] = 31;
	MonthNames[10] = "November"; MonthLengths[10] = 30;
	MonthNames[11] = "December"; MonthLengths[11] = 31;



}

// Function that returns true if the input is a leap year.
bool CheckForLeap(int Year)
{
	bool LeapYear = false;

	if (Year % 4 == 0)
	{
		LeapYear = true;
	}

	if (Year % 100 == 0)
	{
		LeapYear = false;
	}

	if (Year % 400 == 0)
	{
		LeapYear = true;
	}

	return LeapYear;
}

// Sets all values in calender to 0 to overwrite junk values that might be in the array
// in slots where no day exists for a particular month, to avoid outputting them.
void ZeroCalender(int **CalenderInput)
{
	for (unsigned int i = 0; i < 6; i++)
	{
		for (unsigned int c = 0; c < 7; c++)
		{
			CalenderInput[i][c] = 0;
		}
	}
}


// Function for printing month. Takes in all the necessary pointers to arrays storing week and month name and length information.
// Also takes user input to specify which month/year it should output.
void PrintMonth(int Month, int Year, int** CalenderInput, string* MonthNameInput, int* MonthLengthInput, string*DayInput)
{

	ZeroCalender(CalenderInput);

	// This block determines all the day length, first day and total day information.
	// It then translates that information into the appropriate index information for
	// initializing the calender and printing it.
	int JanFirst = (((1) + (5) * ((Year - 1) % (4))) + ((4) * ((Year - 1) % (100))) + ((6) * ((Year - 1) % (400)))) % (7) + (1);
	int TotalDays = 0;
	int Day = 1;

	if (CheckForLeap(Year))
	{
		MonthLengthInput[1] = 29;
	}
	else if (!CheckForLeap(Year))
	{
		MonthLengthInput[1] = 28;
	}

	for (int i = 0; i < Month ; i++)
	{
		TotalDays += MonthLengthInput[i];
	}

	int FirstOfMonthIndex = JanFirst + (TotalDays % 7) - (1);
	int SecondIndex = 0;

	if (FirstOfMonthIndex >= 7)
	{
		FirstOfMonthIndex = FirstOfMonthIndex - 7;
		SecondIndex = 1;
	}


	// This block intializes the calender array using the information given
	// by the last block of code. I.e starts on correct day of given month and
	// ends on correct day.
	for (unsigned int r = 0; r < 6; r++)
	{
		for (unsigned int c = 0; c < 7; c++)
		{
			CalenderInput[r + SecondIndex][c + FirstOfMonthIndex] = Day;
			Day++;

			if (FirstOfMonthIndex + c >= 6)
			{
				FirstOfMonthIndex = 0;
				break;
			}


			if (Day > MonthLengthInput[Month])
			{
				break;
			}
		}

		if (Day > MonthLengthInput[Month])
		{
			break;
		}

		if (SecondIndex + r >= 5)
		{
			break;
		}
	}


	/*	// This block of code is for printing the calender and is entirely for format control.
	cout << " " << MonthNameInput[Month] << "  " << Year << endl;
	cout << endl;

	for (unsigned int i = 0; i < 7; i++)
	{
	cout << DayInput[i] << " ";
	}
	cout << endl;



	for (unsigned int i = 0; i < 6; i++)
	{
	for (unsigned int c = 0; c < 7; c++)
	{
	if (CalenderInput[i][c] == 0)
	{
	cout << "   ";
	}
	else
	{
	if (CalenderInput[i][c] < 10)
	{
	cout << " ";
	}

	cout << CalenderInput[i][c] << " ";
	}
	}
	cout << endl;
	}

	*/

}


// Function that prints a full calender year. Takes in all the necessary pointers to arrays to feed to the PrintMonth
// function and just loops through that 12 times, incrementing the month value input to PrintMonth by +1.
void PrintYear(int Year, int** CalenderInput, string* MonthNameInput, int* MonthLengthInput, string*DayInput)
{
	for (unsigned int i = 1; i <= 12; i++)
	{
		PrintMonth(i, Year, CalenderInput, MonthNameInput, MonthLengthInput, DayInput);
		cout << endl;
	}
}



// Creates an array of nodes that store data for each day in a given month. (Fills entire array with nodes but only days that exist for that month
// have their "date" variable initialized to a number. The rest are given 0. Days appearing in a given month determined by PrintMonth function).
Day_Node** Create_Month(int** InputCalenderArray, int Month, int Year, string* MonthNameInput, int* MonthLengthInput, string* DayInput)
{
	Day_Node** Actual_Month = new Day_Node*[6];

	for (unsigned int i = 0; i < 7; i++)
	{
		Actual_Month[i] = new Day_Node[7];
	}

	PrintMonth(Month, Year, InputCalenderArray, MonthNameInput, MonthLengthInput, DayInput);

	for (unsigned int i = 0; i < 6; i++)
	{
		for (unsigned int c = 0; c < 7; c++)
		{

			Actual_Month[i][c].Year = Year;
			Actual_Month[i][c].Month_Name = MonthNameInput[Month];

			if (InputCalenderArray[i][c] != 0)
			{
				Actual_Month[i][c].Date = InputCalenderArray[i][c];
			}
 			else if (InputCalenderArray[i][c] == 0)
			{
				Actual_Month[i][c].Date = 0;
			}

			if (c == 0)
			{
				Actual_Month[i][c].Day_Name = "Sunday";
			}
			else if (c == 1)
			{
				Actual_Month[i][c].Day_Name = "Monday";
			}
			else if (c == 2)
			{
				Actual_Month[i][c].Day_Name = "Tuesday";
			}
			else if (c == 3)
			{
				Actual_Month[i][c].Day_Name = "Wednesday";
			}
			else if (c == 4)
			{
				Actual_Month[i][c].Day_Name = "Thursday";
			}
			else if (c == 5)
			{
				Actual_Month[i][c].Day_Name = "Friday";
			}
			else if (c == 6)
			{
				Actual_Month[i][c].Day_Name = "Saturday";
			}
		}
	}


	return Actual_Month;

}

// Basically just loops through the create month function 12 times feeding in the appropriate info to initialize an entire year properly.
Day_Node*** Create_Year(int Year, int** InputCalender, string* MonthNameInput, int* MonthLengthInput, string* DayInput)
{
	Day_Node*** Actual_Year = new Day_Node**[12];

	for (int i = 0; i < 12; i++)
	{
		Actual_Year[i] = Create_Month(InputCalender, i, Year, MonthNameInput, MonthLengthInput, DayInput);
	}



	return Actual_Year;




}

Day_Node**** Create_Calender_Book(int Calender_Start_Year, int Calender_Year_Coverage, int** InputCalender, string* MonthNameInput, int* MonthLengthInput, string* DayInput)
{
	Day_Node**** Actual_Calender = new Day_Node***[Calender_Year_Coverage];

	for (unsigned int i = 0; i < Calender_Year_Coverage; i++)
	{
		Actual_Calender[i] = Create_Year(Calender_Start_Year, InputCalender, MonthNameInput, MonthLengthInput, DayInput);
		Calender_Start_Year++;
	}


	return Actual_Calender;

}

void Display_Actual_Month(Day_Node**** Calender_Book, string* DayInput, int CalenderStart)
{
	int Year;
	int Month;


	cout << "Input year: ";
	cin >> Year;
	cout << endl;
	cout << "Input month: ";
	cin >> Month;
	cout << endl;



	cout << "     " << Calender_Book[Year - CalenderStart][Month - 1][0][0].Month_Name << "  " << Calender_Book[Year - CalenderStart][Month - 1][0][0].Year << endl;
	cout << endl;


	for (unsigned int i = 0; i < 7; i++)
	{
		cout << DayInput[i] << " ";
	}
	cout << endl;
	cout << endl;



	for (unsigned int i = 0; i < 6; i++)
	{
		for (unsigned int c = 0; c < 7; c++)
		{
			if (Calender_Book[Year - CalenderStart][Month - 1][i][c].Date == 0)
			{
				cout << "   ";
			}
			else
			{
				if (Calender_Book[Year - CalenderStart][Month - 1][i][c].Date < 10)
				{
					cout << " ";
				}

				cout << Calender_Book[Year - CalenderStart][Month - 1][i][c].Date << " ";
			}
		}
		cout << endl;
	}
	cout << endl;


}


void Set_Day_Note(Day_Node**** InputCalender)
{
	int Year;
	int Month;
	int Day;
	int Note_Number;
	string Note = "c";

	int Calender_Year_Start = InputCalender[0][0][0][0].Year;

	cout << "Select year: ";
	cin >> Year;
	cout << endl;
	cout << "Select month: ";
	cin >> Month;
	cout << endl;
	cout << "Select day: ";
	cin >> Day;
	cout << endl;
	cout << "Select which note (1-5): ";
	cin >> Note_Number;
	cout << endl;


	cout << "Input note " << Note_Number << " for " << InputCalender[0][Month - 1][0][0].Month_Name << ", " << Day << ", " << InputCalender[Year - Calender_Year_Start][0][0][0].Year << ": ";
	// This tells the getline function to ignore the "\n" character that was left in the input buffer by the previous cin.
	cin.ignore();
	getline(cin, Note);
	cout << endl;

	for (int i = 0; i < 6; i++)
	{
		for (int c = 0; c < 7; c++)
		{
			if (InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Date == Day)
			{
				if (Note_Number == 1)
				{
					InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note1 = Note;
				}
				if (Note_Number == 2)
				{
					InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note2 = Note;
				}
				if (Note_Number == 3)
				{
					InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note3 = Note;
				}
				if (Note_Number == 4)
				{
					InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note4 = Note;
				}
				if (Note_Number == 5)
				{
					InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note1 = Note;
				}

			}
			else
			{
				continue;
			}
		}
	}



}


void Read_Day_Note(Day_Node**** InputCalender)
{
	int Year;
	int Month;
	int Day;
	int Note_Number;

	int Calender_Year_Start = InputCalender[0][0][0][0].Year;

	cout << "Select year: ";
	cin >> Year;
	cout << endl;
	cout << "Select month: ";
	cin >> Month;
	cout << endl;
	cout << "Select day: ";
	cin >> Day;
	cout << endl;
	cout << "Select note number (1-5): ";
	cin >> Note_Number;
	cout << endl;

	for (int i = 0; i < 6; i++)
	{
		for (int c = 0; c < 7; c++)
		{
			if (InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Date == Day)
			{
				if (Note_Number == 1)
				{
					cout << "Note: " << InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note1 << endl;
					cout << endl;
				}
				if (Note_Number == 2)
				{
					cout << "Note: " << InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note2 << endl;
					cout << endl;
				}
				if (Note_Number == 3)
				{
					cout << "Note: " << InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note3 << endl;
					cout << endl;
				}
				if (Note_Number == 4)
				{
					cout << "Note: " << InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note4 << endl;
					cout << endl;
				}
				if (Note_Number == 5)
				{
					cout << "Note: " << InputCalender[Year - Calender_Year_Start][Month - 1][i][c].Note5 << endl;
					cout << endl;
				}
			}
			else
			{
				continue;
			}
		}
	}



}


// Saves current active calender into a text file in custom format
void Save_Calender(Day_Node**** Input_Calender, int Calender_Length_Years, int Calender_Start_Year)
{

	string Calender_File_Name;
	cout << endl;
	cout << "Save as: ";
	cin >> Calender_File_Name;
	cout << endl;

	cout << "Saving calender..." << endl;

	ofstream SaveFile;
	SaveFile.open(Calender_File_Name + ".txt");

	if (SaveFile.is_open())
	{
		SaveFile << Calender_Length_Years << endl;
		SaveFile << Calender_Start_Year << endl;

		for (unsigned int i = 0; i < Calender_Length_Years; i++)
		{
			for (unsigned int c = 0; c < 12; c++)
			{
				for (unsigned int a = 0; a < 6; a++)
				{
					for (unsigned int b = 0; b < 7; b++)
					{
						for (unsigned int z = 1; z < 6; z++)
						{
							if (z == 1)
							{
								SaveFile << Input_Calender[i][c][a][b].Note1 << endl;
							}
							else if (z == 2)
							{
								SaveFile << Input_Calender[i][c][a][b].Note2 << endl;
							}
							else if (z == 3)
							{
								SaveFile << Input_Calender[i][c][a][b].Note3 << endl;
							}
							else if (z == 4)
							{
								SaveFile << Input_Calender[i][c][a][b].Note4 << endl;
							}
							else if (z == 5)
							{
								SaveFile << Input_Calender[i][c][a][b].Note5 << endl;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		cout << "Unable to create file for saving..." << endl;
		cout << endl;
	}

	SaveFile.close();
	cout << "Calender saved." << endl;
	cout << endl;
}


Calender_Load_Package Load_Calender(int** InputCalender, string* MonthNameInput, int* MonthLengthInput, string* DayInput)
{

	Calender_Load_Package Output_Package;

	int Start;
	int Length;
	string Temp_Text;

	string File_Load_Name;
	cout << "Input calender filename to load: ";
	cin >> File_Load_Name;
	cout << endl;
	File_Load_Name = File_Load_Name + ".txt";

	ifstream Load_File;
	Load_File.open(File_Load_Name);

	if (Load_File.is_open())
	{
		cout << "Loading calender..." << endl;

		Load_File >> Temp_Text;
		Length = stoi(Temp_Text);
		Load_File >> Temp_Text;
		Start = stoi(Temp_Text);

		Output_Package.Calender_Pointer = Create_Calender_Book(Start, Length, InputCalender, MonthNameInput, MonthLengthInput, DayInput);
		Output_Package.Length = Length;
		Output_Package.Start = Start;

		string Test;
		Load_File >> Test;





		for (unsigned int i = 0; i < Output_Package.Length; i++)
		{
			for (unsigned int c = 0; c < 12; c++)
			{
				for (unsigned int z = 0; z < 6; z++)
				{
					for (unsigned int x = 0; x < 7; x++)
					{
						for (unsigned int r = 0; r < 5; r++)
						{
							if (r == 0)
							{
								getline(Load_File, Temp_Text);
								Output_Package.Calender_Pointer[i][c][z][x].Note1 = Temp_Text;
							}
							else if (r == 1)
							{
								getline(Load_File, Temp_Text);
								Output_Package.Calender_Pointer[i][c][z][x].Note2 = Temp_Text;
							}
							else if (r == 2)
							{
								getline(Load_File, Temp_Text);
								Output_Package.Calender_Pointer[i][c][z][x].Note3 = Temp_Text;
							}
							else if (r == 3)
							{
								getline(Load_File, Temp_Text);
								Output_Package.Calender_Pointer[i][c][z][x].Note4 = Temp_Text;
							}
							else if (r == 4)
							{
								getline(Load_File, Temp_Text);
								Output_Package.Calender_Pointer[i][c][z][x].Note5 = Temp_Text;
							}
						}
					}
				}
			}
		}



		cout << "Calender loaded!" << endl;
		cout << endl;
		return Output_Package;
	}
	else
	{
		cout << "There was a problem loading the file!" << endl;
		cout << endl;
		Output_Package.Calender_Pointer = 0;
		return Output_Package;
	}

}



int Display_Menu_Picture1()
{

	int Menu_Selection;




	cout << "  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =   " << endl;
	cout << "  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =   " << endl;
	cout << "||                          Calender Menu                        || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                      [1] to display month                     || " << endl;
	cout << "||                      [2] to set day note                      || " << endl;
	cout << "||                      [3] to read day note                     || " << endl;
	cout << "||                      [4] to save calender                     || " << endl;
	cout << "||                      [8] to EXIT to main menu                 || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =   " << endl;
	cout << "   = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =    " << endl;
	cout << "                       Input Selection: ";
	cin >> Menu_Selection;
	cout << endl;

	return Menu_Selection;
}



int Display_Menu_Picture2()
{

	int OuterMenu;



	cout << "  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =   " << endl;
	cout << "  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =   " << endl;
	cout << "||                          MAIN MENU                            || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                   [1] create new calender                     || " << endl;
	cout << "||                   [2] load calender                           || " << endl;
	cout << "||                   [3] to exit program                         || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "||                                                               || " << endl;
	cout << "  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =   " << endl;
	cout << "   = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =    " << endl;
	cout << "                       Input Selection: ";
	cin >> OuterMenu;
	cout << endl;



	return OuterMenu;
}


void Calender_Memory_Cleanup(Day_Node**** Calender_To_Be_Deleted, int Calender_Year_Size)
{
	cout << "Cleaning calender memory..." << endl;

	for (int a = 0; a < Calender_Year_Size; a++)
	{
		for (int b = 0; b < 12; b++)
		{
			for (int c = 0; c < 6; c++)
			{
				delete[] Calender_To_Be_Deleted[a][b][c];
			}
		}
	}

	for (int a = 0; a < Calender_Year_Size; a++)
	{
		for (int b = 0; b < 12; b++)
		{
			delete[] Calender_To_Be_Deleted[a][b];
		}
	}


	



	cout << "Calender deleted!" << endl;
}









int main()
{
	// Creates pointers and initializes them to arrays of various types and sizes to store
	// relevant information. IMPORTANT. DO NOT DELETE. WILL BREAK EVERYTHING.
	int *MonthLengths = new int[12];
	string *MonthNames = new string[12];
	string *DayNames = new string[7];

	// This calender array is constantly passed around among functions like a cheap whore. Don't edit it.
	int **Calender = new int*[6];

	for (unsigned int i = 0; i < 7; i++)
	{
		Calender[i] = new int[7];
	}

	// Initializes arrays to contain all necessary information using SetCalender function.
	// ALSO IMPORTANT. DO NOT DELETE.
	SetCalender(DayNames, MonthNames, MonthLengths);

	Day_Node**** Created_Calender;



	// Where heap corruption test code begins

	int Length = 1;
	int Start = 2010;


	Day_Node** Test = Create_Month(Calender, 1, 2010, MonthNames, MonthLengths, DayNames);


	Day_Node*** Test2 = Create_Year(2010, Calender, MonthNames, MonthLengths, DayNames);

	for (int a = 0; a < 12; a++)
	{
		for (int b = 0; b < 6; b++)
		{
			delete[] Test2[a][b];
			cout << "Month " << a << " day nodes deleted" << endl;
		}
	}


	for (int a = 0; a < 12; a++)
	{
		delete[] Test2[a];
	}

	

	// Where heap corruption test code ends



/*	bool Primary_Menu_Exit = false;
	bool Outer_Menu_Exit = false;

	while (true)
	{



		int OuterMenu = Display_Menu_Picture2();





		if (OuterMenu == 1)
		{

			int Start;
			int Length;

			cout << "Input calender start year: ";
			cin >> Start;
			cout << endl;
			cout << "Input calender year coverage: ";
			cin >> Length;
			cout << endl;


			cout << "Creating calender..." << endl;

			Created_Calender = Create_Calender_Book(Start, Length, Calender, MonthNames, MonthLengths, DayNames);
			cout << "Calender created." << endl;
			cout << endl;



			while (true)
			{


				int Menu_Selection = Display_Menu_Picture1();




				if (Menu_Selection == 1)
				{
					Display_Actual_Month(Created_Calender, DayNames, Start);
				}
				else if (Menu_Selection == 2)
				{
					Set_Day_Note(Created_Calender);
				}
				else if (Menu_Selection == 3)
				{
					Read_Day_Note(Created_Calender);
				}
				else if (Menu_Selection == 4)
				{
					Save_Calender(Created_Calender, Length, Start);
				}
				else if (Menu_Selection == 8)
				{
					Calender_Memory_Cleanup(Created_Calender, Length);
					cout << endl;
					break;
				}
				else
				{
					cout << "Invalid selection, please try again!" << endl << endl;
				}
			}
		}
		else if (OuterMenu == 2)
		{
			Calender_Load_Package Loaded_Calender_Package = Load_Calender(Calender, MonthNames, MonthLengths, DayNames);
			Created_Calender = Loaded_Calender_Package.Calender_Pointer;

			while (true)
			{

				if (Created_Calender == 0)
				{
					break;
				}


				int Menu_Selection = Display_Menu_Picture1();




				if (Menu_Selection == 1)
				{
					Display_Actual_Month(Created_Calender, DayNames, Loaded_Calender_Package.Start);
				}
				else if (Menu_Selection == 2)
				{
					Set_Day_Note(Created_Calender);
				}
				else if (Menu_Selection == 3)
				{
					Read_Day_Note(Created_Calender);
				}
				else if (Menu_Selection == 4)
				{
					Save_Calender(Created_Calender, Loaded_Calender_Package.Length, Loaded_Calender_Package.Start);
				}
				else if (Menu_Selection == 8)
				{
					Calender_Memory_Cleanup(Created_Calender, Loaded_Calender_Package.Length);
					cout << endl;
					break;
				}
				else
				{
					cout << "Invalid selection, please try again!" << endl << endl;
				}
			}
		}
		else if (OuterMenu == 3)
		{
			break;
		}
		else
		{
			cout << "Invalid selection, please try again!" << endl << endl;
		}

	}

	cout << "Goodbye!" << endl;
	cout << endl;




*/


	return 0;
}
