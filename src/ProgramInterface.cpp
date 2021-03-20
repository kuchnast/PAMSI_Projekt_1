#include <ctime>
#include <iomanip>
#include <chrono>
#include <cstdlib>

#include "ProgramInterface.hpp"

using std::cin;
using std::cout;
using std::endl;

using MS = MergeSort<int>;
using QS = QuickSort<int>;
using IS = IntroSort<int>;

void ShowMenu()
{
    cout << "========== MENU ==========" << endl;
    cout << "1) Read array." << endl;
    cout << "2) Write array." << endl;
    cout << "3) Generate array." << endl;
    cout << "4) Choose sorting algorithm." << endl;
    cout << "5) Sort array." << endl;
    cout << "6) Check if array is sorted." << endl;
    cout << "7) Efficiency tests." << endl;
    cout << "9) Exit." << endl;
    cout << "0) Show menu." << endl;
}

void ReadArray(TestingSorters<int> & T)
{
    char c;
    int *array;

    cout << "\t1) Insert array elements" << endl;
    cout << "\t2) Read array from file" << endl;
    cout << "\t9) Cancel" << endl;
    do
    {
        cout << "\tChoose option: ";
        cin >> c;
        switch (c)
        {
        case '1':
        {
            size_t size;
            cout << "\t\tNumber of elements: ";
            cin >> size;
            array = new int[size];
            cout << "\t\tElements: ";
            for (size_t i = 0; i < size; ++i)
            {
                cin >> array[i];
            }
            T.InsertInputData(size, array);
            c = '9';
            break;
        }
        case '2':
        {
            std::string path;
            cout << "\t\tPath to file: ";
            cin >> path;
            if(T.ReadInputData(path))
            {
                cout << "\t\tNew array size: " << T.GetSize() << endl;
                cout << "\t\tDo you want to print it? (y) ";
                cin >> c;
                if(c == 'y')
                    T.PrintArray();
            }
            else
            {
                cout << "\t\tError: Can't read data or invalid file." << endl;
            }

            c = '9';
            break;
        }
        case '9':
        {
            cout << "\tCanceled.\n";
            break;
        }
        default:
        {
            cout << "\tInvalid argument." << endl;
            break;
        }
        }
    } while (c != '9');
}

void WriteArray(TestingSorters<int> &T)
{
    char c;

    cout << "\t1) Print array elements" << endl;
    cout << "\t2) Write array to file" << endl;
    cout << "\t9) Cancel" << endl;
    do
    {
        cout << "\tChoose option: ";
        cin >> c;
        switch (c)
        {
        case '1':
        {
            cout << "\t\tNumber of elements: " << T.GetSize() << endl;
            cout << "\t\tElements: ";
            T.PrintArray();
            c = '9';
            break;
        }
        case '2':
        {
            std::string path;
            cout << "\t\tPath to file: ";
            cin >> path;
            if(T.WriteOutputData(path))
            {
                cout << "\t\tSaved array size: " << T.GetSize() << endl;
            }
            else
            {
                cout << "\t\tError: Can't write data or invalid file." << endl;
            }

            c = '9';
            break;
        }
        case '9':
        {
            cout << "\t\tCanceled.\n";
            break;
        }
        default:
        {
            cout << "\t\tInvalid argument." << endl;
            break;
        }
        }
    } while (c != '9');
}

void GenerateArray(TestingSorters<int> &T)
{
    char c;
    size_t size;

    cout << "\t1) Generate random array" << endl;
    cout << "\t2) Generate partly sorted array by current algorithm" << endl;
    cout << "\t9) Cancel" << endl;

    do
    {
        cout << "\tChoose option: ";
        cin >> c;
        switch (c)
        {
        case '1':
        {
            cout << "\t\tNumber of elements: ";
            cin >> size;
            T.FillArrayRandom(size);
            c = '9';
            break;
        }
        case '2':
        {
            double percent;

            cout << "\t\tNumber of elements: ";
            cin >> size;
            cout << "\t\tPercent of array to sort: (0-100): ";
            cin >> percent;
            T.FillArrayPartlySorted(size, percent);
            c = '9';
            break;
        }
        case '9':
        {
            cout << "\tCanceled.\n";
            break;
        }
        default:
        {
            cout << "\tInvalid argument." << endl;
            break;
        }
        }
    } while (c != '9');
}

void ChooseSortingAlgorithm(TestingSorters<int> &T)
{
    char c;
    SortType order;

    cout << "\tChose sorting order" << endl;
    cout << "\tA) Ascending" << endl;
    cout << "\tD) Descending" << endl;
    
    do
    {
        cout << "\tChoose option: ";
        cin >> c;
        switch (c)
        {
        case 'A':
        {
            order = ASC;
            break;
        }
        case 'D':
        {
            order = DES;
            break;
        }
        default:
        {
            cout << "\tInvalid argument." << endl;
            break;
        }
        }
    } while (c != 'A' && c != 'D');

    cout << "\t1) QuickSort" << endl;
    cout << "\t2) MergeSort" << endl;
    cout << "\t3) IntroSort" << endl;
    cout << "\t9) Cancel" << endl;

    do
    {
        cout << "\tChoose option: ";
        cin >> c;
        switch (c)
        {
        case '1':
        {
            T.ChangeSorter(std::make_shared<QS>(order));
            c = '9';
            break;
        }
        case '2':
        {
            T.ChangeSorter(std::make_shared<MS>(order));
            c = '9';
            break;
        }
        case '3':
        {
            IS Temp(order);
            T.ChangeSorter(std::make_shared<IS>(order));
            c = '9';
            break;
        }
        case '9':
        {
            cout << "\tCanceled.\n";
            break;
        }
        default:
        {
            cout << "\tInvalid argument." << endl;
            break;
        }
        }
    } while (c != '9');
}

void RunSorting(TestingSorters<int> &T)
{
    using namespace std::chrono;

    auto time = system_clock::to_time_t(system_clock::now());
    cout << "Sorting starts at " << std::put_time(std::localtime(&time), "%F %T.\n") << std::flush << endl;

    auto duration_us = T.RunSort();

    time = system_clock::to_time_t(system_clock::now());
    cout << "Sorting ends at " << std::put_time(std::localtime(&time), "%F %T.\n") << std::flush << endl;

    cout << "Time taken by function: " << endl;
    cout << "\t" << duration_us.count() << " microseconds" << endl;
    cout << "\t" << duration_us.count() / 1000 << " miliseconds" << endl;
    cout << "\t" << duration_us.count() / 1000000 << " seconds" << endl;
}

void TestIfSorted(TestingSorters<int> &T)
{
    if(T.TestIfSorted(ASC))
    {
        cout << "Array is sorted in ascending order." << endl;
    }
    else
    {
        if(T.TestIfSorted(DES))
        {
            cout << "Array is sorted in descending order." << endl;
        }
        else
        {
            cout << "Array is not sorted." << endl;
        }
    }
}

bool GenerateTestSummary(size_t number, size_t size, std::string folder_path, std::chrono::microseconds *duration, bool *state)
{
    std::ofstream file;

    file.open(folder_path + "/summary.txt", std::ios::out);
    file << "Size" << ',' << "Duration_in_us" << ',' << "If_sorted" << endl;

    if(file.is_open())
    {
        for (size_t i = 0; i < number; ++i)
        {
            file << size << ',' << duration[i].count() << ',' << state[i] << endl;
        }
    }
    else
    {
        return false;
    }
    return true;
}

void NRandomArraysTest(TestingSorters<int> *T, size_t number, size_t size, std::string folder_path)
{
    std::string path;

    cout << "Generating and saving input data... ";
    for (size_t i = 0; i < number; ++i)
    {
        T[i].FillArrayRandom(size);
        path = folder_path + "/in/test_" + std::to_string(i) + ".in";
        T[i].WriteOutputData(path);
    }
    cout << "DONE" << endl;

    std::chrono::microseconds *duration = new std::chrono::microseconds[number];

    cout << "Sorting... " << endl;
    for (size_t i = 0; i < number; ++i)
    {
        duration[i] = T[i].RunSort();
        cout << "\tTest " << i << " done. (" << duration[i].count() / 1000 << " ms)" << endl;
    }
    cout << "DONE" << endl;

    cout << "Saving output data... ";
    for (size_t i = 0; i < number; ++i)
    {
        path = folder_path + "/out/test_" + std::to_string(i) + ".out";
        T[i].WriteOutputData(path);
    }
    cout << "DONE" << endl;

    bool *state = new bool[number];

    cout << "Check if data are sorted... " << endl;
    for (size_t i = 0; i < number; ++i)
    {
        state[i] = T[i].TestIfSorted(ASC);
        cout << "\tTest " << i << " done. (" << (state[i] ? "true" : "false") << ")" << endl;
    }
    cout << "DONE" << endl;

    cout << "Generating tests summary..." << endl;
    GenerateTestSummary(number, size, folder_path, duration, state);
    cout << "DONE" << endl;

    delete[] duration;
    delete[] state;
}

void NPartlySortedArraysTest(TestingSorters<int> *T, size_t number, size_t size, std::string folder_path, double percent)
{
    std::string path;

    cout << "Generating and saving input data... ";
    for (size_t i = 0; i < number; ++i)
    {
        T[i].FillArrayPartlySorted(size, percent);
        path = folder_path + "/in/test_" + std::to_string(i) + ".in";
        T[i].WriteOutputData(path);
    }
    cout << "DONE" << endl;

    std::chrono::microseconds *duration = new std::chrono::microseconds[number];

    cout << "Sorting... " << endl;
    for (size_t i = 0; i < number; ++i)
    {
        duration[i] = T[i].RunSort();
        cout << "\tTest " << i << " done. (" << duration[i].count() / 1000 << " ms)" << endl;
    }
    cout << "DONE" << endl;

    cout << "Saving output data... ";
    for (size_t i = 0; i < number; ++i)
    {
        path = folder_path + "/out/test_" + std::to_string(i) + ".out";
        T[i].WriteOutputData(path);
    }
    cout << "DONE" << endl;

    bool *state = new bool[number];

    cout << "Check if data are sorted... " << endl;
    for (size_t i = 0; i < number; ++i)
    {
        state[i] = T[i].TestIfSorted(ASC);
        cout << "\tTest " << i << " done. (" << (state[i] ? "true" : "false") << ")" << endl;
    }
    cout << "DONE" << endl;

    cout << "Generating tests summary..." << endl;
    GenerateTestSummary(number, size, folder_path, duration, state);
    cout << "DONE" << endl;

    delete[] duration;
    delete[] state;
}

void NRandomReverseSortedArraysTest(TestingSorters<int> *T, size_t number, size_t size, std::string folder_path)
{
    std::string path;

    cout << "Generating and saving input data... ";
    for (size_t i = 0; i < number; ++i)
    {
        T[i].FillArrayReverseSorted(size);
        path = folder_path + "/in/test_" + std::to_string(i) + ".in";
        T[i].WriteOutputData(path);
    }
    cout << "DONE" << endl;

    std::chrono::microseconds *duration = new std::chrono::microseconds[number];

    cout << "Sorting... " << endl;
    for (size_t i = 0; i < number; ++i)
    {
        duration[i] = T[i].RunSort();
        cout << "\tTest " << i << " done. (" << duration[i].count() / 1000 << " ms)" << endl;
    }
    cout << "DONE" << endl;

    cout << "Saving output data... ";
    for (size_t i = 0; i < number; ++i)
    {
        path = folder_path + "/out/test_" + std::to_string(i) + ".out";
        T[i].WriteOutputData(path);
    }
    cout << "DONE" << endl;

    bool *state = new bool[number];

    cout << "Check if data are sorted... " << endl;
    for (size_t i = 0; i < number; ++i)
    {
        state[i] = T[i].TestIfSorted(ASC);
        cout << "\tTest " << i << " done. (" << (state[i] ? "true" : "false") << ")" << endl;
    }
    cout << "DONE" << endl;

    cout << "Generating tests summary..." << endl;
    GenerateTestSummary(number, size, folder_path, duration, state);
    cout << "DONE" << endl;

    delete[] duration;
    delete[] state;
}

void EfficiencyTests()
{
    char c;
    size_t number, size;
    std::string folder_path, command;

    cout << "\tNumber of arrays: ";
    cin >> number;
    cout << "\tArray size: ";
    cin >> size;
    cout << "\tOutput folder: ";
    cin >> folder_path;

    cout << "\tSorting algotithms: " << endl;
    cout << "\t1) QuickSort" << endl;
    cout << "\t2) MergeSort" << endl;
    cout << "\t3) IntroSort" << endl;

    system(("mkdir " + folder_path).c_str());
    system(("mkdir " + folder_path + "/in").c_str());
    system(("mkdir " + folder_path + "/out").c_str());

    TestingSorters<int> *T = new TestingSorters<int>[number];

    do
    {
        cout << "\tChoose option: ";
        cin >> c;
        switch (c)
        {
        case '1':
        {
            for (size_t i = 0; i < number; ++i)
                T[i].ChangeSorter(std::make_shared<QS>(ASC));
            c = '9';
            break;
        }
        case '2':
        {
            for (size_t i = 0; i < number; ++i)
                T[i].ChangeSorter(std::make_shared<MS>(ASC));
            c = '9';
            break;
        }
        case '3':
        {
            for (size_t i = 0; i < number; ++i)
                T[i].ChangeSorter(std::make_shared<IS>(ASC));
            c = '9';
            break;
        }
        default:
        {
            cout << "\tInvalid argument." << endl;
            break;
        }
        }
        } while (c != '9');

        cout << "=========================" << endl;
        cout << "\t1) n random arrays test" << endl;
        cout << "\t2) n partly sorted arrays test" << endl;
        cout << "\t3) n random arrays sorted in descending order" << endl;
        cout << "\t9) Cancel" << endl;
        cout << "=========================" << endl;

        do
        {
            cout << "\tChoose option: ";
            cin >> c;
            switch (c)
            {
            case '1':
            {
                NRandomArraysTest(T, number, size, folder_path);
                c = '9';
                break;
            }
            case '2':
            {
                double percent;

                cout << "\tChoose percent: ";
                cin >> percent;
                NPartlySortedArraysTest(T, number, size, folder_path, percent);
                c = '9';
                break;
            }
            case '3':
            {
                NRandomReverseSortedArraysTest(T, number, size, folder_path);
                c = '9';
                break;
            }
            case '9':
            {
                cout << "\tCanceled.\n";
                break;
            }
            default:
            {
                cout << "\tInvalid argument." << endl;
                break;
            }
            }
    } while (c != '9');

    delete[] T;
}