#ifndef CELL_HPP
#define CELL_HPP

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
