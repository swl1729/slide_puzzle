#ifndef INCLUDED_SLPuzzle
#define INCLUDED_SLPuzzle

#define D_LEVEL 3
#define MAX_LEVEL 10
#define SHUFFLE_ITERATION 1000

class Point {
public:
    int x;
    int y;
    Point(int xx, int yy) :x(xx), y(yy) {}
};

#endif