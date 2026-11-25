void sub_080C31E4(void *, void *, s32);

/* Zero the entity's velocity, arm the sub-object's 60-frame timer, clear the
 * current script step counter and dispatch the next command. */
void sub_080554E4(void *entity) {
    u8 *work = *(u8 **)((u8 *)entity + 0x3C);
    u16 *sub = (u16 *)(work + 0x48);
    s32 zero = 0;
    void **pp;
    *(u32 *)(work + 0x14) = zero;
    *(u32 *)(work + 0x10) = zero;
    sub[3] = 0x3C;
    ((u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2))[0x19] = zero;
    pp = (void **)0x08671BB0;
    sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, (s32)*pp);
}
