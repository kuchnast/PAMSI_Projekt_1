#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <chrono> 
#include <random>
#include <filesystem>

#include "Sorter.hpp"
/**
 * @brief Interface for Sorter class
 * 
 * @tparam T type of data to sort
 */
template<class T>
class SorterInterface
{
private:
    std::vector<T> m_array; ///< array of elements to sort
    std::unique_ptr<Sorter<T>> m_current_sorter; ///< pointer to current sorter algorithm

    /**
     * @brief Fill array by random numbers generated according to a uniform discrete distribution
     * 
     */
    void m_GenerateIntRandomNumbers(int max_value = 1000);

public:
    /**
     * @brief Construct a new Sorter Interface object with empty array and no sort algorithm
     * 
     */
    SorterInterface() : m_array(), m_current_sorter(nullptr){}

    /**
     * @brief Construct a new Sorter Interface object with empty array
     * 
     * @param Sorter sort algorithm
     */
    explicit SorterInterface(std::unique_ptr<Sorter<T>> Sorter) : m_array(), m_current_sorter(std::move(Sorter)) {}

    /**
     * @brief Construct a new Sorter Interface object
     * 
     * @param array array of elements to sort
     * @param Sorter sort algorithm
     */
    SorterInterface(const std::vector<T> &array, std::unique_ptr<Sorter<T>> &Sorter) : m_array(array), m_current_sorter(std::move(Sorter)) {}

    /**
     * @brief Set the current sorter object
     * 
     * @param Sorter sort algorithm
     */
    void SetSorter(std::unique_ptr<Sorter<T>> Sorter);

    /**
     * @brief Get the Size object
     * 
     * @return size_t size of array
     */
    size_t GetSize() const;

    /**
     * @brief Print array on standard output
     * 
     */
    void PrintArray() const;

    /**
     * @brief Read array from file where first value is number of elements
     * 
     * @param filepath path to file
     * @return true success
     * @return false cant read from file
     */
    bool ReadFromFile(const std::string &filepath);

    /**
     * @brief Write array to file where first value is number of elements
     *        If folders from path dont exist, create them
     * 
     * @param filepath path to file
     * @return true success
     * @return false cant write to file
     */
    bool WriteToFile(const std::string &filepath) const;

    /**
     * @brief Check if array is sorted in specified order
     * 
     * @return true array is sorted in specified order
     * @return false array is not sorted in specified order
     */
    bool TestIfSorted() const;

    /**
     * @brief Fill array with specified elements
     * 
     * @param array reference to other vector
     */
    void FillArray(const std::vector<T> &array);

    /**
     * @brief Fill array with random integer elements
     * 
     * @param size array size
     * @param max_value max value of generated values
     */
    void FillArrayRandom(size_t size, int max_value = 1000);

    /**
     * @brief Fill array with random integer elements and then sort part of array
     *        Sort part of array with currently selected algorithm and order
     * 
     * @param size array size
     * @param percent percent of array to sort
     * @param max_value max value of generated values
     */
    void FillArrayPartlySorted(size_t size, double percent, int max_value = 1000);

    /**
     * @brief Fill array with random integer elements and then sort them in descending order
     * 
     * @param size array size
     * @param max_value max value of generated values
     */
    void FillArrayReverseSorted(size_t size, int max_value = 1000);

    /**
     * @brief Run sort by selected algorithm
     * 
     * @return uint64_t sort time in microseconds
     */
    uint64_t RunSort();

    /**
     * @brief Run sort for only part of array
     * 
     * @param percent percent of array to sort
     * @return uint64_t sort time in microseconds
     */
    uint64_t RunPartlySort(double percent);

    /**
     * @brief Run sort in reverse order than selected 
     * 
     * @return uint64_t sort time in microseconds
     */
    uint64_t RunReverseSort();
};

template<class T>
void SorterInterface<T>::m_GenerateIntRandomNumbers(int max_value) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, max_value);
 
    for (size_t i = 0; i < m_array.size(); ++i)
        m_array[i] = distrib(gen);
}

template<class T>
void SorterInterface<T>::SetSorter(std::unique_ptr<Sorter<T>> Sorter) 
{
    m_current_sorter = std::move(Sorter);
}


template<class T>
size_t SorterInterface<T>::GetSize() const
{
    return m_array.size();
}

template<class T>
void SorterInterface<T>::PrintArray() const
{  
    for (size_t i = 0; i < m_array.size(); ++i)
    {
        if (i % 10 == 0)
            std::cout << std::endl;
        std::cout << m_array[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
bool SorterInterface<T>::ReadFromFile(const std::string &filepath)
{   
    std::fstream fs;
    size_t size;
    fs.open(filepath, std::fstream::in);

    if(fs.is_open())
    {
        fs >> size;

        m_array.resize(size);    

        for (size_t i = 0; i < size; ++i)
        {
            fs >> m_array[i];
        }

        bool state = fs.eof();

        fs.close();
        return !state;
    }
    return true;
}

template <class T>
bool SorterInterface<T>::WriteToFile(const std::string &filepath) const
{
    std::filesystem::create_directories(filepath.substr(0, filepath.find_last_of('/')));
    
    std::fstream fs;
    fs.open(filepath, std::fstream::out | std::fstream::trunc);

    if(fs.is_open() && m_array.size())
    {
        fs << m_array.size();

        for (size_t i = 0; i < m_array.size(); ++i)
        {
            fs << std::endl << m_array[i];
        }

        fs.close();
        return false;
    }
    return true;
}

template<class T>
bool SorterInterface<T>::TestIfSorted() const
{
    if (m_array.size() <= 1)
        return true;

    switch (m_current_sorter->GetSortOrder())
    {
    case ASC:
        {
            for (int i = m_array.size() - 1; i > 0; --i)
                if (m_array[i] < m_array[i - 1]) 
                    return false;

            return m_array[0] <= m_array[1];
            break;
        }
        

    case DES:
        {
            for (int i = m_array.size() - 1; i > 0; --i)
                if (m_array[i] > m_array[i-1])
                    return false;

            return m_array[0] >= m_array[1];
            break;
        }
    }
    
    return true;
}

template <class T>
void SorterInterface<T>::FillArray(const std::vector<T> &array)
{
    m_array = array;
}

template<class T>
void SorterInterface<T>::FillArrayRandom(size_t size, int max_value) 
{
    if (max_value < 0)
        throw std::invalid_argument("Invalid max_value for random numbers generator");

    m_array.resize(size);
    m_GenerateIntRandomNumbers();
}

template <class T>
void SorterInterface<T>::FillArrayPartlySorted(size_t size, double percent, int max_value)
{
    int r;

    FillArrayRandom(size, max_value);
    if(percent > 0 && percent < 100)
        r = (percent * (m_array.size() - 1)) / 100;
    else
        throw(std::invalid_argument("Invalid percent value"));
    m_current_sorter->Sort(m_array, 0, r);
}

template <class T>
void SorterInterface<T>::FillArrayReverseSorted(size_t size, int max_value)
{
    FillArrayRandom(size, max_value);
    
    SortOrder temp = m_current_sorter->GetSortOrder();
    if(temp != DES)
    {
        m_current_sorter->SetSortOrder(DES);
        m_current_sorter->Sort(m_array, 0, size - 1);
        m_current_sorter->SetSortOrder(ASC);
    }
    m_current_sorter->Sort(m_array, 0, size - 1);
}

template<class T>
uint64_t SorterInterface<T>::RunSort() 
{
    using namespace std::chrono;

    if(!m_array.size())
        throw(std::invalid_argument("Empty array"));

    if(m_current_sorter == nullptr)
        throw(std::invalid_argument("No sort algorithm was selected"));

    auto start = high_resolution_clock::now();

    m_current_sorter->Sort(m_array, 0, m_array.size() - 1);

    auto stop = high_resolution_clock::now();
    
    return duration_cast<microseconds>(stop - start).count();
}

template <class T>
uint64_t SorterInterface<T>::RunPartlySort(double percent)
{
    using namespace std::chrono;
    int r;

    if (!m_array.size())
        throw(std::invalid_argument("Empty array"));

    if (m_current_sorter == nullptr)
        throw(std::invalid_argument("No sort algorithm was selected"));

    if (percent > 0 && percent < 100)
        r = (percent * (m_array.size() - 1)) / 100;
    else
        throw(std::invalid_argument("Invalid percent value"));

    auto start = high_resolution_clock::now();

    m_current_sorter->Sort(m_array, 0, r);

    auto stop = high_resolution_clock::now();

    return duration_cast<microseconds>(stop - start).count();
}