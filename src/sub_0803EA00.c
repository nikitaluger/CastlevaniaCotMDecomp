extern s32 sub_0808DBF8(s32, s32, s32);
extern s32 spawnVariant2Effect(s32, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Spawn two effect particles just below and above the work area's recorded
 * position, clear two of the work area's fields, then call back into the
 * entity's state handler. */
void sub_0803EA00(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    sub_0808DBF8(*(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0x20000, 8);
    spawnVariant2Effect(*(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0xFFFA0000, 8);
    *(s32 *)(work + 0x14) = 0;
    *(s32 *)(work + 0x10) = 0;
    sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
