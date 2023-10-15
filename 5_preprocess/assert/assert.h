#undef assert

#ifdef DEBUG

#define assert(test) ((void)0)

#else

void _Assert(char* msg);
#define _STR(x)      _VAL(x)
#define _VAL(x)      #x
#define assert(test) (test) ? (void)0 : _Assert(__FILE__ ":" _STR(__LINE__) " " #test)

#endif
