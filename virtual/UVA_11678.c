#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define min(x, y) ((x)>(y)?(y):(x))

typedef struct 
{
    int *array;
    size_t size;
} Array;

/* Initialise an empty array */
void Array_Init(Array *array) 
{
    int *int_pointer;

    int_pointer = (int *)malloc(sizeof(int));

    if (int_pointer == NULL)
    {       
        printf("Unable to allocate memory, exiting.\n");
        free(int_pointer);
        exit(0);
    }
    else
    {
        array->array = int_pointer; 
        array->size = 0;
    }
}

/* Dynamically add to end of an array */
void Array_Add(Array *array, int item) 
{
    int *int_pointer, i = 0;

    for(i = 0; i < array->size; i++)
    {
        if(item == array->array[i])
        {
            return;
        }
    }

    array->size += 1;

    int_pointer = (int *)realloc(array->array, array->size * sizeof(int));

    if (int_pointer == NULL)
    {       
        printf("Unable to reallocate memory, exiting.\n");
        free(int_pointer);
        exit(0);
    }
    else
    {
        array->array = int_pointer;
        array->array[array->size-1] = item;
    }
}

/* Free an array */
void Array_Free(Array *array) 
{
  free(array->array);
  array->array = NULL;
  array->size = 0;  
}

void show_Array(Array *array) 
{
    int i = 0;
    printf("\nsize: %ld\n", array->size);
    for(i = 0; i < array->size; i++)
    {
        printf("%d ", array->array[i]);
    }
    printf("\n");
}

int main()
{
    int i = 0;

    int A, B, val;
    while(scanf("%d %d", &A, &B) != EOF)
    {
        if(A == 0 && B == 0)
        {
            return 0;
        }
        int a[100005] = {0};
        int b[100005] = {0};
        int T[100005] = {0};
        int CNT_Alice = 0, CNT_Betty = 0;
        int CNT_union = 0;

        for(i = 0; i < A; i++)
        {
            scanf("%d", &val);
            if(a[val] == 0)
            {
                a[val] = 1;
                CNT_Alice++;
            }
            if(T[val] == 0)
            {
                T[val] = 1;
                CNT_union++;
            }
        }
        for(i = 0; i < B; i++)
        {
            scanf("%d", &val);
            if(b[val] == 0)
            {
                b[val] = 1;
                CNT_Betty++;
            }
            if(T[val] == 0)
            {
                T[val] = 1;
                CNT_union++;
            }
        }
        printf("%d\n", min(CNT_union - CNT_Alice, CNT_union - CNT_Betty));
    }
}