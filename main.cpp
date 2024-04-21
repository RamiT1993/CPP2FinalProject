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
#include <random>

#include "json.hpp"


using namespace std; //getting rid of annoying std - rami



/*also when you sort allow the user to sort based on length or alphabetical nature*/


//Base Class or derived class will have others work on it to include searching/sorting operations



//Rami Portion Start

//This base class Purpose is to load the data from the json file located inside of the rootfolder - Rami
class HangManBase
{
	protected:
		vector<string> HoldWords; //Rami - Holding the words to be used in the Hangman Game


	public:




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
			cout << JsonDataInfoHolder;

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






int main()
{
	HangManBase ii;
}





//Final Portion, thinking about having a class call all these stuff, and we just use the constructor and call the class constructor;