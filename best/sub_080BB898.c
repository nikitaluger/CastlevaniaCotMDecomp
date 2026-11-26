void sub_080BB898(void **arg0)
{
    u32 i;
    void **p;
    void *obj;

    p = arg0;
    i = 0;
    do {
        obj = *p;
        p++;
        *(u8 *)((u8 *)obj + 1) = 1;
        i++;
    } while (i <= 4);
}
