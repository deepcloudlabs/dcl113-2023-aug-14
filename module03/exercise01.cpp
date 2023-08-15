#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
int x=549;

const auto&
fun1(){
    return x;
}

auto
factorial(int n){
    if (n==0) return 1;
    else return factorial(n-1) * n;
}

/* error
auto
factorial2(int n){
    if (n>0)
        return factorial2(n-1) * n;
    else
        return 1;
}
 */

decltype(auto)
fun3(){
    return 42 * x;
}

int fun4(){ return 108;}

typedef decltype(fun4) *fun_ptr;
// (2) Function Object
struct EvenPredicate {
    bool operator()(int p){
         return p%2 == 0;
     }
};

template <class T>
struct PrintFunction {
    void operator()(T value){
         cout << value << " ";
     }
};

template <class T>
struct ToCube {
    T operator()(T u){
         return u*u*u;
     }
};

template <class T>
struct SumReducer {
    T operator()(T u,T v){
        return u+v;
    }
};

int main() {
    vector<int> numbers{4,8,15,16,23,42};
    vector<int> even_numbers;
    vector<int> cubed_numbers;
    // filter
    copy_if(numbers.begin(),numbers.end(), back_inserter(even_numbers), EvenPredicate());
    std::for_each(even_numbers.begin(), even_numbers.end(),PrintFunction<int>());
    // map
    transform(even_numbers.begin(),even_numbers.end(), back_inserter(cubed_numbers), ToCube<int>());
    cout << endl;
    std::for_each(cubed_numbers.begin(), cubed_numbers.end(),PrintFunction<int>());
    // reduce
    auto result =
    accumulate(cubed_numbers.begin(), cubed_numbers.end(),int(),SumReducer<int>());
    cout << endl << "result is " << result << endl;
    return 0;
}
