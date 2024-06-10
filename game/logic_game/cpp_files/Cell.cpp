#include "../hpp_files/Cell.hpp"

// This file is a class that creates a cell
// The cell can be created with a type, a width, a height and an occupied state
// The cell can be displayed with the type, the width and the height

Cell::Cell(int typeCell, int widthCell, int heightCell, bool occupied)
    : typeCell(typeCell), widthCell(widthCell), heightCell(heightCell), occupied(occupied) {}

Cell::~Cell() {}
