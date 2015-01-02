#ifndef __POSITION_H__
#define __POSITION_H__

class Position {
public:
    int x_coord;
    int y_coord;

public:
    Position(int x, int y):x_coord(x),y_coord(y){}

    bool operator==(const Position& other) const {
         return x_coord == other.x_coord &&
                y_coord == other.y_coord;
    }

};

class PositionHash {

public:
    std::size_t operator()(const Position* p) const {
    	 // 16 is the maximum value in the pair of coordination integers
    	 return p->x_coord * 16 + p->y_coord;
    }
};

#endif