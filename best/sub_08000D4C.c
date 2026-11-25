void sub_08000D4C(void **arg0, void **arg1)
{
    void **p = arg1;
    void **saved;
    void **v;
    *(void **)(arg1 + 1) = arg0;
    *arg0 = arg1;
    if (arg1 == (void **)0)
        return;
    v = *p;
    saved = arg1;
    if (v != (void **)0) {
        do {
            p = (void **)*p;
        } while (*p != (void **)0);
    }
    *p = saved;
    *(void **)(saved + 1) = p;
}
