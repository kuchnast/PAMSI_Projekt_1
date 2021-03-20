#include <iostream>
#include <vector>
#include <memory>

#include "Sorter.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "HeapSort.hpp"
#include "IntroSort.hpp"
#include "TestingSorters.hpp"
#include "ProgramInterface.hpp"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    try
    {
        char option;
        TestingSorters<int> T;

        ShowMenu();
        do
        {
            cout << "Choose option: ";
            cin >> option;
            switch (option)
            {
            case '1':
            {
                ReadArray(T);
                break;
            }
            case '2':
            {
                WriteArray(T);
                break;
            }
            case '3':
            {
                GenerateArray(T);
                break;
            }
            case '4':
            {
                ChooseSortingAlgorithm(T);
                break;
            }
            case '5':
            {
                RunSorting(T);
                break;
            }
            case '6':
            {
                TestIfSorted(T);
                break;
            }
            case '7':
            {
                EfficiencyTests();
                break;
            }
            case '9':
            {
                cout << "Exiting the program..." << endl;
                break;
            }
            case '0':
            {
                ShowMenu();
                break;
            }
            default:
            {
                cout << "Invalid argument." << endl;
                break;
            }
            }
        } while (option != '9');
    }
     catch (const std::invalid_argument &e)
    {
        cerr << e.what() << "\nKończenie pracy programu." << endl;
    }
    catch (...)
    {
        cerr << "Nieznany wyjątek.\nKończenie pracy programu." << endl;
    }
    return 0;
}