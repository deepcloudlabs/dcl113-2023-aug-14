#include <iostream>
#include <vector>
#include <fstream>
#include <execution>
#include <parallel/algorithm>
#include <ranges>

using namespace std;
ifstream
open_file(const string& file){
    cout << "open_file() is called." << endl;
    return ifstream(file);
}

int
count_lines_in_file(ifstream input_file){
    cout << "count_lines_in_file() is called." << endl;
    return count(istreambuf_iterator<char>(input_file),istreambuf_iterator<char>(), '\n');
}

template <std::ranges::range R>
constexpr auto
to_vector(R &&r){
    using elem_t = std::decay_t<std::ranges::range_value_t<R>>;
    return vector<elem_t>{r.begin(),r.end()};
}

vector<int>
count_lines_declarative_ranges(const vector<string> &files){
     // string -> ifstream -> int
    return to_vector(files | std::ranges::views::transform(open_file) | std::ranges::views::transform(count_lines_in_file));
}
// string -> int
int
count_line(const string &file) {
    ifstream input_file(file);
    char c;
    auto line_count = 0;
    while (input_file.get(c)) {
        if (c == '\n')
            line_count++;
    }
    return line_count;
}

vector<int>
count_lines_declarative(const vector<string> &files) {
    vector<int> line_counts(files.size());
    transform(execution::par,files.begin(), files.end(), line_counts.begin(), count_line); // internal loop
    return line_counts;
}

auto
get_total_lines_declarative(const vector<string> &files) {
    vector<int> line_counts(files.size());
    transform(execution::par,files.begin(), files.end(), line_counts.begin(), count_line); // internal loop
    return accumulate(line_counts.begin(),line_counts.end(),0,plus<int>());
}

auto
get_total_lines_declarative2(const vector<string> &files) {
    return accumulate(files.begin(), files.end(),0,[](int total_lines,const string& file){
        return total_lines + count_line(file);
    });
}

vector<int>
count_lines_imperative(const vector<string> &files) {
    vector<int> line_counts;
    for (const auto &file: files) { // external loop
        /*
        ifstream input_file(file);
        char c;
        auto line_count = 0;
        while (input_file.get(c)) {
            if (c == '\n')
                line_count++;
        }*/
        line_counts.push_back(count_line(file));
    }
    return line_counts;
}

int main() {
    vector<string> files;
    files.push_back(string("c:\\tmp\\dictionary-tur.txt"));
    files.push_back(string("c:\\tmp\\dictionary-eng.txt"));
    files.push_back(string("c:\\tmp\\algotrading-market-apis.txt"));
    files.push_back(string("c:\\tmp\\cluster-info.txt"));

    // imperative programming: procedural (like in C), or oop (like in c++)
    auto total_line_count = 0;
    for (auto &line_count: count_lines_imperative(files)) {
        cout << "imperative: " << line_count << endl;
        total_line_count += line_count;
    }
    cout << "total line count: " << total_line_count << endl;
    // declarative programming: functional programming (like since c++11) : stl-based
    for (auto &line_count: count_lines_declarative(files)) {
        cout << "declarative (stl): " << line_count << endl;
    }
    // declarative programming: functional programming (like since c++11) : ranges (since c++20)
    for (auto &line_count: count_lines_declarative_ranges(files)) {
        cout << "declarative (ranges): " << line_count << endl;
    }
    cout << "total line count: " << get_total_lines_declarative(files) << endl;
    cout << "total line count (alternative): " << get_total_lines_declarative2(files) << endl;
    return 0;
}

