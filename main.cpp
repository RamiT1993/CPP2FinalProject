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

#include "json.hpp"


using namespace std; //getting rid of annoying std - rami



/*also when you sort allow the user to sort based on length or alphabetical nature*/


//Base Class or derived class will have others work on it to include searching/sorting operations



//Rami Portion Start


//Rami-T Creation of the linked list template class to operate the dynamically allocated data and use it for some calculations and outputting.

//Struct To Hold the linked list data
struct LinkedListData 
{
	string WordName = "";
	bool SuccessfullyGuessed = false;
	LinkedListData* next;
};


template <typename T>
class LinkedList
{
	private:


		T* TLinkedListPtr;

	public:
		//This push template class operation, will push into the linked list if you have guessed it correctly
		void lListPush(string Word, bool Guessed)
		{

		}


};

//This base class Purpose is to load the data from the json file located inside of the rootfolder - Rami
class HangManBase
{
	//friend ostream
	protected:
		vector<string> HoldWords; //Rami - Holding the words to be used in the Hangman Game

		virtual ostream& Output(ostream& Output) //Output to the overloaded ostream operator that outputs not just to the console but to the output file as well.
		{

		}

		//Template Operator call here

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
		}
		


		virtual ~HangManBase() // This is the last thing that should be destroyed i.e. when the game ends -Rami
		{

		};

};


//Rami Portion End

//All the stuff will be passed into here so main will only have one function being called;
void MainFunctSimple()
{
	const string HoldWelcome = "Welcome to the Hangman Game";
	const string WantToPlayInitial = "Do you want to play the game? p for yes, q for quitting program : ";
	char PlayChecker = 'w';

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
		HangManBase BaseClass;
		PlayChecker = 'q';
	}

	














	



}



int main()
{
	MainFunctSimple();
}





//Final Portion, thinking about having a class call all these stuff, and we just use the constructor and call the class constructor;