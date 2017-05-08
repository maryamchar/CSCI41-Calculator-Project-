//CSCI 41 group project.
//Monotoniclly Increasing Calculator.
//Kevin,Khoa,Mahesh,Maryan,Nick.
//This file performs the main functionality of performing the operations once
//the string has been parsed and all chars(operations) and ints(numbers) have been put into the deques.
//This .cc will eventually be edited to get rid of the main() function and then compiled separately with the
//actual main so that the process of performing equations may be abstracted away to further contributers.
#include <iostream>
#include <deque>
#include <cmath>

using namespace std;

int operation_Result(int,int,char); // Function Prototype

//Die function to catch bad input.
//Will be replaced later with proper exception handling.
void die()
{
	cout<<"\nBad Input\n";
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

//Simple class to implement a deque of ints(numbers) who's pop_back() returns a value AND takes an element off of the back.
//Deque chosen to allow FIFO behavior and allow pop_back()'s.
class number_Deque
{
	public:
	deque<int> nums;
	int pop_Back()
	{
		int val=nums.back();
		nums.pop_back();
		return val;
	}
};

//Simple class to implement a deque of chars(operations) who's pop_back() returns a value AND takes an element off the back.
//Deque chosen for FIFO structure, but a regular queue would suffice.
//! MAYBE CHANGE TO QUEUE LATER ! Why would i need a deque for this??
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

//This recursive function takes a modified deque of ints(numbers) and a modified deque of chars(operations) as inputs.
//The # elements in the operations deque= (# elements in the numbers deque)-1.
//The base case is reached when the operations deque has size 0 (ie all the operations have been performed, the only element in the numbers deque is the final result),at which point it returns that final result.
//If the base case hasn't been reached then the numbers deque pushes back the result returned from the operation_Result function.
//Then the function calls itself with the now decreased numbers deque and operation deque and continues until the base case is reached.
int do_operations(number_Deque &NumDeque,char_Deque &CharDeque)
{
	if(CharDeque.chars.size()==0) //Base case
		return NumDeque.nums.at(0);
	else
	{
		NumDeque.nums.push_back(operation_Result(NumDeque.pop_Back(),NumDeque.pop_Back(),CharDeque.pop_Back())); //Work towards goal
		return do_operations(NumDeque,CharDeque);
	}
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
int main()
{	
	//Input has been tested and is functional.
	//Tests also passed for bad input such as 0^0, 3/0, 5mod(0), etc.	
	
	number_Deque MyNumbers;
	MyNumbers.nums.push_front(3);
	MyNumbers.nums.push_front(0);
	
	char_Deque MyChars;
	MyChars.chars.push_front('%');

	cout<<do_operations(MyNumbers,MyChars)<<endl;
	
	
	return 0;
}
