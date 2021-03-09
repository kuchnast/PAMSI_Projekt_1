#pragma once

#include <iostream>
#include <Sorter.hpp>

template <class T>
class MergeSort : public Sorter<T>
{
private:
    void m_mergeSort(T *array, int l, int r, SortType type);

    void m_merge(T *array, int l, int q, int r, SortType type);

public:
    void sort(T *array, int l, int r, SortType type = ASC) override;
};

template <class T>
void MergeSort<T>::m_mergeSort(T *array, int l, int r, SortType type)
{
    if (l < r)
    {
        int q = (l + r) / 2;
        m_mergeSort(array, l, q, type);
        m_mergeSort(array, q + 1, r, type);
        m_merge(array, l, q, r, type);
    }
}

template <class T>
void MergeSort<T>::m_merge(T *array, int l, int r, SortType type)
{
    const int n = q - l + 1;
    const int m = r - q;
    int temp_L[n], temp_R[m];

    for (int i = 0; i < n; i++)
        temp_L[i] = array[l + i];

    for (int i = 0; i < m; i++)
        temp_R[i] = array[q + 1 + i];

    int i = 0, j = 0, k = l;
    do
    {
        if (i == n)
        {
            do
            {
                array[k++] = temp_R[j++];
            }
            while(j < m)
        }
        else if (j == m)
        {
            do
            {
                array[k++] = temp_L[i++];
            } while (i < n)
        }
        else
        {
            switch (type)
            {
            case ASC:
                temp_L[n] <= temp_R[m] ? array[k++] = temp_L[i++] : array[k++] = temp_R[j++];
                break;

            case DES:
                temp_L[n] <= temp_R[m] ? array[k++] = temp_R[j++] : array[k++] = temp_L[i++];
                break;
            }
        }
    } while (k < n + m);
}

template <class T>
void MergeSort<T>::sort(T *array, int l, int r, SortType type = ASC)
{
    m_mergeSort(array, l, r, type);
}