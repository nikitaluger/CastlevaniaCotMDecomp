void *sub_08000C84(void **arg0)
{
    void *r2 = *arg0;
    if (r2 == 0) {
        return 0;
    }
    {
        void *r0 = *(void **)((u8 *)r2 + 4);
        *(void **)((u8 *)r2 + 4) = 0;
        *arg0 = *(void **)(*arg0);
        return r0;
    }
}
