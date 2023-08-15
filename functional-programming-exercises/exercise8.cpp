#include "city.h"
#include "country.h"
#include "world-util.h"

#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace world;

map<int,shared_ptr<city>> cities;
map<string,shared_ptr<country>> countries;
auto map2capital = [](shared_ptr<country>& ctry){
    return ctry->capital;
};
auto if_has_capital = [](shared_ptr<country>& ctry){
    return ctry->capital_id > 0;
};
auto map2country = [](const pair<string,shared_ptr<country>>& entry){
    return entry.second;
};

auto print_capital= [](const shared_ptr<world::city>& capital){
    cout << capital->name << ", " << capital->population << endl;
};

auto compareByPopulation= [](shared_ptr<world::city>& firstCapital,shared_ptr<world::city>& secondCapital){
    return firstCapital->population < secondCapital->population;
};

int main(){
    create_world();
    vector<shared_ptr<city>> capitals;
    vector<shared_ptr<country>> v_countries;
    vector<shared_ptr<country>> countriesWithCapitals;
    // map -> filter -> map - > reduce
    transform(countries.begin(),countries.end(), back_inserter(v_countries),map2country);
    copy_if(v_countries.begin(),v_countries.end(), back_inserter(countriesWithCapitals),if_has_capital);
    transform(countriesWithCapitals.begin(),countriesWithCapitals.end(), back_inserter(capitals),map2capital);
    for_each(capitals.begin(),capitals.end(),print_capital);
    auto high_pop_capital = max_element(capitals.begin(), capitals.end(), compareByPopulation);
    cout << "high populated capital is " << (*high_pop_capital)->name
         << ", "
         << (*high_pop_capital)->population << endl;
    return 0;
}