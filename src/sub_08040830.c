struct S_02025FF0_40830 { u8 _0[0x174C]; u32 f174C; u32 f1750; };
extern struct S_02025FF0_40830 gMainWorkspace;
extern void *gMainObjTimerCallbacks;
extern s32 nextRandomWord(void);
extern s32 getAngleFromDelta(s32, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void stepAnimationTrack(void *, void *);
extern void setPolarOffset(void *, s32, s32);
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
    stepAnimationTrack(sprite, animTrack);
    {
        u8 trackFlag = *(u8 *)(body + 0x34);
        u32 flagMask = 2;
        flagMask &= trackFlag;
        if (flagMask != 0) {
            if (*(u8 *)(entity + 0x7C) != 0) {
                sub_080C31E0(entity, *(void **)(entity + 0x24));
                return;
            }
            { s32 random = nextRandomWord(); one = 1; randomBit = random & one; direction = -1; if (randomBit) direction = 1; }
            { s32 *angleSlot = (s32 *)(entity + 0x6C);
              angle = getAngleFromDelta(gMainWorkspace.f1750 - *(s32 *)(body + 0xC), gMainWorkspace.f174C - *(s32 *)(body + 8));
              angle += (direction * 3) << 12;
              *angleSlot = angle; }
            setPolarOffset(body, angle, 0xE0 << 9);
            *(s8 *)(*(u8 **)(body + 0x28) + 2) = 8;
            *(u8 *)(*(u8 **)(body + 0x28) + 3) = (u8)one;
            setAnimationFrame(sprite, animTrack, 0x15, 1);
            { u16 spriteAttr = *(u16 *)((u8 *)sprite + 0x28);
              u8 *gfxCopy = entity + 0x84;
              u8 zero = 0;
              *(u16 *)gfxCopy = spriteAttr;
              (entity + *(s16 *)(entity + 0x22) * 2)[0x19] = zero; }
            { void **handlerTable = &gMainObjTimerCallbacks; sub_080C31E4(entity + 0x18, entity + 0x22, *handlerTable); }
        }
    }
}
