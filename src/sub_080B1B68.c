extern void advanceAnimTrack(void *sprite, void *anim);
extern void *spawnBudgetedEffect(s32, s32);
extern s32 sub_080C31E0(s32, s32);

struct GameState_B1B68 { u8 _0[0x1870]; u32 v; };
extern struct GameState_B1B68 gMainWorkspace;

/* When the animation's flag bit 2 is set, fire an offset projectile using
 * the owner's work position and facing, then switch state. */
void sub_080B1B68(u8 *self) {
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *anim = *(u8 **)(self + 0x3C) + 0x34;
    u8 *ownerWork = *(u8 **)(*(u8 **)(self + 0x28) + 0x3C);

    advanceAnimTrack(sprite, anim);
    if (*anim & 2) {
        void *shot = spawnBudgetedEffect(gMainWorkspace.v, 0x1B9);
        s32 ownerX = *(s32 *)(ownerWork + 8);
        u32 dirFlag = *(u16 *)(*(u8 **)(*(u8 **)(self + 0x28) + 0x38) + 2) & 0x10;
        if (dirFlag)
            *(s32 *)((u8 *)shot + 0x4C) = ownerX + 0x140000;
        else
            *(s32 *)((u8 *)shot + 0x4C) = ownerX + (s32)0xFFEC0000;
        *(s32 *)((u8 *)shot + 0x5C) = *(s32 *)(ownerWork + 0xC) + 0xE0000;
        dirFlag = *(u16 *)(*(u8 **)(*(u8 **)(self + 0x28) + 0x38) + 2) & 0x10;
        if (dirFlag)
            *(s32 *)((u8 *)shot + 0x7C) = 0;
        else
            *(s32 *)((u8 *)shot + 0x7C) = 0x8000;
        *(s32 *)((u8 *)shot + 0x6C) = 0x20000;
        sub_080C31E0((s32)self, *(s32 *)(self + 0x24));
    }
}
