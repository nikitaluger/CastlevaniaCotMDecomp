struct S_02025FF0 {
    u8 _0[0x174C];
    s32 targetX;
    s32 targetY;
};

extern struct S_02025FF0 gMainWorkspace;

extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern s32 sub_08005910(s32, s32);
extern s32 sub_080C31E0(s32, void *);
extern s32 sub_0800583C(s32);
extern void sub_08014B1C(void *, void *, s32, s32);

extern void *D_08671BFC;

/* When the entity is near the target point, aim it (with a little random
 * spread) toward that point and start its movement toward it. */
void sub_0805C814(void *script)
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

    if (sub_08014A04(body, *(s32 *)((u8 *)extra + 8), *(s32 *)((u8 *)extra + 0xC), 0x100000, 0x100000) == 1) {
        struct S_02025FF0 *p = &gMainWorkspace;
        s32 angle = sub_08005910(p->targetY - *(s32 *)((u8 *)body + 0x0C),
                                  p->targetX - *(s32 *)((u8 *)body + 0x08));
        void **fpPtr = &D_08671BFC;

        *(s32 *)((u8 *)body + 0x48) += sub_080C31E0(angle + 0x4000, *fpPtr) * 8;
        *(s32 *)((u8 *)extra + 0x04) += sub_080C31E0(angle, *fpPtr) * 8;

        *(s32 *)((u8 *)extra + 0x08) = *(s32 *)((u8 *)body + 0x48) + sub_0800583C(0x200000);
        *(s32 *)((u8 *)extra + 0x0C) = *(s32 *)((u8 *)extra + 0x04) + sub_0800583C(0x200000);
    }

    sub_08014B1C(body, (u8 *)body + 0x58, *(s32 *)((u8 *)extra + 0x08), *(s32 *)((u8 *)extra + 0x0C));
}
