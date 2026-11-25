s32 sub_080160A0(s32, s32, s32, s32, void *);

/* On contact with `other` whose flag bit 0 is set: mark the work area's state
 * as 1, set flag 0x400 on `other`, then forward the work area's fields to
 * sub_080160A0. */
void sub_0809291C(void *entity, void *other) {
    s32 field4;
    void *work;
    work = *(void **)((s8 *)entity + 0x3C);
    if (1 & (*(u16 *)((s8 *)other + 2))) {
        *(s16 *)((s8 *)work + 0xE) = 1;
        if (1 & (*(u16 *)((s8 *)other + 2))) {
            *(u16 *)((s8 *)other + 2) = (u16)(0x400 | (*(u16 *)((s8 *)other + 2)));
        }
    }
    field4 = *(s32 *)((s8 *)work + 4);
    sub_080160A0(field4, *(s32 *)((s8 *)work + 0x14), field4, *(s32 *)((s8 *)work + 0x18), other);
}
