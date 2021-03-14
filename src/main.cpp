#include <iostream>
#include <vector>
#include <memory>

#include "Sorter.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "HeapSort.hpp"
#include "IntroSort.hpp"

using std::shared_ptr;

int main(int argc, char* argv[])
{
    std::vector<shared_ptr<Sorter<int>>> Sorters;
    SortType type = DES;

    shared_ptr<Sorter<int>> M = std::make_shared<MergeSort<int>>(type);
    Sorters.push_back(M);
    
    shared_ptr<Sorter<int>> N = std::make_shared<QuickSort<int>>(type);
    Sorters.push_back(N);
    
    shared_ptr<Sorter<int>> O = std::make_shared<HeapSort<int>>(type);
    Sorters.push_back(O);

    shared_ptr<Sorter<int>> P = std::make_shared<IntroSort<int>>(type);
    Sorters.push_back(P);

    int array[4][10] = {{4, 10, 5, 2, 3, 7, 6, 9, 8, 1},
                        {4, 10, 5, 2, 3, 7, 6, 9, 8, 1},
                        {4, 10, 5, 2, 3, 7, 6, 9, 8, 1},
                        {4, 10, 5, 2, 3, 7, 6, 9, 8, 1}};

    int size = sizeof(*array) / sizeof(**array);
    int l = 0;
    int r = size - 1;

    for (int i = 0; i < (int)Sorters.size(); ++i)
    {
        Sorters[i]->sort(array[i], l, r);

        std::cout << std::endl;
        std::cout << "Po sortowaniu[" << i << "]:" << std::endl;
        for (int j = 0; j < size; ++j)
        {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}