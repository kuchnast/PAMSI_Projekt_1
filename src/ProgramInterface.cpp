#include <ctime>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <numeric>

#include "ProgramInterface.hpp"

using std::cin;
using std::cout;
using std::endl;

using S = Sorter<int>;
using MS = MergeSort<int>;
using QS = QuickSort<int>;
using IS = IntroSort<int>;
using IFC = SorterInterface<int>;

const std::array<int, 5> num_of_elements = {10000, 50000, 100000, 500000, 1000000}; ///< number of elements in array for tests
const std::array<double, 6> percent_values = {25, 50, 75, 95, 99, 99.7};    ///< percentages for partlySorted tests

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

void ReadArray(IFC &T)
{
    char c;

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

            std::vector<int> temp;
            temp.reserve(size);

            cout << "\t\tElements: ";
            for (size_t i = 0; i < size; ++i)
            {
                cin >> temp[i];
            }
            T.FillArray(temp);
            c = '9';
            break;
        }
        case '2':
        {
            std::string path;
            cout << "\t\tPath to file: ";
            cin >> path;
            if(T.ReadFromFile(path))
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

void WriteArray(IFC &T)
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
            if(T.WriteToFile(path))
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

void GenerateArray(IFC &T)
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

void ChooseSortingAlgorithm(IFC &T)
{
    char c;
    SortOrder order;

    cout << "\tChose sorting order:" << endl;
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
            T.SetSorter(std::unique_ptr<S>(new QS(order)));
            c = '9';
            break;
        }
        case '2':
        {
            T.SetSorter(std::unique_ptr<S>(new MS(order)));
            c = '9';
            break;
        }
        case '3':
        {
            T.SetSorter(std::unique_ptr<S>(new IS(order)));
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

void RunSorting(IFC &T)
{
    using namespace std::chrono;

    auto time = system_clock::to_time_t(system_clock::now());
    cout << "Sorting starts at " << std::put_time(std::localtime(&time), "%F %T.\n") << std::flush << endl;

    uint64_t duration_us = T.RunSort();

    time = system_clock::to_time_t(system_clock::now());
    cout << "Sorting ends at " << std::put_time(std::localtime(&time), "%F %T.\n") << std::flush << endl;

    cout << "Time taken by function: " << duration_us << " microseconds" << endl;
}

void TestIfSorted(IFC &T)
{
    if(T.TestIfSorted())
    {
        cout << "Array is sorted" << endl;
    }
    else
    {
        cout << "Array is not sorted." << endl;
    }
}

void PerformanceTests()
{
    char c;
    std::string path;

    cout << "=========================" << endl;
    cout << "\t1) Generate all random arrays" << endl;
    cout << "\t2) Random arrays test" << endl;
    cout << "\t3) Partly sorted arrays test" << endl;
    cout << "\t4) Random arrays sorted in descending order" << endl;
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
            cout << "\tPath to folder wher arrays will be generated: ";
            cin >> path;
            GenerateAllRandomArrays(path);
            c = '9';
            break;
        }
        case '2':
        {
            cout << "\tPath to folder where arrays was saved: ";
            cin >> path;
            RandomArraysTest(path);
            c = '9';
            break;
        }
        case '3':
        {
            cout << "\tPath to folder where arrays was saved: ";
            cin >> path;
            PartlySortedArraysTest(path);
            c = '9';
            break;
        }
        case '4':
        {
            cout << "\tPath to folder where arrays was saved: ";
            cin >> path;
            ReverseArraysTest(path);
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

void GenerateAllRandomArrays(const std::string &path)
{
    IFC T;

    for (size_t i = 0; i < num_of_elements.size(); ++i)
    {
        std::string temp_path(path + '/' + std::to_string(num_of_elements[i]) + "/in");
        cout << "Generating " << ARRAYS_NUM << " arrays with size " << num_of_elements[i] << "...\n" << std::flush;
        for (int j = 0; j < ARRAYS_NUM; ++j)
        {
            cout << "\tProgress " << j + 1<< '/' << ARRAYS_NUM << '\n' << std::flush;

            T.FillArrayRandom(num_of_elements[i], num_of_elements[i] / 10);
            if(T.WriteToFile(temp_path + std::to_string(j) + ".txt"))
                throw std::runtime_error("Error writing to file");
        }
    }
}

void RandomArraysTest(const std::string &path)
{
    std::string testName("RandomTest");
    std::array<int64_t, ARRAYS_NUM> duration;
    std::array<bool, ARRAYS_NUM> state;
    std::array<std::string, 3> sorters = {"QuickSort", "MergeSort", "IntroSort"};
    std::array<IFC, 3> T = {IFC(std::unique_ptr<S>(new QS(ASC))), 
                            IFC(std::unique_ptr<S>(new MS(ASC))), 
                            IFC(std::unique_ptr<S>(new IS(ASC)))};

    for (size_t n = 0; n < T.size(); ++n)
    {
        cout << "Runing tests for " << sorters[n] << " ...\n" << std::flush;

        for (size_t i = 0; i < num_of_elements.size(); ++i)
        {
            std::string temp_path(path + '/' + std::to_string(num_of_elements[i]) + "/in");
            cout << "\tSorting " << ARRAYS_NUM << " arrays with size " << num_of_elements[i] << " ...\n"<< std::flush;
            
            for (int j = 0; j < ARRAYS_NUM; ++j)
            {
                if (T[n].ReadFromFile(temp_path + std::to_string(j) + ".txt"))
                    throw std::runtime_error("Error reading from file");

                duration[j] = T[n].RunSort();
                state[j] = T[n].TestIfSorted();
                cout << "\t\tProgress " << j + 1 << '/' << ARRAYS_NUM << " (" << duration[j] << " us)\n" << std::flush;
            }

            cout << "\tGenerating test summary...\n" << std::flush;
            GenerateTestSummary("RandomTest", sorters[n], num_of_elements[i], duration, state);
        }
    }
}

void PartlySortedArraysTest(const std::string &path)
{
    std::string testName("PartlySortedTest");
    std::array<int64_t, ARRAYS_NUM> duration;
    std::array<bool, ARRAYS_NUM> state;
    std::array<std::string, 3> sorters = {"QuickSort", "MergeSort", "IntroSort"};
    std::array<IFC, 3> T = {IFC(std::unique_ptr<S>(new QS(ASC))),
                            IFC(std::unique_ptr<S>(new MS(ASC))),
                            IFC(std::unique_ptr<S>(new IS(ASC)))};

    for (size_t p = 0; p < percent_values.size(); ++p)
    {
        cout << "Tests for arrays sorted in " << percent_values[p] << "%\n" <<std::flush;
        for (int n = 0; n < 3; ++n)
        {
            cout << "\tRuning tests for " << sorters[n] << " ...\n"<< std::flush;

            for (size_t i = 0; i < num_of_elements.size(); ++i)
            {
                std::string temp_path(path + '/' + std::to_string(num_of_elements[i]) + "/in");
                cout << "\t\tSorting " << ARRAYS_NUM << " arrays with size " << num_of_elements[i] << " ...\n" << std::flush;

                for (int j = 0; j < ARRAYS_NUM; ++j)
                {
                    if (T[n].ReadFromFile(temp_path + std::to_string(j) + ".txt"))
                        throw std::runtime_error("Error reading from file");
                    
                    T[n].RunPartlySort(percent_values[p]);
                    duration[j] = T[n].RunSort();
                    state[j] = T[n].TestIfSorted();
                    cout << "\t\t\tProgress " << j + 1 << '/' << ARRAYS_NUM << " (" << duration[j] << " us)\n" << std::flush;
                }

                cout << "\t\tGenerating test summary...\n" << std::flush;
                std::ostringstream temp;
                temp << sorters[n] << '_' << std::fixed << std::setprecision(1) << percent_values[p];
                GenerateTestSummary("PartlySortedTest", temp.str(), num_of_elements[i], duration, state);
            }
        }
    }
}

void ReverseArraysTest(const std::string &path)
{
    std::string testName("ReverseTest");
    std::array<int64_t, ARRAYS_NUM> duration;
    std::array<bool, ARRAYS_NUM> state;
    std::array<std::string, 3> sorters = {"MergeSort", "IntroSort", "QuickSort"};
    std::array<IFC, 3> T = {IFC(std::unique_ptr<S>(new MS(ASC))),
                            IFC(std::unique_ptr<S>(new IS(ASC))),
                            IFC(std::unique_ptr<S>(new QS(ASC)))};

    for (size_t n = 0; n < T.size(); ++n)
    {
        cout << "Runing tests for " << sorters[n] << " ...\n" << std::flush;

        for (size_t i = 0; i < num_of_elements.size(); ++i)
        {
            std::string temp_path(path + '/' + std::to_string(num_of_elements[i]) + "/in");
            cout << "\tSorting " << ARRAYS_NUM << " arrays with size " << num_of_elements[i] << " ...\n"<< std::flush;
            
            for (int j = 0; j < ARRAYS_NUM; ++j)
            {
                if (T[n].ReadFromFile(temp_path + std::to_string(j) + ".txt"))
                    throw std::runtime_error("Error reading from file");

                T[n].RunReverseSort();
                duration[j] = T[n].RunSort();
                state[j] = T[n].TestIfSorted();
                cout << "\t\tProgress " << j + 1 << '/' << ARRAYS_NUM << " (" << duration[j] << " us)\n" << std::flush;
            }

            cout << "\tGenerating test summary...\n" << std::flush;
            GenerateTestSummary("ReverseTest", sorters[n], num_of_elements[i], duration, state);
        }
    }
}

void GenerateTestSummary(const std::string &test_name, const std::string &sort_name, int elements, const std::array<int64_t, ARRAYS_NUM> &duration, const std::array<bool, ARRAYS_NUM> &state)
{
    std::fstream file;
    const std::string file_path("summary/" + test_name + "/summary.txt");

    std::filesystem::create_directories("summary/" + test_name);
    file.open("summary/" + test_name + "/summary.txt", std::fstream::out | std::fstream::app);

    if (!file.is_open())
        throw std::runtime_error("Cant write to summary file");

    if (std::filesystem::is_empty(file_path))
        file << "Sort_algorithm, Array_size, Min(us), Avg(us), Max(us), All_sorted" << endl;

    auto minmax = std::minmax_element(duration.begin(), duration.end());
    int64_t avg = std::accumulate(duration.begin(), duration.end(), 0) / ARRAYS_NUM;

    bool if_sorted = true;
    for (const bool &i : state)
    {
        if (!i)
        {
            if_sorted = false;
            break;
        }
    }

    file << sort_name << ',' << elements << ',' << *minmax.first << ',' << avg << ',' << *minmax.second << ',' << if_sorted << endl;
}