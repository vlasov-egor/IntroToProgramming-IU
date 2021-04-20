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

template <class T>
void shuffle_stack(stack<T> &container)
{
    vector<T> tmp;
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

template <class T>
void shuffle_list(list<T> &container)
{
    vector<T> tmp;
    for (auto i : container)
    {
        tmp.push_back(i);
    }

    container = list<T>();

    T buffer;
    for (int i = tmp.size() - 1; i > -1; i--)
    {
        int j = rand() % (i + 1);
        buffer = tmp[i];
        tmp[i] = tmp[j];
        tmp[j] = buffer;
    }

    for (auto i : tmp)
    {
        container.push_back(i);
    }
}

template <class T>
void sort_stack(stack<T> &container)
{
    // copying to vector
    vector<T> tmp;
    while (!container.empty())
    {
        tmp.push_back(container.top());
        container.pop();
    }

    // vector sorting
    for (int i = 0; i < tmp.size() - 1; i++)
    {
        for (int j = i + 1; j < tmp.size(); j++)
        {

            if (tmp[i]->id > tmp[j]->id)
            {
                auto buffer = tmp[j];
                tmp[j] = tmp[i];
                tmp[i] = buffer;
            }
        }
    }

    // stack refilling
    for (auto i : tmp)
    {
        container.push(i);
    }
}

template <class T>
void sort_list(list<T> &container)
{
    // copying to vector
    vector<T> tmp;
    for (auto i : container)
    {
        tmp.push_back(i);
    }

    container = list<T>();

    // vector sorting
    for (int i = 0; i < tmp.size() - 1; i++)
    {
        for (int j = i + 1; j < tmp.size(); j++)
        {
            if (tmp[i]->id > tmp[j]->id)
            {
                auto buffer = tmp[j];
                tmp[j] = tmp[i];
                tmp[i] = buffer;
            }
        }
    }

    // stack refilling
    for (auto i : tmp)
    {
        container.push_back(i);
    }
}

template <class T>
void show_stack(stack<T> &container)
{
    for (stack<T> tmp = container; !tmp.empty(); tmp.pop())
        cout << tmp.top() << endl;
}

// ITEM 3.c: use for list and vector
template <typename... E, template <typename...> class T>
void show_array(T<E...> &container)
{
    for (auto i : container)
    {
        cout << i << endl;
    }
}

// ITEM 3.g:
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

    cout << "----------" << endl;
    cout << "| VECTOR |" << endl;
    cout << "----------" << endl;
    cout << endl;

    show_array(boxes_vector);

    cout << endl;

    // !Task 2

    // ITEM 3.e: type of object that returns func toList is a type of boxes_list
    // ITEM 3.b: this sets the size of the original vector in void
    decltype(toList<0>(boxes_vector)) boxes_list = toList<0>(boxes_vector);

    stack<Thing *> boxes_stack = toStack(boxes_vector);

    cout << "--------" << endl;
    cout << "| LIST |" << endl;
    cout << "--------" << endl;
    cout << endl;

    // cout list
    show_array(boxes_list);

    cout << endl;

    // cout stack
    cout << "---------" << endl;
    cout << "| STACK |" << endl;
    cout << "---------" << endl;
    cout << endl;

    show_stack(boxes_stack);
    cout << endl;

    // !Task 3
    shuffle_stack(boxes_stack);
    shuffle_list(boxes_list);

    // cout shuffled list
    cout << "-----------------" << endl;
    cout << "| SHUFFLED LIST |" << endl;
    cout << "-----------------" << endl;
    cout << endl;

    show_array(boxes_list);

    cout << endl;

    // cout shuffled stack
    cout << "------------------" << endl;
    cout << "| SHUFFLED STACK |" << endl;
    cout << "------------------" << endl;
    cout << endl;

    show_stack(boxes_stack);

    cout << endl;

    // !TASK 4
    sort_stack(boxes_stack);
    sort_list(boxes_list);

    // cout sorted list
    cout << "---------------" << endl;
    cout << "| SORTED LIST |" << endl;
    cout << "---------------" << endl;
    cout << endl;

    show_array(boxes_list);

    cout << endl;

    // cout sorted stack
    cout << "----------------" << endl;
    cout << "| SORTED STACK |" << endl;
    cout << "----------------" << endl;
    cout << endl;

    show_stack(boxes_stack);

    cout << endl;

    // !TASK 6
    cout << "HIGHEST THING IN LIST: " << endl
         << boxes_list.back() << endl;
    cout << "HIGHEST THING IN STACK: " << endl
         << boxes_stack.top() << endl;

    cout << endl;

    // !TASK 7

    // boolean predicate function

    // ITEM 3.g:
    vector<Thing *> filtered_boxes;
    copy_if(boxes_list.begin(), boxes_list.end(), back_inserter(filtered_boxes), predicate_func);

    // cout sorted vector
    cout << "-----------------" << endl;
    cout << "| SORTED VECTOR |" << endl;
    cout << "-----------------" << endl;
    cout << endl;

    show_array(filtered_boxes);

    return 0;
}
