#ifndef DYNAMIC_TABLE_HPP
#define DYNAMIC_TABLE_HPP
#include <stdexcept>

template <typename T>
class DynamicTable {
private:
    unsigned long _capacity;  
    unsigned long _size;      
    T * _table;

public:
    DynamicTable(unsigned long capacity = 1){
        this->_capacity = (capacity > 0) ? capacity : 1; 
        this->_size = 0;
        this->_table = new T[this->_capacity];
    }

    void append(T val){
        if(this->_size == this->_capacity){
            this->_capacity *= 2;
            T * newTable = new T[this->_capacity];
            for(unsigned long i = 0; i < this->_size; i++){
                newTable[i] = this->_table[i];
            }
            delete[] this->_table;
            this->_table = newTable;
        }
        
        this->_table[this->_size] = val;
        this->_size++;
    }

    void remove(unsigned long index){
        if(index > this->_size){
            throw std::runtime_error("Index out of range"); 
        }

        for(unsigned long i = index; i < this->_size - 1; i++){
            this->_table[i] = this->_table[i+1];
        }

        this->_size--;

        if(this->_size > 0 && this->_size <= this->_capacity / 3){
            this->_capacity /= 2;
            T * newTable = new T[this->_capacity];
            for(unsigned long i = 0; i < this->_size; i++){
                newTable[i] = this->_table[i];
            }
            delete[] this->_table;
            this->_table = newTable;
        }
    }

    void insert(T val, unsigned long index){
        if(index > this->_size){
            throw std::runtime_error("Index out of range"); 
        }

        if(this->_size == this->_capacity){
            this->_capacity *= 2;
            T * newTable = new T[this->_capacity];
            for(unsigned long i = 0; i < this->_size; i++){
                newTable[i] = this->_table[i];
            }
            delete[] this->_table;
            this->_table = newTable;
        }

        for(unsigned long i = this->_size; i > index; i--){
            this->_table[i] = this->_table[i-1]; 
        }
        
        this->_table[index] = val; 
        this->_size++;
    }

    unsigned long find(T val){
        for(unsigned long i = 0; i < this->_size; i++){
            if(this->_table[i] == val){
                return i;
            }
        }
    }

    T& operator[](unsigned long index){
        if(index >= this->_size){
            throw std::runtime_error("Index out of range"); 
        }
        return this->_table[index];
    }

    ~DynamicTable(){
        delete [] this->_table;
    }
};

#endif