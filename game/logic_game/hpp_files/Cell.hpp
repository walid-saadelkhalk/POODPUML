#ifndef CELL_HPP
#define CELL_HPP

// Cell class
// This class is used to create a cell
// The cell is created with a type, a width, a height and an occupied status


class Cell {
public:
    int typeCell;
    int widthCell;
    int heightCell;
    bool occupied;

    Cell(int typeCell, int widthCell, int heightCell, bool occupied);
    ~Cell();
};

#endif // CELL_HPP
