//
// Created by admin on 07.01.2024.
//

#ifndef UNION_FIND_DYNAMICARRAY_H
#define UNION_FIND_DYNAMICARRAY_H

#include <iostream>
#include <string>
#include <utility>
#include <math.h>
#include <chrono>
#include <random>

unsigned int randValue(unsigned int min , unsigned int max)
{
    std::random_device dev;
    std::mt19937 random(dev());
    std::uniform_int_distribution<std::mt19937::result_type> zakres(min, max);
    return zakres(random);
}

template<typename Data_type>
class Dynamic_Array {
public:
    Data_type *array;
    unsigned int currentSize;
    unsigned int maxSize;
    float growthRate;

    Dynamic_Array() : currentSize(0), maxSize(1), growthRate(2.0) {
        array = new Data_type[maxSize];
    }

    explicit Dynamic_Array(unsigned int max) : currentSize(0), maxSize(max), growthRate(2.0) {
        array = new Data_type[maxSize];
    }

    ~Dynamic_Array() {
        delete array;
    }

    Dynamic_Array(const Dynamic_Array<Data_type> &otherDynamic) {
        maxSize = otherDynamic.maxSize;
        currentSize = otherDynamic.currentSize;
        growthRate = otherDynamic.growthRate;
        array = new Data_type[maxSize];
        for (unsigned int i = 0; i < currentSize; i++) {
            array[i] = otherDynamic.array[i];
        }
    }

    Dynamic_Array(const Dynamic_Array<Data_type> &otherDynamic, bool changeSize) {
        growthRate = otherDynamic.growthRate;
        if (changeSize) {
            maxSize = otherDynamic.maxSize * growthRate;
        } else {
            maxSize = otherDynamic.maxSize;
        }
        currentSize = otherDynamic.currentSize;
        array = new Data_type[maxSize];
        for (unsigned int i = 0; i < currentSize; i++) {
            array[i] = otherDynamic.array[i];
        }
    }

    void addObj(Data_type *obj) {
        if (currentSize == maxSize) {
            maxSize *= growthRate;
            Data_type *newArray = new Data_type[maxSize];
            for (unsigned int i = 0; i < currentSize; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
        }
        array[currentSize] = *obj;
        currentSize++;
    }

    Data_type getObj(unsigned int indeks) {
        if (indeks > currentSize) {
            std::cerr << "\n'getObj(" << indeks << ") indeks wiekszy od tablicy!!\n";
            return nullptr;
        }
        return array[indeks];
    }

    bool editObjDate(Data_type inputData, unsigned int indeks) {
        Data_type editObj = getObj(indeks);
        if (getObj(indeks) == nullptr) return false;
        else {
            (*editObj)(inputData);//PRZECIAZONY OPERATOR !!!!
            return true;
        }
    }

    bool clear() {
        while (currentSize > 0) {
            Data_type currentToDelete = array[currentSize - 1];
            delete currentToDelete;
            currentSize--;
        }
        maxSize = 1;
        return true;
    }

    void print() {
        std::cout << "\n===================================================================================="
                     "\nAkt. Rozmiar: " << currentSize <<
                  "\t|\tWsp. Powiekszenia: " << growthRate <<
                  "\t|\tMaks. Rozmiar: " << maxSize <<
                  "\n====================================================================================";
    }

    void switchObj(unsigned int indexOne, unsigned int indexTwo) {
        if (indexOne < currentSize && indexTwo < currentSize) {
            Data_type temp = array[indexOne];
            array[indexOne] = array[indexTwo];
            array[indexTwo] = temp;
        } else {
            std::cerr << "Nieprawidłowy indeks." << std::endl;
        }
    }

    bool BubbleSort(bool growing) {
        for (int i = 0; i < currentSize - 1; i++) {
            for (int j = 1; j < currentSize - i; j++) {

                if (growing) {
                    if (objectCompare(array[j - 1], array[j]) >= 1) {
                        switchObj(j - 1, j);
                    }
                } else {
                    if (objectCompare(array[j - 1], array[j]) <= -1) {
                        switchObj(j - 1, j);
                    }
                }
            }
        }
    }
};
#endif //UNION_FIND_DYNAMICARRAY_H
