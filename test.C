
#include "variant2.h"

#include <iostream>
#include <string>
#include <vector>

template <typename variant_t>
void visit(const variant_t variant) {
    variant.visit([](const std::string& s) {
        std::cout << "it's a string: " << s << "\n";
    },
    [](const std::vector<int>& v) {
        std::cout << "it's a vector of length " << v.size() << "\n";
    });
}

int main() {
    variant2_t<std::string, std::vector<int>> thing("hi there");
    visit(thing);

    thing = std::vector<int>({1, 2, 3, 4, 5, 6});
    visit(thing);
}
