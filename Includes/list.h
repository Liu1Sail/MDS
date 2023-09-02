//
// Created by 23118 on 2023/9/2.
//

#ifndef MDS_LIST_H
#define MDS_LIST_H
#include <algorithm>
namespace MDS {

    template<typename T>
    class list {


    private:
        struct node{
            T*  m_pObject;
            node* m_pPrev;
            node* m_pNext;
            node(T* pObject = nullptr,node* prev = nullptr, node* next = nullptr):m_pObject(pObject),m_pPrev(prev),m_pNext(next){
            }
            ~node(){
                if(!m_pObject)return;
                m_pPrev->m_pNext = m_pNext;
                m_pNext->m_pPrev = m_pPrev;
                delete m_pObject;
            }
        };//node

        node* m_pHead;
        node* m_pTail;
        unsigned m_uSize;


    public:

        class iterator{
        protected:
            node* m_pNode;
        public:
            friend list;
            explicit iterator(node* pNode = nullptr):m_pNode(pNode){}
            bool operator== (const iterator & otherIterator) const{
                return m_pNode == otherIterator.m_pNode;
            }
            bool operator != (const iterator& otherIterator) const{
                return m_pNode != otherIterator.m_pNode;
            }

            virtual iterator operator++ (int){
                iterator old(*this);
                ++(*this);
                return old;
            }
            virtual iterator& operator++(){
                m_pNode = m_pNode->m_pNext;
                return *this;
            }

            virtual iterator operator--(int){
                auto old = *this;
                --(*this);
                return old;
            }

            virtual iterator& operator--(){
                m_pNode = m_pNode->m_pPrev;
                return *this;
            }

            virtual T& operator*(){
                return *(m_pNode->m_pObject);
            }
        };//iterator

        class const_iterator : public iterator{
        public:
            explicit const_iterator(node* pNode = nullptr): iterator(pNode){}
            const_iterator operator++ (int){
                const_iterator old(*this);
                ++(*this);
                return old;
            }
            const_iterator& operator++(){
                this->m_pNode = this->m_pNode->m_pNext;
                return *this;
            }

            const_iterator operator--(int){
                auto old = *this;
                --(*this);
                return old;
            }
            const_iterator& operator--(){
                this->m_pNode = this->m_pNode->m_pPrev;
                return *this;
            }

            const T& operator*(){
                return iterator::operator*(*this);
            }
        };//const_iterator

        list():m_uSize(0){
            m_pHead = new node;
            m_pTail = new node;
            m_pHead->m_pNext = m_pTail;
            m_pTail->m_pPrev = m_pHead;
        }
        list(const list & otherList):list(){
            for(auto & ele : otherList){
                push_back(ele);
            }
        }
        list(list&& otherList):list(){
            std::swap(m_uSize,otherList.m_uSize);
            std::swap(m_pHead , otherList.m_pHead);
            std::swap(m_pTail , otherList.m_pTail);
        }
        list& operator=(list&& otherList){
            std::swap(m_uSize,otherList.m_uSize);
            std::swap(m_pHead , otherList.m_pHead);
            std::swap(m_pTail , otherList.m_pTail);
            return *this;
        }
        list& operator=(const list& otherList){
            if(this == &otherList)return *this;
            auto copy = otherList;
            std::swap(*this , copy);
            return *this;
        }

        ~list(){
            erase(begin() , end());
            delete m_pHead;
            delete m_pTail;
        }
        void push_back(const T & object){
            auto p = new node(new T(object),m_pTail->m_pPrev,m_pTail);
            p->m_pPrev->m_pNext = p;
            m_pTail ->m_pPrev = p;
            m_uSize++;
        }
        void push_back(T&& object){
            auto p = new node(new T(std::move(object)),m_pTail->m_pPrev,m_pTail);
            p->m_pPrev->m_pNext = p;
            m_pTail ->m_pPrev = p;
            m_uSize++;
        }



        iterator begin(){
            return iterator(m_pHead->m_pNext);
        }
        const_iterator begin() const{
            return const_iterator(m_pHead->m_pNext);
        }
        iterator end(){
            return iterator(m_pTail);
        }
        const_iterator end() const{
            return const_iterator(m_pTail);
        }


        iterator insert(const iterator& itr,const T & obj){
            auto p = new node(new T(itr),itr.m_pNode->m_pPrev , itr.m_pNode);
            p->m_pPrev->m_pNext = p;
            itr.m_pNode->m_pPrev = p;
            m_uSize++;
            return iterator(p);
        }
        iterator insert(const iterator& itr,T && obj){
            auto p = new node(new T(std::move(itr)),itr.m_pNode->m_pPrev , itr.m_pNode);
            p->m_pPrev->m_pNext = p;
            itr.m_pNode->m_pPrev = p;
            m_uSize++;
            return iterator(p);
        }

        unsigned size(){
            return m_uSize;
        }

        iterator erase(const iterator& itr){
            iterator tmp(itr.m_pNode->m_pNext);
            delete itr.m_pNode;
            --m_uSize;
            return tmp;
        }

        iterator erase(const iterator &from , const iterator& to)
        {
            for(auto it = from ;it!=to;)
            {
                it = erase(it);
            }
            return to;
        }



    };//list



} // MDS

#endif //MDS_LIST_H
