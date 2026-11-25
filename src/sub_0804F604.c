extern void *SpawnEffectAtPos(s32, s32, s32);
extern s32 sub_080C31E0(void *, s32);

/* Spawn the effect's two kind-8 sub-effects alongside it (0x40000 left and
 * right, 0xC0000 down from its 16.16 position), then run its update callback. */
void sub_0804F604(void *entity) {
    void *work;
    work = *(void **)((u8 *)entity + 0x3C);
    SpawnEffectAtPos(*(s32 *)((u8 *)work + 8) + 0xFFFC0000, *(s32 *)((u8 *)work + 0xC) + 0xC0000, 8);
    SpawnEffectAtPos(*(s32 *)((u8 *)work + 8) + 0x40000, *(s32 *)((u8 *)work + 0xC) + 0xC0000, 8);
    sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
}
