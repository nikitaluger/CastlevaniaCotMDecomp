extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void updateFollowPath(u8 *, u8 *, s32, s32);
extern void setSpriteFlip(s32, s32);
extern u8 gMainWorkspace[];

struct FollowWorkspace {
    u8 _0[0x1728];
    s32 targetX;   /* 0x1728 */
    s32 targetY;   /* 0x172C */
};

void sub_0805A500(u8 *self) {
    s32 parent = *(s32 *)(self + 0x38);
    u8 *obj = *(u8 **)(self + 0x3C);
    u8 *animState = obj + 0x34;
    u8 *moveState = obj + 0x48;
    s32 dx, dy, ax, ay;
    s32 bias;
    s32 *dispatch;

    setAnimationFrame(parent, animState, 0, 1);

    if (gMainWorkspace[0x14ED] == 0xA9) goto end;

    dx = ((struct FollowWorkspace *)gMainWorkspace)->targetX - *(s32 *)(obj + 8);

    bias = 0x80;
    bias <<= 0xC;
    dy = ((struct FollowWorkspace *)gMainWorkspace)->targetY - (*(s32 *)(obj + 0xC) + bias);

    ax = dx;
    if (dx < 0) ax = -dx;
    if (ax > 0x07FFFF) goto end;

    ay = dy;
    if (dy < 0) ay = -dy;
    if (ay > 0x07FFFF) goto end;

    *(s32 *)(obj + 0x48) = -dx;
    *(s32 *)(moveState + 4) = -dy;
    {
        s32 zero = 0;
        u16 speed = 0x12C;
        *(u16 *)(moveState + 8) = speed;
        *(u16 *)(moveState + 0xA) = 1;
        *(u16 *)(gMainWorkspace + 0x18BC) += 1;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        dispatch = (s32 *)0x08671BD0;
    }
    sub_080C31E8(self + 0x18, self + 0x22, 1, *dispatch);
    return;

end:
    bias = 0x80;
    bias <<= 0xC;
    updateFollowPath(obj, moveState + 0x14, ((struct FollowWorkspace *)gMainWorkspace)->targetX,
                 ((struct FollowWorkspace *)gMainWorkspace)->targetY - bias);
    setSpriteFlip(parent, *(s32 *)(moveState + 0x18));
}
