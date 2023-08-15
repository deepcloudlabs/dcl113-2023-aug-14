#include <iostream>
#include <vector>
#include <ranges>

using namespace std;

auto if_even = [](int value) {
    cout << "if_even(" << value << ")" << endl;
    return value % 2 == 0;
};
auto cubed = [](int value) {
    cout << "cubed(" << value << ")" << endl;
    return value*value*value;
};

int main() {
    vector<int> numbers{4, 8, 15, 16, 23, 42};
    for (auto number: numbers | std::ranges::views::filter(if_even)
                              | std::ranges::views::transform(cubed)
    ) {
        cout << "[for loop] number: " << number << endl;
    }

    return 0;
}
