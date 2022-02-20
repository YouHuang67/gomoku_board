#ifndef UTILS_TEST_H__
#define UTILS_TEST_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "utils.h"


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


static void TestConversionOfAction()
{
    Action action(7, 8);
    Uint iRow = 7, iCol = 8;
    Uint iAction = (iRow << 4) ^ iCol;
    Uchar cRow = 7, cCol = 8;
    Uchar cAction = (cRow << 4) ^ cCol;
    EXPECT_EQ_INT(iAction, static_cast<Uint>(action));
    EXPECT_EQ_INT(cAction, static_cast<Uchar>(action));
    EXPECT_EQ_INT(action.row, static_cast<Action>(iAction).row);
    EXPECT_EQ_INT(action.col, static_cast<Action>(iAction).col);
    EXPECT_EQ_INT(action.row, static_cast<Action>(cAction).row);
    EXPECT_EQ_INT(action.col, static_cast<Action>(cAction).col);
}


static void TestActionSet()
{
    LineActionArray actions;
    actions.Append(Action(7, 7));
    actions.Append(Action(7, 8));
    EXPECT_EQ_INT(2, actions.Size());
    EXPECT_EQ_INT(static_cast<Uint>(Action(7, 8)), static_cast<Uint>(actions[1]));
    actions.Reset();
    EXPECT_EQ_INT(0, actions.Size());
}


static void TestUtils()
{
    TestConversionOfAction();
    TestActionSet();
    printf("utils_test: %d/%d (%3.2f%%) passed\n", testPass, testCount, testPass * 100.0 / testCount);
}

#endif