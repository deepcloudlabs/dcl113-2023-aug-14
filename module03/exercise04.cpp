#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

auto
is_even(int u){
    return u%2 == 0;
}

int main() {
    vector<int> numbers{4,8,15,16,23,42};
    vector<int> even_numbers;
    auto is_greater = greater<int>();

    auto is_greater_than_42 = bind(is_greater,placeholders::_1,42);
    auto is_less_than = bind(is_greater,placeholders::_2,placeholders::_1);
    auto is_less_than_lambda = [&is_greater](int x,int y){return is_greater(y,x);};
    auto is_odd = [](int u){return !is_even(u);};
    cout << is_greater(3,5) << endl;
    cout << is_greater(3,3) << endl;
    cout << is_greater(5,3) << endl;
    cout <<  is_greater_than_42(5) << endl;
    cout <<  is_greater_than_42(108) << endl;
    cout << is_less_than(5,3) << endl;
    cout << is_less_than(3,5) << endl;
    cout << is_less_than(3,3) << endl;
    cout << is_less_than_lambda(5,3) << endl;
    cout << is_less_than_lambda(3,5) << endl;
    cout << is_less_than_lambda(3,3) << endl;
    cout << is_odd(3) << endl;
    cout << is_odd(4) << endl;
    // filter
    //copy_if(numbers.begin(),numbers.end(), back_inserter(even_numbers), EvenPredicate());

    return 0;
}
