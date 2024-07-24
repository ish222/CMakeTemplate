#include "LibraryFile.h"

Library::Library(int p_num, std::string p_name) : _num{p_num}, _name{std::move(p_name)} {}

std::string Library::ToString() const {
    return std::to_string(_num) + _name;
}