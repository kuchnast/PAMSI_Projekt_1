#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <chrono> 
#include <random>

#include "Sorter.hpp"

template<class T>
class TestingSorters
{
private:
    T *m_array;
    size_t m_size;
    std::shared_ptr<Sorter<T>> m_current_sorter;

    void m_GenerateRandomNumbers();

public:
    TestingSorters() : m_array(nullptr), m_size(0), m_current_sorter(nullptr){}
    explicit TestingSorters(std::shared_ptr<Sorter<T>> Sorter) : m_array(nullptr), m_size(0), m_current_sorter(Sorter) {}
    ~TestingSorters();

    void ChangeSorter(std::shared_ptr<Sorter<T>> Sorter);
    size_t GetSize();
    void PrintArray();
    void InsertInputData(size_t size, T *array);
    bool ReadInputData(std::string path);
    bool WriteOutputData(std::string path);
    bool TestIfSorted(SortType type);
    void FillArrayRandom(size_t size);
    void FillArrayPartlySorted(size_t size, double percent);
    void FillArrayReverseSorted(size_t size);
    std::chrono::microseconds RunSort();
};

template<class T>
void TestingSorters<T>::m_GenerateRandomNumbers() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1000);
 
    for (size_t i = 0; i < m_size; ++i)
        m_array[i] = distrib(gen);
}

template<class T>
TestingSorters<T>::~TestingSorters() 
{
    if(m_array != nullptr)
    {
        delete[] m_array;
    }
}

template<class T>
void TestingSorters<T>::ChangeSorter(std::shared_ptr<Sorter<T>> Sorter) 
{
    m_current_sorter = Sorter;
}


template<class T>
size_t TestingSorters<T>::GetSize() 
{
    return m_size;
}

template<class T>
void TestingSorters<T>::PrintArray() 
{
    for (size_t i = 0; i < m_size; ++i)
    {
        if (i % 10 == 0)
            std::cout << std::endl;
        std::cout << m_array[i] << " ";
    }
    std::cout << std::endl;
}

template<class T>
void TestingSorters<T>::InsertInputData(size_t size, T *array) 
{
    if(m_array != nullptr)
    {
        delete[] m_array;
    }
    m_array = array;
    m_size = size;
}

template<class T>
bool TestingSorters<T>::ReadInputData(std::string path) 
{
    std::ifstream file;
    bool state = false;

    file.open(path, std::ios::in);

    if(file.is_open())
    {
        file >> m_size;
        if(m_array != nullptr)
        {
            delete[] m_array;
        }
        m_array = new T[m_size];

        for (size_t i = 0; i < m_size; ++i)
        {
            file >> m_array[i];
        }

        if(file.eof())
            state = true;

        file.close();
    }
    return state;
}

template<class T>
bool TestingSorters<T>::WriteOutputData(std::string path) 
{
    std::ofstream file;
    bool state = false;

    file.open(path, std::ios::out);

    if(file.is_open() && m_size != 0)
    {
        file << m_size << std::endl;

        for (size_t i = 0; i < m_size; ++i)
        {
            file << m_array[i] << std::endl;
        }

        file.close();
        state = true;;
    }
    return state;
}

template<class T>
bool TestingSorters<T>::TestIfSorted(SortType type) 
{
    int i = m_size - 1;
    if (i <= 0)
        return true;

    switch (type)
    {
    case ASC:
        {
            while(i > 0)
                if (m_array[i] < m_array[--i]) 
                    return false;

            return m_array[0] <= m_array[1];
            break;
        }
        

    case DES:
        {
            while(i > 0)
                if (m_array[i] > m_array[--i]) 
                    return false;

            return m_array[0] >= m_array[1];
            break;
        }
    }
    
    return true;
}

template<class T>
void TestingSorters<T>::FillArrayRandom(size_t size) 
{
    m_size = size;
    if (m_array != nullptr)
    {
        delete[] m_array;
    }
    m_array = new T[m_size];
    m_GenerateRandomNumbers();
}

template<class T>
void TestingSorters<T>::FillArrayPartlySorted(size_t size, double percent) 
{
    int r;

    FillArrayRandom(size);
    if(percent > 0 && (100 - percent) >= 0)
        r = percent * (m_size - 1) / 100;
    else
        throw(std::invalid_argument("Bad percent value"));
    m_current_sorter->sort(m_array, 0, r);
}

template<class T>
void TestingSorters<T>::FillArrayReverseSorted(size_t size) 
{
    FillArrayRandom(size);
    QuickSort<T> Temp(DES);
    Temp.sort(m_array, 0, size - 1);
}

template<class T>
std::chrono::microseconds TestingSorters<T>::RunSort() 
{
    using namespace std::chrono;

    if(m_array == nullptr)
        throw(std::invalid_argument("Brak elementów w tablicy"));

    auto start = high_resolution_clock::now();

    m_current_sorter->sort(m_array, 0, m_size - 1);

    auto stop = high_resolution_clock::now();
    
    return duration_cast<microseconds>(stop - start);
}