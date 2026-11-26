extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_0800583C(s32);
extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);

/* When the body is close to its wandering target, re-roll that target with a
 * little random spread, then steer the body toward it. */
void sub_0805C268(void *script)
{
    void *sprite;
    void *body;
    void *anim;
    void *extra;

    sprite = *(void **)((u8 *)script + 0x38);
    body = *(void **)((u8 *)script + 0x3C);
    anim = (u8 *)body + 0x34;
    extra = (u8 *)body + 0x48;

    setAnimationFrame(sprite, anim, 0, 1);
    if (sub_08014A04(body, *(s32 *)((u8 *)extra + 8), *(s32 *)((u8 *)extra + 0xC), 0x80000, 0x80000) == 1) {
        *(s32 *)((u8 *)extra + 8) = *(s32 *)((u8 *)body + 0x48) + sub_0800583C(0x200000);
        *(s32 *)((u8 *)extra + 0xC) = *(s32 *)((u8 *)extra + 4) + sub_0800583C(0x200000);
    }
    sub_08014B1C(body, (u8 *)body + 0x58, *(s32 *)((u8 *)extra + 8), *(s32 *)((u8 *)extra + 0xC));
}

extern u8 gCameraState[];

s32 sub_08060370(void) {
    u8 *base = gCameraState;
    *(u32 *)(base + 0x1454) += 1;
    {
        u8 t = *(u8 *)(base + 0x145C);
        t |= 4;
        *(u8 *)(base + 0x145C) = t;
        if (t & 2) {
            *(u8 *)(base + 0x145C) = t & 0xFD;
            *(u8 *)(base + 0x143C) = *(u8 *)(base + 0x1444);
        }
    }
    return 0;
}
