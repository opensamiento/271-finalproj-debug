#include <iostream>
#include <fstream> //stream class to read/write to/from files
#include <cstring>
#include <vector>
#include <stdlib.h>


using namespace std;

int read_file(vector <string> &v);
int str_conversion(string n_str);
int sorted_ints (vector <int> &vi);

int main()
{
    vector <string> csv;
    vector <int> int_vector;
    read_file(csv);
    string temp;
    /*debug
    int i; //n = no of chars in string from vector at some index
    for (i=0;i<21;i++)
        cout << i << ": " << " " << csv [i] << endl; //pay attention to \n (happens at every 5th position (where i%5=0)
    cout << endl;
    temp = csv [15];
    cout << "Element at pos 15: " << endl;
    for (i=0;i<temp.size();i++) {
        cout << temp[i] << " ";
    }

    cout << "Size: " << temp.size() << endl;
    string newl = "\n";
    cout << "L of new1: " << newl.size() << endl << endl; //mystery solved: \n is read as 1 char!!!!
    end-debug*/

    cout << "Size of vector csv: " << csv.size() << endl;
    for (int j=0;j<csv.size();j++)
        sorted_ints()
    return 0;
}

int read_file (vector <string> &v)
{
    ifstream in; //input filestream to read file
    char * filename = new char [15]; //user input to type name of file with .txt extension
    cout << "Please enter the name of the file: ";
    cin >> filename;
    in.open(filename); //read from file name
    if (!in.is_open()){ //when the file cannot be opened, show error msg and give user another chance until the right file is typed
        cout << "Error, please try another file. \n \n";
        return read_file(v); //give user another chance to type in filename
    }

    char * num = new char [100]; //char array to store the integers as they are read
    while(in.peek()!=EOF)
    {
        in.getline(num,100,',');//int will be put in char array with the delimiter being a comma and the instance of a new line
        v.push_back(num);
    }

    in.clear();
    in.close();
    return 1;
}

int str_conversion (string n_str) //l=size of string being inserted (size of nos depends in this case)
{
    int real_int, l;
    l = n_str.size();
    char * new_array = new char [l];
    for (int b=0;b<l;b++)
        new_array [l] = n_str [l];
    real_int = atoi(new_array);
    return real_int;
}

int sorted_ints(vector <int> &vi)
{

}
