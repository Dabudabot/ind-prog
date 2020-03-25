#include <iostream>
#include <vector>

int main(void) {
    int x;
    std::cin >> x;

    for (int i = 0; i < x; i++)
    {
        long long y;
        std::cin >> y;

        if (std::cin.fail()) return 1;

        if (y % 3 == 0 && y % 5 == 0)
        {
            std::cout << "fizzbuzz ";
        }
        else if (y % 3 == 0)
        {
            std::cout << "fizz ";
        }
        else if (y % 5 == 0)
        {
            std::cout << "buzz ";
        }
        else
        {
            std::cout << y << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}