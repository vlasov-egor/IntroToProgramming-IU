/**
 * @file egor_vlasov.cpp
 * @author Egor Vlasov (e.vlasov@innopolis.university)
 * @date 2021-04-17
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <random>
#include <iterator>

using namespace std;

/**
 * @brief enum with sex for student and transformer classes
 * 
 */
enum Sex
{
    MALE,
    FEMALE
};

// it contains last id of object in list
int lastId = 0;

/**
 * @brief class thing
 * 
 */
class Thing
{
public:
    int id;

    virtual ~Thing() = default;
};

/**
 * @brief class person for 
 * transformer and student classes
 * 
 */
class Person : public Thing
{
public:
    Person(Sex sex)
    {
        //  genering of new id
        id = lastId++;

        //  sex assignment
        this->sex = sex;
    }
    Sex sex;
};

/**
 * @brief class student
 * 
 */
class Student : public Person
{
public:
    //  constructor inheritance
    using Person::Person;
};

/**
 * @brief class car
 * 
 */
class Car : public Thing
{
public:
    Car()
    {
        //  genering of new id
        id = lastId++;
    }
};

/**
 * @brief class transformer
 * 
 */
class Transformer : public Car, public Person
{
public:
    //  constructor inheritance
    Transformer() = delete;
    Transformer(Sex sex) : Person(sex) {}
};

/**
 * @brief << (cout) operator overloading 
 * 
 * @param out 
 * @param o object
 * @return ostream& 
 */
ostream &operator<<(ostream &out, Thing *o)
{
    printf("Id: %02d |", o->id);

    if (Transformer *trans = dynamic_cast<Transformer *>(o))
    {
        out << " Type: Transformer |";
    }
    else if (Student *student = dynamic_cast<Student *>(o))
    {
        out << " Type: Student     |";
    }
    else if (Car *car = dynamic_cast<Car *>(o))
    {
        out << " Type: Car         |";
    }

    if (Person *person = dynamic_cast<Person *>(o))
    {
        if (person->sex == 1)
        {
            out << " Sex: FEMALE";
        }
        else
        {
            out << " Sex: MALE";
        }
    }

    return out;
}

// ITEM 3.d: void show can be used for list, vector and stack because of explicit specialization
// ITEM 3.c: void show can be used for different containers (list, stack, vector)

/**
 * @brief shuffle some container
 * in default case it is list
 * 
 * @tparam list<Thing *> 
 * @param container 
 */
template <class T = list<Thing *>>
void shuffle(T &container)
{
    vector<Thing *> tmp;
    for (auto i : container)
    {
        tmp.push_back(i);
    }

    container = list<Thing *>();

    for (int i = tmp.size() - 1; i > -1; i--)
    {
        int j = rand() % (i + 1);
        auto buffer = tmp[i];
        tmp[i] = tmp[j];
        tmp[j] = buffer;
    }

    for (auto i : tmp)
    {
        container.push_back(i);
    }
}

/**
 * @brief shuffle stack
 * 
 * @tparam  
 * @param container 
 */
template <>
void shuffle<stack<Thing *>>(stack<Thing *> &container)
{
    vector<Thing *> tmp;
    while (!container.empty())
    {
        tmp.push_back(container.top());
        container.pop();
    }

    for (int i = tmp.size() - 1; i > -1; i--)
    {
        int j = rand() % (i + 1);
        auto buffer = tmp[i];
        tmp[i] = tmp[j];
        tmp[j] = buffer;
    }

    for (auto i : tmp)
    {
        container.push(i);
    }
}

// ITEM 3.f: bubble sort on iterators
/**
 * @brief bubble sort
 * 
 * @tparam Iterator 
 * @param begin begin of container
 * @param end end of container
 */
template <class Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    for (Iterator i = begin; i != end; ++i)
    {
        for (Iterator j = begin; j < i; ++j)
        {
            if ((*i)->id < (*j)->id)
                iter_swap(i, j);
        }
    }
}

// ITEM 3.d: void show can be used for list, vector and stack because of explicit specialization
// ITEM 3.c: void show can be used for different containers (list, stack, vector)

/**
 * @brief sorting container
 * in default case it is list
 * 
 * @tparam list<Thing *> 
 * @param container 
 */
template <class T = list<Thing *>>
void sort(T &container)
{
    // copying to vector
    vector<Thing *> tmp;
    for (auto i : container)
    {
        tmp.push_back(i);
    }

    container = list<Thing *>();

    // vector sorting

    // ITEM 3.f: bubble sort on iterators
    bubble_sort(tmp.begin(), tmp.end());

    // stack refilling
    for (auto i : tmp)
    {
        container.push_back(i);
    }
}

/**
 * @brief sorting stack
 * 
 * @tparam  
 * @param container 
 */
template <>
void sort<stack<Thing *>>(stack<Thing *> &container)
{
    // copying to vector
    vector<Thing *> tmp;
    while (!container.empty())
    {
        tmp.push_back(container.top());
        container.pop();
    }

    // vector sorting

    // ITEM 3.f: bubble sort on iterators
    bubble_sort(tmp.begin(), tmp.end());

    // stack refilling
    for (auto i : tmp)
    {
        container.push(i);
    }
}

// ITEM 3.d: void show can be used for list, vector and stack because of explicit specialization
// ITEM 3.c: void show can be used for different containers (list, stack, vector)
/**
 * @brief cout vector 
 * 
 * @tparam vector<Thing *> 
 * @param container 
 */
template <class T = vector<Thing *>>
void show(T &container)
{
    for (auto i : container)
    {
        cout << i << endl;
    }
}

/**
 * @brief cout list
 * 
 * @tparam  
 * @param container 
 */
template <>
void show<list<Thing *>>(list<Thing *> &container)
{
    for (auto i : container)
    {
        cout << i << endl;
    }
}

/**
 * @brief cout stack
 * 
 * @tparam  
 * @param container 
 */
template <>
void show<stack<Thing *>>(stack<Thing *> &container)
{
    for (stack<Thing *> tmp = container; !tmp.empty(); tmp.pop())
        cout << tmp.top() << endl;
}

// ITEM 3.g:
/**
 * @brief predicate function for choosing only male things from vector
 * 
 * @param thing object
 * @return true if male
 * @return false if female
 */
bool predicate_func(Thing *thing)
{
    if (Transformer *trans = dynamic_cast<Transformer *>(thing))
    {
        return trans->sex == Sex::MALE;
    }
    else if (Student *student = dynamic_cast<Student *>(thing))
    {
        return student->sex == Sex::MALE;
    }

    return false;
}

/**
 * @brief converting vector to list
 * 
 * @tparam size size of original list
 * @tparam T objects in vector
 * @param v original vector
 * @return list<T> list
 */
template <int size, class T>
list<T> toList(vector<T> &v)
{
    list<T> res(size, 0);
    for (auto i : v)
    {
        res.push_back(i);
    }

    return res;
}

/**
 * @brief converting vector to stack
 * 
 * @tparam T objects in vector
 * @param v original vector
 * @return stack<T> stack
 */
template <class T>
stack<T> toStack(vector<T> &v)
{
    stack<T> res;
    for (auto i : v)
    {
        res.push(i);
    }

    return res;
}

int main(int argc, char const *argv[])
{

    // !Task 1
    vector<Thing *> boxes_vector;

    // random genering
    Sex cur_sex = Sex::MALE;
    for (int i = 0; i < 10; i++)
    {

        if (i % 2)
        {
            cur_sex = Sex::FEMALE;
        }
        else
        {
            cur_sex = Sex::MALE;
        }

        auto car = new Car();
        auto student = new Student(cur_sex);
        auto trans = new Transformer(cur_sex);

        boxes_vector.push_back(car);
        boxes_vector.push_back(student);
        boxes_vector.push_back((Car *)trans);
    }

    cout << "\033[1;31m----------\033[0m" << endl;
    cout << "\033[1;31m| VECTOR |\033[0m" << endl;
    cout << "\033[1;31m----------\033[0m" << endl;
    cout << endl;

    show(boxes_vector);

    cout << endl;

    // !Task 2

    // ITEM 3.e: type of object that returns func toList is a type of boxes_list
    // ITEM 3.b: this sets the size of the original vector in void
    decltype(toList<0>(boxes_vector)) boxes_list = toList<0>(boxes_vector);

    stack<Thing *> boxes_stack = toStack(boxes_vector);

    cout << "\033[1;32m--------\033[0m" << endl;
    cout << "\033[1;32m| LIST |\033[0m" << endl;
    cout << "\033[1;32m--------\033[0m" << endl;
    cout << endl;

    // cout list
    show(boxes_list);

    cout << endl;

    // cout stack
    cout << "\033[1;34m---------\033[0m" << endl;
    cout << "\033[1;34m| STACK |\033[0m" << endl;
    cout << "\033[1;34m---------\033[0m" << endl;
    cout << endl;

    show(boxes_stack);
    cout << endl;

    // !Task 3
    ::shuffle(boxes_stack);
    ::shuffle(boxes_list);

    // cout shuffled list
    cout << "\033[1;32m-----------------\033[0m" << endl;
    cout << "\033[1;32m| SHUFFLED LIST |\033[0m" << endl;
    cout << "\033[1;32m-----------------\033[0m" << endl;
    cout << endl;

    show(boxes_list);

    cout << endl;

    // cout shuffled stack
    cout << "\033[1;34m------------------\033[0m" << endl;
    cout << "\033[1;34m| SHUFFLED STACK |\033[0m" << endl;
    cout << "\033[1;34m------------------\033[0m" << endl;
    cout << endl;

    show(boxes_stack);

    cout << endl;

    // !TASK 4
    ::sort(boxes_stack);
    ::sort(boxes_list);

    // cout sorted list
    cout << "\033[1;32m---------------\033[0m" << endl;
    cout << "\033[1;32m| SORTED LIST |\033[0m" << endl;
    cout << "\033[1;32m---------------\033[0m" << endl;
    cout << endl;

    show(boxes_list);

    cout << endl;

    // cout sorted stack
    cout << "\033[1;34m----------------\033[0m" << endl;
    cout << "\033[1;34m| SORTED STACK |\033[0m" << endl;
    cout << "\033[1;34m----------------\033[0m" << endl;
    cout << endl;

    show(boxes_stack);

    cout << endl;

    // !TASK 6
    cout << "\033[1;36mHIGHEST THING IN LIST: \033[0m" << endl
         << boxes_list.back() << endl;
    cout << "\033[1;36mHIGHEST THING IN STACK: \033[0m" << endl
         << boxes_stack.top() << endl;

    cout << endl;

    // !TASK 7

    // boolean predicate function

    // ITEM 3.g:
    vector<Thing *> filtered_boxes;
    copy_if(boxes_list.begin(), boxes_list.end(), back_inserter(filtered_boxes), predicate_func);

    // cout sorted vector
    cout << "\033[1;31m-----------------\033[0m" << endl;
    cout << "\033[1;31m| SORTED VECTOR |\033[0m" << endl;
    cout << "\033[1;31m-----------------\033[0m" << endl;
    cout << endl;

    show(filtered_boxes);

    return 0;
}
