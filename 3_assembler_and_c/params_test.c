int foo();
int bar();

int main(void)
{
    foo(2, 3);
    return 0;
}

int foo(int a, int b)
{
    return bar(a);
}

int bar(int c, int d)
{
    int e = c + d;
    return e;
}
