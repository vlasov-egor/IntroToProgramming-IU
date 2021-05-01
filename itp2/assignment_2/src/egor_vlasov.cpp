/**
 * @file egor_vlasov.cpp
 * @author Egor Vlasov (e.vlasov@innopolis.university)
 * @brief implementation of two-dimensionalworld in which two players control units 
 * that battle to take each other’s flag. 
 * 
 */

#include <iostream>
#include <tuple>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono_literals;

const int TIMEOUT = 400; // maximum number of milliseconds that a player is allowed to take

// it contains last id of object in list
int lastId = 0;

class Position
{
public:
    std::tuple<int, int> pos;
    // TODO Implement the operator == and other operators if necessary
};

class Thing
{
public:
    int id; // ?I don't know for what, but let's it will be there
    Position position;

    Thing(int position_x, int position_y)
    {
        this->id = lastId++;
        position.pos = make_tuple(position_x, position_y);
    }
};
class SmallScissors : public Thing
{
};

class CapitalScissors : public Thing
{
};

class SmallRock : public Thing
{
};

class CapitalRock : public Thing
{
};

class SmallPaper : public Thing
{
};

class CapitalPaper : public Thing
{
};

class Flag : public Thing
{
};

class Mountain : public Thing
{
};
class World
{
    // TODO Create a container of smart pointers of units and flags of player 0
    // TODO Create a container of smart pointers of units and flags of player 1
    // TODO Create a container of smart pointers of mountains

public:
    vector<vector<Position>> world;
};

class Action
{
    Position from; // current row, column of the unit to be moved
    Position to;   // position to where the unit must be moved
};

Action actionPlayerZero(const World world)
{
    // TODO Implement some basic strategy and remove the lines below
    std::cout << "actionPlayerZero()" << endl;
    std::this_thread::sleep_for(385ms); // 0.4 seconds
}

Action actionPlayerOne(const World world)
{
    // TODO Implement some basic strategy and remove the lines below
    std::cout << "actionPlayerOne()" << endl;
    std::this_thread::sleep_for(385ms); // 0.4 seconds
}

/**
 * The return is a pair: action and a boolean whether a timeout happened
 */
std::tuple<Action, bool> waitPlayer(Action (*f)(World), World world)
{
    auto start = std::chrono::high_resolution_clock::now();
    // TODO Important. Below, action should be the result of calling the function passed as parameter
    Action action;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    // TODO This line can be removed
    std::cout << "Waited " << elapsed.count() << " ms\n";
    if (elapsed.count() > TIMEOUT) // if time > 0.3 s
        return {action, true};     // player failed to answer in less than 400 ms
    else
        return {action, false};
}

int main()
{
    World world;
    // TODO Initialize the world
    bool endGame = false;
    while (!endGame)
    {
        auto [action0, timeout0] = waitPlayer(actionPlayerZero, world);
        auto [action1, timeout1] = waitPlayer(actionPlayerOne, world);
        if (timeout0 || timeout1)
        {
            endGame = true;
            // TODO Show the result of the game. Who caused the timeout?
        }
        else
        {
            // TODO Validate the actions: actionPlayer0 and actionPlayer1
            // TODO Update the world
            // TODO Show the world
            // TODO End the game and show the result if a player won
        }
    }
    return 0;
}