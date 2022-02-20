#ifndef UTILS_H__
#define UTILS_H__

#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::memcpy;

typedef unsigned int Uint;
typedef unsigned char Uchar;
typedef unsigned long int Uint32;
typedef unsigned long long Uint64;

const Uint SIZE = 15;
const Uint NUM_STONES = 225;
enum Item {BLACK = 0, WHITE, EMPTY, NONE_ITEM};
enum Direction {ROW, COL, DIA, COU};
enum Shape { FIVE, OPEN_FOUR, FOUR, OPEN_THREE, THREE, OPEN_TWO, TWO };


struct Action
{
    Uint row: 4;
    Uint col: 4;
    Action() {};
    explicit Action(Uint r, Uint c): row(r), col(c) {}
    explicit Action(Uint act): row(act >> 4), col(act & 15) {}
    explicit Action(Uchar act): row(act >> 4), col(act & 15) {}
    explicit operator Uint() const { return static_cast<Uint>((row << 4) ^ col); }
    explicit operator Uchar() const { return static_cast<Uchar>((row << 4) ^ col); }
};


template<size_t N>
class ActionArray
{
    public:
        void Reset() { size = 0; }
        size_t Size() const { return size; }
        void Append(const Action& act) { actions[size++] = act; }
        const Action& operator[](int i) const { return actions[i]; }

    private:
        Action actions[N];
        size_t size = 0;

};


typedef ActionArray<SIZE> LineActionArray;
typedef ActionArray<NUM_STONES> BoardActionArray;


#endif