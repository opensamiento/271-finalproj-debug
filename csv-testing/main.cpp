#include <iostream>
#include <fstream> //stream class to read/write to/from files
#include <cstring>
#include <vector>
#include <stdlib.h>


using namespace std;

class Job
{
private:
    int id; //customer ID
    int transfer; //transfer amount
    int withdraw; //account # withdrawing from
    int deposit; //account # depositing to
    int wealth; //customer wealth
    int dtime; //time deposit must be made by

public:
    Job ();
    //getters (data obtained from int_vector when constructing jobs)
    int get_id ();
    int get_transfer ();
    int get_withdraw ();
    int get_deposit ();
    int get_wealth ();
    int get_dtime ();
    //setters
    void set_id (int idd);
    void set_transfer (int trans);
    void set_withdraw (int with);
    void set_deposit (int dep);
    void set_wealth (int we);
    void set_dtime (int dtim);
};

Job::Job() //empty constructor
{
    id=transfer=withdraw=deposit=wealth=dtime=0; //set up job's values as all 0s, change them later when inserted into job_vector
}

int Job::get_id()
{
    return id;
}

int Job::get_transfer()
{
    return transfer;
}

int Job::get_withdraw()
{
    return withdraw;
}

int Job::get_deposit()
{
    return deposit;
}

int Job::get_wealth()
{
    return wealth;
}

int Job::get_dtime()
{
    return dtime;
}

void Job::set_id(int idd)
{
    id = idd;
}

void Job::set_transfer(int trans)
{
    transfer=trans;
}

void Job::set_withdraw(int with)
{
    withdraw = with;
}

void Job::set_deposit(int dep)
{
    deposit = dep;
}

void Job::set_wealth(int we)
{
    wealth = we;
}

void Job::set_dtime(int dtim)
{
    dtime = dtim;
}


int read_file(vector <string> &v);
int str_conversion(string n_str);
int sorted_ints (vector <int> &vi, string int_str);
void endl_conversion(vector <int> &vi, string int_str);

void QuickSort (vector <Job> &jv, int left, int right);
void swapp (Job &x, Job &y); //for use in quicksort, swapping values

int main()
{
    vector <string> csv; //items first read in from CSV file are strings
    vector <int> int_vector; //conversions happen just for ints in CSV file, put here
    vector <Job> jobs_vector; //jobs w 6 related categories, inserted into vector w all jobs (unsorted in beginning)
    int left, right;
    left=right=0;
    read_file(csv);
    /*
    cout << "Size of vector csv: " << csv.size() << endl; //debugging
    cout << "Item 6 (Pos 5): " << csv [5] << endl;
    */
    string no_str = csv[5]; //use for special case at beg of csv file (string AND int are joined together)
    char * no_array = new char [3];
    int k=0, i=0; //indexing purposes
    for (k=0;k<no_str.size();k++) //UNIQUE CASE - get fifth position of string vector when numbers are combined with string of text
                                    //in this case it's the first line on the CSV file (423 is attached at end)
    {
        if (no_str[k] == '\n' ) //find the newline char
        {
            no_array[0] = no_str[no_str.size()-3]; //customer ID for first job is 423, 3 digits total
            no_array[1] = no_str [no_str.size()-2];
            no_array[2] = no_str [no_str.size()-1];
            int_vector.push_back(atoi(no_array)); //first item is put on int_vector, later to be used for first job's ID
            k = no_str.size(); //ends loop (k's value indicates loop should end)
        }
    }
    for (i=6;i<csv.size();i++) //sort thru string vector AFTER first 6 lines
    {
        if (i%5==0) //every line that has the two nos combined is in index divisible by 5 (i.e. every 5th position in vector csv)
            endl_conversion(int_vector, csv[i]);
        else
            int_vector.push_back(str_conversion(csv[i])); //if it's not at that position, just insert the number onto the vector (after conversion)
    }
    /*
    cout << "Size of int_vector: " << int_vector.size() << endl;
    for (int l=0; l<int_vector.size();l++)
    {
        cout << "Elements in int vector:" << int_vector[l] <<endl;
    }
    int j;
    for (j=0; j< csv.size(); j++)
    {
        cout<<"Elements in csv vector:" << csv[j] <<endl;
    }
    */

    Job temp_job; //temp_job will represent the new job to be inserted into jobs_vector
    i = 0; //reset index indicator i to 0 to start new search
    while (i<int_vector.size()) { //begin searching in int_vector for data; data is grouped as 6 ints in int_vector for each job
        temp_job.set_id(int_vector[i]);
        temp_job.set_transfer(int_vector[i+1]);
        temp_job.set_withdraw(int_vector[i+2]);
        temp_job.set_deposit(int_vector[i+3]);
        temp_job.set_wealth(int_vector[i+4]);
        temp_job.set_dtime(int_vector[i+5]);
        jobs_vector.push_back(temp_job); //push newly created job onto jobs_vector
        i+=6; //increase index by 6 to get next set of information for next job
    }
    cout << "size of jobs_vector: " << jobs_vector.size() << endl << endl; //debugging
    QuickSort(jobs_vector, left, right);

    for (i=0;i<jobs_vector.size();i++) {
        cout << "stuff in temp_job at index " << i << ": \n";
        cout << "id: " << jobs_vector[i].get_id() << endl;
        //cout << "transfer: " << jobs_vector[i].get_transfer() << endl;
        //cout << "withdraw: " << jobs_vector[i].get_withdraw() << endl;
        //cout << "deposit: " << jobs_vector[i].get_deposit() << endl;
        //cout << "wealth: " << jobs_vector[i].get_wealth() << endl;
        cout << "time: " << jobs_vector[i].get_dtime() << endl << endl << endl;
    }
    cout << "Done with jobs_vector! \n";


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
    if (tempA!=0) //if number is NOT 0, add it!
        vi.push_back(atoi(A_array)); //two numbers are pushed onto vector, first is A and then B (time, THEN cust ID)
    if (tempB!=0) //same as tempA, avoid having any 0s in vector
        vi.push_back(atoi(B_array));

}

void QuickSort (vector <Job> &jv, int left, int right)
{
    right = jv.size();
	int i = left, j = right;
    int pivot = jv[(left + right) / 2].get_dtime(); //get pivot, sorting by time

    //partition of 2 arrays and swapping
    while (i <= j) {
            while (jv[i].get_dtime() < pivot) {
                  i++;
            }
            while (jv[j].get_dtime() > pivot) {
                  j--;
            }
            if (i <= j && jv[i].get_id()!= jv[j].get_id()) { //make sure jobs are NOT the same!
                  swapp(jv[i], jv[j]); //swap jobs here
                  i++;
                  j--; //after swap, change index counters
            }
    }

    if (left < j)
        QuickSort(jv, left, j);
    if (i < right)
		QuickSort(jv, i, right);
}

void swapp (Job &x, Job &y) //for use in quicksort, swapping jobs
{
    Job tempjob; //to be used to move jobs around
    //set up tempjob = x
    tempjob.set_id(x.get_id());
    tempjob.set_transfer(x.get_transfer());
    tempjob.set_withdraw(x.get_withdraw());
    tempjob.set_deposit(x.get_deposit());
    tempjob.set_wealth(x.get_wealth());
    tempjob.set_dtime(x.get_dtime());

    //set up x = y;
    x.set_id(y.get_id());
    x.set_transfer(y.get_transfer());
    x.set_withdraw(y.get_transfer());
    x.set_deposit(y.get_deposit());
    x.set_wealth(y.get_wealth());
    x.set_dtime(y.get_dtime());


    //set up y = temp;
    y.set_id(tempjob.get_id());
    y.set_transfer(tempjob.get_transfer());
    y.set_withdraw(tempjob.get_withdraw());
    y.set_deposit(tempjob.get_deposit());
    y.set_wealth(tempjob.get_wealth());
    y.set_dtime(tempjob.get_dtime());
}

