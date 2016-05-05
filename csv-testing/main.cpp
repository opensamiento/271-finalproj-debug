#include <iostream>
#include <fstream> //stream class to read/write to/from files
#include <cstring>
#include <vector>
#include <stdlib.h>


using namespace std;

class Job
{
private:
    int id;
    int transfer;
    int withdraw;
    int deposit;
    int wealth;
    int dtime;

public:
    Job (int i, int t, int wi, int d, int we, int dt);

    bool get_id (int &idno);
    bool get_transfer (int &trans);
    bool get_withdraw (int &with);
    bool get_deposit (int &dep);
    bool get_wealth (int &we);
    bool get_dtime (int &dtim);

    bool set_id (int idd);
    bool set_transfer (int trans);
    bool set_withdraw (int with);
    bool set_deposit (int dep);
    bool set_wealth (int we);
    bool set_dtime (int dtim);
};

int read_file(vector <string> &v);
int str_conversion(string n_str);
int sorted_ints (vector <int> &vi, string int_str);
void endl_conversion(vector <int> &vi, string int_str);

int main()
{
    vector <string> csv;
    vector <int> int_vector;
    vector <Job> jobs_vector;
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

    cout << "Size of vector csv: " << csv.size() << endl; //debugging
    cout << "Item 6 (Pos 5): " << csv [5] << endl;
    string no_str = csv[5]; //use for special case at beg of csv file (string AND int are joined together)
    char * no_array = new char [3];
    int k=0, i=0;
    for (k=0;k<no_str.size();k++) //THIS WORKS - get first position when numbers are combined with other items
                                    //in this case it's the first line (where number is combined w a string of text)
    {
        if (no_str[k] == '\n' )
        {
            no_array[0] = no_str[no_str.size()-3];
            no_array[1] = no_str [no_str.size()-2];
            no_array[2] = no_str [no_str.size()-1];
            int_vector.push_back(atoi(no_array));
            k = no_str.size(); //ends loop (k's value indicates loop should end)
        }
    }
    cout << "In array: ";
    for (i=0;i<3;i++)
        cout << no_array[i];
    cout << endl << "In vector int_vector: " << int_vector[0] << endl;
    for (i=6;i<csv.size();i++) //sort thru vector AFTER first few lines
    {
        if (i%5==0) //every line that has the two nos combined is in index divisible by 5 (i.e. every 5th position in vector csv)
        {

            endl_conversion(int_vector, csv[i]);
        }
        else
        {
            int_vector.push_back(str_conversion(csv[i]));
        }
    }

    cout << "Size of int_vector: " << int_vector.size() << endl;
    for (int l=0; l<int_vector.size();l++)
    {
        cout << "Elements in int vector:" << int_vector[l] <<endl;
    }
    /*
    int j;
    for (j=0; j< csv.size(); j++)
    {
        cout<<"Elements in csv vector:" << csv[j] <<endl;
    }
    */
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
    {
           new_array [b] = n_str [b];
    }
    real_int = atoi(new_array);
    return real_int;
}

void endl_conversion(vector <int> &vi, string int_str)
{
    int A, B, j, e; //length of digits for these two numbers (time and customer ID); e = pos where endl exists; j = indexing purposes
    int k=0; //for B_array position
    for (j=0;j<int_str.size();j++) //get no of units for first and second int (time and cust ID)
    {
        if (int_str[j] == '\n'){
            e=j; //record pos where endl char exists
        }
        else{
            A++;
        }
    }
    B = e+1;
    char * A_array = new char [A]; //set up char arrays (to be used for conversion later below)
    char * B_array = new char [B];
    for (j=0;j<int_str.size();j++)
    {
        if (j<e)
            A_array[j]=int_str[j];
    }

    for (j=e;j<int_str.size();j++)
    {
        B_array[k] = int_str[j];
        k++;
    }
    int tempA, tempB;
    tempA = atoi(A_array);
    tempB = atoi (B_array);
    if (tempA!=0)
        vi.push_back(atoi(A_array)); //two numbers are pushed onto vector, first is A and then B (time, THEN cust ID)
    if (tempB!=0)
        vi.push_back(atoi(B_array));

}


