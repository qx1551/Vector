#include "vectorex.h"
#include"vectordes.h"

template <typename T> class stack : public Vector<T> {
public:
    void push(T const& e) { Vector<T>::insert(Vector<T>::size(), e); }
    T pop() { return Vector<T>::remove(Vector<T>::size() - 1); }
    T& top() { return (*this)[Vector<T>::size() - 1]; }
    void* realloc(void* ptr, size_t size);
   
};
  
