#ifndef LINESHAPE_H__
#define LINESHAPE_H__

#include "utils.h"


const Uint32 ACTION_CODING_TABLE_SIZE = 1 << SIZE;
const Uint32 ACTION_CODING_MASK       = (1 << SIZE) - 1;
const Uint   LINE_MAP_LENGTH          = 10;
const Uint   LINE_MAP_SIZE            = 1 << (2 * LINE_MAP_LENGTH);
const Uint32 LINE_MAP_MASK            = LINE_MAP_SIZE - 1;


class LineItemArray : public Array<Item, SIZE>
{
    public:
        LineItemArray() : Array<Item, SIZE>() {}
        LineItemArray(const Item* _items, size_t _size) : Array<Item, SIZE>(_items, _size) 
        {
            while (Size() < SIZE)
                Append(NONE_ITEM);
        }
        explicit LineItemArray(Uint32 line)
        {
            for (int pos = 0; pos < SIZE; pos++)
                Append(static_cast<Item>((~(line >> (2 * pos))) & 3));
        }
        explicit operator Uint32() const 
        {
            Uint32 line = 0;
            for (int pos = 0; pos < SIZE; pos++)
                line ^= ((~static_cast<Uint32>(pos < Size() ? (*this)[pos] : NONE_ITEM)) & 3) << (2 * pos);
            return line;
        }

};


class LineBase {};


class Line : public LineBase 
{
    public:
        Line(LineItemArray& items) : line(static_cast<Uint32>(items)) { Initialize(); }
        Line(Uint32 _line = 0) : line(_line) { Initialize(); }
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
        void SetLine(Uint32 _line) { line = _line; }
        Uint32 GetLine() const { return line; }
        void SetFive(bool _isFive) { isFive = _isFive; }
        bool IsFive() const { return isFive; }
        bool GetActions(Shape shape, bool isAttacker, 
                        LineActionArray* arrayPtr = nullptr) const
        {
            Uint32 coding = GetActionCoding(shape, isAttacker);
            if (arrayPtr) *arrayPtr = actionCodingTable[coding];
            return coding != 0;
        }
        static LineActionArray* GetActionCodingTable() { return actionCodingTable; }

    private:
        Uint32 line;
		bool isFive = false;
		Uint32 actionCodings[5];
		static LineActionArray* actionCodingTable;

};


class LineTable : public LineBase
{
    public:
        LineTable() {}
        LineTable(size_t size)
        {
            ptr = new LineBase*[size];
            for (int i = 0; i < size; i++)
                ptr[i] = nullptr;
        }
        ~LineTable() { delete[] ptr; }
        LineBase* Find(Uint32 key) { return *FindHandle(key); }
        LineBase** FindHandle(Uint32 key)
        {
            Uint32 mainKey = key & LINE_MAP_MASK;
            Uint32 leftKey = key >> (2 * LINE_MAP_LENGTH);
            LineBase** handle = ptr + lineIndices[mainKey];
            if (LINE_MAP_LENGTH != lineLengths[mainKey]) return handle;
            if (!(*handle))
            {
                int length = SIZE > 2 * LINE_MAP_LENGTH ? LINE_MAP_LENGTH : SIZE - LINE_MAP_LENGTH;
                *handle = new LineTable(1 << (2 * length));
            }
            return static_cast<LineTable*>(*handle)->FindHandle(leftKey);
        }

    private:
        LineBase**     ptr;
		static int*    lineLengths;
        static int*    lineIndices;
		static Uint32* lineMasks;

};


std::ostream& operator<<(std::ostream& os, const LineItemArray& items);
std::ostream& operator<<(std::ostream& os, const Line& line);


#endif