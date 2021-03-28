#pragma once

#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief Sorting order (ascending or descending)
 * 
 */
enum SortOrder{
    ASC,
    DES
};

/**
 * @brief Base class for specific sorting algorithms
 * 
 * @tparam T type of data to sort
 */
template<class T>
class Sorter
{
protected:
    SortOrder m_order;    ///< sort order

public:
    
    /**
     * @brief Construct a new Sorter object
     * If not specified, sort in ascending order.
     */
    Sorter() : m_order(ASC){}

    /**
     * @brief Construct a new Sorter object with specific order
     * 
     * @param order sort order (ASC or DES)
     */
    explicit Sorter(SortOrder order) : m_order(order){}

    /**
     * @brief Sort array in specified order
     * 
     * @param array reference to array
     * @param first index of first item to be sorted
     * @param last index of last item to be sorted
     */
    virtual void Sort(std::vector<T> & array, int first, int last) = 0;

    /**
     * @brief Set the Sort Order object
     * 
     * @param order sort order (ASC or DES)
     */
    void SetSortOrder(SortOrder order);

    /**
     * @brief Get the Sort Order object
     * 
     * @return SortOrder sort order (ASC or DES)
     */
    SortOrder GetSortOrder() const;
};

template<class T>
void Sorter<T>::SetSortOrder(SortOrder order) 
{
    m_order = order;
}


template<class T>
SortOrder Sorter<T>::GetSortOrder() const
{
    return m_order;
}