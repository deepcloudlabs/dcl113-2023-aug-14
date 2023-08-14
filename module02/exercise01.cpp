#include <iostream>
#include <vector>
#include <algorithm>
#include "person.h"

using namespace std;

template<class T, class OrderByFirst, class CompareByFirst, class OrderBySecond, class CompareBySecond>
decltype(auto)
then(OrderByFirst orderByFirst, CompareByFirst compareByFirst,
     OrderBySecond orderBySecond, CompareBySecond compareBySecond) {
    return [orderByFirst, compareByFirst, orderBySecond, compareBySecond](const T &first,
                                                                          const T &second) -> bool { // body
        if (orderByFirst(first) == orderByFirst(second))
            return compareBySecond(orderBySecond(first), orderBySecond(second));
        return compareByFirst(orderByFirst(first), orderByFirst(second));
    };
}

template<class T, class OrderBy, class CompareBy>
decltype(auto)
getOrder(OrderBy orderBy, CompareBy compareBy) { // higher-order function
    // functions can be one of the following:
    //   i) c function,
    //  ii) struct/class + overloading operator (): Function Object/functor
    // iii) lambda expression (like a class) + closure (like an object)
    // capturing?
    // parameters
    return [orderBy, compareBy](const T &first, const T &second) -> bool { // body
        return compareBy(orderBy(first), orderBy(second));
    };
}

auto
byAge(const person &p) {
    return p.age();
}

auto
bySalary(const person &p) {
    return p.salary();
}

auto
bySurname(const person &p) {
    return p.surname();
}

auto
print_person(const person &p) {
    cout << p.surname() << ", " << p.name() << ": age= " << p.age() << ", salary: " << p.salary() << endl;
}

template<typename T>
struct DESC {
    bool
    operator()(const T &first, const T &second) const { return first > second; }
};

template<typename T>
struct ASC {
    bool
    operator()(const T &first, const T &second) const { return first < second; }
};

struct ByName {
    auto operator()(const person &p) const {
        return p.name();
    }
};

int main() {
    auto byName = [](const person &p) { return p.name(); };
    vector<person> employees{
            {"kate",   "austen", person::gender_t::female, 46, 100'000.0},
            {"sun",    "kwon",   person::gender_t::male,   43, 150'000.0},
            {"jin",    "kwon",   person::gender_t::female, 38, 170'000.0},
            {"ben",    "linus",  person::gender_t::male,   58, 50'000.0},
            {"juliet", "burke",  person::gender_t::female, 48, 70'000.0},
            {"john",   "locke",  person::gender_t::male,   64, 80'000.0}
    };
    // higher-order function
    for_each(employees.begin(), employees.end(), print_person); // (i)
    // higher-order function, generic programming
    sort(employees.begin(), employees.end(), getOrder<person>(byAge, greater<int>()));
    // higher-order function
    for_each(employees.begin(), employees.end(), print_person); // (i)
    // higher-order function, generic programming
    sort(employees.begin(), employees.end(), getOrder<person>(byAge, less<int>()));
    // higher-order function
    for_each(employees.begin(), employees.end(), print_person); // (i)
    // higher-order function, generic programming
    sort(employees.begin(), employees.end(), getOrder<person>(bySalary, greater<int>()));
    // higher-order function
    for_each(employees.begin(), employees.end(), print_person); // (i)
    // higher-order function, generic programming
    sort(employees.begin(), employees.end(), getOrder<person>(bySurname, greater<string>()));
    // higher-order function
    for_each(employees.begin(), employees.end(), print_person); // (i)    // higher-order function, generic programming
    sort(employees.begin(), employees.end(), getOrder<person>(ByName(), less<string>()));
    // higher-order function
    for_each(employees.begin(), employees.end(), print_person); // (i)
    sort(employees.begin(), employees.end(), then<person>(bySurname, less<string>(),byName, less<string>()));
    // higher-order function
    for_each(employees.begin(), employees.end(), print_person); // (i)    return 0;
}
