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
#include <memory>
#include <algorithm>
#include <random>

using namespace std;
using namespace chrono_literals;

const int TIMEOUT = 400; // maximum number of milliseconds that a player is allowed to take
// const int TIMEOUT = 4000; // maximum number of milliseconds that a player is allowed to take

// it contains last id of object in list
int lastId = 0;

template <typename Type, unsigned N, unsigned Last>
struct tuple_printer
{

    static void print(std::ostream &out, const Type &value)
    {
        out << std::get<N>(value) << ", ";
        tuple_printer<Type, N + 1, Last>::print(out, value);
    }
};

template <typename Type, unsigned N>
struct tuple_printer<Type, N, N>
{

    static void print(std::ostream &out, const Type &value)
    {
        out << std::get<N>(value);
    }
};

template <typename... Types>
std::ostream &operator<<(std::ostream &out, const std::tuple<Types...> &value)
{
    out << "(";
    tuple_printer<std::tuple<Types...>, 0, sizeof...(Types) - 1>::print(out, value);
    out << ")";
    return out;
}

template <typename I>
I random_element(I begin, I end)
{
    const unsigned long n = std::distance(begin, end);

    std::advance(begin, std::rand() % n);
    return begin;
}

class Position
{
public:
    tuple<int, int> pos;

    int x()
    {
        return std::get<0>(pos);
    }

    int y()
    {
        return std::get<1>(pos);
    }

    Position(int x, int y)
    {
        pos = make_tuple(x, y);
    }

    Position(){};

    Position
    random_move()
    {
        Position npos;

        switch (rand() % 4)
        {
        case 0:
            npos.pos = make_tuple(std::get<0>(pos), std::get<1>(pos) + 1);
            break;
        case 1:
            npos.pos = make_tuple(std::get<0>(pos), std::get<1>(pos) - 1);
            break;
        case 2:
            npos.pos = make_tuple(std::get<0>(pos) + 1, std::get<1>(pos));
            break;
        case 3:
            npos.pos = make_tuple(std::get<0>(pos) - 1, std::get<1>(pos));
            break;
        }

        return npos;
    };

    float distanceTo(Position pos2)
    {
        return sqrt(
            (abs(pos2.x() - this->x()) *
             abs(pos2.x() - this->x())) +
            (abs(pos2.y() - this->y()) *
             abs(pos2.y() - this->y())));
    }
};

// TODO Implement the operator == and other operators if necessary
bool operator==(Position &lhs, Position &rhs)
{
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
}

class Thing
{
public:
    int id;
    Position position;

    Thing(){};
    Thing(int position_x, int position_y)
    {
        this->id = lastId++;
        position.pos = make_tuple(position_x, position_y);
    }

    virtual ~Thing() = default;
};
class SmallScissors : public Thing
{
public:
    SmallScissors(int position_x, int position_y) : Thing(position_x, position_y) {}
};

class CapitalScissors : public Thing
{
public:
    CapitalScissors(int position_x, int position_y) : Thing(position_x, position_y) {}
};

class SmallRock : public Thing
{
public:
    SmallRock(int position_x, int position_y) : Thing(position_x, position_y) {}
};

class CapitalRock : public Thing
{
public:
    CapitalRock(int position_x, int position_y) : Thing(position_x, position_y) {}
};

class SmallPaper : public Thing
{
public:
    SmallPaper(int position_x, int position_y) : Thing(position_x, position_y) {}
};

class CapitalPaper : public Thing
{
public:
    CapitalPaper(int position_x, int position_y) : Thing(position_x, position_y) {}
};

class Flag : public Thing
{
public:
    Flag(int position_x, int position_y) : Thing(position_x, position_y) {}
};

class Mountain : public Thing
{
public:
    Mountain(int position_x, int position_y) : Thing(position_x, position_y) {}
};
class World
{
public:
    // TODO Create a container of smart pointers of units and flags of player 0
    shared_ptr<Flag> flag0 = shared_ptr<Flag>(new Flag(0, 0));
    vector<shared_ptr<Thing>> units0 = {
        shared_ptr<Thing>(new SmallRock(1, 0)),
        shared_ptr<Thing>(new SmallRock(2, 0)),
        shared_ptr<Thing>(new SmallRock(3, 0)),
        shared_ptr<Thing>(new SmallRock(4, 0)),
        shared_ptr<Thing>(new SmallRock(5, 0)),

        shared_ptr<Thing>(new SmallPaper(1, 1)),
        shared_ptr<Thing>(new SmallPaper(2, 1)),
        shared_ptr<Thing>(new SmallPaper(3, 1)),
        shared_ptr<Thing>(new SmallPaper(4, 1)),
        shared_ptr<Thing>(new SmallPaper(5, 1)),

        shared_ptr<Thing>(new SmallScissors(1, 2)),
        shared_ptr<Thing>(new SmallScissors(2, 2)),
        shared_ptr<Thing>(new SmallScissors(3, 2)),
        shared_ptr<Thing>(new SmallScissors(4, 2)),
        shared_ptr<Thing>(new SmallScissors(5, 2)),

        shared_ptr<Thing>(new SmallRock(1, 3)),
        shared_ptr<Thing>(new SmallRock(2, 3)),
        shared_ptr<Thing>(new SmallRock(3, 3)),
        shared_ptr<Thing>(new SmallRock(4, 3)),
        shared_ptr<Thing>(new SmallRock(5, 3)),

        shared_ptr<Thing>(new SmallPaper(1, 4)),
        shared_ptr<Thing>(new SmallPaper(2, 4)),
        shared_ptr<Thing>(new SmallPaper(3, 4)),
        shared_ptr<Thing>(new SmallPaper(4, 4)),
        shared_ptr<Thing>(new SmallPaper(5, 4)),

        shared_ptr<Thing>(new SmallScissors(1, 5)),
        shared_ptr<Thing>(new SmallScissors(2, 5)),
        shared_ptr<Thing>(new SmallScissors(3, 5)),
        shared_ptr<Thing>(new SmallScissors(4, 5)),
        shared_ptr<Thing>(new SmallScissors(5, 5)),
    };

    // TODO Create a container of smart pointers of units and flags of player 1
    shared_ptr<Flag> flag1 = shared_ptr<Flag>(new Flag(14, 14));
    vector<shared_ptr<Thing>> units1 = {
        shared_ptr<Thing>(new CapitalScissors(9, 9)),
        shared_ptr<Thing>(new CapitalScissors(10, 9)),
        shared_ptr<Thing>(new CapitalScissors(11, 9)),
        shared_ptr<Thing>(new CapitalScissors(12, 9)),
        shared_ptr<Thing>(new CapitalScissors(13, 9)),

        shared_ptr<Thing>(new CapitalPaper(9, 10)),
        shared_ptr<Thing>(new CapitalPaper(10, 10)),
        shared_ptr<Thing>(new CapitalPaper(11, 10)),
        shared_ptr<Thing>(new CapitalPaper(12, 10)),
        shared_ptr<Thing>(new CapitalPaper(13, 10)),

        shared_ptr<Thing>(new CapitalRock(9, 11)),
        shared_ptr<Thing>(new CapitalRock(10, 11)),
        shared_ptr<Thing>(new CapitalRock(11, 11)),
        shared_ptr<Thing>(new CapitalRock(12, 11)),
        shared_ptr<Thing>(new CapitalRock(13, 11)),

        shared_ptr<Thing>(new CapitalScissors(9, 12)),
        shared_ptr<Thing>(new CapitalScissors(10, 12)),
        shared_ptr<Thing>(new CapitalScissors(11, 12)),
        shared_ptr<Thing>(new CapitalScissors(12, 12)),
        shared_ptr<Thing>(new CapitalScissors(13, 12)),

        shared_ptr<Thing>(new CapitalPaper(9, 13)),
        shared_ptr<Thing>(new CapitalPaper(10, 13)),
        shared_ptr<Thing>(new CapitalPaper(11, 13)),
        shared_ptr<Thing>(new CapitalPaper(12, 13)),
        shared_ptr<Thing>(new CapitalPaper(13, 13)),

        shared_ptr<Thing>(new CapitalRock(9, 14)),
        shared_ptr<Thing>(new CapitalRock(10, 14)),
        shared_ptr<Thing>(new CapitalRock(11, 14)),
        shared_ptr<Thing>(new CapitalRock(12, 14)),
        shared_ptr<Thing>(new CapitalRock(13, 14)),
    };

    // TODO Create a container of smart pointers of mountains
    vector<shared_ptr<Mountain>> mountains = {
        shared_ptr<Mountain>(new Mountain(10, 2)),
        shared_ptr<Mountain>(new Mountain(12, 2)),
        shared_ptr<Mountain>(new Mountain(9, 4)),
        shared_ptr<Mountain>(new Mountain(13, 4)),
        shared_ptr<Mountain>(new Mountain(10, 5)),
        shared_ptr<Mountain>(new Mountain(11, 5)),
        shared_ptr<Mountain>(new Mountain(12, 5)),
        shared_ptr<Mountain>(new Mountain(6, 7)),
        shared_ptr<Mountain>(new Mountain(7, 7)),
        shared_ptr<Mountain>(new Mountain(8, 7)),
        shared_ptr<Mountain>(new Mountain(2, 10)),
        shared_ptr<Mountain>(new Mountain(2, 11)),
        shared_ptr<Mountain>(new Mountain(2, 12)),
        shared_ptr<Mountain>(new Mountain(4, 10)),
        shared_ptr<Mountain>(new Mountain(4, 11)),
        shared_ptr<Mountain>(new Mountain(4, 12)),
        shared_ptr<Mountain>(new Mountain(5, 12)),
        shared_ptr<Mountain>(new Mountain(6, 10)),
        shared_ptr<Mountain>(new Mountain(6, 11)),
        shared_ptr<Mountain>(new Mountain(6, 12)),
    };
};

class Action
{
public:
    Position from; // current row, column of the unit to be moved
    Position to;   // position to where the unit must be moved

    Action(){};
    Action(Position from, Position to) : from(from), to(to){};
};

bool occupied(Position pos, vector<shared_ptr<Thing>> &units)
{
    if (pos.x() > 14 || pos.x() < 0 || pos.y() > 14 || pos.y() < 0)
    {
        return true;
    }

    auto occuped = find_if(
        begin(units),
        end(units),
        [&pos](shared_ptr<Thing> unit) {
            return unit->position == pos;
        });

    return occuped != end(units);
}

Action actionPlayerZero(World &world)
{
    if (world.units0.size() == 0)
    {
        this_thread::sleep_for(600ms);
        Action action;
        return action;
    }

    auto unit0 = random_element(begin(world.units0), end(world.units0));
    auto pos = (*unit0)->position;

    Position target_pos = pos.random_move();
    int tries = 5;

    while (occupied(target_pos, world.units0) && tries-- > 0)
    {
        target_pos = pos.random_move();
    }

    Action action(pos, target_pos);

    this_thread::sleep_for(85ms); // 0.4 seconds
    // this_thread::sleep_for(385ms); // 0.4 seconds
    // this_thread::sleep_for(1000ms); // 0.4 seconds
    return action;
}

Action actionPlayerOne(World &world)
{
    if (world.units1.size() == 0)
    {
        this_thread::sleep_for(600ms);
        Action action;
        return action;
    }

    sort(
        begin(world.units1),
        end(world.units1),
        [&world](shared_ptr<Thing> a, shared_ptr<Thing> b) {
            return a->position.distanceTo(world.flag0->position) < b->position.distanceTo(world.flag0->position);
        });

    int idx = world.units1.size();

    Position target_pos;
    Position pos;

    int x = 0;
    int y = 0;

    bool obstacleAtLeft = false;
    bool obstacleAtTop = false;

    while (idx > 0)
    {
        x = 0;
        y = 0;

        if (rand() % 50 > 30)
        {
            continue;
        }

        idx--;
        auto unit1 = world.units1[idx];

        pos = unit1->position;

        bool isX = abs(world.flag0->position.x() - pos.x()) >= abs(world.flag0->position.y() - pos.y());

        Position find_pos;

        find_pos.pos = make_tuple(pos.x(), pos.y() - 1);
        auto mountain = find_if(
            begin(world.mountains),
            end(world.mountains),
            [&find_pos](shared_ptr<Mountain> mountain) {
                return mountain->position == find_pos;
            });
        auto unit = find_if(
            begin(world.units1),
            end(world.units1),
            [&find_pos](shared_ptr<Thing> unit) {
                return unit->position == find_pos;
            });

        obstacleAtTop = mountain != end(world.mountains) || unit != end(world.units1) || pos.y() == 0;

        find_pos.pos = make_tuple(pos.x() - 1, pos.y());
        mountain = find_if(
            begin(world.mountains),
            end(world.mountains),
            [&find_pos](shared_ptr<Mountain> mountain) {
                return mountain->position == find_pos;
            });
        unit = find_if(
            begin(world.units1),
            end(world.units1),
            [&find_pos](shared_ptr<Thing> unit) {
                return unit->position == find_pos;
            });

        obstacleAtLeft = mountain != end(world.mountains) || unit != end(world.units1) || pos.x() == 0;

        if (obstacleAtLeft && obstacleAtTop)
        {
            continue;
        }
        else if (obstacleAtLeft)
        {
            y = -1;
        }
        else if (obstacleAtTop)
        {
            x = -1;
        }
        else if (isX)
        {
            x = (world.flag0->position.x() - pos.x()) / abs(world.flag0->position.x() - pos.x());
        }
        else
        {
            y = (world.flag0->position.y() - pos.y()) / abs(world.flag0->position.y() - pos.y());
        }

        target_pos.pos = make_tuple(pos.x() + x, pos.y() + y);
        break;
    }

    // cout << "LEFT " << (obstacleAtLeft ? "TRUE" : "FALSE") << endl;
    // cout << "TOP " << (obstacleAtTop ? "TRUE" : "FALSE") << endl;
    // cout << "IQ " << idx << endl;
    // cout << "POS " << pos.pos << endl;
    // cout << "DELTA " << make_tuple(x, y) << endl;
    // cout << "TPOS " << target_pos.pos << endl;

    Action action(pos, target_pos);

    this_thread::sleep_for(85ms); // 0.4 seconds
    // this_thread::sleep_for(385ms); // 0.4 seconds
    // this_thread::sleep_for(1000ms); // 0.4 seconds
    return action;
}

/**
 * The return is a pair: action and a boolean whether a timeout happened
 */
tuple<Action, bool> waitPlayer(Action (*f)(World &), World world)
{
    auto start = chrono::high_resolution_clock::now();
    Action action = f(world);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;

    if (elapsed.count() > TIMEOUT) // if time > 0.3 s
        return {action, true};     // player failed to answer in less than 400 ms
    else
        return {action, false};
}

void displayWorld(World &world)
{
    string matrix[15][15] = {};

    matrix[world.flag0->position.x()][world.flag0->position.y()] = "🇷🇺";
    matrix[world.flag1->position.x()][world.flag1->position.y()] = "🇧🇷";

    for (auto mountain : world.mountains)
    {
        matrix[mountain->position.x()][mountain->position.y()] = "⛰️";
    }

    for (auto unit : world.units0)
    {
        if (auto scissors = dynamic_pointer_cast<SmallScissors>(unit))
        {
            matrix[unit->position.x()][unit->position.y()] = "✌🏻";
        }
        if (auto rock = dynamic_pointer_cast<SmallRock>(unit))
        {
            matrix[unit->position.x()][unit->position.y()] = "✊🏻";
        }
        if (auto paper = dynamic_pointer_cast<SmallPaper>(unit))
        {
            matrix[unit->position.x()][unit->position.y()] = "✋🏻";
        }
    }

    for (auto unit : world.units1)
    {
        if (auto scissors = dynamic_pointer_cast<CapitalScissors>(unit))
        {
            matrix[unit->position.x()][unit->position.y()] = "✌🏿";
        }
        if (auto rock = dynamic_pointer_cast<CapitalRock>(unit))
        {
            matrix[unit->position.x()][unit->position.y()] = "✊🏿";
        }
        if (auto paper = dynamic_pointer_cast<CapitalPaper>(unit))
        {
            matrix[unit->position.x()][unit->position.y()] = "✋🏿";
        }
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (matrix[j][i] == "")
            {
                cout << "⬜️";
            }
            else
            {
                cout << matrix[j][i] << "";
            }
        }
        cout << endl;
    }

    cout.flush();
}

shared_ptr<Thing> findAndValidate(Action action, vector<shared_ptr<Mountain>> &mountains, vector<shared_ptr<Thing>> &units, shared_ptr<Thing> flag)
{
    if (action.to.x() > 14 || action.to.x() < 0 || action.to.y() > 14 || action.to.y() < 0 || flag->position == action.to)
    {
        return nullptr;
    }

    auto mountain = find_if(
        begin(mountains),
        end(mountains),
        [&action](shared_ptr<Mountain> mountain) {
            return mountain->position == action.to;
        });

    if (mountain != end(mountains))
    {
        return nullptr;
    }

    auto occuped = find_if(
        begin(units),
        end(units),
        [&action](shared_ptr<Thing> unit) {
            return unit->position == action.to;
        });

    if (occuped != end(units))
    {
        return nullptr;
    }

    auto thing = find_if(
        begin(units),
        end(units),
        [&action](shared_ptr<Thing> unit) {
            return unit->position == action.from;
        });

    if (thing != end(units))
    {
        return *thing;
    }
    else
    {
        return nullptr;
    }
}

void moveUnit(shared_ptr<Thing> unit, Action action)
{
    unit->position = action.to;
}

bool winCheck(shared_ptr<Thing> unit, shared_ptr<Flag> flag)
{
    return unit->position == flag->position;
}

void cancelAction(
    shared_ptr<Thing> unit,
    Action action)
{
    unit->position = action.from;
}

void killMe(shared_ptr<Thing> unit0, vector<shared_ptr<Thing>> &units)
{
    auto start = remove_if(
        begin(units),
        end(units),
        [&unit0](shared_ptr<Thing> unit) {
            return unit->position == unit0->position;
        });

    units.erase(start, end(units));
}

void jonality(
    shared_ptr<Thing> unit0,
    shared_ptr<Thing> unit1,
    World &world,
    Action action,
    shared_ptr<Thing> unit)
{
    if (auto scissors = dynamic_pointer_cast<SmallScissors>(unit0))
    {
        if (auto scissors = dynamic_pointer_cast<CapitalScissors>(unit1))
        {
            cancelAction(unit, action);
        }
        if (auto rock = dynamic_pointer_cast<CapitalRock>(unit1))
        {
            killMe(unit0, world.units0);
        }
        if (auto paper = dynamic_pointer_cast<CapitalPaper>(unit1))
        {
            killMe(unit1, world.units1);
        }
    }
    if (auto rock = dynamic_pointer_cast<SmallRock>(unit0))
    {
        if (auto scissors = dynamic_pointer_cast<CapitalScissors>(unit1))
        {
            killMe(unit1, world.units1);
        }
        if (auto rock = dynamic_pointer_cast<CapitalRock>(unit1))
        {
            cancelAction(unit, action);
        }
        if (auto paper = dynamic_pointer_cast<CapitalPaper>(unit1))
        {
            killMe(unit0, world.units0);
        }
    }
    if (auto paper = dynamic_pointer_cast<SmallPaper>(unit0))
    {
        if (auto scissors = dynamic_pointer_cast<CapitalScissors>(unit1))
        {
            killMe(unit0, world.units0);
        }
        if (auto rock = dynamic_pointer_cast<CapitalRock>(unit1))
        {
            killMe(unit1, world.units1);
        }
        if (auto paper = dynamic_pointer_cast<CapitalPaper>(unit1))
        {
            cancelAction(unit, action);
        }
    }
}

void mortalCombat(
    World &world,
    shared_ptr<Thing> unit0,
    Action action0,
    shared_ptr<Thing> unit1,
    Action action1)
{
    auto enemy0 = find_if(
        begin(world.units1),
        end(world.units1),
        [&action0](shared_ptr<Thing> unit) {
            return unit->position == action0.to;
        });

    if (enemy0 != end(world.units1))
    {
        jonality(unit0, *enemy0, world, action0, unit0);
    }

    auto enemy1 = find_if(
        begin(world.units0),
        end(world.units0),
        [&action1](shared_ptr<Thing> unit) {
            return unit->position == action1.to;
        });

    if (enemy1 != end(world.units0))
    {
        jonality(*enemy1, unit1, world, action1, unit1);
    }
}

int main()
{
    srand(time(0));

    World world;
    // TODO Initialize the world
    bool endGame = false;
    displayWorld(world);

    int i = 20000;

    while (!endGame)
    {
        auto [action0, timeout0] = waitPlayer(actionPlayerZero, world);
        auto [action1, timeout1] = waitPlayer(actionPlayerOne, world);
        if (timeout0 || timeout1)
        {
            endGame = true;
            if (world.units1.size() == 0)
            {
                for (int i = 0; i < 7; i++)
                {
                    cout << "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
                }
                cout << "🏆🏆🏆🏆🏆🏆🏆🇷🇺🏆🏆🏆🏆🏆🏆🏆" << endl;
                for (int i = 0; i < 7; i++)
                {
                    cout << "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
                }
                cout.flush();
            }
            else
            {
                for (int i = 0; i < 7; i++)
                {
                    cout << "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
                }
                cout << "🏆🏆🏆🏆🏆🏆🏆🇧🇷🏆🏆🏆🏆🏆🏆🏆" << endl;
                for (int i = 0; i < 7; i++)
                {
                    cout << "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
                }
                cout.flush();
            }
            // TODO Show the result of the game. Who caused the timeout?
        }
        else
        {
            endGame = i-- < 0;

            auto thing0 = findAndValidate(action0, world.mountains, world.units0, world.flag0);

            if (thing0 != nullptr)
            {
                moveUnit(thing0, action0);
                if (winCheck(thing0, world.flag1))
                {
                    for (int i = 0; i < 7; i++)
                    {
                        cout << "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
                    }
                    cout << "🏆🏆🏆🏆🏆🏆🏆🇷🇺🏆🏆🏆🏆🏆🏆🏆" << endl;
                    for (int i = 0; i < 7; i++)
                    {
                        cout << "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
                    }
                    endGame = true;
                    cout.flush();
                    break;
                    // TODO
                }
            }

            auto thing1 = findAndValidate(action1, world.mountains, world.units1, world.flag1);

            if (thing1 != nullptr)
            {
                moveUnit(thing1, action1);
                if (winCheck(thing1, world.flag0))
                {
                    for (int i = 0; i < 7; i++)
                    {
                        cout << "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
                    }
                    cout << "🏆🏆🏆🏆🏆🏆🏆🇧🇷🏆🏆🏆🏆🏆🏆🏆" << endl;
                    for (int i = 0; i < 7; i++)
                    {
                        cout << "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
                    }
                    endGame = true;
                    cout.flush();
                    break;
                    // TODO
                }
            }

            mortalCombat(world, thing0, action0, thing1, action1);

            displayWorld(world);

            // TODO Validate the actions: actionPlayer0 and actionPlayer1
            // TODO Update the world
            // TODO Show the world
            // TODO End the game and show the result if a player won
        }
    }

    return 0;
}