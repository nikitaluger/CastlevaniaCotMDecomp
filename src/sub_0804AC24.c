extern u32 gTrigFuncTable[];
extern void stepAnimationTrack(void *, void *);
extern void sub_0804ACB0(void *, void *);

typedef s32 (*Fn1)(s32);

/* Per-frame motion step: integrate horizontal position, offset the vertical
 * position by a wave function of the body's angle, advance that angle, then
 * refresh the sprite animation and its graphics pointer. */
void sub_0804AC24(void *actor) {
    u8 *sprite = *(u8 **)((u8 *)actor + 0x38);
    u8 *work = *(u8 **)((u8 *)actor + 0x3C);
    u8 *anim = 0x34 + work;
    u8 *motion = work + 0x48;
    s32 wave;

    *(s32 *)(work + 8) = *(s32 *)(work + 8) + *(s32 *)(work + 0x10);
    wave = ((Fn1)gTrigFuncTable[0])(*(s32 *)(motion + 4));
    *(s32 *)(work + 0xC) = *(s32 *)(work + 0x48) + (wave << 2);
    *(s32 *)(motion + 4) = *(s32 *)(motion + 4) + 0x200;
    stepAnimationTrack(sprite, anim);
    sub_0804ACB0(work, sprite);
}
