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


// implement array that scores a set of elements, e.g., actions
template<class T, size_t maxSize>
class Array
{
    public:
        Array() {}
        Array(const T* arr, size_t s) 
        { memcpy(array, arr, (size = s) * sizeof(T)); }
        Array& operator=(const T& targetArray)
        { 
            memcpy(array, targetArray.array, (size = targetArray.size) * sizeof(T)); 
            return *this;
        }
        Array(const T& targetArray) { *this = targetArray; }
        size_t Size() const { return size; }
        void Append(const T& elem) { array[size++] = elem; }
        const T& operator[](int i) const { return array[i]; }
        void Set(T* handle) { memcpy(handle, array, size * sizeof(T)); }
        void Clear() { size = 0; }

    private:
        T array[maxSize];
        size_t size = 0;

};


template<class T, size_t maxSize>
inline std::ostream& operator<<(std::ostream& os, const Array<T, maxSize>& array)
{
    size_t size = array.Size();
    os << size << " actions:";
    for (int i = 0; i < size; i++)
        os << " " << array[i];
    return os;
}


typedef Array<Item, SIZE> LineItemArray;
typedef Array<Action, SIZE> LineActionArray;
typedef Array<Action, NUM_STONES> BoardActionArray;

#endif