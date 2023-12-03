#pragma once
/***************************************************************************************
*    Title: C++ Plus Data Structures SIXTH EDITION
*    Author: Nell Dale, Chip Weems
*    Date: 11/30/2023
*    Code version: C++11
*    Availability: Chapter 12
*
***************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

void Split(vector<string>&, int, int, int&);
void Swap(string&, string&);
void QuickSort(vector<string>&, int, int);

void Split(vector<string>& values, int first, int last, int& splitPoint) {
  string splitVal = values[first];
  int saveFirst = first;
  bool onCorrectSide;

  first++;
  do {
    onCorrectSide = true;
    while (onCorrectSide) {
      if (values[first] > splitVal) {
        onCorrectSide = false;
      }
      else {
        first++;
        onCorrectSide = (first <= last);
      }
    }
    onCorrectSide = (first <= last);
    while (onCorrectSide) {
      if (values[last] <= splitVal) {
        onCorrectSide = false;
      }
      else {
        last--;
        onCorrectSide = (first <= last);
      }
    }
    if (first < last) {
      Swap(values[first], values[last]);
      first++;
      last--;
    }
  } while (first <= last);


  splitPoint = last;
  Swap(values[saveFirst], values[splitPoint]);
}

void QuickSort(vector<string>& values, int first, int last) {
  if (first < last) {
    int splitPoint;
    Split(values, first, last, splitPoint);
    QuickSort(values, first, splitPoint - 1);
    QuickSort(values, splitPoint + 1, last);
  }
}

void Swap(string& item1, string& item2) {
  string tempItem;

  tempItem = item1;
  item1 = item2;
  item2 = tempItem;
}