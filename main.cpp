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
		int ReturnTimesWon()
		{
			int Count = 0;
			T* TempSearcher = TLinkedListPtr;

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


			return Count;
		}

		//Searches through the list to see the amount of times won.
		int ReturnTimesLost()
		{
			int Count = 0;
			T* TempSearcher = TLinkedListPtr;

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


			return Count;
		}

		virtual ~LinkedList()
		{
			DeleteRecursive(this->TLinkedListPtr);
		};


};

//This base class Purpose is to load the data from the json file located inside of the rootfolder - Rami
class HangManBase
{
	//friend ostream
	protected:
		vector<string> HoldWords; //Rami - Holding the words to be used in the Hangman Game

		virtual ostream& Output(ostream& Output) //Output to the overloaded ostream operator that outputs not just to the console but to the output file as well.
		{
			return Output;
		}

		LinkedList<LinkedListData> LinkedListTemplateCall; //Template Call for linkedList

	public:


		//overloaded == operator

		//Operation Section

		

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
			LinkedListTemplateCall.lListPush("hi", true);
			LinkedListTemplateCall.lListPush("hi", true);
			LinkedListTemplateCall.lListPush("hi", true);
			LinkedListTemplateCall.lListPush("hi", false);
			LinkedListTemplateCall.lListPush("hi", true);
			LinkedListTemplateCall.lListPush("hi", true);
			LinkedListTemplateCall.lListPush("hi", true);
			LinkedListTemplateCall.lListPush("hi", false);
			LinkedListTemplateCall.lListPush("hi", true);
			cout << LinkedListTemplateCall.ReturnTimesLost();

			
		}
		


		virtual ~HangManBase() // This is the last thing that should be destroyed i.e. when the game ends -Rami
		{

		};

};


//Rami Portion End




int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Memory Management
	//const string HoldWelcome = "Welcome to the Hangman Game";
	//const string WantToPlayInitial = "Do you want to play the game? p for yes, q for quitting program : ";
	//char PlayChecker = 'w';

	//bool PlayedOnce = false; //Playing the game once allows you to output;

	//cout << setw(50) << setfill('*') << "" << endl
	//	<< setw((49 - HoldWelcome.size()) / 2) << "" << HoldWelcome << setw((49 - HoldWelcome.size()) / 2) << "" << endl
	//	<< setw(50) << "" << endl << setw(0) << setfill(' ') << endl;

	//cout << WantToPlayInitial;
	//cin >> PlayChecker;

	//try
	//{
	//	if (PlayChecker != 'p' && PlayChecker != 'P' && PlayChecker != 'q' && PlayChecker != 'Q')
	//	{
	//		throw exception("Wrong Input: Exiting by default");
	//	}

	//}
	//catch (exception e)
	//{
	//	cout << e.what() << endl;
	//	PlayChecker = 'q';
	//}

	//while (PlayChecker == 'p' || PlayChecker == 'P')
	//{
	//	HangManBase BaseClass();
	//	
	//}
	

	HangManBase BaseClass;
}





//Final Portion, thinking about having a class call all these stuff, and we just use the constructor and call the class constructor;