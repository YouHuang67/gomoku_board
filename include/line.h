#ifndef LINESHAPE_H__
#define LINESHAPE_H__

#include "utils.h"


const Uint32 ACTION_CODING_TABLE_SIZE = 1 << SIZE;
const Uint32 ACTION_CODING_MASK = (1 << SIZE) - 1;


class LineItemArray : public Array<Item, SIZE>
{
    public:
        LineItemArray() : Array<Item, SIZE>() {}
        LineItemArray(const Item* _items, size_t s) : Array<Item, SIZE>(_items, s) {}
        explicit LineItemArray(Uint32 l)
        {
            for (int pos = 0; pos < SIZE; pos++)
                Append(static_cast<Item>((l >> (2 * pos)) & 3));
        }
        explicit operator Uint32() const 
        {
            Uint32 l = 0;
            for (int pos = 0; pos < SIZE; pos++)
                l ^= static_cast<Uint32>(pos < Size() ? (*this)[pos] : NONE_ITEM) << (2 * pos);
            return l;
        }

};


class LineBase {};


class Line : public LineBase 
{
    public:
        Line(LineItemArray& items) : _line(static_cast<Uint32>(items)) { Initialize(); }
        Line(Uint32 l = 0) : _line(l) { Initialize(); }
        void Initialize() { memset(actionCodings, 0, 5 * sizeof(Uint32)); }
        void SetActionCoding(Shape shape, bool isAttacker, Uint32 coding)
        {
            coding &= ACTION_CODING_MASK;
            if (isAttacker) coding <<= SIZE;
            actionCodings[static_cast<int>(shape)] ^= coding;
        }
        Uint32 GetActionCoding(Shape shape, bool isAttacker) const
        {
            if (isAttacker) return actionCodings[static_cast<int>(shape)] >> SIZE;
            else            return actionCodings[static_cast<int>(shape)] & ACTION_CODING_MASK;
        }
        void SetLine(Uint32 l) { _line = l; }
        Uint32 GetLine() const { return _line; }
        void SetFive(bool isFive) { _isFive = isFive; }
        bool IsFive() const { return _isFive; }
        bool GetActions(Shape shape, bool isAttacker, 
                        LineActionArray* arrayPtr = nullptr) const
        {
            Uint32 coding = GetActionCoding(shape, isAttacker);
            if (arrayPtr) *arrayPtr = actionCodingTable[coding];
            return coding != 0;
        }
        static LineActionArray* GetActionCodingTable() { return actionCodingTable; }

    private:
        Uint32 _line;
		bool _isFive = false;
		Uint32 actionCodings[5];
		static LineActionArray* actionCodingTable;

};


std::ostream& operator<<(std::ostream& os, const LineItemArray& items);
std::ostream& operator<<(std::ostream& os, const Line& line);


#endif