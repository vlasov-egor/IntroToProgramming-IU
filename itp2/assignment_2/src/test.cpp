#include <iostream>
#include <tuple>
#include <thread>
#include <chrono>

using namespace std;

int main(int argc, char const *argv[])
{
    tuple<int, string> a(1, "sdasda");
    cout << get<0>(a) << endl;
    return 0;
}
