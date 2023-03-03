#include <stdio.h>

int main()
{
    int num = 0, arr1[5] = {}, arr2[3][4] = {},
        *ptr = 0,
        *aop[4] = {};
    
       ptr          =       &num;
    // (int*)       =       (int*)

       aop[0]       =       ptr;
    // (int*)       =       (int*)

       *aop[0]      =       60;
    // int          =       int
    // dereference of (int *) => int

       aop[1]       =       &arr1[2];
    // (int*)       =       (int*)
    //                      address of(arr1[2])
    //                                *(arr1 + 2)
    //                                  arr1 => array-to-pointer conversion

       *aop[1]      =       70;
    // int          =       int

       aop[2]       =       arr1;
    // (int*)       =       (int*)
    //                      array-to-pointer conversion
    //                      int[5] => int*

       aop[2][1]    =       80;
    // (int)        =       int
    // aop[2] is (int*), so aop[2][1] = *(aop[2] + 1)

       aop[3]       =       arr2[1];
    // (int*)       =       (int*)
    //                      first: Implicit conversion => array of array to points to array 
    //                      then:  array-to-pointer conversion => int[4] > int*

       int (* tab)[4];               // arr2 is an array of int [3]
       tab          =       arr2;    // the converted address is of type int (*)[4]
    // int(*)[4]    =       int(*)[4]

       aop[3][1]    =       90;
}
