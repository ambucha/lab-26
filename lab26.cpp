// COMSC-210 | Lab 26 | Andrei Buchatskiy
// IDE used : Visual Studio Code

#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;
using namespace std::chrono;

// sizes plus the column for output sizes (now add for ammount of runs, number of operation types, and number of data structures)
const int RUNS = 15;
const int OP = 4;
const int DATA = 3;
const int SIZE = 20000; 
const int width = 12;

// i need to add some variables for the operator and data structure indices, so im not just typing diret numbers in the main
const int READ = 0;
const int SORT = 1;
const int INSERT = 2;
const int DELETE = 3;

const int VEC = 0;
const int LIST = 1;
const int SET = 2;

// set up a designated const int for the sum index
const int SUM = 15;

int main() {
    // 3d array for results
    // first is the runs, which is +1 because i have the fifteen runs, and then in the last i will store the sum
    // second is the number of different operators
    // third is number of different data structures

    // i think i need this variable to be long long for the duration_cast 
    long long results[RUNS + 1][OP][DATA] = {0};

    // set up the loop to run each operation 15 times
    for(int i = 0; i < RUNS;i++){
        // gonna start with the reading race
        set<string> s;
        list<string> l;
        vector<string> v;
        string code;

        auto start = high_resolution_clock::now();
        ifstream fin("codes.txt");

        // loop through the file and add each string code to the vector
        while(getline(fin, code)){
            v.push_back(code);
        }
        fin.close();
        auto end = high_resolution_clock::now();

        // add the variable for vectorRead time in microseconds
        // nevermind i j needed to make this a .count()
        results[i][READ][VEC] = duration_cast<microseconds>(end - start).count();
        // add the new result to the sum of results
        results[SUM][READ][VEC] += results[i][READ][VEC];

        // now read for the list
        start = high_resolution_clock::now();
        fin.open("codes.txt");

        // loop through the file and add each string to the list
        while(getline(fin, code)){
            l.push_back(code);
        }
        fin.close();

        end = high_resolution_clock::now();
        // add the variable for listRead time in microseconds
        results[i][READ][LIST] = duration_cast<microseconds>(end - start).count();
        results[SUM][READ][LIST] += results[i][READ][LIST];

        // now read for the set
        start = high_resolution_clock::now();
        fin.open("codes.txt");

        // loop through the file and add each string to the list
        while(getline(fin, code)){
            s.insert(code);
        }
        fin.close();

        end = high_resolution_clock::now();
        // add the variable for setRead time in microseconds
        results[i][READ][SET] = duration_cast<microseconds>(end - start).count();
        results[SUM][READ][SET] += results[i][READ][SET];

        // sorting time
        start = high_resolution_clock::now();

        // just use sort for vector sorting
        sort(v.begin(), v.end());
        end = high_resolution_clock::now();
        results[i][SORT][VEC] = duration_cast<microseconds>(end - start).count();
        results[SUM][SORT][VEC] += results[i][SORT][VEC];

        // list sorting time
        start = high_resolution_clock::now();
        l.sort();
        end = high_resolution_clock::now();
        results[i][SORT][LIST] = duration_cast<microseconds>(end - start).count();
        results[SUM][SORT][LIST] += results[i][SORT][LIST];

        // just set the set sort to -1 since its auto sorted
        results[i][SORT][SET] = -1;
        results[SUM][SORT][SET] += results[i][SORT][SET];

        string test = "69lol";

        start = high_resolution_clock::now();
        // i need to insert it into the middle of the vector
        v.insert(v.begin() + (v.size() / 2), test);
        end = high_resolution_clock::now();
        results[i][INSERT][VEC] = duration_cast<microseconds>(end - start).count();
        results[SUM][INSERT][VEC] += results[i][INSERT][VEC];

        //list insert time
        start = high_resolution_clock::now();

        // loop till ur in the middle of the list
        auto it = l.begin();
        int mid = l.size() / 2;
        for(int i = 0; i < mid; i++) {
            it++;
        }

        // insert in the mid point
        l.insert(it, test);
        end = high_resolution_clock::now();
        results[i][INSERT][LIST] = duration_cast<microseconds>(end - start).count();
        results[SUM][INSERT][LIST] += results[i][INSERT][LIST];

        // set insert now
        start = high_resolution_clock::now();
        
        // just insert the test in it will sort for you, cant put it in the middle
        s.insert(test);
        end = high_resolution_clock::now();
        auto setInsert = duration_cast<microseconds>(end - start);

        // deleting time
        start = high_resolution_clock::now();

        // delete the middle ish element in the vector
        v.erase(v.begin() + (v.size() / 2));
        end = high_resolution_clock::now();
        auto vectorDelete = duration_cast<microseconds>(end - start);

        // list deleting
        start = high_resolution_clock::now();

        // go through till middle element then delete
        it = l.begin();
        mid = l.size() / 2;
        for(int i = 0; i < mid; i++) {
            it++;
        }
        l.erase(it);
        
        end = high_resolution_clock::now();
        auto listDelete = duration_cast<microseconds>(end - start);

        //set delete
        start = high_resolution_clock::now();

        // similar to list delete
        auto itS = s.begin();
        mid = s.size() / 2;

        for(int i = 0; i < mid; i++){
            itS++;
        }
        s.erase(itS);

        end = high_resolution_clock::now();
        auto setDelete = duration_cast<microseconds>(end - start);
    }

    // displays
    cout << right << setw(width) << "Operation" << setw(width) << "Vector" << setw(width) << "List" << setw(width) << "Set" << endl;
    cout << right << setw(width) << "Read" << setw(width) << vectorRead.count() << setw(width) << listRead.count() << setw(width) << setRead.count() << endl;
    cout << right << setw(width) << "Sort" << setw(width) << vectorSort.count() << setw(width) << listSort.count() << setw(width) << setSort << endl;
    cout << right << setw(width) << "Insert" << setw(width) << vectorInsert.count() << setw(width) << listInsert.count() << setw(width) << setInsert.count() << endl;
    cout << right << setw(width) << "Delete" << setw(width) << vectorDelete.count() << setw(width) << listDelete.count() << setw(width) << setDelete.count() << endl;

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/