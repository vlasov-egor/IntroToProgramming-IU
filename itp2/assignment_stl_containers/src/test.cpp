
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <random>
using namespace std;

template <class T>
void show_stack(stack<T> &container)
{
    for (stack<T> tmp = container; !tmp.empty(); tmp.pop())
        cout << tmp.top() << endl;
}

template <class T>
void show_list(list<T> &container)
{
    for (auto i : container)
    {
        cout << i << endl;
    }
}

template <typename... E, template <typename...> class T>
void show(T<E...> &container)
{
    if (typeid(container).name() == typeid(stack<E...>).name())
    {
        for (stack<E...> tmp = container; !tmp.empty(); tmp.pop())
            cout << tmp.top() << endl;
    }
    else
    {
        for (auto i : container)
        {
            cout << i << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    vector<int> a = {1,
                     2,
                     3,
                     4,
                     5,
                     6};

    list<int> b = {1,
                   2,
                   3,
                   4,
                   5,
                   6};

    stack<int> c;
    for (int i = 0; i < 10; i++)
    {
        c.push(i);
    }

    show(c);
}
