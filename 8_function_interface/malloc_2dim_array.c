#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define assign_array(pointer, pointer_p, dim1, dim2) \
    do {                                             \
        pointer_p = pointer;                         \
        for (int i = 0; i < dim1; i++) {             \
            for (int j = 0; j < dim2; j++) {         \
                p[i][j] = (i + 1) * (j + 1);         \
            }                                        \
        }                                            \
    } while (0)

#define printf_array(pointer, pointer_p, dim1, dim2) \
    do {                                             \
        pointer_p = pointer;                         \
        for (int i = 0; i < dim1; i++) {             \
            for (int j = 0; j < dim2; j++) {         \
                printf("%d\t", p[i][j]);             \
            }                                        \
            printf("\n");                            \
        }                                            \
    } while (0)

/**
 * 数组指针
 */
void array_pointer(int dim1, int dim2)
{
    int(*pa)[dim2] = malloc(sizeof(int) * dim1 * dim2);
    memset(pa, 0, sizeof(int) * dim1 * dim2);
    assign_array(pa, int(*p)[dim2], dim1, dim2);
    printf_array(pa, int(*p)[dim2], dim1, dim2);
    free(pa);
}

/**
 * 二级指针
 */
void pointer_array(int dim1, int dim2)
{
    int **arr_pointers = malloc(sizeof(int *) * dim1);
    for (int i = 0; i < dim1; i++) {
        *(arr_pointers + i) = malloc(sizeof(int) * dim2);
    }
    assign_array(arr_pointers, int **p, dim1, dim2);
    printf_array(arr_pointers, int **p, dim1, dim2);
    for (int i = 0; i < dim1; i++) {
        free(*(arr_pointers + i));
    }
    free(arr_pointers);
}

/*
 * 一维数组模拟
 */
void single_array(int dim1, int dim2)
{
    int *p = malloc(sizeof(int) * dim1 * dim2);
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
            p[dim2 * i + j] = (i + 1) * (j + 1);
        }
    }
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
            printf("%d\t", p[dim2 * i + j]);
        }
        printf("\n");
    }
    free(p);
}

int main(int argc, char *argv[])
{
    array_pointer(5, 5);
    pointer_array(5, 5);
    single_array(5, 5);
    return EXIT_SUCCESS;
}
