#include <iostream>
#include <vector>

// Filling the auxiliary array
void auxiliary_vector(std::vector<int> &domain, int &M) {
    for(int i = 0; i < M; i++) {
        domain.push_back(i);
    }
}

// Marking numbers from the "input" array
int marking_vector(std::vector<int> &array, std::vector<int> &domain) {
    int size = domain.size();
    for(auto i: array) {
        if(i >= size || i < 0) {
            std::cerr << i << " is invalid number in input array!\n";
            return 1;
        }
        domain[i] = -1; 
    }
	return 0;
}

int check_the_sizes(int &M, int& array_size) {
    if(M < array_size) {
        std::cerr << "Invalid sizes!\n";
        return 1;
    }
	return 0;
}

int main(void) {
    // "Input" array and it's size
    std::vector<int> array;
    int array_size;

    // Auxiliary array and it's size
    std::vector<int> domain;
    int M;

    std::cout << "Введите M и размер массива" << std::endl;
    std::cin >> M >> array_size;

    int result = check_the_sizes(M, array_size);
	
	  if (result) return result;
	
    // Auxiliary variable for reading
    int number;
    std::cout << "Введите массив" << std::endl;
    for(int i = 0; i < array_size; i++) {
        std::cin >> number;
        if (std::cin.fail()) return 1;
        array.push_back(number);
    }

    auxiliary_vector(domain, M);
    result = marking_vector(array, domain);
	  if (result) return result;

    // Unmarked elements are reqiered
    for(int i = 0; i < M; i++) {
        if(domain[i] != -1) {
            std::cout << domain[i] << " ";
        } 
    }
    std::cout << std::endl;
}