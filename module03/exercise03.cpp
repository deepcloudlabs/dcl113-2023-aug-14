#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <fstream>
#include "person.h"

template<class T, class OrderBy, class CompareBy>
decltype(auto)
getOrder(OrderBy orderBy, CompareBy compareBy) { // higher-order function
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
print_person(ostream& out, const person &p,person::output_format format) {
    if (format == person::name_only)
      out << p.surname() << ", " << p.name() << endl;
    else if (format == person::full_details)
      out << p.surname() << ", " << p.name() << ": age= " << p.age() << ", salary: " << p.salary() << endl;
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

auto
is_older(const person& p,int age){
    return p.age() > age;
}

int main() {
    vector<person> employees{
            {"kate",   "austen", person::gender_t::female, 46, 100'000.0},
            {"sun",    "kwon",   person::gender_t::male,   43, 150'000.0},
            {"jin",    "kwon",   person::gender_t::female, 38, 170'000.0},
            {"ben",    "linus",  person::gender_t::male,   58, 50'000.0},
            {"juliet", "burke",  person::gender_t::female, 48, 70'000.0},
            {"john",   "locke",  person::gender_t::male,   64, 80'000.0}
    };
    vector<person> experienced_employees;
    vector<person> inexperienced_employees;
    ofstream emp_file;
    emp_file.open("inexpreienced_employees.txt");
    auto is_experienced = bind(is_older,placeholders::_1,50);
    auto is_inexperienced = [&is_experienced](person &p){return !is_experienced(p);};
    auto print_person_name_only = bind(print_person,ref(emp_file),placeholders::_1,person::name_only);
    auto print_person_all_details = bind(print_person,ref(cout),placeholders::_1,person::full_details);
    auto orderByAgeDesc = getOrder<person>(byAge, greater<int>());
    auto orderByAgeAsc = bind(orderByAgeDesc,placeholders::_2,placeholders::_1);
    auto result = orderByAgeDesc(employees[0],employees[1]);
    cout << "result: " << result << endl ;

    cout << "Sorting by age in descending order..." << endl;
    sort(employees.begin(), employees.end(), orderByAgeDesc);
    for_each(employees.begin(), employees.end(), print_person_all_details);

    cout << "Sorting by age in ascending order..." << endl;
    sort(employees.begin(), employees.end(), orderByAgeAsc);
    for_each(employees.begin(), employees.end(), print_person_all_details);

    cout << "Experienced employees: " << endl;
    copy_if(employees.begin(),employees.end(), back_inserter(experienced_employees), is_experienced );
    for_each(experienced_employees.begin(),experienced_employees.end(), print_person_all_details);

    cout << "Inexperienced employees: " << endl;
    copy_if(employees.begin(),employees.end(), back_inserter(inexperienced_employees), is_inexperienced );
    for_each(inexperienced_employees.begin(),inexperienced_employees.end(), print_person_name_only);


    return 0;
}
