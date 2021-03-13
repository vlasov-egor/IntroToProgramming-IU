#include <iostream>
#include <string>

template <class T>
class SinglyLinkedListADT
{
public:
    virtual void add(T item) = 0;
    virtual T least() = 0;
    virtual T greatest() = 0;
    virtual T get(int i) = 0;
    virtual int indexOf(T item) = 0;
    virtual void remove(int i) = 0;
    virtual SortedList<T> *searchRange(T from, T to) = 0;
    virtual Node<T> *getHead() = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

template <class T>
class SinglyLinkedList : SinglyLinkedListADT<T>
{
private:
    int len = 0;
    Node<T> *head = NULL;
    Node<T> *tail = NULL;

public:
    /**
     * @brief adding element to list
     * 
     * @param item some element
     */
    void add(T item)
    {
        if (!has(item))
        {

            Node<T> *new_node = new Node<T>();
            new_node->data = item;
            Node<T> *current = head;

            // empty list
            if (!head)
            {
                head = new_node;
                tail = new_node;
            }
            //  adding in begining
            else if (new_node->data <= head->data)
            {
                new_node->next_node = head;
                head = new_node;
            }
            else
            // adding in some place(sorting)
            {
                while (current->next_node != NULL && current->next_node->data <= new_node->data)
                {
                    current = current->next_node;
                }
                new_node->next_node = current->next_node;
                current->next_node = new_node;

                if (current == tail)
                {
                    tail = new_node;
                }
            }

            len++;
        }
    }

    /**
     * @brief adding element to the end
     * 
     * @param item some element
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
        for (int j = 0; j <= i; j++)
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
        Node<T> *current = head;
        Node<T> *prev = head;

        for (int j = 0; j <= i; ++j)
        {
            prev = current;
            current = current->next_node;
        }

        prev->next_node = current->next_node;
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
     * @brief search range in list from <from> to <to>
     * 
     * @param from lower bound
     * @param to upper bound
     * @return SortedList<T>* neww list with that range
     */
    SortedList<T> *searchRange(T from, T to)
    {
        auto List = new SinglyLinkedSortedList<T>();

        Node<T> *current = head;

        for (; current->data < from; current = current->next_node)
            ;
        for (; current && current->data <= to; current = current->next_node)
        {
            List->addLast(current->data);
            // cout << current->data << endl;
        }

        return List;
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

template <class T>
class Node
{
    T things;
    T Sex;
    Node<T> *next_node;
};

using namespace std;
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
