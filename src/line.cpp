#include "line.h"


LineActionArray* InitializeActionCodingTable();
LineActionArray* Line::actionCodingTable = InitializeActionCodingTable();


LineActionArray* InitializeActionCodingTable()
{
    LineActionArray* tablePtr = new LineActionArray[ACTION_CODING_TABLE_SIZE];
    for (Uint32 coding = 0; coding < ACTION_CODING_TABLE_SIZE; coding++)
        for (int pos = 0; pos < SIZE; pos++)
            if ((coding >> pos) & 1) tablePtr[coding].Append(Action(0, pos));
    return tablePtr;
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