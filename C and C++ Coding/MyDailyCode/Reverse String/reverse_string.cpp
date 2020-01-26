#include<iostream>
#include<string>

using namespace std;

string reverseString(string);

//Driver Program to test Function
int main(){
  string myString = "hello my name is sam";
  string reversedString;

  reversedString = reverseString(myString);
  cout << reversedString;

  return 0;
}

string reverseString(string old_str){
  //Get String Length
  string r_string;
  int str_length = old_str.length();

  r_string = old_str;

  //Reverse the String
  for(int index = 0; index < str_length; index++){
    r_string[index] = old_str[(str_length-1)-index];
  }

  return(r_string);
}