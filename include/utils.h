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


inline std::ostream& operator<<(std::ostream& os, const Action& action)
{
    os << "(" << action.row << ", " << action.col << ")";
	return os;
}


class ActionArray
{
    public:
        ActionArray() {}
        ActionArray(const Action* acts, size_t s) 
        { memcpy(actions, acts, (size = s) * sizeof(Action)); }
        ActionArray& operator=(const ActionArray& array)
        { 
            memcpy(actions, array.actions, (size = array.size) * sizeof(Action)); 
            return *this;
        }
        ActionArray(const ActionArray& array) { *this = array; }
        size_t Size() const { return size; }
        void Append(const Action& act) { actions[size++] = act; }
        const Action& operator[](int i) const { return actions[i]; }
        void SetActions(Action* handle) { memcpy(handle, actions, size * sizeof(Action)); }

    private:
        Action actions[NUM_STONES];
        size_t size = 0;

};


inline std::ostream& operator<<(std::ostream& os, const ActionArray& array)
{
    size_t size = array.Size();
    os << size << " actions:";
    for (int i = 0; i < size; i++)
        os << " " << array[i];
    return os;
}


#endif