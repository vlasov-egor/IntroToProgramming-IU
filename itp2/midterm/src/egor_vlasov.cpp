/**
 * @file egor_vlasov.cpp
 * @author Egor Vlasov (e.vlasov@innopolis.university)
 * @date 2021-03-14
 * 
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief enum for student and transformer classes
 * 
 */
enum Sex
{
    MALE,
    FEMALE
};

// it contains last id of object in box
int lastId = 0;

/**
 * @brief the main class
 * 
 */
class Thing
{
public:
    int id;

    //  ITEM 3.d
    virtual ~Thing() = default;
};

/**
 * @brief class person
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
 * @brief class Student
 * 
 */
class Student : public Person
{
public:
    //  constructor inheritance
    using Person::Person;

    //  operators overloading
    //  ITEM 3.f
    friend bool operator==(Student &lhs, Thing *rhs);
    friend bool operator>=(Student &lhs, Thing *rhs);
};

/**
 * @brief class Car
 * 
 */
class Car : public Thing
{
public:
    //  ITEM 3.d
    Car()
    {
        //  genering of new id
        id = lastId++;
    }

    //  operators overloading
    friend bool operator==(Car &lhs, Thing *rhs);
    friend bool operator>=(Car &lhs, Thing *rhs);
};

class Transformer : public Car, public Person
{
public:
    //  ITEM 3.d
    //  ITEM 3.b
    //  ITEM 3.k
    //  constructor inheritance
    Transformer() = delete;
    Transformer(Sex sex) : Person(sex) {}

    //  operators overloading
    friend bool operator==(Transformer &lhs, Thing *rhs);
    friend bool operator>=(Transformer &lhs, Thing *rhs);
};

//  operators overloading for Student class
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

//  operators overloading for Car class
bool operator==(Car &lhs, Thing *rhs)
{
    return (lhs.id == rhs->id);
}
bool operator>=(Car &lhs, Thing *rhs)
{
    return false;
}

//  operators overloading for Transformer class
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
 * @brief Node for SinglyLinkedlist
 * 
 * @tparam T 
 */
template <class T>
class Node
{
public:
    T data;
    Node<T> *next_node;
};

/**
 * @brief interface of SinglyLinkedList
 * 
 * @tparam T 
 */
//  ITEM 3.o
template <class T>
class SinglyLinkedListADT
{
public:
    //  ITEM 3.j
    virtual void add(T item) = 0;
    virtual T least() = 0;
    virtual T greatest() = 0;
    virtual T get(int i) = 0;
    virtual void remove(int i) = 0;
    virtual Node<T> *getHead() = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

/**
 * @brief SinglyLinkedList
 * 
 * @tparam T 
 */
template <class T>
class SinglyLinkedList : SinglyLinkedListADT<T>
{
    //  ITEM 3.e
private:
    int len = 0;
    Node<T> *head = NULL;
    Node<T> *tail = NULL;

public:
    /**
     * @brief adding element to the begining of the list
     * 
     * @param item some item for adding
     */
    void add(T item)
    {

        Node<T> *new_node = new Node<T>();
        new_node->data = item;
        Node<T> *current = head;

        if (!head)
        {
            // empty list
            head = new_node;
            tail = new_node;
        }
        else
        {
            //  adding in begining

            new_node->next_node = head;
            head = new_node;
        }

        len++;
    }

    /**
     * @brief adding element to the end of the list
     * 
     * @param item some item for adding
     */
    void addLast(T item)
    {
        Node<T> *new_node = new Node<T>();
        new_node->data = item;

        if (!head)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next_node = new_node;
            tail = new_node;
        }

        len++;
    }

    /**
     * @brief returns the smallest element
     * 
     * @return T smallest element
     */
    T least()
    {
        return head->data;
    }

    /**
     * @brief returns the greatest element
     * 
     * @return T greatest element
     */
    T greatest()
    {
        return tail->data;
    }

    /**
     * @brief getting element by index
     * 
     * @param i index
     * @return T element with index i
     */
    T get(int i)
    {
        Node<T> *current = head;
        for (int j = 0; j < i; j++)
        {
            current = current->next_node;
        }

        return current->data;
    }

    /**
     * @brief check if there exists element item
     * 
     * @param item element
     * @return true if there exists item
     * @return false if there not exists item
     */
    bool has(T item)
    {
        if (size() == 0)
        {
            return false;
        }

        Node<T> *current = head;
        while (current)
        {
            if (current->data == item)
            {
                return true;
            }

            current = current->next_node;
        }

        return false;
    }

    /**
     * @brief removing of element by index
     * 
     * @param i index
     */
    void remove(int i)
    {
        if (i < this->size())
        {
            Node<T> *current = head;
            Node<T> *prev = head;

            for (int j = 0; j < i; ++j)
            {
                prev = current;
                current = current->next_node;
            }

            prev->next_node = current->next_node;

            len--;
        }
    }

    /**
     * @brief remove element which is equal to item
     * 
     * @param item some element
     */
    void removeItem(T item)
    {
        if (item == head->data)
        {
            head = head->next_node;
            // cout << "ЮХУ -3" << endl;
            return;
        }

        Node<T> *current = head;
        Node<T> *prev = head;
        while (current->data != item)
        {
            prev = current;
            current = current->next_node;
        }

        prev->next_node = current->next_node;
    }

    /**
     * @brief Get the Head object
     * 
     * @return Node<T>* head element
     */
    Node<T> *getHead()
    {
        return head;
    }

    /**
     * @brief Get the Head Ref object
     * 
     * @return Node<T>** head ref object
     */
    Node<T> **getHeadRef()
    {
        return &head;
    }

    /**
     * @brief Get the Tail object
     * 
     * @return Node<T>* 
     */
    Node<T> *getTail()
    {
        return tail;
    }

    /**
     * @brief Get the Tail Ref object
     * 
     * @return Node<T>** 
     */
    Node<T> **getTailRef()
    {
        return &tail;
    }

    void recalculateTail()
    {
        auto cur = head;
        while (cur->next_node != NULL)
            cur = cur->next_node;

        tail = cur;
    }

    /**
 * @brief returns size of list
 * 
 * @return int size
 */
    int size()
    {
        return len;
    }

    /**
     * @brief checking emptiness of list
     * 
     * @return true if empty
     * @return false if not
     */
    bool isEmpty()
    {
        return head ? true : false;
    }
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

    out << endl;

    return out;
}

/**
 * @brief Split function for merge sort
 * 
 * it split list for 2 parts for Merge Sort
 * 
 * @tparam T 
 * @param source original
 * @param front 1 part
 * @param back 2 part
 */
template <class T>
void Split(Node<T> *source,
           Node<T> **front, Node<T> **back)
{
    Node<T> *fast;
    Node<T> *slow;
    slow = source;
    fast = source->next_node;

    while (fast != NULL)
    {
        fast = fast->next_node;
        if (fast != NULL)
        {
            slow = slow->next_node;
            fast = fast->next_node;
        }
    }

    *front = source;
    *back = slow->next_node;
    slow->next_node = NULL;
}

/**
 * @brief Merge Sort
 * 
 * @tparam T 
 * @param head first element of list
 */
template <class T>
void mergeSort(Node<T> **head)
{
    Node<T> *headRef = *head;
    Node<T> *a;
    Node<T> *b;

    // if in list only 0 or 1 element
    if ((headRef == NULL) || (headRef->next_node == NULL))
    {
        return;
    }

    Split(headRef, &a, &b);

    // recursive
    mergeSort(&a);
    mergeSort(&b);

    *head = MergeSorted(a, b);
}

// ITEM 3.c
//  ITEM 3.k
/**
 * @brief function for comparing 2 Things objects
 * 
 * @param a 1 object
 * @param b 2 object
 * @return true 
 * @return false 
 */
const bool compare(Thing *a, Thing *b)
{
    // for Transformers
    if (Transformer *trans = dynamic_cast<Transformer *>(a))
    {
        return (Transformer &)trans >= b;
    }
    // for Students
    else if (Student *student = dynamic_cast<Student *>(a))
    {
        return (Student &)student >= b;
    }
    // for Cars
    else if (Car *car = dynamic_cast<Car *>(a))
    {
        return (Car &)car >= b;
    }
}

/**
 * @brief it merges 2 sorted parts in 1
 * 
 * @tparam T 
 * @param a 1 part
 * @param b 2 part
 * @return Node<T>* merged list
 */
template <class T>
Node<T> *MergeSorted(Node<T> *a, Node<T> *b)
{
    Node<T> *result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (compare(a->data, b->data))
    {
        result = a;
        result->next_node = MergeSorted(a->next_node, b);
    }
    else
    {
        result = b;
        result->next_node = MergeSorted(a, b->next_node);
    }
    return (result);
}

/**
 * @brief Get the Tail Of List object
 * 
 * @param cur 
 * @return Node<T>* 
 */
template <class T>
Node<T> *getTailOfList(Node<T> *cur)
{
    while (cur->next_node != NULL)
        cur = cur->next_node;
    return cur;
}

/**
 * @brief Partitions the list
 * 
 * @tparam T 
 * @param head begining of list
 * @param end ending of list
 * @param newHead 
 * @param newEnd 
 * @return Node<T>* 
 */
template <class T>
Node<T> *partition(Node<T> *head, Node<T> *end,
                   Node<T> **newHead,
                   Node<T> **newEnd)
{
    Node<T> *pivot = end;
    Node<T> *prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        if (compare(cur->data, pivot->data))
        {
            // First node with value <= than the pivot - new head
            if ((*newHead) == NULL)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next_node;
        }
        else
        {
            if (prev)
                prev->next_node = cur->next_node;
            Node<T> *tmp = cur->next_node;
            cur->next_node = NULL;
            tail->next_node = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}

/**
 * @brief Reccurence sorting without last element
 * 
 * @tparam T 
 * @param head begining of list
 * @param end ending of list
 * @return Node<T>* 
 */
template <class T>
Node<T> *quickSortReccurence(Node<T> *head,
                             Node<T> *end)
{
    // if there only 0 or 1 element
    if (!head || head == end)
        return head;

    Node<T> *newHead = NULL, *newEnd = NULL;

    Node<T> *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        // make Node before the pivot NULL
        Node<T> *tmp = newHead;
        while (tmp->next_node != pivot)
        {
            tmp = tmp->next_node;
        }

        tmp->next_node = NULL;

        // Reccurence for the list before pivot
        newHead = quickSortReccurence(newHead, tmp);

        // last node of the left half -> to pivot
        tmp = getTailOfList(newHead);
        tmp->next_node = pivot;
    }

    // Reccurence for the list after the pivot element
    pivot->next_node = quickSortReccurence(pivot->next_node, newEnd);

    return newHead;
}

/**
 * @brief quick sort
 * 
 * @tparam T 
 * @param headRef begining of list
 */
template <class T>
void quickSort(Node<T> **headRef, Node<T> **tailRef)
{
    (*headRef) = quickSortReccurence(*headRef, *tailRef);
    return;
}

// main function
int main(int argc, char const *argv[])
{
    // !TASK 0.1
    auto boxes = new SinglyLinkedList<Thing *>();

    // random genering
    srand(time(0));
    for (int i = 0; i < 30; i++)
    {
        if (rand() % 5 == 0)
        {
            auto car1 = new Car();
            boxes->add(car1);
        }
        else if (rand() % 5 == 1)
        {
            auto student1 = new Student(Sex::MALE);
            boxes->add(student1);
        }
        else if (rand() % 5 == 2)
        {
            auto student2 = new Student(Sex::FEMALE);
            boxes->add(student2);
        }
        else if (rand() % 5 == 3)
        {
            auto transformer1 = new Transformer(Sex::FEMALE);
            boxes->add((Person *)transformer1);
        }
        else if (rand() % 5 == 4)
        {
            auto transformer2 = new Transformer(Sex::MALE);
            boxes->add((Person *)transformer2);
        }
    }

    // printing

    cout << "---------------" << endl;
    cout << "| RANDOM LIST |" << endl;
    cout << "---------------" << endl;
    cout << endl;

    for (int i = 0; i < boxes->size(); ++i)
    {
        cout << boxes->get(i);
    }

    cout << endl;

    // !TASK 0.2
    // merge sorting
    mergeSort<Thing *>(boxes->getHeadRef());

    // !TASK 0.3
    // printing

    cout << "--------------" << endl;
    cout << "| MERGE SORT |" << endl;
    cout << "--------------" << endl;
    cout << endl;

    for (int i = 0; i < boxes->size(); ++i)
    {
        cout << boxes->get(i);
    }

    cout << endl;

    boxes->recalculateTail();

    cout << endl;

    // !TASK 0.4
    // scrambling
    int in_size = boxes->size();
    for (int i = 0; i < in_size; i++)
    {
        int rr = rand() % (in_size - 2) + 1;
        auto tmp = boxes->get(boxes->size() - rr);
        boxes->remove(boxes->size() - rr);
        boxes->add(tmp);
    }

    boxes->recalculateTail();

    // printing

    cout << "------------------" << endl;
    cout << "| SCRAMBLED LIST |" << endl;
    cout << "------------------" << endl;
    cout << endl;

    for (int i = 0; i < boxes->size(); ++i)
    {
        cout << boxes->get(i);
    }

    cout << endl;

    // !TASK 0.5

    // quick sort
    quickSort<Thing *>(boxes->getHeadRef(), boxes->getTailRef());

    // printing

    cout << "--------------" << endl;
    cout << "| QUICK SORT |" << endl;
    cout << "--------------" << endl;
    cout << endl;

    for (int i = 0; i < boxes->size(); ++i)
    {
        cout << boxes->get(i);
    }

    cout << endl;
}
