//CSCI 41 group project.
//Monotonically Increasing Calculator.
//Group members:Kevin,Khoua,Mahesh,Maryam,Nick.
//Code has been bug checked but feel free to search for more.
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <deque>
#include <cmath>
#include <stdexcept>

using namespace std;

//Function Prototypes.
void die();

//Custom hash table to increment all key value by one each time they are accessed in the code.
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
				auto it=variable_Map.find(variable); //Checking to make sure it exists every time.
				int value= it->second;
				if(value==255)
					die();	
				it->second++;
				return value;
		}
		
		//This function cuts down the coding time to type insert.
		//It also performs error checking on the number that is being inserted and will die if it is out of bounds. !!! CHANGE TO THROW EXCEPTION LATER !!!
		void insert(char variable,int number)
		{
			if(number>255)
				throw runtime_error("INVALID INPUT!\n"); // Throw exception here instead.
			else
				variable_Map.insert(unordered_map<char,int>::value_type(variable,number));
		}
};

//Hash table declared globally for ease of use.
special_Hash_Table Map;

//Multidimensional deque to create a data structure that holds key/value pairs, FIFO behavior, and O(1) insertion and deletion at front and back.
//This data structure was used to make it possible to increment the value in a hash table every time it is popped off in a deque.
//The pop_back() returns a value(int) AND takes an element(deque) off of the back.
//The Map.return_Variable_Value() is what actually increments the variable value each time and is only called here.
class number_Deque
{
	public:
	deque<deque<string> > nums;
	int pop_Back()
	{
		int val;
		if(nums.back()[0].size()>1)
			val=stoi(nums.back()[1]);
		else
			val=Map.return_Variable_Value(nums.back()[0][0]);
		nums.pop_back();
		return val;
	}
};

//Simple class to implement a deque of chars(operations) who's pop_back() returns a value AND takes an element off the back.
//Deque chosen for FIFO structure.
class char_Deque
{
	public:
		deque<char> chars;
		char pop_Back()
		{
			char c=chars.back();
			chars.pop_back();
			return c;
		}
};

//Die function to catch bad input.
//Will be replaced later with proper exception handling.
void die()
{
	cout<<"INVALID INPUT!\n";
	exit(0);
}

//Simple Mod function to handle the modulusing of negative numbers.
unsigned int mod(int a, int b)
{
	while(a<0)
	{
		a+=b;
	}
	return a%b;
}

//This function is passed two numbers and an operation to perform on them, then returns the result.
int operation_Result(int b,int a,char operation)
{
	switch(operation)
	{
		case '+':
			return a+b;
			break;
		case '-':
			return a-b;
			break;
		case '*':
			return a*b;
			break;
		case '/':
			if(b==0)
				die();
			else
				return a/b;
			break;
		case '^':
			if(a==0&&b==0)
				die();
			else
				return pow(a,b);
			break;
		case '%':
			if(b==0)
				die();
			else
				return mod(a,b);
		default:
			break;
	}
}

//This recursive function takes a modified deque of ints(numbers) and a modified deque of chars(operations) as inputs.
//The # elements in the operations deque= (# elements in the numbers deque)-1.
//The base case is reached when the operations deque has size 0 (ie all the operations have been performed, the only element in the numbers deque is the final result),at which point it returns that final result.
//If the base case hasn't been reached then the numbers deque pushes back the result returned from the operation_Result function.
//Then the function calls itself with the now decreased numbers deque and operation deque and continues until the base case is reached.
int do_operations(number_Deque NumDeque,char_Deque CharDeque)
{
	if(CharDeque.chars.size()==0) //Base case
		return stoi(NumDeque.nums[0][1]);
	else
	{
		deque<string> deck;
		deck.push_back("yes");
		deck.push_back(to_string(operation_Result(NumDeque.pop_Back(),NumDeque.pop_Back(),CharDeque.pop_Back()))); //Work towards goal.
		NumDeque.nums.push_back(deck);
		return do_operations(NumDeque,CharDeque);
	}
}

//This function parses the entire line of input and puts the strings in a vector.
//This function uses stringstream to accomplish this, see previous projects to refresh memory if neccesary.
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

//This utility function ensures that a string is a number.
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

//This function returns true if the string is a variable.
bool is_A_Variable(string &variable_String)
{
	if(variable_String.size()==1&&isalpha(variable_String[0]))
		return true;
	else
		return false;
}

//This function returns true if the string is an operator.
bool is_A_Operator(string &operat)
{
	if(operat.size()>1)
		return false;
	char c=operat[0];
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^'||c=='%')
		return true;
	else
		return false;
}

//This function tests to see if the string inputted is valid.
bool good_Input(string input)
{
	if((input=="QUIT")||(input=="LET")||(input=="LOOP")||is_A_Number(input)||is_A_Operator(input)||is_A_Variable(input)) //If the string isn't a number,variable, or operator then it's invalid.
		return true;
	else
		return false;
}

//Simple function to make all the alphanumeric strings in a vector uppercase.
void upperCase_All_Alphanumeric_Strings(vector<string> &vec)
{
	for(size_t i=0;i<vec.size();i++)
	{
		if(isalpha(vec[i][0]))
		{
			for(size_t j=0;j<vec.at(i).size();j++)
			{
				vec[i][j]=toupper(vec[i][j]);
			}	
		}
		else
			continue;
	}
}

//This function seperates the task of when the user inputs "LET" so that it looks cleaner in fill_Deques() function.
void LET_Sequence(vector<string> &vec, int i=1) //DONE
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
}

//This function takes the vector that stores all of the words inputted and then does with them what it needs to to accomplish the algebra.
//It will also assign the loop number if the user inputs LOOP and then a number.
//Function invariant: the number of operators must be 1 less than the number of numbers unless they are both size 0.
//Function invariant: counter 'i' must increment at each step.
void fill_Deques(vector<string> &vec,number_Deque &MyNumbers,char_Deque &MyChars,unsigned int &loop_Iterations)
{
	unsigned int i=0;
	bool seen_An_Loop=false;
	while(i<vec.size())
	{
		if(!good_Input(vec.at(i)))
			die();
		if(vec.at(i)=="LOOP"&&(!seen_An_Loop)) //If the string is loop and we haven't already seen a loop, then we can assign the loop_Iterations number.
		{
			if(vec.size()==i+1)
				die();
			if(!is_A_Number(vec.at(i+1)))
				die();
			loop_Iterations=stoi(vec.at(i+1));
			seen_An_Loop=true;
			i+=2;
			continue;
		}
		if(vec.at(i)=="LET")
		{
			LET_Sequence(vec,i+1); //Call let sequence function above.
			i+=4;
			continue;
		}
		if(vec.at(i)=="QUIT")
			exit(0);
		while(i<vec.size()&&(is_A_Number(vec.at(i))||is_A_Variable(vec.at(i))||is_A_Operator(vec.at(i))))
		{
			//If the # of numbers = # of operators then it must get a number next.
			//This if statement either sees a variable and creates a deque containing the char and associated value to push into the main number deque
			//or it sees a number and inputs the string "yes" and the number into a deque and then push_back's that deque into the main number deque.
			if(MyNumbers.nums.size()==MyChars.chars.size())
			{
				int val;
				string is_num;
				if(is_A_Number(vec.at(i))) //If it's a number.
				{
					val=stoi(vec.at(i));
					is_num="yes";
				}
				else //If it's a variable.
				{
					if(Map.no_Duplicates(vec[i][0])) //If it doesn't exist then it can't be accessed.
						die();
					val=Map.variable_Map.find(vec[i][0])->second;
					is_num.push_back(vec[i][0]); //Assign is_num the first char of the string.
				}
				deque<string> deck;
				deck.push_back(is_num);
				deck.push_back(to_string(val));
				MyNumbers.nums.push_front(deck);	
				i++;
				continue;
			}
			else //If it doesn't see a number then it must be an operator, so it push_back()'s that char into the operator deque.
			{
				MyChars.chars.push_front(vec.at(i)[0]);
				i++;
				continue;
			}	
		}
	}
}

//Main has a loop that first calls a function to get a line of input and store the strings in a vector.
//Then it calls the fill_Deques() function to fill up the int(number) deque and the char(operation) deque.
//Once the deques have their elements, they are passed into the do_operations() function which does the algebra and returns the result.
//This loop continues until bad input is encountered or the user inputs "QUIT".
int main()
{
    while(cin&&(!cin.eof()))
	{
		try
		{	
			vector<string> words;
			number_Deque MyNumbers;
			char_Deque MyChars;
			unsigned int loop_Iterations=0;
		
			populate_Word_Vector(words);
			upperCase_All_Alphanumeric_Strings(words);
			fill_Deques(words,MyNumbers,MyChars,loop_Iterations);
			if(MyNumbers.nums.size()==0&&MyChars.chars.size()==0)
				continue;
			if(loop_Iterations==0)
				cout<<do_operations(MyNumbers,MyChars)<<endl;
			else
				for(int i=loop_Iterations;i>0;i--)
				{
					cout<<do_operations(MyNumbers,MyChars)<<endl;
				}
		}
		catch(exception &e)
		{
			cout<<e.what();
			exit(0);
		}
	}
    return 0;
}

