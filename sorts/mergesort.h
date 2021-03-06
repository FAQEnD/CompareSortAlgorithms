#ifndef MERGESORT_H
#define MERGESORT_H
#include "isort.h"
#include <algorithm>
#include <memory>

template <class T>
class MergeSort : public ISort<T>
{
public:
    MergeSort();
    void merge(std::vector<T>&, const int, const int, const int);
    static double algTimeSum;
    double getAlgTimeSum()
    {
        double tempSum = this->algTimeSum;
        this->algTimeSum = 0;
        return tempSum;
    }
    void sort()
    {
        this->_tManager.start();
//        auto A = std::make_unique<std::vector<T> >(this->_arr);
        unsigned int size = this->_arr.size();
        if (size <= 50)
            {
                std::sort(this->_arr.begin(), this->_arr.end());
                return;
            }
            for (unsigned int i = 1; i < size; i *= 2)
                for (unsigned int j = 0; j < size - i; j += 2 * i)
                    merge(this->_arr, j, j + i, std::min(j + 2 * i, size));
        this->_tManager.stop();
        this->isSorted();
        this->algTimeSum += this->getAlgorithmTime();
    }
};

template <class T>
double MergeSort<T>::algTimeSum;

template <class T>
void MergeSort<T>::merge(std::vector<T> &arr, const int left, const int middle, const int right)
{
    int indexA(0), indexB(0);
    std::vector<T> result;
    result.resize(right - left);

    while (left + indexA < middle && middle + indexB < right)
    {
        if (arr[left + indexA] < arr[middle + indexB])
        {
//            result[indexA + indexB] = std::move(arr[left + indexA]);
            result[indexA + indexB] = arr[left + indexA];
            ++indexA;
        }
        else
        {
//            result[indexA + indexB] = std::move(arr[middle + indexB]);
            result[indexA + indexB] = arr[middle + indexB];
            ++indexB;
        }
    }

    while (left + indexA < middle)
    {
//        result[indexA + indexB] = std::move(arr[left + indexA]);
        result[indexA + indexB] = arr[left + indexA];
        ++indexA;
    }

    while (middle + indexB < right)
    {
//        result[indexA + indexB] = std::move(arr[middle + indexB]);
        result[indexA + indexB] = arr[middle + indexB];
        ++indexB;
    }

    for (int i = 0; i < indexA + indexB; ++i)
    {
//        arr[left + i] = std::move(result[i]);
        arr[left + i] = result[i];
    }
}

template <class T>
MergeSort<T>::MergeSort()
{
    this->readArrayFromFile();
    this->_sortAlgorithmName = "Merge";
}

#endif // MERGESORT_H
