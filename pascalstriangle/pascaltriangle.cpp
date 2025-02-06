#include <format>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
template<typename T>
std::ostream& operator << (std::ostream & s, const std::vector<std::vector<T>>& triangle) {
    for (const auto& row : triangle)
    {
        std::ranges::copy(row, std::ostream_iterator<T>(s, " "));
        s << '\n';
    }
    return s;
}

std::vector<int> get_next_row(const std::vector<int> & last_row) {
    std::vector<int> next_row { 1 };
    if (last_row.empty()) {
        return next_row;
    }
    for (size_t idx = 0; idx + 1 < last_row.size(); ++idx) {
        next_row.emplace_back(last_row[idx] + last_row[idx + 1]);
    }
    next_row.emplace_back(1);
    return next_row;
}
auto generate_triangle(int rows){
    std::vector<std::vector<int>> triangle{ {1} };
    for (int row = 1 ; row < rows ; ++row) {
        triangle.push_back(get_next_row(triangle.back()));
    }
    return triangle;
}

void show_vectors(std::ostream& s,
    const std::vector<std::vector<int>>& v, size_t width = 6)
{
    const auto gaps  = width/2;
    std::string spaces(v.back().size() * gaps, ' ');
    for (const auto& row : v)
    {
        s << spaces;
        if (spaces.size() > gaps)
            spaces.resize(spaces.size()- gaps);
        for (const auto& data : row)
        {
            s << std::format("{: ^{}}", data, width);
        }
        s << '\n';
    }
}

int main() {
    auto triangle = generate_triangle(16);
    show_vectors(std::cout, triangle);
}
