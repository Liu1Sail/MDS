//
// Created by 23118 on 2023/9/11.
//

#ifndef MDS_SORT_H
#define MDS_SORT_H
#include <algorithm>
namespace MDS{

    //默认从小到大
    template <class T>
    void StraightInsertSort(const T& begin , const T& end)
    {
        for(auto itj = begin+1 ;  itj != end ; ++itj)
        {
            auto temp = *itj;
            for(auto it = itj -1 ; it >= begin ; --it)
            {
                if(*it > temp){
                    *(it + 1) = *it;
                }else
                {
                    *(it + 1) = temp;
                    break;
                }
                if(it == begin){
                    *begin = temp;
                }
            }

        }
    }//StraightInsertSort

    template<class T>
    void BinaryInsertSort(const T& begin , const T& end)
    {}//BinaryInsertSort

    //默认从小到大
    template<class T>
    void BubbleSort(const T& begin , const T& end)
    {
        for(auto iti = end ; iti != begin + 1 ; --iti)
        {
            for(auto itj = begin ; itj != iti - 1 ;itj++ )
            {
                if(*itj > *(itj+1))
                {
                    std::swap(*itj , *(itj+1));
                }
            }
        }
    }//BubbleSort

    template<class T>
    void QuickSort(const T& begin , const T& end)
    {}//QuickSort

    template<class T>
    void SelectSort(const T& begin , const T& end)
    {}//SelectSort

    template<class T>
    void HeapSort(const T& begin , const T& end)
    {}//HeapSort

    template<class T>
    void MergingSort(const T& begin , const T& end)
    {}//MergingSort

}//MDS

#endif //MDS_SORT_H