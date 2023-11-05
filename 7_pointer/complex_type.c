int (*(*fp)(void *))[10];

// fp是一个指针，假设这个指针的类型是T1
typedef int (*T1(void *))[10];
T1 *fp;

// T1 是一个函数指针类型，返回T2类型
typedef int (*T2)[10];
typedef T2 T1(void *);

// T2明显可以看出来是一个数组指针类型，也可以继续拆解
typedef int T3[10];
typedef T3 *T2;


