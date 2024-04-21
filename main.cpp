//Program Name: Hangman
//Group Number: 5
//Group Leader: Rami Toma
//Group Members: Hussein Alanbari, Tajwar Rahman



#include <iostream>
#include <vector>
#include <map>
#include <cctype>
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

		}


		//Constructor - When called it activates the loading of data from json file to the vector - Rami T
		HangManBase()
		{

		}


		virtual ~HangManBase() // This is the last thing that should be destroyed i.e. when the game ends -Rami
		{

		};

};


//Rami Portion End






int main()
{

}





//Final Portion, thinking about having a class call all these stuff, and we just use the constructor and call the class constructor;