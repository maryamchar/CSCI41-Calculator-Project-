#include <iostream>
#include <ncurses.h>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

class special_Hash_Table  // Pods class to hold hash table and do error checking on inputs
{
    public:
    unordered_map<char,int> variable_Map;
    void valid_Number(int num)
    {
        if(num>255)
            // Write code to throw exception here instead of die()
        cout<<"Bad input\n"; // Change this to throw an exception
    }
};
void uppercaseify(string& mystr)
{                              //Converts the passed in string to all uppercase.
	for (auto& c: mystr)
    {
		c = toupper(c);
	}
}
bool is_alpha(string& mystr)
{                                  //True if the passed in string is all letters.
    for (auto& c: mystr)
        if(!(isalpha(c)))
            return false;
    return true;
}
bool is_digit(string& mystr)
{
    for (auto& c: mystr)
        if(!(isdigit(c)))
            return false;
    return true;
}
unsigned int mod(int num,int modulus)
{
	while(num<0)
	{
		num+=modulus;
	}
	return num;
}
void die() 
{                                                    //Exits program.
    cout << "BAD INPUT" << endl;
    exit(0);
}
int main() 
{
    special_Hash_Table Map;
	int number;
    float answer;
    float scalor;
    string variable_string;
    string operation;
    string a;
    char operat;
    string equals;
    while(cin) 
	{                                                //MAIN LOOP.
        cin >> operation;
        uppercaseify(operation);
        if(operation == "QUIT") break;
        if(operation == "LET")                              //Takes in "LET" to make sure they are creating variables.
 		{
            cin >> variable_string;                         // Get the variable and do error checking
            if(variable_string.size()>1)
                die();
            char variable=toupper(variable_string[0]);
            if(!isalpha(variable))
                die();
            if(Map.variable_Map.find(variable)!=Map.variable_Map.end()) // If it already exists then die
                die();

            cin>>equals;                                     // Get equal sign, and die if it's not equal sign
            //if(equals!="=")
              //  die();

            cin >> number;                                   // Get number and do error checking on it
            if(!cin)
                die();

            Map.variable_Map.insert(unordered_map<char,int>::value_type(variable,number)); // Insert a key/value pair into hash table if all things are good
		}
		
		if(operation.size() == 1) 
		{
        	 while(cin) 
			 {
				 answer=Map.variable_Map.find(operation[0])->second;
                cin >> operat;
                switch(operat)
				{
					case '+':
                    	cin >> a;
                    	uppercaseify(a);
						cout<<"\nwoooooow\n";
                    	if(is_alpha(a)) 
						{
							auto it=Map.variable_Map.find(a[0]);
							cout<<"\nhahahah\n";
                        	if(it==Map.variable_Map.end())
								die();
							else
							{
								answer+=it->second;
								it->second++;
								cout<<endl<<answer<<endl;
							}
                   		}
                    	else 
						{
						cout<<"\nTHIS PLACE\N";
						//answer=Map.variable_Map.find(operation[0])->second;
						scalor = atoi(a.c_str());               //Converts numbers in a string to an int.
						answer += scalor;
					}
					break;
				case '-':
					cin >> a;
                    	uppercaseify(a);
                    	if(is_alpha(a))
						{
							auto it=Map.variable_Map.find(a[0]);
                        	if(it==Map.variable_Map.end())
                        		die();
                        	else
                        	{
                        		answer-=it->second;
                            	it->second++;
                        	}
						}
                    	else 
						{
                        	scalor = atoi(a.c_str());
                        	answer -= scalor;
                   		}
            			break;
                	case '*':
                    	cin >> a;
                    	uppercaseify(a);
                    	if(is_alpha(a))
						{
                            auto it=Map.variable_Map.find(a[0]);
							if(it==Map.variable_Map.end())
                            	die();
                            else
                            {
                            	answer*=it->second;
                            	it->second++;
                            }
                        }
						else
						{
                        	scalor = atoi(a.c_str());
                        	answer *= scalor;
						}
						break;
          
                	case'/':
                    	cin >> a;
                    	uppercaseify(a);
                    	if(is_alpha(a))
						{
                         	auto it=Map.variable_Map.find(a[0]);
							if(it==Map.variable_Map.end())
                         		die();
                         	else
                         	{
                         		answer/=it->second;
                            	it->second++;
                         	}
                    	}
                    	else 
						{
                    		scalor = atoi(a.c_str());
                        	answer /= scalor;
                    	}
              			break;
                	case '^':
                    	cin >> a;
                    	uppercaseify(a);
                    	if(is_alpha(a))
						{
                            auto it=Map.variable_Map.find(a[0]);
							if(it==Map.variable_Map.end())
                            	die();
                            else
                            {
                            	answer=pow(answer,it->second);
                                it->second++;
                            }
                        }

                    	else
					    {
                        	scalor = atoi(a.c_str());
                        	answer = pow(answer, scalor);
                    	}
						break;
                
                	case '%':
                    	cin >> a;
                    	uppercaseify(a);
                    	if(is_alpha(a))
						{
                            auto it=Map.variable_Map.find(a[0]);
							if(it==Map.variable_Map.end())
                            	die();
                            else
                            {
                            	answer=mod(answer,it->second);
                                it->second++;
                            }
                        }
                    	else 
						{
                        	scalor = atoi(a.c_str());
                        	answer=mod(static_cast<int>(answer),static_cast<int>(scalor));
							//Casts the values as ints; can't use float values with (%).
                    	}
                	case '\n':
                		break;
            		default:
						break;
				}
				cout << "answer = " << answer << endl;
				break;
        }
        if(operation == "AS") // this is our way to see all the values in the hash table ( take this out later )
		{
			for(auto p:Map.variable_Map)
			{
				cout<<p.second<<" ";
			}
		}
	}// end of inner while loop
} // end of while loop
} // end of main
