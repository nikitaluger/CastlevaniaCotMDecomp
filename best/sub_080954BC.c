extern u8 D_02025368[];
extern u8 D_081008CC[];

void *sub_080954BC(void *arg0, void *a1, void *a2, void *a3)
{
    u8 *base = D_02025368;
    void *r2 = *(void **)((u8 *)arg0 + 0xAC);
    void *ret = a3;
    u8 *p = base + 0x94;

    if (*p == 5) {
        void *r0 = *(void **)((u8 *)r2 + 4);
        u16 idx = *(u16 *)((u8 *)r0 + 6);
        ret = D_081008CC + (u32)idx * 12;
    }
    return ret;
}
