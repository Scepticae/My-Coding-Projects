#include<iostream>
#include<array>

using namespace std;

//Bit Array Class
class BitArray {
  int size;
  int *bitArray;

  public:
    //Function Prototypes
    BitArray(int);
    void setBit(int, int);
    int getBit(int);
};

//Test Driver
int main(){
  int num = 0;
  int index = 0;
  int value = 0;
  bool check = true;
  BitArray *checkArray;

  //Get Number
  cin >> num;

  //Create BitArray
  checkArray = new BitArray(num);

  //Set the Bits for the array
  for(int i=0; i < num; i++){
    cout << "Enter a 1 or a 0" << endl;
    cin >> value;
    checkArray->setBit(i, value);
  }

  //Get a Value from the Array
  while(check){
    cout << "Enter an Index to get value" << endl;
    cin >> index;
    if (index >= num){
      check = false;
    }
    else{
      value = checkArray->getBit(index);
      cout << "The bit is " << value << endl;
    }
  }

  return(0);
}

// Function Definitions
BitArray::BitArray(int s){
  size = s;
  bitArray = new int[size];
}

void BitArray::setBit(int index, int val){
  bitArray[index] = val;
}

int BitArray::getBit(int index){
  return(bitArray[index]);
}