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

map<int,shared_ptr<city>> cities;
map<string,shared_ptr<country>> countries;

int main(int argc, char* argv[]){
	create_world();

    // TODO: Find continents
		
	return 0;
}