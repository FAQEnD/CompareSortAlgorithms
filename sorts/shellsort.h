#ifndef SHELLSORT_H
#define SHELLSORT_H
#include <vector>
#include <stack>
#include <QString>
#include <QtDebug>
#include <algorithm>
#include "isort.h"

template <class T>
class ShellSort : public ISort<T>
{
public:
    ShellSort(QString);
    static double algTimeSumShell;
    static double algTimeSumPratt;
    static double algTimeSumPrattSecond;
private:
    std::stack<int> _gaps;
    QString _sequenceName;
    void isSorted();
    void generateGap();

public:
    double getAlgTimeSumShell()
    {
        double tempSum = this->algTimeSumShell;
        this->algTimeSumShell = 0;
        return tempSum;
    }
    double getAlgTimeSumPratt()
    {
        double tempSum = this->algTimeSumPratt;
        this->algTimeSumPratt = 0;
        return tempSum;
    }
    double getAlgTimeSumPrattSecond()
    {
        double tempSum = this->algTimeSumPrattSecond;
        this->algTimeSumPrattSecond = 0;
        return tempSum;
    }
    void sort()
    {
        /*
        *	@Params:
        *	@_arr - vector with elements. Shoud be sorted
        *	@_gaps - stack of shell sort gaps
        *
        *	*This method shoud sort @_arr by Shell Sort with gap from @_gaps
        */
        this->_tManager.start();
        while (!_gaps.empty())
        {
            unsigned int gap = _gaps.top();
            _gaps.pop();

            for (unsigned int i = gap; i < this->_arr.size(); ++i)
            {
                T buff = this->_arr[i];
                unsigned int j = i;

                while (j >= gap && this->_arr[j - gap] > buff)
                {
                    this->_arr[j] = this->_arr[j - gap];
                    j -= gap;
                }

                this->_arr[j] = buff;
            }
        }
        this->_tManager.stop();
        isSorted();
        if(this->_sequenceName == "Shell")
            this->algTimeSumShell += this->getAlgorithmTime();
        else
            if(this->_sequenceName == "Pratt")
                this->algTimeSumPratt += this->getAlgorithmTime();
            else
                this->algTimeSumPrattSecond += this->getAlgorithmTime();
    }
};

template <class T>
double ShellSort<T>::algTimeSumShell;
template <class T>
double ShellSort<T>::algTimeSumPratt;
template <class T>
double ShellSort<T>::algTimeSumPrattSecond;

template <class T>
ShellSort<T>::ShellSort(QString sequenceName)
{
    this->readArrayFromFile();
    _sequenceName = sequenceName;
    generateGap();
    this->_sortAlgorithmName = "Shell";
}

template <class T>
void ShellSort<T>::generateGap()
{

    /*
    *	@Params:
    *	@_gaps - stack of int elements
    *	@_arr.size() - contains count of unsorted elements
    *	@_sequenceName - shoud contain one of types chosed by user
    *		Aviable types:
    *			Shell;
    *			Knuth;
    *			Pratt;
    *		"Shell" type was choosed by default.
    *
    *	*This method shoud generate steps by one of algorithms, based on @_sequenceName
    */
    _gaps = std::stack<int>(); // clear stack
    if (_sequenceName == "Pratt_second" || _sequenceName == "Pratt2")
    {
        unsigned int k = 1, gap = 0;
        while (gap < this->_arr.size())
        {
            gap = (int)(pow(3, k) - 1)/2;
            _gaps.push(gap);
            k++;
        }
        _gaps.pop();
    }else
        if (_sequenceName == "Pratt")
        {
            std::vector<int> gapsTable;
            unsigned int pow2 = 0, pow3 = 1;
            while (pow3 < this->_arr.size())
            {
                pow2 = pow3;
                while (pow2 < this->_arr.size())
                {
                    gapsTable.push_back(pow2);
                    pow2 *= 2;
                }
                pow3 *= 3;
            }
            std::sort(gapsTable.begin(), gapsTable.end());
            for (unsigned int i = 0; i < gapsTable.size(); ++i)
            {
                _gaps.push(gapsTable[i]);
            }
        }
        else
        {
            // Default sequence
            for (unsigned int i = 1; i < this->_arr.size(); i *= 2)
            {
                _gaps.push(i);
            }
        }
}

template <class T>
void ShellSort<T>::isSorted()
{
    QString type;
    int sizeOfElement = sizeof(this->_arr[0]);
    if(sizeOfElement == 4)
        type = "int";
    else
        type = "double";
    if(std::is_sorted(this->_arr.begin(), this->_arr.end()))
        qDebug() << "Array of " << type <<  "sorted by shell sort, with " << _sequenceName << " sequence";
    else
        qDebug() << "array of " << type <<  "not sorted by shell sort" << _sequenceName << " sequence";
}

#endif // SHELLSORT_H
