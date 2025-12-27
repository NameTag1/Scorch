#include "Utility.hpp"

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

template<typename T>
inline bool contains(const std::vector<T>& vec, const T& item)
{
    return std::find(std::cbegin(vec), std::cend(vec), item) != std::cend(vec);
}
