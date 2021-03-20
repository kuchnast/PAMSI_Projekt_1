#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Sorter.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "HeapSort.hpp"
#include "IntroSort.hpp"
#include "TestingSorters.hpp"

void ShowMenu();

void ReadArray(TestingSorters<int> &T);

void WriteArray(TestingSorters<int> &T);

void GenerateArray(TestingSorters<int> &T);

void ChooseSortingAlgorithm(TestingSorters<int> &T);

void RunSorting(TestingSorters<int> &T);

void TestIfSorted(TestingSorters<int> &T);

void EfficiencyTests();

