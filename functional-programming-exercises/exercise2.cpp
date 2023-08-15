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

map<int, shared_ptr<world::city>> cities;
map<std::string, shared_ptr<world::country>> countries;

int main(int argc, char *argv[]) {
    create_world();

    // Find the number of countries in each continent
    // pair<string,int>
    // country -- map --> (continent,1) -- reduce/group by --> map<string,int>
    auto group_by_continent_count_reducer =
            [] // capturing
            (map<string, int> groups, pair<const string, shared_ptr<country>> &entry) // params
            { // body
                groups[entry.second->continent]++;
                return groups;
            };

    auto country_counts_by_continent = accumulate(countries.begin(), countries.end(), map<string, int>(),
                                                  group_by_continent_count_reducer);
    for_each(country_counts_by_continent.begin(), country_counts_by_continent.end(), [](const auto &entry) {
        cout << entry.first << ": " << entry.second << endl;
    });
    cout << endl << "Done." << endl;
    return 0;
}