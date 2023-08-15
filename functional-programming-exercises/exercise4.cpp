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

int main() {
    create_world();

    auto is_asian = [](shared_ptr<country>& ctry){
        return ctry->continent == "Asia";
    };
    auto to_name = [](shared_ptr<country>& ctry){
        return ctry->name;
    };
    auto shorter_than = [](const string& s,int size){return s.length() < size; };
    auto shorter_than6 = bind(shorter_than,placeholders::_1,6);

    // Asian countries, name<6 char
    for (auto name : // lazy evaluation
            std::ranges::views::values(countries) // declarative programming
            | std::ranges::views::filter(is_asian)
            | std::ranges::views::transform(to_name)
            | std::ranges::views::filter(shorter_than6)
            )
    { // 1-PASS
        cout << name << endl;
    }
    return 0;
}