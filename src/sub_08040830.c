struct S_02025FF0_40830 { u8 _0[0x174C]; u32 f174C; u32 f1750; };
extern struct S_02025FF0_40830 D_02025FF0;
extern void *D_08671BB0;
extern s32 sub_080057F8(void);
extern s32 sub_08005910(s32, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void sub_080113A8(void *, void *);
extern void sub_080146D0(void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);

/* Step the entity's animation; when its track flags request it, aim a movement
 * at the player with a random bias, copy the sprite attribute and advance the
 * script step. */
void sub_08040830(u8 *entity) {
    void *sprite;
    u8 *body;
    u8 *animTrack;
    s32 direction, one, randomBit, angle;
    sprite = *(void **)(entity + 0x38);
    body = *(u8 **)(entity + 0x3C);
    animTrack = body + 0x34;
    sub_080113A8(sprite, animTrack);
    {
        u8 trackFlag = *(u8 *)(body + 0x34);
        u32 flagMask = 2;
        flagMask &= trackFlag;
        if (flagMask != 0) {
            if (*(u8 *)(entity + 0x7C) != 0) {
                sub_080C31E0(entity, *(void **)(entity + 0x24));
                return;
            }
            { s32 random = sub_080057F8(); one = 1; randomBit = random & one; direction = -1; if (randomBit) direction = 1; }
            { s32 *angleSlot = (s32 *)(entity + 0x6C);
              angle = sub_08005910(D_02025FF0.f1750 - *(s32 *)(body + 0xC), D_02025FF0.f174C - *(s32 *)(body + 8));
              angle += (direction * 3) << 12;
              *angleSlot = angle; }
            sub_080146D0(body, angle, 0xE0 << 9);
            *(s8 *)(*(u8 **)(body + 0x28) + 2) = 8;
            *(u8 *)(*(u8 **)(body + 0x28) + 3) = (u8)one;
            sub_08011368(sprite, animTrack, 0x15, 1);
            { u16 spriteAttr = *(u16 *)((u8 *)sprite + 0x28);
              u8 *gfxCopy = entity + 0x84;
              u8 zero = 0;
              *(u16 *)gfxCopy = spriteAttr;
              (entity + *(s16 *)(entity + 0x22) * 2)[0x19] = zero; }
            { void **handlerTable = &D_08671BB0; sub_080C31E4(entity + 0x18, entity + 0x22, *handlerTable); }
        }
    }
}
