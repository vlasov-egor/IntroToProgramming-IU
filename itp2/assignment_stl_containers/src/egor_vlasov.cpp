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

    //  operators overloading
    friend bool operator==(Student &lhs, Thing *rhs);
    friend bool operator>=(Student &lhs, Thing *rhs);
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

    //  operators overloading
    friend bool operator==(Car &lhs, Thing *rhs);
    friend bool operator>=(Car &lhs, Thing *rhs);
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

    //  operators overloading
    friend bool operator==(Transformer &lhs, Thing *rhs);
    friend bool operator>=(Transformer &lhs, Thing *rhs);
};

//  operators overloading for student class
bool operator==(Student &lhs, Thing *rhs)
{
    return (lhs.id == rhs->id);
}
bool operator>=(Student &lhs, Thing *rhs)
{
    string right_type;
    Sex right_sex;

    // defining the type of object
    if (Student *student = dynamic_cast<Student *>(rhs))
    {
        right_type = "student";
        right_sex = student->sex;
    }
    else if (Transformer *trans = dynamic_cast<Transformer *>(rhs))
    {
        right_type = "trans";
        right_sex = trans->sex;
    }
    else if (Car *car = dynamic_cast<Car *>(rhs))
    {
        right_type = "car";
    }

    if (right_type == "car" || right_type == "trans")
    {
        return true;
    }
    else if (right_sex == Sex::FEMALE)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//  operators overloading for car class
bool operator==(Car &lhs, Thing *rhs)
{
    return (lhs.id == rhs->id);
}
bool operator>=(Car &lhs, Thing *rhs)
{
    return false;
}

//  operators overloading for transformer class
bool operator==(Transformer &lhs, Thing *rhs)
{
    return (((Person)lhs).id == rhs->id);
}
bool operator>=(Transformer &lhs, Thing *rhs)
{
    string right_type;
    Sex right_sex;

    if (Student *student = dynamic_cast<Student *>(rhs))
    {
        right_type = "student";
        right_sex = student->sex;
    }
    else if (Transformer *trans = dynamic_cast<Transformer *>(rhs))
    {
        right_type = "trans";
        right_sex = trans->sex;
    }
    else if (Car *student = dynamic_cast<Car *>(rhs))
    {
        right_type = "car";
    }

    if (right_type == "car")
    {
        return true;
    }
    else if (right_type == "student")
    {
        return false;
    }
    else if (right_sex == Sex::FEMALE)
    {
        return false;
    }
    else
    {
        return true;
    }
}

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
    for (stack<Thing *> tmp = container; !tmp.empty(); tmp.pop())
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

    for (auto i : boxes_vector)
    {
        cout << i << endl;
    }

    // !Task 2
    list<Thing *> boxes_list;
    stack<Thing *> boxes_stack;

    // copying
    for (auto i : boxes_vector)
    {
        boxes_list.push_back(i);
        boxes_stack.push(i);
    }

    cout << endl;

    cout << "--------" << endl;
    cout << "| LIST |" << endl;
    cout << "--------" << endl;
    cout << endl;

    // cout list
    show_list(boxes_list);

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

    show_list(boxes_list);

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

    show_list(boxes_list);

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

    // !TASK 7
    // boolean predicate function

    return 0;
}
