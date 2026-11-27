s32 advanceMotion(void *, s32);
s32 sub_0808DBF8(s32, s32, s32);
s32 sub_0808DC40(s32, s32, s32);
s32 sub_080C31E0(void *, s32);

/*
 * Script step: integrate gravity on the work struct, copy its position into
 * the entity, spawn a trail effect every fourth step, and on step 0x14 spawn
 * the final effect and switch state.
 */
void sub_0809EF64(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    advanceMotion(work, 0x2D82);
    *(s32 *)(self + 0x4C) = (s32)*(s32 *)(work + 8);
    *(s32 *)(self + 0x5C) = (s32)*(s32 *)(work + 0xC);
    if (!(3 & *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19))) {
        sub_0808DBF8(*(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0x80000, 8);
    }
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x14) {
        sub_0808DC40(*(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0x80000, 8);
        sub_080C31E0(arg0, *(s32 *)(self + 0x24));
    }
}
