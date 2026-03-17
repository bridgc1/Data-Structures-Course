#include <iostream>
#include <chrono> //time measurements
using namespace std;

int main()
{
        chrono::time_point<std::chrono::steady_clock> start, end;
        // also in std library: system_clock, monotonic_clock, steady_clock
        chrono::duration<double, std::milli> elapsedTime; // time diference variable
        //number: count  number of milliseconds in double format for us to print and analyze

        start = chrono::steady_clock::now(); //take a time stamp right now from the steady clock source
        int n = 0;
        for (int i = 0; i < 5; i++)
        {
            n++;
        }

        end = chrono::steady_clock::now();

        elapsedTime = end - start;

        cout << "Example under test: " << elapsedTime.count() << "ms" << endl;
}