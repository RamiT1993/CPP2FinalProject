//Program Name: Hangman
//Group Number: 5
//Group Leader: Rami Toma
//Group Members: Hussein Alanbari, Tajwar Rahman



#include <iostream>
#include <vector>
#include <map>
#include <cctype>
#include <fstream> //needed for input/output of data
#include <string>
#include <iomanip> //Format Editor
#include <random>
#include <crtdbg.h> //memory management
#include "json.hpp"


using namespace std; //getting rid of annoying std - rami

//We all started fixing others codes because of the amount of bugs in each other code. Like mine had an issue with the linked list, hussein had an issue where it was exiting early, tajwar had issues implementing the composition.
//We didn't have enough time so everyone was helping each other with their work.

/*also when you sort allow the user to sort based on length or alphabetical nature*/


//Base Class or derived class will have others work on it to include searching/sorting operations






//Rami-T Creation of the linked list template class to operate the dynamically allocated data and use it for some calculations and outputting.

//Struct To Hold the linked list data, To be used in template class - Rami
struct LinkedListData 
{
	string WordName = "";
	bool SuccessfullyGuessed = false;
	LinkedListData* next = nullptr;
};

//Creating a linked list.
template <typename T>
class LinkedList
{
	private:


		T* TLinkedListPtr = nullptr; //Must be unchanged because its a pointer to its initial spot
		void DeleteRecursive(T* LinkedPtrOriginStart) //Recursive Delete that starts at the first pointer of origin start and recursively enters until a nullptr that doesn't exist enter; - Rami
		{
			//Classic Primitive Looping through and deleting the recursive list
			T* LinkedNext;
			if (LinkedPtrOriginStart != nullptr)
			{
				if (LinkedPtrOriginStart->next != nullptr)
				{
					LinkedNext = LinkedPtrOriginStart->next;
					delete LinkedPtrOriginStart;
					LinkedPtrOriginStart = nullptr;
					DeleteRecursive(LinkedNext);
				}
				else
				{
					delete LinkedPtrOriginStart;
					LinkedPtrOriginStart = nullptr;
				}
			}


		}

	public:
		//This push template class operation, will push into the linked list if you have guessed it correctly or not
		void lListPush(string Word, bool Guessed)
		{
			
			//If empty by default create a new spot in memory from the beginning
			if (TLinkedListPtr == nullptr)
			{
				//cout << "hi" << endl;
				TLinkedListPtr = new T;
				TLinkedListPtr->WordName = Word;
				
				TLinkedListPtr->SuccessfullyGuessed = Guessed;

				//Return();
			}
			//Else sets the temporary ptr of TLinkedListPtr and inserted it at the next location
			else
			{
				//cout << "byue" << endl;
				T* TempSearcher = TLinkedListPtr;
				while (TempSearcher->next != nullptr)
				{
					TempSearcher = TempSearcher->next;

				}

				if (TempSearcher->next == nullptr)
				{
					TempSearcher->next = new T;
					TempSearcher = TempSearcher->next;
					TempSearcher->WordName = Word;
					//cout << TLinkedListPtr->WordName << endl;
					TempSearcher->SuccessfullyGuessed = Guessed;
					//Return();
					//cout << TempSearcher->WordName << endl;
				}
			}
		}

		//Searches through the list to see the amount of times won.
		int ReturnTimesWon() const
		{
			int Count = 0;
			T* TempSearcher = TLinkedListPtr;

			if (TempSearcher != nullptr)
			{
				//makes sure if their are multiple or only 1 in the list it outputs the correct count
				if (TempSearcher->next != nullptr)
				{
					while (TempSearcher->next != nullptr)
					{
						if (TempSearcher->SuccessfullyGuessed == true)
							Count++;

						TempSearcher = TempSearcher->next;

						if (TempSearcher->next == nullptr) //Increments only if the next spot is equal to null ptr and if its true
							if (TempSearcher->SuccessfullyGuessed == true)
								Count++;
					}

				}
				else if (TempSearcher != nullptr && TempSearcher->next == nullptr) //used to make sure theirs only 1 object from the beginning.
				{

					if (TempSearcher->SuccessfullyGuessed == true)
						Count++;
				}
			}



			return Count;
		}

		//Searches through the list to see the amount of times won.
		int ReturnTimesLost() const
		{
			int Count = 0;
			T* TempSearcher = TLinkedListPtr;

			if (TempSearcher != nullptr)
			{
				//makes sure if their are multiple or only 1 in the list it outputs the correct count
				if (TempSearcher->next != nullptr)
				{
					while (TempSearcher->next != nullptr)
					{
						if (TempSearcher->SuccessfullyGuessed == false)
							Count++;

						TempSearcher = TempSearcher->next;

						if (TempSearcher->next == nullptr) //Increments only if the next spot is equal to null ptr and if its true
							if (TempSearcher->SuccessfullyGuessed == false)
								Count++;
					}

				}
				else if (TempSearcher != nullptr && TempSearcher->next == nullptr) //used to make sure theirs only 1 object from the beginning.
				{

					if (TempSearcher->SuccessfullyGuessed == false)
						Count++;
				}

			}


			return Count;
		}

		//Going through the return
		//void Return()
		//{
		//	T* Temp = TLinkedListPtr;

		//	while (Temp->next != nullptr)
		//	{
		//		cout << Temp->WordName << endl;
		//	}
		//	
		//}

		//Output Data To File, Done Before Deletion Automatically.
		ostream& OutputToFile(ostream& OutputToFile)
		{
			T* TempSearcher = this->TLinkedListPtr;

			OutputToFile << "Word Guessed : Guessed Successfully" << endl;


			if (TempSearcher != nullptr)
			{
				//makes sure if their are multiple or only 1 in the list it outputs the correct count
				if (TempSearcher->next != nullptr)
				{
					while (TempSearcher->next != nullptr)
					{

						string Output = TempSearcher->SuccessfullyGuessed == true ? "Yes" : "No";


						OutputToFile << TempSearcher->WordName << setw(15 - TempSearcher->WordName.size()) << setfill(' ') << "" << Output << setw(1) << "" << endl;
						TempSearcher = TempSearcher->next;

						if (TempSearcher->next == nullptr)
						{

							string Output = TempSearcher->SuccessfullyGuessed == true ? "Yes" : "No";


							OutputToFile << TempSearcher->WordName << setw(15 - TempSearcher->WordName.size()) << setfill(' ') << "" << Output << setw(1) << "" << endl;
						}

					}

				}
				else if (TempSearcher != nullptr && TempSearcher->next == nullptr) //used to make sure theirs only 1 object from the beginning.
				{

					string Output = TempSearcher->SuccessfullyGuessed == true ? "Yes" : "No";


					OutputToFile << TempSearcher->WordName << setw(15 - TempSearcher->WordName.size()) << setfill(' ') << "" << Output << setw(1) << "" << endl;

				}
			}




			return OutputToFile;
		}

		virtual ~LinkedList()
		{
			DeleteRecursive(this->TLinkedListPtr);
		};


};


//This base class Purpose is to load the data from the json file located inside of the rootfolder - Rami
class HangManBase
{
	//Overloader operator makes it easier to output to the console
	friend ostream& operator<<(ostream& OutputToConsole, HangManBase& ClassReferenceBase) //overloaded operator that returns only times won/lost
	{
		ClassReferenceBase.OutputToFile();
		string ConsoleOutput = "You have won " + to_string(ClassReferenceBase.LinkedListTemplateCall.ReturnTimesWon()) + " times and lost " + to_string(ClassReferenceBase.LinkedListTemplateCall.ReturnTimesLost()) + " times!";
		OutputToConsole << ConsoleOutput << endl;
		

		return OutputToConsole;
	}


	private:
		// basic Output with no file selected
		virtual void OutputToFile() //This Outputs to the file when everything is done.
		{


			string OutputLocation = "";

			cout << "Please Input File Name To Store This As: ";
			cin >> OutputLocation;

			OutputLocation += ".txt";


			ofstream OutputFile;
			OutputFile.open(OutputLocation);

			LinkedListTemplateCall.OutputToFile(OutputFile);

		};


		 

		

	public:

		LinkedList<LinkedListData> LinkedListTemplateCall; //Template Call for linkedList
		

		//Operation Section
		vector<string> HoldWords; //Rami - Holding the words to be used in the Hangman Game


		void StoringOfData(vector<string>& DataStorer, string JsonKey) //Rami - Operation to store the data, this opens the file and stores the data.
		{
			const string HoldFolderLocationplusfile = "Words.json"; //input file location - Rami
			ifstream WordsDataFile; //using if because it will only input the file and not write over it;

			WordsDataFile.open(HoldFolderLocationplusfile); //Opening the file

			//Using nlohmann json library as done previously because I will not loop through it if theirs already a previously done library.
			nlohmann::json JsonDataInfoHolder;
			WordsDataFile >> JsonDataInfoHolder; // Outputting infomation in file to Json as the library will handle the whole outputting of data - Rami 

			WordsDataFile.close(); //Closing Words Data File As I don't Need to mess with it anymore.


			//cout << JsonDataInfoHolder["Words"][2]; //Checking words if inputted correctly

			const size_t JSONTOTALSIZE = JsonDataInfoHolder[JsonKey].size(); //Keeps the size of the jsonData inside a const to be used later, unchanged

			for (size_t StartingPushingIntoVector = 0; StartingPushingIntoVector < JSONTOTALSIZE; StartingPushingIntoVector++)
			{
				DataStorer.push_back(JsonDataInfoHolder[JsonKey][StartingPushingIntoVector]);
				//cout << StartingPushingIntoVector << endl;
			}
			

			//for (auto& WordChecker : DataStorer)
			//{
			//	cout << WordChecker << endl;
			//}
		}


		//Constructor - When called it activates the loading of data from json file to the vector - Rami T
		HangManBase()
		{
			StoringOfData(this->HoldWords, "Words");
			//LinkedListTemplateCall.lListPush("hi", false);

			//LinkedListTemplateCall.lListPush("hiaaa", true);

			//LinkedListTemplateCall.lListPush("hiaaaaa", true);

			//LinkedListTemplateCall.lListPush("hiffff", true);

			//LinkedListTemplateCall.lListPush("hi", false);

			//LinkedListTemplateCall.lListPush("hiaaaaaaaa", true);

			//LinkedListTemplateCall.lListPush("hissss", false);

			//LinkedListTemplateCall.lListPush("hidddd", true);

			//cout << LinkedListTemplateCall.ReturnTimesLost();
			

			
		}
		


		virtual ~HangManBase() // This is the last thing that should be destroyed i.e. when the game ends -Rami
		{
			//OutputToFile();
			//cout << "hi" << endl;
		};




		//ALL the methods need to handled in the aggregation class, it shouldn't be in the base class
		// 
		//// Methods for sorting words using WordManager - Tajwar R
		//    void sortWordsAlphabetically() {
		//        wordManager.sortWordsAlphabetically(holdWords);
		//    }
		//
		//    void sortWordsByLength() {
		//        wordManager.sortWordsByLength(holdWords);
		//    }
		//
		//    // Aggregation methods using WordManager
		//    size_t countWords() const {
		//        return wordManager.countWords(holdWords);
		//    }
		
		    //size_t countUniqueWords() const {
		    //    return wordManager.countUniqueWords(holdWords);
		    //}

		
};


//As agreed upon between hussein and rami, we will edit the hangman game to include operator ++ (prefix)
class HangManGame : public HangManBase {


	//virtual function that overloads from its previous version, Hussein and Rami Fixed This Code Together
	friend ostream& operator<<(ostream& OutputToConsole, HangManGame& ClassReferenceBase)  //overloaded operator that returns only times won/lost
	{
		//cout << ClassReferenceBase.LinkedListTemplateCall.ReturnTimesWon() + ClassReferenceBase.LinkedListTemplateCall.ReturnTimesLost();

		ClassReferenceBase.OutputToFile();
		int Denom = ClassReferenceBase.LinkedListTemplateCall.ReturnTimesWon() + ClassReferenceBase.LinkedListTemplateCall.ReturnTimesLost();
		double Average = 0;
		if (Denom == 0 && ClassReferenceBase.LinkedListTemplateCall.ReturnTimesWon() <= 0) {
			Average = 0;
		}	
		else {
			Average = static_cast<double>(ClassReferenceBase.LinkedListTemplateCall.ReturnTimesWon()) / static_cast<double>(Denom);
		}
		//cout << 0 / 1 << endl;
		//double Average = ClassReferenceBase.LinkedListTemplateCall.ReturnTimesWon() / (ClassReferenceBase.LinkedListTemplateCall.ReturnTimesWon() + ClassReferenceBase.LinkedListTemplateCall.ReturnTimesLost());
		
		string ConsoleOutput = "You have won " + to_string(ClassReferenceBase.LinkedListTemplateCall.ReturnTimesWon()) + " times and lost " + to_string(ClassReferenceBase.LinkedListTemplateCall.ReturnTimesLost()) + " times!\n" + "Average Win Rate is: ";

		OutputToConsole << ConsoleOutput;
		OutputToConsole << fixed << setprecision(2) << Average << "%" << endl;


		return OutputToConsole;
	}



private:
	string secretWord;
	string guessedWord;
	int maxAttempts;
	bool DifficultyOnHard = false;
	bool DifficultyAlreadyChosen = false;
	int remainingAttempts;
	vector<string> HangManASCII;
	vector<string> guessedLetters;


	void OutputToFile() 
	{
		const string OutputLocation = "GameResult.txt";

		ofstream OutputFile;
		OutputFile.open(OutputLocation);

		LinkedListTemplateCall.OutputToFile(OutputFile);
	}

	bool isLetterGuessed(string letter) const {
		return find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end();
	}

	bool isGameWon() const {
		return secretWord == guessedWord;
	}

	bool isGameOver() const {
		return remainingAttempts <= 0 || isGameWon();
	}

	void printHangman(int incorrectGuesses) {
		// Print Hangman ASCII art based on number of incorrect guesses
		StoringOfData(HangManASCII, "HangMan_ASCII");
		cout << HangManASCII[incorrectGuesses] << endl;
	}

	void initializeGame() {
		srand(static_cast<unsigned int>(time(nullptr)));
		int randomIndex = rand() % HoldWords.size();

		if (DifficultyOnHard == true)
		{
			//Setting Up HardMode Here

			while (HoldWords[randomIndex].size() <= 5) {

				randomIndex = rand() % HoldWords.size();
			}
			maxAttempts = 3;
		}
		else
		{
			maxAttempts = 6;
		}

		secretWord = HoldWords[randomIndex];
		guessedWord = string(secretWord.length(), '_');
		//maxAttempts = 6; // Adjust as needed
		remainingAttempts = maxAttempts;
		guessedLetters.clear();
	}

	void DifficultySetting() {

		if (DifficultyAlreadyChosen == false)
		{
			char DiffChosen;
			cout << "Choose 'e' for easy difficulty or 'h' for hard difficulty (Can Only Be Changed On Game START):";
			cin >> DiffChosen;

			if (DiffChosen != 'e' && DiffChosen != 'h'){

				cout << "Wrong Input Selected. Setting It To Default Difficulty" << endl;
				DiffChosen = 'e';
				cin.clear();
				cin.ignore(1000);
				DifficultyOnHard = false;
			}
			else 
			{
				if (DiffChosen == 'e') {
					cout << "Easy Mode Selected" << endl;
					DifficultyOnHard = false;
				}
				else if (DiffChosen == 'h') {
					cout << "Hard Mode Selected" << endl;
					DifficultyOnHard = true;
				}
			}





			DifficultyAlreadyChosen = true;
		}
	}

	void playGame() {
		
		string guess;

		cout << "Welcome to Hangman!\n";
		//Main game loop
		while (!isGameOver()) {
			printHangman(maxAttempts - remainingAttempts);

			cout << "Secret Word: " << guessedWord << endl;
			cout << "Remaining Attempts: " << remainingAttempts << endl;

			cout << "Guessed Letters/Words: ";
			for (string letter : guessedLetters) {
				cout << letter << " ";
			}
			cout << endl;
			cout << "Enter a letter guess: ";
			cin >> guess;



			// Convert to lowercase for consistency
			for (auto& letter : guess) {
				letter = tolower(letter);
			}


			if (isLetterGuessed(guess)) {
				cout << "You've already guessed that letter!" << endl;
				continue;
			}

			//Check if player guess the whole word or one letter only
			if (guess.length() != secretWord.length() && guess.length() != 1)
			{
				cout << "Please enter one letter or guess the whole word" << endl;
				cin.clear();
				continue;
			}
			else if (guess == secretWord) //Check if player guessed the whole word correctly
			{
				guessedWord = guess; // changes the guessed word to the players guess in order to set the winning conditions
			}

			guessedLetters.push_back(guess); 
			//Updates guessed word 
			if (secretWord.find(guess) != string::npos) {
				cout << "Correct guess!" << endl;
				for (int i = 0; i < secretWord.length(); ++i) {
					if (secretWord[i] == guess[0]) {
						guessedWord[i] = guess[0];
					}
				}
			}
			else {
				cout << "Incorrect guess!" << endl;
				--remainingAttempts;
			}
		}
		if (isGameWon() ) {
			cout << "Congratulations! You've guessed the word: " << secretWord << endl;
			LinkedListTemplateCall.lListPush(secretWord, true);
			//LinkedListTemplateCall.Return();
		}
		else {
			cout << "\nYou've run out of attempts. The secret word was: " << secretWord << endl;
			LinkedListTemplateCall.lListPush(secretWord, false);
			//cout << LinkedListTemplateCall.ReturnTimesLost();
			//LinkedListTemplateCall.Return();
		}
	}

public:

	//Purpose of this operator++ prefix overloader is to initialize the game and then play it without accessing the member functions directly.
	void operator++(){

		DifficultySetting();
		initializeGame();
		playGame();

	}


	virtual ~HangManGame(){

		//initializeGame(); removed because called in main
	}
};










//We agreed upon this is how WordManager Should look like.
// WordManager class that will handle the sorting of words by length and alphabetical order - Tajwar R
//A Couple of issues that Hussein/Tajwar fixed the code so it could be run successfully
class WordManager {
public:
	HangManGame* PtrGameHold = nullptr;
	WordManager(HangManGame& obj)
	{
		PtrGameHold = &obj;
	};

	// Displays the words in the HoldWords vector and iterates through the words using a normal for loop with a vector iterator and then prints each word.
	void DisplayWords()
	{
	    const int COLUMN_SIZE = 3; // Display three words per row
	    int counter = 0;
	    // Use a normal for loop with a vector iterator
	    for (vector<string>::iterator it = PtrGameHold->HoldWords.begin(); it != PtrGameHold->HoldWords.end(); ++it)
	    {
	        // Print the current word
	        cout << left << setw(15) << *it << "\t";
	        counter++;
	        // Print a newline every three words
	        if (counter % COLUMN_SIZE == 0)
	        {
	            cout << endl;
	        }
	    }
	    // Add a newline at the end if necessary
	    if (counter % COLUMN_SIZE != 0)
	    {
	        cout << endl;
	    }
	}

	// Sorts the words vector alphabetically
	void sortWordsAlphabetically() {
		sort(PtrGameHold->HoldWords.begin(), PtrGameHold->HoldWords.end());
		DisplayWords();
		//DisplayWords(words);
	}

	// Sorts the words vector by word length, change the magic numbers/letters - rami t
	void sortWordsByLength() {
		sort(PtrGameHold->HoldWords.begin(), PtrGameHold->HoldWords.end(), [](const string& a, const string& b) {
			return a.length() < b.length();
			});
		DisplayWords();
		//DisplayWords(words);

	}

	// Returns the total number of words in the vector
	size_t countWords() const {
		return PtrGameHold->HoldWords.size();
	}

};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Memory Management
	const string HoldWelcome = "Welcome to the Hangman Game";
	string WantToPlay = "Do you want to play the game? p-play, v-sort/display words, or q-quit: ";
	char PlayChecker = 'w'; 
	bool OnlySortOnce = false; //Only sorts the game once
	
	bool PlayedOnce = false; //Playing the game once allows you to output;
	
	cout << setw(50) << setfill('*')  << "" << endl;
	cout << setw((50 - HoldWelcome.size())/2) << "" << HoldWelcome << setw((50 - HoldWelcome.size()) / 2) << "" << endl;
	cout << setw(50) << setfill('*') << "" << endl;
	cout << setw(0) << setfill(' ') << "";
	

	//So it doesn't exit early
	HangManGame game;

	while (PlayChecker != 'q')
	{
		string ErrorCode;

		cout << WantToPlay;
		cin >> PlayChecker;

		PlayChecker = tolower(PlayChecker); //Changing user input to lower case for consistency

		//Checks for valid input
		try
		{
			if (PlayChecker != 'p' && PlayChecker != 'q' && PlayChecker != 'v' && OnlySortOnce == false)
			{
				throw exception("Wrong Input: Exiting by default");
			}
			else if (PlayChecker != 'p' && PlayChecker != 'q' && OnlySortOnce == true)
			{
				throw logic_error("Replaying Game");
			}

		}
		catch (logic_error e)
		{
			cout << e.what() << endl;
			PlayChecker = 'p';
		}
		catch (exception e)
		{
			//making sure in the beginning program exit if incorrect but after the first time it just replays the game - rami
			cout << e.what() << endl;

			PlayChecker = 'q';
			
				
			//else if (ErrorChecker == "Replaying Game")
			//	PlayChecker = 'p';
			cin.ignore(100, '\n');
			cin.clear();

			cout << PlayChecker << endl;
		}

		//This Activates only once
		if (OnlySortOnce == false && PlayChecker == 'v')
		{
			char SortingOfWords = 0;

			cout << "How would you like to sort the words? a(alphabetical), l(length), or unsorted(u):";
			cin >> SortingOfWords;

			try
			{
				if (SortingOfWords != 'a' && SortingOfWords != 'l' && SortingOfWords != 'u')
				{
					throw exception("Incorrect Entry Inputted, Keeping Words Unsorted");
				}
			}
			catch (exception e)
			{
				cout << e.what() << endl;;
				SortingOfWords = 'u';

			}

			//Done to constantly deallocate the aggregate - rami t
			{
				WordManager SorterSystem(game);
				switch (SortingOfWords)
				{
				case 'a':

					SorterSystem.sortWordsAlphabetically();
					OnlySortOnce = true;
					PlayChecker = 'p';
					break;
				case 'l':
					OnlySortOnce = true;

					SorterSystem.sortWordsByLength();
					PlayChecker = 'p';
					break;
				case 'u': //keeps it unsorted
				default:
					OnlySortOnce = true;
					PlayChecker = 'p';
					break;
				}
			}
		}
		else if (OnlySortOnce == true && PlayChecker == 'v')
		{
			cout << "You can only view word list once per session!\n";
		}
		else if (PlayChecker == 'p')
		{
			++game; //Operator overload ++ prefix to play the game
			WantToPlay = "Do you want to play the game? p for yes or q for quitting program  : ";
			
		}
		else if (PlayChecker == 'q')
		{
			cout << game;
		}
	}



}





//Final Portion, thinking about having a class call all these stuff, and we just use the constructor and call the class constructor;
