//
// Created by 23118 on 2023/9/11.
//

#ifndef MDS_SORT_H
#define MDS_SORT_H
namespace MDS{

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

}//MDS

#endif //MDS_SORT_H