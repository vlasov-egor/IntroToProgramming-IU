// TASK 4

/**
 * @file egor_vlasov.cpp
 * @author Egor Vlasov (e.vlasov@innopolis.university)
 * @brief implementation of two-dimensional world in which two players control units 
 * that battle to take each other’s flag. 
 * 
 * it is a simulator of a battle on stones-paper-scissors between brazil (black gestures) and russia (white gestures), 
 * the russian troops operate on random, and brazil has a tactic that is expressed in reaching out in a chain, 
 * thereby creating a defensive front
 * 
 * to launch the program correctly, use the command 
 * clear && g++ -std=c++2a egor_vlasov.cpp && ./a.out > out.txt 
 * and look at the out.txt file 
 * (since the stickers are not displayed correctly in the terminal)
 * 
 * I also made a visualizer on the node.js, 
 * which you can see from the link
 * https://egor-vlasov.alexstrnik.ru/
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

// it contains last id of object
int lastId = 0;

// ITEM 3.h: tuple_printer with explicit specialization
// ITEM 3.b: tuple_printer have templates
/**
 * @brief class for tuple printing
 * 
 * @tparam Type type of value
 * @tparam N index
 * @tparam Last last element
 */
template <typename Type, unsigned N, unsigned Last>
struct tuple_printer
{

    /**
     * @brief prints tuple 
     * 
     * @param out out stream
     * @param value some value
     */
    static void print(std::ostream &out, const Type &value)
    {
        out << std::get<N>(value) << ", ";
        tuple_printer<Type, N + 1, Last>::print(out, value);
    }
};

/**
 * @brief class for tuple printing
 * 
 * @tparam Type type of value
 * @tparam N index
 * @tparam Last last element
 */
template <typename Type, unsigned N>
struct tuple_printer<Type, N, N>
{
    /**
     * @brief prints tuple 
     * 
     * @param out out stream
     * @param value some value
     */
    static void print(std::ostream &out, const Type &value)
    {
        out << std::get<N>(value);
    }
};

/**
 * @brief << operator overloading for tuple
 * 
 * @tparam Types types in tuple
 * @param out out stream
 * @param value some value 
 * @return std::ostream& new out stream 
 */
template <typename... Types>
std::ostream &operator<<(std::ostream &out, const std::tuple<Types...> &value)
{
    out << "(";
    tuple_printer<std::tuple<Types...>, 0, sizeof...(Types) - 1>::print(out, value);
    out << ")";
    return out;
}

/**
 * @brief returns random element in some range
 * 
 * @tparam I type of element
 * @param begin begin of range
 * @param end end of range
 * @return I random element
 */
template <typename I>
I random_element(I begin, I end)
{
    const unsigned long n = std::distance(begin, end);

    std::advance(begin, std::rand() % n);
    return begin;
}

/**
 * @brief class which contains position in tuple format
 * 
 */
class Position
{
public:
    // tuple <x, y>
    tuple<int, int> pos;

    /**
     * @brief getting x
     * 
     * @return int x
     */
    int x() const
    {
        return std::get<0>(pos);
    }

    /**
     * @brief getting y
     * 
     * @return int y
     */
    int y() const
    {
        return std::get<1>(pos);
    }

    /**
     * @brief Construct a new Position object
     * 
     * @param x 
     * @param y 
     */
    Position(int x, int y)
    {
        pos = make_tuple(x, y);
    }

    /**
     * @brief Construct a new Position object
     * 
     */
    Position(){};

    /**
     * @brief random moving
     * 
     * @return Position new random position
     */
    Position random_move()
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

    // ITEM 3.f:
    /**
     * @brief calculating a distance between pos2 and current position
     * 
     * @param pos2 some position
     * @return float distance
     */
    float distanceTo(Position pos2) const
    {
        return sqrt(
            (abs(pos2.x() - this->x()) *
             abs(pos2.x() - this->x())) +
            (abs(pos2.y() - this->y()) *
             abs(pos2.y() - this->y())));
    }

    /**
     * @brief returns max between distance by x and be y
     * 
     * @param a first position
     * @param b second position
     * @return int max distance
     */
    int squareDistance(Position pos2)
    {
        return max(abs(this->x() - pos2.x()), abs(this->y() - pos2.y()));
    }
};

// TODO Implement the operator == and other operators if necessary
// ITEM 3.c:
/**
 * @brief == operator overloading
 * 
 * @param lhs left side element
 * @param rhs right side element
 * @return true if ==
 * @return false if !=
 */
bool operator==(Position &lhs, Position &rhs)
{
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
}

Position operator+(Position &lhs, Position &rhs)
{
    // ITEM 3.d:
    auto res = Position(lhs.x() + rhs.x(), lhs.y() + rhs.y());
    return res;
};

bool operator>(Position &lhs, Position &rhs)
{
    return (lhs.x() > rhs.x() && lhs.y() > rhs.y());
};

// ITEM 3.b:
/**
 * @brief it contains scissors, rocks and papers 
 * 
 */
class Thing
{
public:
    int id;
    Position position;

    /**
     * @brief Construct a new Thing object
     * 
     */
    Thing(){};

    /**
     * @brief Construct a new Thing object
     * 
     * @param position_x 
     * @param position_y 
     */
    Thing(int position_x, int position_y)
    {
        this->id = lastId++;
        position.pos = make_tuple(position_x, position_y);
    }

    // ITEM 3.e: virtual
    // ITEM 3.g:
    virtual ~Thing() = default;

    // ITEM 3.e: pure virtual
    virtual string emoji() = 0;
};

/**
 * @brief contains small scissors
 * 
 */
class SmallScissors : public Thing
{
public:
    SmallScissors(int position_x, int position_y) : Thing(position_x, position_y) {}

    string emoji() override
    {
        return "✌🏻";
    }
};

/**
 * @brief contains capital scissors
 * 
 */
class CapitalScissors : public Thing
{
public:
    CapitalScissors(int position_x, int position_y) : Thing(position_x, position_y) {}

    string emoji() override
    {
        return "✌🏿";
    }
};

/**
 * @brief contains small rock
 * 
 */
class SmallRock : public Thing
{
public:
    SmallRock(int position_x, int position_y) : Thing(position_x, position_y) {}

    string emoji() override
    {
        return "✊🏻";
    }
};

/**
 * @brief contains capital rock
 * 
 */
class CapitalRock : public Thing
{
public:
    CapitalRock(int position_x, int position_y) : Thing(position_x, position_y) {}

    string emoji() override
    {
        return "✊🏿";
    }
};

/**
 * @brief contains small paper
 * 
 */
class SmallPaper : public Thing
{
public:
    SmallPaper(int position_x, int position_y) : Thing(position_x, position_y) {}

    string emoji() override
    {
        return "✋🏻";
    }
};

/**
 * @brief contains capital paper
 * 
 */
class CapitalPaper : public Thing
{
public:
    CapitalPaper(int position_x, int position_y) : Thing(position_x, position_y) {}

    string emoji() override
    {
        return "✋🏿";
    }
};

/**
 * @brief contains flag
 * 
 */
class Flag : public Thing
{
public:
    Flag(int position_x, int position_y) : Thing(position_x, position_y) {}

    string emoji() override
    {
        return "F";
    }
};

/**
 * @brief contains mountains
 * 
 */
class Mountain : public Thing
{
public:
    Mountain(int position_x, int position_y) : Thing(position_x, position_y) {}

    string emoji() override
    {
        return "⛰️";
    }
};

/**
 * @brief contains bomb for bombers
 * 
 */
class Bomb : public Thing
{
public:
    Bomb(int position_x, int position_y) : Thing(position_x, position_y) {}

    string emoji() override
    {
        return "💣";
    }
};

/**
 * @brief contains small bomber
 * 
 */
class SmallBomber : public Thing
{
public:
    SmallBomber(int position_x, int position_y) : Thing(position_x, position_y) {}

    shared_ptr<Bomb> spawnBomb()
    {
        return shared_ptr<Bomb>(new Bomb(position.x(), position.y()));
    }

    string emoji() override
    {
        return "👌🏻";
    }
};

/**
 * @brief contains capital bomber
 * 
 */
class CapitalBomber : public Thing
{
public:
    CapitalBomber(int position_x, int position_y) : Thing(position_x, position_y) {}

    shared_ptr<Bomb> spawnBomb()
    {
        return shared_ptr<Bomb>(new Bomb(position.x(), position.y()));
    }

    string emoji() override
    {
        return "👌🏿";
    }
};

/**
 * @brief it contains all world 15x15
 * 
 */
class World
{
public:
    // TODO Create a container of smart pointers of units and flags of player 0
    shared_ptr<Flag> flag0 = shared_ptr<Flag>(new Flag(0, 0));
    shared_ptr<SmallBomber> bomber0 = shared_ptr<SmallBomber>(new SmallBomber(0, 6));

    // ITEM 3.k:
    vector<shared_ptr<Thing>>
        units0 = {
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
    shared_ptr<CapitalBomber> bomber1 = shared_ptr<CapitalBomber>(new CapitalBomber(14, 8));

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
    vector<shared_ptr<Bomb>> bombs = {};
};

/**
 * @brief contains action of moving from somewhere to somewhere
 * 
 */
class Action
{
public:
    Position from; // current row, column of the unit to be moved
    Position to;   // position to where the unit must be moved

    Action(){};
    Action(Position from, Position to) : from(from), to(to){};
};

/**
 * @brief check is cell occupied or not
 * 
 * @param pos position for checking
 * @param units vector of all units
 * @return true occupied
 * @return false not occupied
 */
bool occupied(Position pos, vector<shared_ptr<Thing>> &units)
{
    if (pos.x() > 14 || pos.x() < 0 || pos.y() > 14 || pos.y() < 0)
    {
        return true;
    }

    auto occupied = find_if(
        begin(units),
        end(units),
        [&pos](shared_ptr<Thing> unit) {
            return unit->position == pos;
        });

    return occupied != end(units);
}

/**
 * @brief action of zero player
 * 
 * @param world ref to world 15x15
 * @return Action some move
 */
Action actionPlayerZero(World &world)
{
    if (rand() % 50 > 30 && world.bomber0 != nullptr)
    {
        auto bombPos = world.bomber0->position;

        auto killCount = count_if(
            begin(world.units1),
            end(world.units1),
            [&bombPos](shared_ptr<Thing> unit) {
                return unit->position.squareDistance(bombPos) <= 2;
            });

        if (killCount > 10)
        {
            // Explode
            auto bomb = world.bomber0->spawnBomb();
            world.bombs.push_back(bomb);
            world.bomber0 = nullptr;

            this_thread::sleep_for(385ms); // 0.4 seconds
            return Action(Position(-1, -1), Position(-1, -1));
        }
        else
        {
            Position target_pos = world.bomber0->position.random_move();
            int tries = 5;

            while (occupied(target_pos, world.units0) && tries-- > 0)
            {
                target_pos = world.bomber0->position.random_move();
            }

            Action action(world.bomber0->position, target_pos);

            this_thread::sleep_for(385ms); // 0.4 seconds
            return action;
        }
    }

    if (world.units0.size() == 0)
    {
        this_thread::sleep_for(600ms);
        Action action;
        return action;
    }

    // ITEM 3.i:
    decltype(random_element(begin(world.units0), end(world.units0))) unit0 = random_element(begin(world.units0), end(world.units0));

    auto pos = (*unit0)->position;

    Position target_pos = pos.random_move();
    int tries = 5;

    while (occupied(target_pos, world.units0) && tries-- > 0)
    {
        target_pos = pos.random_move();
    }

    Action action(pos, target_pos);

    this_thread::sleep_for(385ms); // 0.4 seconds
    return action;
}

/**
 * @brief action of first player
 * 
 * @param world ref to world 15x15
 * @return Action some move
 */
Action actionPlayerOne(World &world)
{
    if (world.bomber1 != nullptr)
    {
        Position bombPos = world.bomber1->position;
        auto killCount = count_if(
            begin(world.units0),
            end(world.units0),
            [&bombPos](shared_ptr<Thing> unit) {
                return unit->position.squareDistance(bombPos) <= 2;
            });

        if (killCount > 15)
        {
            // Explode
            auto bomb = world.bomber1->spawnBomb();
            world.bombs.push_back(bomb);
            world.bomber1 = nullptr;

            this_thread::sleep_for(385ms); // 0.4 seconds
            return Action(Position(-1, -1), Position(-1, -1));
        }

        Position pos = world.bomber1->position;
        Position target_pos;

        int x = 0;
        int y = 0;

        bool isX = abs(world.flag0->position.x() - pos.x()) >= abs(world.flag0->position.y() - pos.y());

        Position find_pos;
        bool obstacleAtLeft, obstacleAtTop;

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

        if (obstacleAtLeft)
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

        // cout << "TPOS: " << target_pos.pos << endl;

        Action action(pos, target_pos);

        this_thread::sleep_for(385ms); // 0.4 seconds

        return action;
    }

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

    Action action(pos, target_pos);

    this_thread::sleep_for(385ms); // 0.4 seconds

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

/**
 * @brief it shows all world 15x15
 * 
 * @param world 
 */
void displayWorld(World &world)
{
    string matrix[15][15] = {};

    matrix[world.flag0->position.x()][world.flag0->position.y()] = "🇷🇺";
    matrix[world.flag1->position.x()][world.flag1->position.y()] = "🇧🇷";

    if (world.bomber0 != nullptr)
    {
        matrix[world.bomber0->position.x()][world.bomber0->position.y()] = world.bomber0->emoji();
    }

    if (world.bomber1 != nullptr)
    {
        matrix[world.bomber1->position.x()][world.bomber1->position.y()] = world.bomber1->emoji();
    }

    for (auto mountain : world.mountains)
    {
        matrix[mountain->position.x()][mountain->position.y()] = mountain->emoji();
    }

    for (auto bomb : world.bombs)
    {
        matrix[bomb->position.x()][bomb->position.y()] = bomb->emoji();
    }

    for (auto unit : world.units0)
    {
        matrix[unit->position.x()][unit->position.y()] = unit->emoji();
    }

    for (auto unit : world.units1)
    {
        matrix[unit->position.x()][unit->position.y()] = unit->emoji();
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

    cout << endl;
    cout.flush();
}

/**
 * @brief it checks valid or not some move
 * 
 * @param action some move
 * @param mountains all mountains
 * @param units all units
 * @param flag flag of that player
 * @return shared_ptr<Thing> 
 */
shared_ptr<Thing> findAndValidate(World &world, Action action, vector<shared_ptr<Mountain>> &mountains, vector<shared_ptr<Thing>> &units, shared_ptr<Thing> flag, shared_ptr<Thing> bomber)
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

    if (bomber != nullptr && bomber->position == action.from)
    {
        return bomber;
    }

    if (world.bomber0 != nullptr && world.bomber0->position == action.to)
    {
        return nullptr;
    }

    if (world.bomber1 != nullptr && world.bomber1->position == action.to)
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

/**
 * @brief it moves unit
 * 
 * @param unit some unit
 * @param action some move
 */
void moveUnit(shared_ptr<Thing> unit, Action action)
{
    unit->position = action.to;
}

/**
 * @brief checks is anyone wins
 * 
 * @param unit some unit
 * @param flag flag of opposite player
 * @return true win
 * @return false not
 */
bool winCheck(shared_ptr<Thing> unit, shared_ptr<Flag> flag)
{
    return unit->position == flag->position;
}

/**
 * @brief it canceling action if it was illegal move
 * 
 * @param unit some unit
 * @param action move
 */
void cancelAction(
    shared_ptr<Thing> unit,
    Action action)
{
    unit->position = action.from;
}

/**
 * @brief it kills unit and deletes it from units vector
 * 
 * @param unit0 some unit
 * @param units units vector
 */
void killMe(shared_ptr<Thing> unit0, vector<shared_ptr<Thing>> &units)
{
    // ITEM 3.j:
    auto start = remove_if(
        begin(units),
        end(units),
        [&unit0](shared_ptr<Thing> unit) {
            return unit->position == unit0->position;
        });

    units.erase(start, end(units));
}

/**
 * @brief something like fatality, when there are some fight
 * 
 * @param unit0 first unit
 * @param unit1 second unit
 * @param world ref to world 15x15
 * @param action some move
 * @param unit unit-winner
 */
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

/**
 * @brief check is there needed fight
 * 
 * @param world ref to world 
 * @param unit0 first unit
 * @param action0 move of first unit
 * @param unit1 second unit
 * @param action1 move of second unit
 */
void mortalCombat(
    World &world,
    shared_ptr<Thing> unit0,
    Action action0,
    shared_ptr<Thing> unit1,
    Action action1)
{
    if (auto bomber = dynamic_pointer_cast<SmallBomber>(unit0))
    {
        if (world.bomber1 != nullptr && world.bomber1->position == action0.to)
        {
            world.bomber0 = nullptr;
        }
        else
        {
            // ITEM 3.j:
            auto enemy0 = find_if(
                begin(world.units1),
                end(world.units1),
                [&action0](shared_ptr<Thing> unit) {
                    return unit->position == action0.to;
                });

            if (enemy0 != end(world.units1))
            {
                killMe(*enemy0, world.units1);
                auto bomb = world.bomber0->spawnBomb();
                world.bombs.push_back(bomb);
                world.bomber0 = nullptr;
            }
        }
    }
    else
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
    }

    if (auto bomber = dynamic_pointer_cast<CapitalBomber>(unit1))
    {
        if (world.bomber0 != nullptr && world.bomber0->position == action1.to)
        {
            world.bomber1 = nullptr;
        }
        else
        {
            auto enemy1 = find_if(
                begin(world.units0),
                end(world.units0),
                [&action1](shared_ptr<Thing> unit) {
                    return unit->position == action1.to;
                });

            if (enemy1 != end(world.units0))
            {
                killMe(*enemy1, world.units0);
                auto bomb = world.bomber1->spawnBomb();
                world.bombs.push_back(bomb);
                world.bomber1 = nullptr;
            }
        }
    }
    else
    {

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
}

void deNuke(World &world)
{
    for (auto bomb : world.bombs)
    {
        Position bombPos = bomb->position;

        auto units0_start = remove_if(
            begin(world.units0),
            end(world.units0),
            [&bombPos](shared_ptr<Thing> unit) {
                return unit->position.squareDistance(bombPos) <= 2;
            });
        world.units0.erase(units0_start, end(world.units0));

        auto units1_start = remove_if(
            begin(world.units1),
            end(world.units1),
            [&bombPos](shared_ptr<Thing> unit) {
                return unit->position.squareDistance(bombPos) <= 2;
            });
        world.units1.erase(units1_start, end(world.units1));

        auto mountains_start = remove_if(
            begin(world.mountains),
            end(world.mountains),
            [&bombPos](shared_ptr<Mountain> mountain) {
                return mountain->position.squareDistance(bombPos) <= 2;
            });
        world.mountains.erase(mountains_start, end(world.mountains));

        if (world.bomber0 != nullptr && world.bomber0->position.squareDistance(bombPos) <= 2)
        {
            world.bomber0 = nullptr;
        }

        if (world.bomber1 != nullptr && world.bomber1->position.squareDistance(bombPos) <= 2)
        {
            world.bomber1 = nullptr;
        }
    }

    world.bombs = {};
}

int main()
{

    srand(time(0));

    // TODO Initialize the world
    World world;

    bool endGame = false;
    displayWorld(world);

    int i = 100000;

    while (!endGame)
    {
        auto [action0, timeout0] = waitPlayer(actionPlayerZero, world);
        auto [action1, timeout1] = waitPlayer(actionPlayerOne, world);
        if (timeout0 || timeout1)
        {
            endGame = true;
            // TODO Show the result of the game. Who caused the timeout?
            // TODO End the game and show the result if a player won
            // checks is there any units of players
            if (world.units1.size() == 0)
            {
                // russia wins
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
                // brazilia wins
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
        }
        else
        {
            endGame = i-- < 0;

            // Explode bombs
            deNuke(world);

            auto thing0 = findAndValidate(world, action0, world.mountains, world.units0, world.flag0, world.bomber0);

            if (thing0 != nullptr)
            {
                moveUnit(thing0, action0);
                if (winCheck(thing0, world.flag1))
                {
                    // russia wins
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
                }
            }

            // TODO Validate the actions: actionPlayer0 and actionPlayer1
            auto thing1 = findAndValidate(world, action1, world.mountains, world.units1, world.flag1, world.bomber1);

            if (thing1 != nullptr)
            {
                moveUnit(thing1, action1);
                if (winCheck(thing1, world.flag0))
                {
                    // brazilia wins
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
                }
            }
            // Update the world
            mortalCombat(world, thing0, action0, thing1, action1);
            // Show the world
            displayWorld(world);
        }
    }

    return 0;
}