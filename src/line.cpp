#include <math.h>
#include "line.h"


LineActionArray* InitializeActionCodingTable();
int* GetLineLengths(); 
int* GetLineIndices();


LineActionArray* Line::actionCodingTable = InitializeActionCodingTable();
int*    LineTable::lineLengths = GetLineLengths();
int*    LineTable::lineIndices = GetLineIndices();
LineTable LINE_TABLE = *(new LineTable(LINE_MAP_SIZE));


LineActionArray* InitializeActionCodingTable()
{
    LineActionArray* tablePtr = new LineActionArray[ACTION_CODING_TABLE_SIZE];
    for (Uint32 coding = 0; coding < ACTION_CODING_TABLE_SIZE; coding++)
        for (int pos = 0; pos < SIZE; pos++)
            if ((coding >> pos) & 1) tablePtr[coding].Append(Action(0, pos));
    return tablePtr;
}


int GetLineLength(Uint32 line)
{
    int length = 0;
    LineItemArray items = static_cast<LineItemArray>(line);
    for (int i = 0; i < SIZE; i++)
        if (NONE_ITEM != items[i]) 
            if (length++ < i) return -1;
    return length;
}


int* GetLineLengths()
{
    int* ptr = new int[LINE_MAP_SIZE];
    for (Uint32 line = 0; line < LINE_MAP_SIZE; line++)
        ptr[line] = GetLineLength(line);
    return ptr;
}


int* GetLineIndices()
{
    int length, index = 0, *ptr = new int[LINE_MAP_SIZE];
    for (Uint32 line = 0; line < LINE_MAP_SIZE; line++)
        if ((length = GetLineLength(line)) >= 0)
            ptr[line] = index++;
    return ptr;
}


std::ostream& operator<<(std::ostream& os, const LineItemArray& items)
{
    for (int pos = 0; pos < items.Size(); pos++)
        switch (items[pos])
        {
        case BLACK:
            os << "X";
            break;
        case WHITE:
            os << "O";
            break;
        case EMPTY:
            os << "_";
            break;
        default:
            break;
        }
    return os;
}


std::ostream& operator<<(std::ostream& os, const Line& line)
{
    os << static_cast<LineItemArray>(line.GetLine());
    return os;
}