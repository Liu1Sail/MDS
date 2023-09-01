//
// Created by 23118 on 2023/9/1.
//

#ifndef MDS_ARRAY_H
#define MDS_ARRAY_H

#include <initializer_list>
#include <algorithm>
namespace MDS {
    template<class T>
    class array{
    private:
        unsigned m_uCapacity;
        unsigned  m_uSize;
        T* m_pObjects = nullptr;
    public:
        explicit array(unsigned uInitSize = 0);
        array(const array& initArray);
        array(array&& initArray);
        explicit array(const std::initializer_list<T>& initList);
        ~array();
        array& operator=(const array& otherArray);
        array& operator=(array&& otherArray);

        typedef  T* iterator;
        typedef const T* const_iterator;

        iterator begin();
        const_iterator begin()const;
        iterator end();
        const_iterator end()const;

        T& operator[](int iIndex);
        const T & operator[](int iIndex) const;

        void reverse(unsigned uNewCapacity);
        void resize(unsigned uNewSize);

        bool empty() const;
        unsigned size() const;
        unsigned capacity() const;




        void push_back(const T& object);
        void push_back(T&& object);

    };


} // MDS

#endif //MDS_ARRAY_H
