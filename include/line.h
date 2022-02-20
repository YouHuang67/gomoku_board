#ifndef LINESHAPE_H__
#define LINESHAPE_H__

#include "utils.h"


class LineBase {};


class Line : public LineBase 
{
    public:
        Line(Uint32 l = 0);

    private:
        Uint32 _line;
		bool _isFive;
		Uint32 _actions[5];
		// static UC** actionTable;

};

#endif