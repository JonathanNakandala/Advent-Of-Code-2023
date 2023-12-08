#include <vector>
#include<string>

#include "Utils.h"

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string_view string_view(str);
    size_t pos = 0;

    while (pos < string_view.size()) {
        size_t found = string_view.find(delimiter, pos);
        if (found == std::string_view::npos) {
            result.emplace_back(string_view.substr(pos));
            break;
        }
        result.emplace_back(string_view.substr(pos, found - pos));
        pos = found + 1;
    }

    return result;
}