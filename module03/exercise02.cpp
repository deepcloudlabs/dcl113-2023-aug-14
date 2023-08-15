#include <iostream>
#include <vector>
#include <parallel/algorithm>
#include <parallel/numeric>

using namespace std;
class A {}; // class: A

auto
fun(){
    return [](auto value) { cout << value << " "; };
}

int main() {
    auto f1 = fun();
    A a; // object: a
    vector<int> numbers{4,8,15,16,23,42};
    vector<int> even_numbers;
    vector<int> cubed_numbers;
    // filter: 500k, 1-PASS: 1M
    copy_if(numbers.begin(),numbers.end(), back_inserter(even_numbers), [](int p){ return p%2 == 0; });
    auto print = // object
            [](auto value) { cout << value << " "; }; // class -> function object
    std::for_each(even_numbers.begin(), even_numbers.end(), print);
    // map: 500k, 1-PASS: 500k
    transform(even_numbers.begin(),even_numbers.end(), back_inserter(cubed_numbers), [](auto u) { return u*u*u;});
    cout << endl;
    std::for_each(cubed_numbers.begin(), cubed_numbers.end(),print);
    // reduce: 0, 1-PASS: 500k
    auto result =
    // accumulate(cubed_numbers.begin(), cubed_numbers.end(),int(),[](auto u, decltype(u) v){ return u+v; });
    accumulate(cubed_numbers.begin(), cubed_numbers.end(),int(),plus<>());
    // 3-PASS, 2M
    cout << endl << "result is " << result << endl;
    // Memory usage: 500k + 500k: 1M element
    // CPU usage: multi-core, n cpu
    // Ranges -> | -> pipeline -> 1-PASS (1M), no additional memory usage, parallel solution is still missing!
    return 0;
}
