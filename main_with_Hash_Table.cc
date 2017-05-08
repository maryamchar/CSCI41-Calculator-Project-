//Main file for the hash table version.
//This code will function independentely from the main_with_Hash_Table_Operations.
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cctype>

void die(); //Function Prototype

using namespace std;

//Custom hash table to increment all key value by one each time they are accessed.
class special_Hash_Table
{
	public:
		unordered_map<char,int> variable_Map;
		
		//This member function checks to see if the key already exists.
		bool no_Duplicates(char variable)
		{
			auto it=variable_Map.find(variable); //Checking to make sure it exists every time.
			if(it==variable_Map.end())
				return true;
			else
				return false;;
		}
		
		//This member function can be passed a key and will return the corresponding value.
		//It is also how the incrementation is implemented.
		int return_Variable_Value(char variable)
		{
			if(no_Duplicates(variable))
			{
				auto it=variable_Map.find(variable); //Checking to make sure it exists every time.
				int value= it->second;
				it->second++;
				return value;
			}
			else
				die();
		}
		//This function cuts down the coding time to type insert.
		//It also performs error checking on the number that is being inserted and will die if it is out of bounds. !!! CHANGE TO THROW EXCEPTION LATER !!!
		void insert(char variable,int number)
		{
			if(number>255)
				die(); // Throw exception here instead.
			else
				variable_Map.insert(unordered_map<char,int>::value_type(variable,number));
		}
};
//I probably shouldn't make this global
special_Hash_Table Map;

void die()
{
	cout<<"\nBad Input\n";
	exit(0);
}
void populate_Word_Vector(vector<string> &word_Vector)
{
    string input_line;
    string word;
    getline(cin,input_line);
    stringstream ssInput_Line(input_line);
    while(ssInput_Line>>word)
    {
        word_Vector.push_back(word);
    }
}
void print(vector<string> &vec)
{
    for(string i:vec){cout<<i<<endl;}
}
bool is_A_Number(string &number_String)
{
	for(char c:number_String)
	{
		if(!isdigit(c))
			return false;
		else
			continue;
	}
	return true;
}
void LET_Sequence(vector<string> &vec, int i=1)
{
	if(!(isalpha(vec.at(i)[0])&&vec.at(i).size()==1)) //If the next string isn't a variable then die.
		die();
	char variable=vec.at(i)[0];
	if(!Map.no_Duplicates(variable))
		die();
	if(!(vec.at(i+1)=="="))
		die();	
	if(!(is_A_Number(vec.at(i+2))))
		die();
	int number=stoi(vec.at(i+2));
	Map.insert(variable,number);
	cout<<"\nThe value is : "<<Map.variable_Map.find(variable)->second<<endl; 
	//^Just a little test to see that it is succseful in storing the key/value pair in the hash table :).
}
void do_Things(vector<string> &vec)
{
	//If it's "LET" or if it's a single letter or if it's a number as the first string, then it's safe to proceed, otherwise die.
	if(!(vec.at(0)=="LET"||(isalpha(vec.at(0)[0])&&vec.at(0).size()==1)||is_A_Number(vec.at(0))))
		die();
	if(vec.at(0)=="LET") //Let sequence
		LET_Sequence(vec,1);
	//Need more here to complete this junk!! :(
}

int main()
{
    vector<string> words;
    while(true)
	{
		populate_Word_Vector(words);
		do_Things(words);
	}

    return 0;
}


