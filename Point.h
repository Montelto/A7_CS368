//
// Joseph McFarland
// 9072511679
// mcfarland3@wis.edu
// https://canvas.wisc.edu/courses/188843/files for slides
// Made in CLion with commits to GitHub
//

#ifndef A7_CS368_POINT_H
#define A7_CS368_POINT_H

#include <iostream>

/*
 * “Status” enumeration with the fields: EMPTY, SHIP, MISS, HIT – to
 * represent the status of each point.
 * EMPTY – initialize the points on the board to empty.
 * SHIP – a ship is placed at this point on the board.
 * MISS – a ship is not placed at this point on the board and the player has
 * incorrectly guessed it.
 * HIT – a ship is placed at this point on the board and the player has
 * guessed it right.
 */
enum Status{EMPTY, SHIP, MISS, HIT};

/*
 * Template classes to be defined.
 */
template <unsigned MAX_X, unsigned MAX_Y>
class Ship;
template <unsigned MAX_X, unsigned MAX_Y>
class Board;

/*
 * The two unsigned parameters represent the maximum value that the x and y
 * co-ordinates of Point can hold.
 */
template <unsigned MAX_X, unsigned MAX_Y>
class Point {
private:
    /*
     * x and y unsigned fields to represent the co-ordinates of the board.
     */
    unsigned x, y;

    /*
     * Status ‘status’ data member to store the status of the point
     */
    Status status;

public:
    /*
     * Parameterized constructor: Point (char, unsigned) – to set the x and y
     * fields of Point object. Here, the x field (alphabet) is converted to
     * unsigned. Throw a “std::out_of_range” exception if any of the
     * arguments passed is not within the bounds of the board size.
     */
    Point(char, unsigned);

    /*
     * Parameterized constructor: Point (unsigned, unsigned) – to set the x
     * and y fields of Point object. Throw a “std::out_of_range” exception if
     * any of the arguments passed is not within the bounds of the board size.
     */
    Point(unsigned, unsigned);

    /*
     * Overload the == operator that returns true, if the two co-ordinates,
     * representing the x and y data members of the Point objects are equal.
     */
    bool operator==(Point const &point);

    /*
     * Overload the << operator that displays the respective Point object’s
     * co-ordinates in the form (x,y), where x denotes the row number and y
     * denotes the column alphabet. For example, if the point is (0, 0), the
     * displayed co-ordinate is (1, A), to represent the board. (Refer to
     * output_format.txt for more details)
     */
    friend std::ostream &operator << (std::ostream &out, const Point &point);

    /*
     * static char xToChar (unsigned) – To convert an integer (x field of
     * Point object) to character, relative to the character ‘A’.
     */
    static char xToChar(unsigned);

    /*
     * static unsigned xToInt (char) - To convert a character (x field of
     * Point object) to an integer, relative to the character ‘A’.
     */
    static unsigned xToInt(char);

    /*
     * Status getStatus () const - To return the enum status member of the
     * Point object.
     */
    Status getStatus() const;

    /*
     * to allow access to point for Ship and Board
     */
    friend class Ship<MAX_X, MAX_Y>;
    friend class Board<MAX_X, MAX_Y>;

    /*
     * Overload the copy-assignment operator. This will look similar to the
     * copy constructor
     */
    Point& operator=(const Point &obj);
};

template <unsigned MAX_X, unsigned MAX_Y>
Point<MAX_X, MAX_Y>::Point(char x, unsigned y) {
    unsigned x_int = xToInt(x);
    Point(x_int, y);
}

template <unsigned MAX_X, unsigned MAX_Y>
Point<MAX_X, MAX_Y>::Point(unsigned row, unsigned col) {
    if (x > MAX_X or y > MAX_Y)
        throw "std::out_of_range";
    x = row;
    y = col;
    status = EMPTY;
}

template <unsigned MAX_X, unsigned MAX_Y>
bool Point<MAX_X, MAX_Y>::operator==(Point const &point) {
    return this->x == point.x and this->y == point.y;
}

template <unsigned MAX_X, unsigned MAX_Y>
std::ostream &operator<<(std::ostream &out, const Point<MAX_X, MAX_Y> &point) {
    out << "(" << point.x << ", " << xToChar(point.y) << ")";
    return out;
}

template <unsigned MAX_X, unsigned MAX_Y>
char Point<MAX_X, MAX_Y>::xToChar(unsigned x) {
    x = x + 64;
    return char(x);
}

template <unsigned MAX_X, unsigned MAX_Y>
unsigned Point<MAX_X, MAX_Y>::xToInt(char x) {
    x = toupper(x);
    return unsigned(x - 64);
}

template <unsigned MAX_X, unsigned MAX_Y>
Status Point<MAX_X, MAX_Y>::getStatus() const {
    return status;
}

template<unsigned int MAX_X, unsigned int MAX_Y>
Point<MAX_X, MAX_Y> &Point<MAX_X, MAX_Y>::operator=(const Point<MAX_X, MAX_Y> &obj) {
    if (this != &obj) {
        x = obj.x;
        y = obj.y;
        status = obj.status;
    }
    return *this;
}

#endif //A7_CS368_POINT_H
