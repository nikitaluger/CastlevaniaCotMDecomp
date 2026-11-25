void sub_08011368(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);

void sub_0801E4D8(void *arg0) {
    u8 *obj = arg0;
    u8 new_var;
    s32 off;
    sub_08011368(*(void **)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34, 0, 0);
    *(u32 *)(obj + 0x14) = 0x0866D768;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    off = (*(s16 *)(obj + 0x22)) * 2;
    new_var = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(new_var + obj))[off]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}

void sub_0801E0DC(void *arg0) {
    u8 *obj = arg0;
    u8 new_var;
    s32 off;
    u32 *p = *(u32 **)(obj + 0x3C);
    p[5] = 0;
    p[4] = 0;
    *(u32 *)(obj + 0x14) = 0x0866D75C;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    off = (*(s16 *)(obj + 0x22)) * 2;
    new_var = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(new_var + obj))[off]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}
