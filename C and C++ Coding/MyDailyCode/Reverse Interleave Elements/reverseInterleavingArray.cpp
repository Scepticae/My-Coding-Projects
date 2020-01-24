//Samuel Leonard
//1-23-20

#include<iostream>
#include<queue>
#include<vector>

using namespace std;

vector<int> reverseInterleaveArray(vector<int>);

int main(){
  vector<int> nums = {4, 6, 9, 3, 7};
  vector<int> newNums;

  newNums = reverseInterleaveArray(nums);

  for (int j = 0; j < newNums.size(); j++) {
    cout << newNums[j];
  }
}

vector<int> reverseInterleaveArray (vector<int> numbers) {
  int i, count, n;
  queue<int> n_queue;

  //Initialize the count and n variables
  count = 0;
  n = numbers.size() - 1;

  //Iterate through the vector and interleave back half with front half
  for(i = 1; i < numbers.size(); i++){
    //Check to make sure i is in the first half of the vector
    if(i < numbers.size() / 2){
      //Check for every other value
      if(((i + 1) % 2) == 0){
        //Store the current element and copy the current back element with
        //the current element
        n_queue.push(numbers[i]);
        numbers[i] = numbers[n - count];
        count++;
      }
      //Otherwise, queue the current element and dequeue the front to current
      //position
      else{
        n_queue.push(numbers[i]);
        numbers[i] = n_queue.front();
        n_queue.pop();
      }
    }
    //Dequeue every other element and store in array
    else{
      if(((i + 1) % 2) != 0){
        numbers[i] = n_queue.front();
        n_queue.pop();
      }
    }
  }
  //Return the Vector
  return(numbers);
}