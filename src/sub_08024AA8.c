s32 spawnVariant2Effect(s32, s32, s32);
s32 sub_080C31E0(void *, s32);

/* Spawn a variant-2 effect at the work position (x at +8, y at +0xC shifted
 * down by 0x40000) with parameter 8, then call the callback held at +0x24 on
 * this entity. */
void sub_08024AA8(void *entity)
{
    void *work;

    work = *(void **)((s8 *)entity + 0x3C);
    spawnVariant2Effect(*(s32 *)((s8 *)work + 8), *(s32 *)((s8 *)work + 0xC) + 0xFFFC0000, 8);
    sub_080C31E0(entity, *(s32 *)((s8 *)entity + 0x24));
}
