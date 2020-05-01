//
// Joseph McFarland
// 9072511679
// mcfarland3@wis.edu
// https://canvas.wisc.edu/courses/188843/files for slides
// Made in CLion with commits to GitHub
//

#ifndef A7_CS368_SHIP_H
#define A7_CS368_SHIP_H

using namespace std;

/*
 * “Direction” enumeration with the fields – VERTICAL and HORIZONTAL to
 * represent the direction in which the ship is placed on the board.
 */
enum Direction{VERTICAL, HORIZONTAL};

/*
 * The two unsigned parameters represent the board dimensions, like in Point
 * class.
 */
template <unsigned MAX_X, unsigned MAX_Y>
class Ship {
private:
    /*
     * string name – the name of the ship
     */
    string name;
    /*
     * vector <Point<unsigned, unsigned>*> ship – the co-ordinates occupied
     * by the ship.
     */
    vector <Point<MAX_X, MAX_Y>*> ship;

public:
    /*
     * Parametrized constructor: Ship(string, const vector <Point<unsigned,
     * unsigned>*>) – to set the name and the co-ordinates occupied by the ship.
     */
    Ship(string, const vector <Point<MAX_X, MAX_Y>*>);

    /*
     * Parametrized constructor: Ship(string, const Point <unsigned,
     * unsigned> &, unsigned len, Direction direction, Board <unsigned,
     * unsigned> &) – to set the name and the coordinates occupied by the
     * ship, depending on the direction (the direction in which the ship is
     * placed) and len (length of the ship). Place the ship on the board, by
     * calling the getShipPoint() function of Board class with the relevant
     * arguments. In case of invalid ship placement, catch and throw the
     * “std::invalid_argument” exception that might be thrown by the
     * getShipPoint() function, and reset the status of the previously placed
     * ship points to EMPTY.
     */
    Ship(string, const Point <MAX_X, MAX_Y> &, unsigned len,
         Direction direction, Board <MAX_X, MAX_Y> &);

    /*
     * void setName (string) and string getName() - setter and getter methods
     * for the string “name” member variable.
     */
    void setName(string);
    string getName();

    /*
     * bool isHit (const Point <unsigned, unsigned> &) const – returns true
     * if the point coordinate represents any ship on the board and sets the status to HIT.
     */
    bool isHit(const Point <MAX_X, MAX_Y> &) const;

    /*
     * bool isSunk () const – returns true if the ship has been sunk by the
     * opponent player.
     */
    bool isSunk () const;
};

template <unsigned MAX_X, unsigned MAX_Y>
Ship<MAX_X, MAX_Y>::Ship(string n, const vector <Point<MAX_X, MAX_Y>*> s) {
    name = n;
    ship = s;
}

template <unsigned MAX_X, unsigned MAX_Y>
Ship<MAX_X, MAX_Y>::Ship(string n, const Point <MAX_X, MAX_Y> & s, unsigned len,
     Direction direction, Board <MAX_X, MAX_Y> & b) {
    name = n;
    b.getShipPoint(s, 0 , 0);
    ship.push_back(s);
    try {
        if (direction == VERTICAL) {
            for (int i = 1; i <= len; i++) {
                ship.push_back(b.getShipPoint(s, 0, i));
            }
        } else if (direction == HORIZONTAL) {
            for (int i = 1; i <= len; i++) {
                ship.push_back(b.getShipPoint(s, i, 0));
            }
        }
    } catch (invalid_argument &) {
        for (auto p: ship) {
            b.setStatus(s, EMPTY);
        }
        throw "std::invalid_argument";
    }

}

template <unsigned MAX_X, unsigned MAX_Y>
void Ship<MAX_X, MAX_Y>::setName(string n){
    name = n;
}

template <unsigned MAX_X, unsigned MAX_Y>
string Ship<MAX_X, MAX_Y>::getName() {
    return name;
}

template <unsigned MAX_X, unsigned MAX_Y>
bool Ship<MAX_X, MAX_Y>::isHit(const Point <MAX_X, MAX_Y> &point) const {
    if (point.getStatus() == SHIP) {
        point.status = HIT;
        return true;
    }
    return false;
}

template<unsigned int MAX_X, unsigned int MAX_Y>
bool Ship<MAX_X, MAX_Y>::isSunk() const {
    int hit_count = 0;
    for (int i = 0; i < ship.size(); i++)
        if (ship[i].status == HIT)
            hit_count++;
    return hit_count == ship.size();
}

#endif //A7_CS368_SHIP_H
