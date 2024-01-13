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

    void switchObj(unsigned int indexOne, unsigned int indexTwo) {
        if (indexOne < currentSize && indexTwo < currentSize) {
            Data_type temp = array[indexOne];
            array[indexOne] = array[indexTwo];
            array[indexTwo] = temp;
        } else {
            std::cerr << "Nieprawidłowy indeks." << std::endl;
        }
    }
};