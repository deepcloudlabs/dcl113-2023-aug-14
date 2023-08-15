#include "city.h"
#include "world-util.h"

#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;
using namespace world;

map<int, shared_ptr<city>> cities;
map<string, shared_ptr<country>> countries;


int main() {
    create_world();
    vector<int> numbers{1, 2, 3, -10, 4, 50, 6, 7, 8, 9};
    // max_element/min_element -> reduce
    auto compareByGnp = [](auto p1, auto p2) {
        cout << p1.second->name << "," << p1.second->gnp
             << " ? "
             << p2.second->name << "," << p2.second->gnp
             << endl;
        return p1.second->gnp < p2.second->gnp;
    };
    auto richest_country = max_element(countries.begin(), countries.end(), compareByGnp);
    cout << "richest country: " << (*richest_country).second->name << endl;
    auto poor_country = min_element(countries.begin(), countries.end(), compareByGnp);
    cout << "poor country: " << (*poor_country).second->name << endl;

    return 0;
}