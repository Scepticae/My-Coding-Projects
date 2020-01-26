#include<iostream>

using namespace std;

int *mergeSortedArrays(int*, int*);

//Driver to test function
int main(){
  int total_length;
  int firstSet[5] = {1, 3, 7, 10, 12};
  int secondSet[4] = {2, 5, 6, 11};
  int *mergedArray;

  mergedArray = mergeSortedArrays(firstSet, secondSet);

  total_length = sizeof(mergedArray)/sizeof(mergedArray[0]);

  for(int num = 0; num < total_length; num++){
    ;
  }

  return 0;
}

int *mergeSortedArrays(int *first, int *second){
  int length1, length2, total;
  int f_count = 0;
  int s_count = 0;
  int *merged;

  length1 = sizeof(first)/sizeof(first[0]);
  length2 = sizeof(second)/sizeof(second[0]);
  total = length1 + length2;
  cout << total;

  merged = new int [total];

  //Merge the two arrays into one
  for (int index = 0; index < total; index++){
    if(f_count != length1 && s_count != length2){
      if(first[f_count] >= second[s_count]){
        merged[index] = first[f_count];
        f_count++;
      }
      else{
        merged[index] = second[s_count];
        s_count++;
      }
    }
    else if(f_count == length1){
      merged[index] = second[s_count];
      s_count++;
    }
    else {
      merged[index] = first[f_count];
      f_count++;
    }
  }

  return(merged);
}