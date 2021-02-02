#include <bits/stdc++.h>

using namespace std;
/* 
input text:
n // size of array n x n
a1 a2 ... an
b1 b2 ... bn
...
...
*/

/*
    reading array

    @param n: size of array
    @param arr: array n x n 
*/
void read_array(int n, int ***arr)
{
    *arr = new int *[n]; //  array init
    for (int i = 0; i < n; i++)
    {
        (*arr)[i] = new int[n]; //  init of new row in array
        for (int j = 0; j < n; j++)
        {
            cin >> (*arr)[i][j]; //  reading
        }
    }
}

/* 
    printing array

    @param n: size of array
    @param arr: array n x n 
*/
void print_array(int n, int ***arr)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << (*arr)[i][j] << " "; //  printing
        }
        cout << "\n"; //  divider between rows
    }
}

int main(int argc, char const *argv[])
{
    //  reading size
    int n;
    cin >> n;

    // array iniy
    int **arr;

    // reading
    read_array(n, &arr);

    // printing
    print_array(n, &arr);
    return 0;
}
