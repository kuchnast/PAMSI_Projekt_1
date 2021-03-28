#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Sorter.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "HeapSort.hpp"
#include "IntroSort.hpp"
#include "SorterInterface.hpp"

#define ARRAYS_NUM 100 ///< number of arrays for single test

/**
 * @brief Show program menu
 * 
 */
void ShowMenu();

/**
 * @brief Read array from standard input or from file
 * 
 * @param T reference to sorter interface
 */
void ReadArray(SorterInterface<int> &T);

/**
 * @brief Write array on standard output or to file
 * 
 * @param T reference to sorter interface 
 */
void WriteArray(SorterInterface<int> &T);

/**
 * @brief Generate random or partly sorted array 
 * 
 * @param T reference to sorter interface
 */
void GenerateArray(SorterInterface<int> &T);

/**
 * @brief Change sorting algorithm or elements order
 * 
 * @param T reference to sorter interface
 */
void ChooseSortingAlgorithm(SorterInterface<int> &T);

/**
 * @brief Run sorting with curently used array and sort algorithm
 * 
 * @param T reference to sorter interface
 */
void RunSorting(SorterInterface<int> &T);

/**
 * @brief Check if all arrays elements are in correct order
 * 
 * @param T reference to sorter interface
 */
void TestIfSorted(SorterInterface<int> &T);

/**
 * @brief Performance tests from projects instruction
 * 
 */
void PerformanceTests();

/**
 * @brief Generate all specified types of tables and save them to directory
 * 
 * @param path directory where arrays will be saved
 */
void GenerateAllRandomArrays(const std::string &path);

/**
 * @brief Read arrays from generated files and sort them with evry of specified algorithms
 *        Save tests summary to file ./summary/RandomTest/summary.txt
 * 
 * @param path directory where arrays was saved
 */
void RandomArraysTest(const std::string &path);

/**
 * @brief Read arrays from generated files, partly sort them and than sort them with evry of specified algorithms
 *        Save tests summary to file ./summary/PartlySortedTest/summary.txt
 * 
 * @param path directory where arrays was saved
 */
void PartlySortedArraysTest(const std::string &path);

/**
 * @brief Read arrays from generated files, sort them in reverse order and than sort them with evry of specified algorithms
 *        Save tests summary to file ./summary/ReverseTest/summary.txt
 * 
 * @param path directory where arrays was saved
 */
void ReverseArraysTest(const std::string &path);

/**
 * @brief Make current test summary in directory ./summary/<test_name>/summary.txt
 *        Summary format: test_type, array_size, min_time_value(us), avg_time_value(us), max_time_value(us), is_all_sorted
 * 
 * @param test_name name of directory with summary
 * @param sort_name name of current test
 * @param elements number of elements in array
 * @param duration reference to array with tests duration
 * @param state reference to array with tests states
 */
void GenerateTestSummary(const std::string &test_name, const std::string &sort_name, int elements, const std::array<int64_t, ARRAYS_NUM> &duration, const std::array<bool, ARRAYS_NUM> &state);