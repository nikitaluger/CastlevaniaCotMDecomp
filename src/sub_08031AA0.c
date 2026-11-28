extern s32 spawnVariant2Effect(s32, s32, s32);
extern s32 sub_080C31E0(void *, s32);

/* Spawn a variant-2 effect at the work area's fixed-point position, raised by
 * 24 units when the linked object's flag is set, then switch to the entity's
 * state handler at +0x24. */
void sub_08031AA0(void *arg0)
{
    void *obj;
    void *work;

    obj = *(void **)((u8 *)arg0 + 0xAC);
    work = *(void **)((u8 *)arg0 + 0x3C);
    obj = *(void **)((u8 *)obj + 4);
    if (2 & *(u16 *)((u8 *)obj + 6)) {
        spawnVariant2Effect(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC) + 0x180000, 8);
    } else {
        spawnVariant2Effect(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC), 8);
    }
    sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
