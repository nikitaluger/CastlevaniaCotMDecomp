extern s32 spawnVariant2Effect(s32, s32, s32);
extern s32 sub_080C31E0(void *, s32);

/* Entity action: spawn a kind-2 effect at the work area's recorded fixed-point
 * position offset upward by 0xC0000 (12.0), then chain to the saved script
 * callback. */
void sub_0801EAC8(void *entity) {
    void *work;

    work = *(void **)((s8 *)entity + 0x3C);
    spawnVariant2Effect(*(s32 *)((s8 *)work + 8), *(s32 *)((s8 *)work + 0xC) + 0xC0000, 8);
    sub_080C31E0(entity, *(s32 *)((s8 *)entity + 0x24));
}
