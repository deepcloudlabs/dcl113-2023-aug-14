#include "city.h"
#include "country.h"
#include "world-util.h"

#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <numeric>
#include <ranges>
#include <functional>

using namespace std;
using namespace world;

map<int, shared_ptr<city>> cities;
map<string, shared_ptr<country>> countries;
auto if_asian = []
        (const shared_ptr<country>& p) {
    return p->continent == "Asia";
};
auto to_name = []
        (const shared_ptr<country>& p) {
    return p->name;
};
auto shorter_than = []
        (const string& s, int size) {
    return s.size() < size;
};

int main() {
    create_world();
    auto shorter_than6 = bind(shorter_than,placeholders::_1,6);
    for (const auto &name: std::ranges::views::values(countries)
                           | std::ranges::views::filter(if_asian)
                           | std::ranges::views::transform(to_name)
                           | std::ranges::views::filter(shorter_than6)
            ) {
        cout << name << endl;
    }

    return 0;
}