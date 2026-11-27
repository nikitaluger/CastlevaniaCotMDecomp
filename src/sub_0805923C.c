s32 getSpriteFacingSign(void *);
s32 sub_080C31E0(s32, s32);
void sub_08014848(s32, s32, s32, s32, s32, s32);

extern s32 gTrigFuncPtr;

/* On one script phase, flip the sprite's facing flag, set its horizontal
 * direction and spawn a small effect burst; advance the script when its timer
 * runs out. */
void sub_0805923C(void *script)
{
    void *sprite;
    void *body;
    void *extra;
    s16 step;
    u32 phase;

    sprite = *(void **)((u8 *)script + 0x38);
    body = *(void **)((u8 *)script + 0x3C);
    extra = (u8 *)body + 0x48;

    step = *(s16 *)((u8 *)script + 0x22);
    phase = *(u8 *)((u8 *)script + step * 2 + 0x19);
    phase &= 3;
    if (phase == 1) {
        *(u16 *)((u8 *)sprite + 2) ^= 0x10;
        if (getSpriteFacingSign(sprite) < 0)
            *(s32 *)((u8 *)body + 0x48) = 0x20000;
        else
            *(s32 *)((u8 *)body + 0x48) = 0xFFFE0000;

        {
            s32 *lit = &gTrigFuncPtr;
            s32 s1 = sub_080C31E0(*(s32 *)((u8 *)extra + 8) + 0x4000, *lit);
            s32 dx = (-s1) * 8;
            s32 s2 = sub_080C31E0(*(s32 *)((u8 *)extra + 8), *lit);
            s32 dy = ((-s2) * 6) + 0x60000;
            sub_08014848(1, 1,
                *(s32 *)((u8 *)body + 8) + dx,
                *(s32 *)((u8 *)body + 0x0C) + dy,
                0x80000, 0x80000);
        }
    }

    step = *(s16 *)((u8 *)script + 0x22);
    if (*(u8 *)((u8 *)script + step * 2 + 0x19) > 0x3C) {
        sub_080C31E0((s32)script, *(s32 *)((u8 *)script + 0x24));
    }
}
