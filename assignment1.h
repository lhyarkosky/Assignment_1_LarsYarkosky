
class Get_Data {
public:
  Get_Data();                          // Constructor
  void ReadFile(const char *filename); // Read data from the file
  void PrintData();                    // Print data stored in the array

  class ArraySearch {
  public:
    ArraySearch(int *arr, int size); // Constructor
    int
    findIndex(int target); // Function to find the index of a specified integer

    int *array;
    int arraySize;
  };

int ModifyValue(int index, int newValue); // Function to modify the value at the specified index
void AddInteger(int value); // Function to add a new integer to the end of the array
void ReplaceWithZero(int index); // Function to replace the value at a specified index with 0

  int data_array[150];
  int data_size;
};

