typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK setAnimationFrame(s32, s32, s32, s32);
M2C_UNK sub_08014848(s32, s32, s32, s32, s32, s32);
M2C_UNK sub_080C31E0(void *, s32);
u8 sub_080C389C(u8, s32);

/* Script-step callback: sets the companion's pose, spawns an effect at the
 * companion's position on every third step, and falls back for late steps. */
void sub_0804C5DC(void *arg0) {
    void *companion;
    s32 sprite;

    sprite = M2C_FIELD(arg0, s32 *, 0x38);
    companion = M2C_FIELD(arg0, void **, 0x3C);
    setAnimationFrame(sprite, companion + 0x34, 0xA, 0);
    if (sub_080C389C(M2C_FIELD(((M2C_FIELD(arg0, s16 *, 0x22) * 2) + arg0), u8 *, 0x19), 3) == 1) {
        sub_08014848(1, 1, M2C_FIELD(companion, s32 *, 8), M2C_FIELD(companion, s32 *, 0xC) + 0x100000, 0x140000, 0x140000);
    }
    if ((u32) M2C_FIELD(((M2C_FIELD(arg0, s16 *, 0x22) * 2) + arg0), u8 *, 0x19) > 0x78U) {
        sub_080C31E0(arg0, M2C_FIELD(arg0, s32 *, 0x24));
    }
}
