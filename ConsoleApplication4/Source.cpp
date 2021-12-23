#include <iostream>
#include<fstream>
using namespace std;
// FloatArray class contains "size" integer variable stores the size of array , and "Array" float pointer which is dynamically allocated to be an float array
class FloatArray {
public:
	// default and parameterized constructor
	FloatArray(int s = 0) {
		size = s;
		Array = new float[size];
		for (int i = 0; i < size; i++) {
			Array[i] = -2147483648;
		}
	}
	// add method of FloatArray that takes the number and its index to store them in the Array
	virtual void Add(int index, float num) {
		Array[index] = num;
	}
	// Destructor to delete the allocated memory for the Array 
	virtual ~FloatArray() {
		delete[] Array;
	}
	//Overloding for the insertation and extraction operators
	friend fstream& operator >>(fstream & infile,FloatArray * obj);
	friend fstream& operator <<(fstream & outfile,FloatArray*obj);
protected:
	float* Array;
	int size;
};
class SortedArray :public FloatArray
{
public:
	SortedArray(int s = 0) :FloatArray(s)
	{

	}
	virtual void Add(int index, float num) {
		for (int i = 0; i < size; i++) {
			if (num <= Array[i]) {
				for (int j = size - 1; j > i; j--) {
					Array[j] = Array[j - 1];
				}
				Array[i] = num;
				break;
			}
			else if (Array[i] == -2147483648) {
				Array[i] = num;
				break;
			}

		}
	}
};

class FrontArray : public FloatArray
{
public:
	FrontArray(int s = 0) :FloatArray(s)
	{
	}
	void Add(int index, float num) {
		int i = size - index - 1;
		Array[i] = num;
	}
};

class PositiveArray :public SortedArray
{
public:
	PositiveArray(int s = 0) :SortedArray(s)
	{
	}
	void Add(int index, float num) {
		if (num > 0) {
			SortedArray::Add(index, num);
		}

	}
};
class NegativeArray :public SortedArray
{
public:
	NegativeArray(int s = 0) :SortedArray(s)
	{
	}
	void Add(int index, float num) {
		if (num < 0) SortedArray::Add(index, num);
	}
};
fstream& operator >>(fstream & infile, FloatArray *obj) {
	for (int i = 0; i < obj->size; i++) {
		float num;
		infile >> num;
		obj->Add(i, num);
	}
	return infile;
}
fstream& operator <<(fstream & outfile, FloatArray * obj) {
	int cnt = 0;
	for (int i = 0; i < obj->size; i++) {
		if (obj->Array[i] == -2147483647)cnt++;
	}
	outfile <<obj->size - cnt << "|" << "\t";
	for (int i = 0; i <obj->size-cnt; i++) {
		outfile << obj->Array[i] << "\t";
	}
	outfile << "\n";
	cnt=0;
	return outfile;
}

int main()
{
	fstream inFile, outFile;
	string filename;
	cout << "Enter input file name: \n";
	cin >> filename;
	inFile.open(filename, ios::in);
	cout << "Enter Output file name: \n";
	cin >> filename;
	outFile.open(filename, ios::out);
	FloatArray* array[10];
	for (int i = 0; i < 10; i++) {
		int sze; string Array_name = "";
		inFile >> Array_name >> sze;
		int choice=0;
		if (Array_name == "Array")choice = 1;
		else if (Array_name == "Front")choice = 2;
		else if (Array_name == "Sorted")choice = 3;
		else if (Array_name == "Positive")choice = 4;
		else if (Array_name == "Negative")choice = 5;

		switch (choice) {
			FloatArray* ptr;
		case 1: {
			ptr = new FloatArray(sze);
			array[i] = ptr;
			inFile>> array[i];
			outFile << array[i];
			break;
		}

		case 2: {
			ptr = new FrontArray(sze);
			array[i] = ptr;
			inFile >> array[i];
			outFile << array[i];
			break;
		}
		case 3: {
			ptr = new SortedArray(sze);
			array[i] = ptr;
			inFile >> array[i];
			outFile << array[i];
			break;
		}
		case 4: {
			ptr = new PositiveArray(sze);
			array[i] = ptr;
			inFile >> array[i];
			outFile << array[i];
			break;
		}
		case 5: {
			ptr = new NegativeArray(sze);
			array[i] = ptr;
			inFile >> array[i];
			outFile << array[i];
			break;
		}
	    }
	}

}