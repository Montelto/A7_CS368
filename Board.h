//
// Joseph McFarland
// 9072511679
// mcfarland3@wis.edu
// https://canvas.wisc.edu/courses/188843/files for slides
// Made in CLion with commits to GitHub
//

#ifndef A7_CS368_BOARD_H
#define A7_CS368_BOARD_H

#include <iostream>
#include <iomanip>

/*
 * The two unsigned parameters represent the board dimensions, like in Point
 * and Ship class.
 */
template <unsigned MAX_X, unsigned MAX_Y>
class Board {
private:
    /*
     * board[unsigned][unsigned] - A 2D grid of type Point<unsigned,
     * unsigned> to represent the internal board, which is updated based on
     * the player’s guesses.
     */
    Point<MAX_X, MAX_Y> board[MAX_X][MAX_Y];

    /*
     * bool hideShips – set to true by default. When the board is displayed,
     * the player’s ships will not be hidden, if hideShips is set to false.
     */
    bool hideShips;

public:
    /*
     * Overload the << operator that displays the status of the respective
     * co-ordinates of the Board object with the rows as numbers and columns
     * as alphabets. (Refer to output_format.txt for more details). Note that
     * the row numbers are right justified with the width set to ‘3’.
     * 1. ‘~’ -> default character
     * 2. ‘*’ –> for the hit positions
     * 3. ‘X’ –> for the miss positions
     * 4. ‘=’ -> for the positions where the ship is placed on the board
     * (hide this, if the hideShips member is true)
     */
    friend std::ostream &operator<<(std::ostream &out, const Board<MAX_X, MAX_Y> &b);

    /*
     * Explicit parameterized constructor: explicit Board (bool hide) – to
     * set the hideShips data member variable and is set to true, by default.
     */
    explicit Board (bool hide);

    /*
     * void setStatus (const Point <unsigned, unsigned>, Status) – to set the
     * status of the coordinate in the 2D board, based on the arguments passed.
     */
    void setStatus (const Point <MAX_X, MAX_Y>, Status);

    /*
     * Point <unsigned, unsigned>* getShipPoint (const Point<unsigned,
     * unsigned> &p, unsigned X, unsigned Y) – returns the Point co-ordinate
     * of the board, where the ship is to be placed and sets the status to
     * SHIP after placement. If the point is already occupied by another
     * ship, throw a “std::invalid_argument” exception. The X and Y
     * parameters represent the offset with respect to the Point p. X and Y
     * should be given as input, according to the direction in which the ship
     * is to be placed on the board.
     */
    Point <MAX_X, MAX_Y>* getShipPoint (const Point<MAX_X, MAX_Y> &p,
                                              unsigned X, unsigned Y);
};

template <unsigned MAX_X, unsigned MAX_Y>
std::ostream &operator<<(std::ostream &out, const Board<MAX_X, MAX_Y> &b) {
    out << "   ABCDEFGHIJ\n";
    for (int i = 0; i < MAX_Y; i++) {
        out << std::setw(3) << i + 1;
        for (int j = 0; j < MAX_X; j++) {
            Point<MAX_X, MAX_Y> p = b[MAX_X][MAX_Y];
            if (p.status == HIT) {
                out << "*";
            } else if (p.status == MISS) {
                out << "X";
            } else if (p.status == SHIP and not b.hideShips) {
                out << "=";
            } else {
                out << "~";
            }
        }
        out << "\n";
    }
    return out;
}

template<unsigned int MAX_X, unsigned int MAX_Y>
Board<MAX_X, MAX_Y>::Board(bool hide) {
    hideShips = hide;
}

template<unsigned int MAX_X, unsigned int MAX_Y>
void Board<MAX_X, MAX_Y>::setStatus(const Point<MAX_X, MAX_Y> point, Status status) {
    point.status = status;
    board[point.x][point.y] = point;
}

template<unsigned int MAX_X, unsigned int MAX_Y>
Point<MAX_X, MAX_Y> *
Board<MAX_X, MAX_Y>::getShipPoint(const Point<MAX_X, MAX_Y> &p, unsigned X,
                                  unsigned Y) {
    Point<MAX_X, MAX_Y> np = board[p.x + X][p.y + Y];
    if (np.getStatus() != SHIP) {
        setStatus(np, SHIP);
        return np;
    }
    throw "std::invalid_argument";
}

#endif //A7_CS368_BOARD_H
