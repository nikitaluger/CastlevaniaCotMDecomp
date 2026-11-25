extern void sub_080113A8(s32, void *);
extern void sub_0801165C(void *, s32);
extern void sub_0804ACB0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Rise-and-fall object step: refresh the sprite animation and sound, integrate
 * the motion under gravity (-0xC00 per frame) plus the horizontal acceleration
 * from its pose block, and when the vertical velocity turns negative (apex),
 * record the height in the pose block, stop, and advance the script. */
void sub_0804ABB8(void *entity) {
    u8 *self = entity;
    s32 sprite;
    u8 *work;
    u8 *body;
    u8 *anim;
    void **callback;
    sprite = *(s32 *)(self + 0x38);
    work = *(u8 **)(self + 0x3C);
    anim = work + 0x34;
    body = work + 0x48;
    sub_080113A8(sprite, anim);
    sub_0804ACB0(work, sprite);
    sub_0801165C(work, 0);
    *(s32 *)(work + 0x14) += 0xFFFFF400;
    *(s32 *)(work + 0x10) += *(s32 *)(body + 8);
    if (*(s32 *)(work + 0x14) < 0) {
        *(s32 *)(work + 0x48) = *(s32 *)(work + 0x0C);
        *(s32 *)(work + 0x14) = 0;
        ((u8 *)(self + (*(s16 *)(self + 0x22)) * 2))[0x19] = 0;
        callback = (void **)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, (s32)*callback);
    }
}
