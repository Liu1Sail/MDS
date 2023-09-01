//
// Created by 23118 on 2023/9/1.
//

#include "array.h"

namespace MDS {
    template<class T>
    array<T>::array(unsigned int uInitSize):m_uCapacity(uInitSize+16),m_uSize(uInitSize) {
        m_pObjects = new T[m_uCapacity];
    }

    template<class T>
    array<T>::array(const array &initArray):m_uCapacity(initArray.m_uCapacity),m_uSize(initArray.m_uSize) {
        m_pObjects = new T[m_uCapacity];
        for(int i = 0; i < m_uSize;++i)
        {
            m_pObjects[i] = initArray.m_pObjects[i];
            // 从非右值 拷贝的话不应该使用迁移资产的std::move
        }
    }

    template<class T>
    array<T>::array(array &&initArray):m_uCapacity(initArray.m_uCapacity),m_uSize(initArray.m_uSize),m_pObjects(initArray.m_pObjects) {
        initArray.m_pObjects = nullptr;
    }

    template<class T>
    array<T>::array(const std::initializer_list<T>& initList):m_uCapacity(initList.size()+16),m_uSize(initList.size()) {
        m_pObjects = new T[m_uCapacity];
        for(int i = 0;i<m_uSize;++i)
        {
            m_pObjects[i] = initList[i];
        }
    }

    template<class T>
    array<T>::~array() {
        delete[] m_pObjects;
    }

    template<class T>
    array<T> &array<T>::operator=(const array &otherArray) {
        if(&otherArray == this)
            return *this;
        auto copy = otherArray;
        std::swap(*this , copy);
        return *this;
    }

    template<class T>
    array<T> &array<T>::operator=(array &&otherArray) {
        std::swap(m_uCapacity , otherArray.m_uCapacity);
        std::swap(m_uSize , otherArray.m_uSize);
        std::swap(m_pObjects , otherArray.m_pObjects);
        return *this;

        /*为什么不能直接 std::swap(*this , otherArray) ?
         * swap内部循环调用 operator=
         * */
    }

    template<class T>
    typename array<T>::iterator array<T>::begin() {
        return &m_pObjects[0];
    }

    template<class T>
    typename array<T>::const_iterator array<T>::begin() const {
        return &m_pObjects[0];
    }

    template<class T>
    typename array<T>::iterator array<T>::end() {
        return &m_pObjects[m_uSize - 1];
    }

    template<class T>
    typename array<T>::const_iterator array<T>::end() const {
        return &m_pObjects[m_uSize - 1];
    }

    template<class T>
    T &array<T>::operator[](int iIndex) {
        return m_pObjects[iIndex];
    }

    template<class T>
    const T &array<T>::operator[](int iIndex) const {
        return m_pObjects[iIndex];
    }

    template<class T>
    void array<T>::reverse(unsigned uNewCapacity)
    {
        if(m_uSize > uNewCapacity)
            return;
        T* pNewObjects = new T[uNewCapacity];
        for(int i = 0; i < m_uSize ; ++i)
        {
            pNewObjects[i] = std::move(m_pObjects[i]);
        }
        std::swap(m_pObjects , pNewObjects);
        delete []pNewObjects;
    }

    template<class T>
    void array<T>::resize(unsigned uNewSize) {
        if(uNewSize > m_uCapacity)
            reverse(uNewSize*2);
        m_uSize = uNewSize;
    }

    template<class T>
    unsigned array<T>::capacity() const {
        return m_uCapacity;
    }

    template<class T>
    unsigned array<T>::size() const {
        return m_uSize;
    }

    template<class T>
    bool array<T>::empty() const {
        return m_uSize == 0;
    }

    template<class T>
    void array<T>::push_back(const T& object)
    {
        if(m_uSize >= m_uCapacity)
            reverse(m_uSize*2 + 1);
        m_pObjects[m_uSize] = object;
        m_uSize ++;
    }

    template<class T>
    void array<T>::push_back(T &&object) {
        if(m_uSize >= m_uCapacity)
            reverse(m_uSize*2 + 1);
        m_pObjects[m_uSize] = std::move(object);
        m_uSize ++;
    }
} // MDS