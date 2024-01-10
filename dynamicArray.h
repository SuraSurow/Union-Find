template<typename Data_type>
class Dynamic_Array {

public:
    Data_type* array;
    unsigned int currentSize;
    unsigned int maxSize;
    float growthRate;

    Dynamic_Array() : currentSize(0), maxSize(1), growthRate(2.0) {
        array = new Data_type[maxSize];
    }

    Dynamic_Array(unsigned int max) : currentSize(0), maxSize(max), growthRate(2.0) {
        array = new Data_type[maxSize];
    }

    ~Dynamic_Array() {
        delete[] array;
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

    Data_type * getObj(unsigned int indeks) const {
        if (indeks >= currentSize) {
            std::cerr << "\n'getObj(" << indeks << ") indeks większy lub równy od rozmiaru tablicy!!\n";
            return nullptr;
        }
        return &array[indeks];
    }

    bool objExist( Data_type& value) const {
        for (unsigned int i = 0; i < currentSize; ++i) {
            if (*getObj(i) == value) {
                return true;
            }
        }
        return false;
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


/*
    bool editObjDate(const Data_type& inputData, unsigned int indeks) {
        if (indeks >= currentSize) {
            std::cerr << "\n'editObjDate(" << indeks << ") indeks większy lub równy od rozmiaru tablicy!!\n";
            return false;
        }

        (array[indeks].*setterFunction)(inputData);
        return true;
    }
*/
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

    void resize(unsigned int newSize) {
        if (newSize == currentSize) {
            return;
        }
        Data_type *newArray = new Data_type[newSize];
        unsigned int elementsToCopy = (currentSize < newSize) ? currentSize : newSize;
        for (unsigned int i = 0; i < elementsToCopy; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        currentSize = newSize;
        maxSize = newSize;
    }




};