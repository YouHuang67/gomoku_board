#ifndef LINE_TEST_H__
#define LINE_TEST_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "line.h"

static int mainRet = 0;
static int testCount = 0;
static int testPass = 0;


#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        testCount++;\
        if (equality)\
            testPass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            mainRet = 1;\
        }\
    } while(0)


#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")


void TestLineItemArray()
{
    const size_t n = 3;
    Item _items[n] = { BLACK, EMPTY, WHITE };
    LineItemArray items(_items, n), assignedItems;
    assignedItems = static_cast<LineItemArray>(static_cast<Uint32>(items));
    for (int i = 0; i < n; i++)
        EXPECT_EQ_INT(static_cast<int>(items[i]), static_cast<int>(assignedItems[i]));
    EXPECT_EQ_INT(static_cast<int>(NONE_ITEM), static_cast<int>(assignedItems[SIZE - 1]));
}


void TestBasicOperatorsOfLine()
{
    Line line;
    Uint32 coding = (1 << 3) ^ (1 << 5) ^ (1 << 7);
    line.SetActionCoding(OPEN_FOUR, true, coding);
    LineActionArray actions;
    EXPECT_EQ_INT(1, static_cast<int>(line.GetActions(OPEN_FOUR, true, &actions)));
    EXPECT_EQ_INT(0, static_cast<int>(line.GetActions(OPEN_FOUR, false)));
    EXPECT_EQ_INT(3, actions.Size());
    EXPECT_EQ_INT(3, static_cast<Uint>(actions[0]));
    EXPECT_EQ_INT(5, static_cast<Uint>(actions[1]));
    EXPECT_EQ_INT(7, static_cast<Uint>(actions[2]));
}


static void TestLine()
{
    TestLineItemArray();
    TestBasicOperatorsOfLine();
    printf("line_test: %d/%d (%3.2f%%) passed\n", testPass, testCount, testPass * 100.0 / testCount);
}


#endif