extern s16 D_080CF858[];
void setAnimationFrame(void *, s32, s16, s32);
void stepAnimationTrack(void *, s32);
void copyPoseAttrs(void *, void *);
void setSpriteFacingToTarget(void *, s32);
void sub_08047164(void *, void *, void *, void *);
void sub_080C31E8(void *, void *, s32, s32);

/* Advance this object's animation, copy its sprite attributes, and on an
 * animation event frame apply the linked frame, facing, sprite data, and callback. */
void sub_08046248(void *self) {
    void *animCtrl;
    void *body;
    s32 animState;
    s32 sprite;
    u8 zero;
    s32 renderMask;
    s32 flag;
    s16 frameIndex;

    animCtrl = *(void **)((u8 *)self + 0x38);
    body = *(void **)((u8 *)self + 0x3C);
    animState = (s32)body + 0x34;
    sprite = 0x48 + (s32)body;
    stepAnimationTrack(animCtrl, (void *)animState);
    sub_08047164(self, body, (void *)sprite, animCtrl);
    if ((*(u8 *)((u8 *)body + 0x34) & 2) != 0) {
        *(u8 *)((u8 *)*(void **)((u8 *)sprite + 4) + 1) = 0;
        frameIndex = D_080CF858[*(u8 *)((u8 *)self + 0x4C)];
        setAnimationFrame(animCtrl, (void *)animState, frameIndex, 1);
        setSpriteFacingToTarget(animCtrl, *(s32 *)((u8 *)body + 8));
        flag = *(u16 *)((u8 *)animCtrl + 2) & 0x10;
        renderMask = 0xFFFFD000;
        if (flag != 0)
            renderMask = 0xC0 << 6;
        *(s32 *)((u8 *)body + 0x10) = renderMask;
        {
            u16 tile = *(u16 *)((u8 *)animCtrl + 0x28);
            zero = 0;
            *(u16 *)((u8 *)sprite + 0) = tile;
        }
        *(u8 *)((u8 *)sprite + 2) = 0x18;
        copyPoseAttrs(*(void **)((u8 *)body + 0x28), (void *)0x080CF5B0);
        *(u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22)) * 2 + 0x19) = zero;
        {
            s32 *lit = (s32 *)0x08671BD0;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 0, *lit);
        }
    }
}
