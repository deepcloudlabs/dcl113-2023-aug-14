#include "city.h"
#include "country.h"
#include "world-util.h"

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace world;

map<int, shared_ptr<city>> cities;
map<string, shared_ptr<country>> countries;

auto
continent_reducer(set<string> continents,const pair<const string, shared_ptr<country>>& entry) {
    auto country = entry.second;
    auto continent = country->continent;
    continents.insert(continent);
    return continents;
}

auto
print_continent(const string &continent) {
    cout << continent << ", ";
}

int main() {
    create_world();
    // filter, map, reduce: HoF -> STL algorithm/numeric/functional ...
    // filter -> copy_if
    // map    -> transform
    // reduce -> accumulate
    auto continents = accumulate(countries.begin(), countries.end(), set<string>(), continent_reducer);
    for_each(continents.begin(), continents.end(), print_continent);
    cout << endl << "Done." << endl;
    return 0;
}