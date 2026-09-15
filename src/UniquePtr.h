#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

// Your implementation here
#include <utility>

template <typename T>
class UniquePtr
{
private:
    T* ptr;

public:
    UniquePtr() : ptr(nullptr) {}
    UniquePtr(T* ptr) : ptr(ptr) {}
    ~UniquePtr(){delete ptr;}
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other) : ptr(other.ptr){other.ptr = nullptr;}
    UniquePtr& operator=(UniquePtr&& other)
    {
        if (this != &other)
        {
            delete ptr;

            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    template <typename U>
    UniquePtr(UniquePtr<U>&& other) : ptr(other.release()){}
    T& operator*(){return *ptr;}
    T* operator->(){return ptr;}
    T* get() const{return ptr;}
    T* release()
    {
        T* oldPtr = ptr;
        ptr = nullptr;
        return oldPtr;
    }
    bool operator==(const UniquePtr<T>& other) const{return ptr == other.ptr;}
    void reset(T* newPtr = nullptr)
    {
        delete ptr;
        ptr = newPtr;
    }
    void swap(UniquePtr<T>& other)
    {
        T* temp = ptr;
        ptr = other.ptr;
        other.ptr = temp;
    }
    operator bool() const{return ptr != nullptr;}
};


template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif
