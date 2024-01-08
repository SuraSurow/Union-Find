template<typename Data_type>
class Dynamic_Array {
    typedef void (Data_type::*SetterFunction)(const Data_type&);

public:
    Data_type* array;
    unsigned int currentSize;
    unsigned int maxSize;
    float growthRate;
    SetterFunction setterFunction;

    explicit Dynamic_Array(SetterFunction _setterFunction) : currentSize(0), maxSize(1), growthRate(2.0), setterFunction(_setterFunction) {
        array = new Data_type[maxSize];
    }

    explicit Dynamic_Array(unsigned int max, SetterFunction _setterFunction) : currentSize(0), maxSize(max), growthRate(2.0), setterFunction(_setterFunction) {
        array = new Data_type[maxSize];
    }

    ~Dynamic_Array() {
        delete[] array;
    }

    Dynamic_Array(const Dynamic_Array<Data_type> &otherDynamic) {
        maxSize = otherDynamic.maxSize;
        currentSize = otherDynamic.currentSize;
        growthRate = otherDynamic.growthRate;
        setterFunction = otherDynamic.setterFunction;
        array = new Data_type[maxSize];
        for (unsigned int i = 0; i < currentSize; i++) {
            array[i] = otherDynamic.array[i];
        }
    }

    void quickSort() {
        quickSort(0, currentSize - 1);
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

    Data_type* getObj(unsigned int indeks) {
        if (indeks >= currentSize) {
            std::cerr << "\n'getObj(" << indeks << ") indeks większy lub równy od rozmiaru tablicy!!\n";
            return nullptr;
        }
        return &array[indeks];
    }

    bool editObjDate(const Data_type& inputData, unsigned int indeks) {
        if (indeks >= currentSize) {
            std::cerr << "\n'editObjDate(" << indeks << ") indeks większy lub równy od rozmiaru tablicy!!\n";
            return false;
        }

        (array[indeks].*setterFunction)(inputData);
        return true;
    }

    bool clear() {
        while (currentSize > 0) {
            delete array[currentSize - 1];
            currentSize--;
        }
        maxSize = 1;
        return true;
    }

    void print() {
        std::cout << "\n===================================================================================="
                     "\nAkt. Rozmiar: " << currentSize <<
                  "\t|\tWsp. Powiększenia: " << growthRate <<
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

private:
    void quickSort(int low, int high) {
        if (low < high) {
            int pivotIndex = partition(low, high);
            quickSort(low, pivotIndex - 1);
            quickSort(pivotIndex + 1, high);
        }
    }

    int partition(int low, int high) {
        Data_type pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (array[j] <= pivot) {
                i++;
                switchObj(i, j);
            }
        }

        switchObj(i + 1, high);
        return i + 1;
    }
};