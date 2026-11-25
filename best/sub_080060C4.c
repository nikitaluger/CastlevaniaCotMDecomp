typedef void (*Fn3)(void *, void *, void *);
typedef void (*Fn2)(void *, void *);

void sub_080060C4(void *arg0, void *arg1, void *arg2, Fn3 arg3)
{
    u32 i;
    u16 count;
    void **p;
    i = 0;
    count = 9;
    if (i < count) {
        p = (void **)0x08106DCC;
        do {
            void *fn = p[0];
            if (fn != 0) {
                if (arg0 != 0) {
                    arg3(fn, arg1, arg2);
                } else {
                    ((Fn2)arg3)(fn, arg1);
                }
            }
            p += 3;
            i++;
        } while (i < count);
    }
}
