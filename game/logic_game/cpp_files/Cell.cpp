#include "../hpp_files/Cell.hpp"

Cell::Cell(int typeCell, int widthCell, int heightCell, bool occupied)
    : typeCell(typeCell), widthCell(widthCell), heightCell(heightCell), occupied(occupied) {}

Cell::~Cell() {}
