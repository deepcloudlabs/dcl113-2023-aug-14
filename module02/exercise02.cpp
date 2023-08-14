#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "person.h"

using namespace std;

auto
csum(double partial_sum, const person &p) {
    cout << "csum() is called." << endl;
    return p.salary() + partial_sum;
}

struct AddSalary {
    auto
    operator()(double partial_sum, const person &p) const {
        cout << "operator()(double, const person &)() is called." << endl;
        return p.salary() + partial_sum;
    }
};

int main() {
    vector<person> employees{
            {"kate",   "austen", person::gender_t::female, 46, 100'000.0},
            {"sun",    "kwon",   person::gender_t::male,   43, 150'000.0},
            {"jin",    "kwon",   person::gender_t::female, 38, 170'000.0},
            {"ben",    "linus",  person::gender_t::male,   58, 50'000.0},
            {"juliet", "burke",  person::gender_t::female, 48, 70'000.0},
            {"john",   "locke",  person::gender_t::male,   64, 80'000.0}
    };
    auto sum_lambda = [](double partial_sum, const person &p) {
        cout << "sum_lambda() is called." << endl;
        return p.salary() + partial_sum;
    };
    // 1. global c-like function
    auto total_salary = accumulate(employees.begin(), employees.end(), 0.0, csum);
    // 2. functor
    total_salary = accumulate(employees.begin(), employees.end(), 0.0, AddSalary());
    // 3. lambda expression
    total_salary = accumulate(employees.begin(), employees.end(), 0.0,sum_lambda);

    cout << "Average salary: " << total_salary / static_cast<double>(employees.size()) << endl;
    return 0;
}