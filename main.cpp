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



/*also when you sort allow the user to sort based on length or alphabetical nature*/


//Base Class or derived class will have others work on it to include searching/sorting operations



//Rami Portion Start


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
				
				TLinkedListPtr = new T;
				TLinkedListPtr->WordName = Word;
				
				TLinkedListPtr->SuccessfullyGuessed = Guessed;

				//TLinkedListPtr->WordName;
			}
			//Else sets the temporary ptr of TLinkedListPtr and inserted it at the next location
			else
			{
				
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
	
	friend ostream& operator<<(ostream& OutputToConsole, const HangManBase& ClassReferenceBase) //overloaded operator that returns only times won/lost
	{

		string ConsoleOutput = "You have won " + to_string(ClassReferenceBase.LinkedListTemplateCall.ReturnTimesWon()) + " times and lost " + to_string(ClassReferenceBase.LinkedListTemplateCall.ReturnTimesLost()) + " times!";
		OutputToConsole << ConsoleOutput << endl;
		

		return OutputToConsole;
	}

	private:
		void OutputToFile() //This Outputs to the file when everything is done.
		{
			const string OutputLocation = "OutputData\\GameResult.txt";

			ofstream OutputFile;
			OutputFile.open(OutputLocation);

			LinkedListTemplateCall.OutputToFile(OutputFile);
		};

	protected:
		
		


		virtual ostream& OutputToConsole(ostream& Output) //Output to the overloaded ostream operator that outputs not just to the console but to the output file as well.
		{
			return Output;
		}

		 

		

	public:

		LinkedList<LinkedListData> LinkedListTemplateCall; //Template Call for linkedList
		//overloaded == operator

		//Operation Section
		vector<string> HoldWords; //Rami - Holding the words to be used in the Hangman Game
		

		void StoringOfData(vector<string>& DataStorer) //Rami - Operation to store the data, this opens the file and stores the data.
		{
			const string HoldFolderLocationplusfile = "InputData\\Words.json"; //input file location - Rami
			

			ifstream WordsDataFile; //using if because it will only input the file and not write over it;

			WordsDataFile.open(HoldFolderLocationplusfile); //Opening the file

			//Using nlohmann json library as done previously because I will not loop through it if theirs already a previously done library.
			nlohmann::json JsonDataInfoHolder;
			WordsDataFile >> JsonDataInfoHolder; // Outputting infomation in file to Json as the library will handle the whole outputting of data - Rami 

			WordsDataFile.close(); //Closing Words Data File As I don't Need to mess with it anymore.


			//cout << JsonDataInfoHolder["Words"][2]; //Checking words if inputted correctly

			const size_t JSONTOTALSIZE = JsonDataInfoHolder["Words"].size(); //Keeps the size of the jsonData inside a const to be used later, unchanged

			for (size_t StartingPushingIntoVector = 0; StartingPushingIntoVector < JSONTOTALSIZE; StartingPushingIntoVector++)
			{
				DataStorer.push_back(JsonDataInfoHolder["Words"][StartingPushingIntoVector]);
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
			StoringOfData(this->HoldWords);
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
			OutputToFile();
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


//Rami Portion End

//This should be location after the derived/base class - rami t
// WordManager class that will handle the sorting of words by length and alphabetical order - Tajwar R
class WordManager {
public:
	// Sorts the words vector alphabetically
	void sortWordsAlphabetically(vector<string>& words) {
		sort(words.begin(), words.end());
	}

	// Sorts the words vector by word length
	void sortWordsByLength(vector<string>& words) {
		sort(words.begin(), words.end(), [](const string& a, const string& b) {
			return a.length() < b.length();
			});
	}

	// Returns the total number of words in the vector
	size_t countWords(const vector<string>& words) const {
		return words.size();
	}


	//Don't need this because all of them are unique because this is hangman - rami t
	//// Returns the number of unique words in the vector
	//size_t countUniqueWords(const vector<string>& words) const {
	//    set<string> uniqueWords(words.begin(), words.end());
	//    return uniqueWords.size();
	//}
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Memory Management
	const string HoldWelcome = "Welcome to the Hangman Game";
	const string WantToPlayInitial = "Do you want to play the game? p for yes, q for quitting program : ";
	char PlayChecker = 'w';
	bool OnlySortOnce = false;

	bool PlayedOnce = false; //Playing the game once allows you to output;

	cout << setw(50) << setfill('*') << "" << endl
		<< setw((49 - HoldWelcome.size()) / 2) << "" << HoldWelcome << setw((49 - HoldWelcome.size()) / 2) << "" << endl
		<< setw(50) << "" << endl << setw(0) << setfill(' ') << endl;

	cout << WantToPlayInitial;
	cin >> PlayChecker;

	try
	{
		if (PlayChecker != 'p' && PlayChecker != 'P' && PlayChecker != 'q' && PlayChecker != 'Q')
		{
			throw exception("Wrong Input: Exiting by default");
		}

	}
	catch (exception e)
	{
		cout << e.what() << endl;
		PlayChecker = 'q';
	}

	while (PlayChecker == 'p' || PlayChecker == 'P')
	{
		HangManBase BaseClass; //Needs to be switched out with derived class
		//cout << BaseClass;
		//PlayChecker = 'q';


		if (OnlySortOnce == false)
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
				cout << e.what();
				SortingOfWords = 'u';

			}

			//Done to constantly deallocate the aggregate - rami t
			{
				WordManager SorterSystem(BaseClass);
				switch (SortingOfWords)
				{
				case 'a':

					SorterSystem.sortWordsAlphabetically();
					OnlySortOnce = true;
					break;
				case 'l':
					OnlySortOnce = true;

					SorterSystem.sortWordsByLength();
					break;
				case 'u': //keeps it unsorted
				default:
					break;
				}
			}
		}



	}



}





//Final Portion, thinking about having a class call all these stuff, and we just use the constructor and call the class constructor;
