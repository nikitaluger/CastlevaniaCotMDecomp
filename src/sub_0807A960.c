struct S_02025FF0 {
    u8 _0[0x10];
    s32 flag10;
    u8 _1[0x14ED - 0x14];
    u8 flag14ED;
    u8 _2[0x173A - 0x14EE];
    u8 state173A;
    u8 _3[0x18C2 - 0x173B];
    u16 sprite18C2;
};
extern struct S_02025FF0 gMainWorkspace;
extern s32 applyAreaSpecialBehavior(void *, void *, void *);
extern void stepDelayTimer(void *, void *);
extern void sub_0806D588(void *, void *);
extern void _call_via_r1(void *, s32);

/* Per-frame update for a moving entity: defer to its callback while a special
 * position mode owns it, otherwise apply the scroll delta to the sprite, copy in
 * the global sprite index, tick a countdown that calls back on expiry, then
 * refresh motion and fire the callback for certain area states. */
void sub_0807A960(u8 *self) {
    u8 *object;
    u8 *pos;
    u8 *sprite;
    struct S_02025FF0 *gameState;
    object = *(u8 **)(self + 0x6C);
    pos = object + 4;
    sprite = *(u8 **)(self + 0x38);
    if (applyAreaSpecialBehavior(self, sprite, pos) > 0) {
        _call_via_r1(self, *(s32 *)(self + 0x24));
        return;
    }
    *(s32 *)(sprite + 0x18) = *(s32 *)(sprite + 0x18) + *(s32 *)(pos + 0x0C);
    gameState = &gMainWorkspace;
    { u16 spriteIndex = gMainWorkspace.sprite18C2; *(u16 *)sprite = spriteIndex; }
    {
        s32 countdown = *(s32 *)(pos + 0x10) - 1;
        *(s32 *)(pos + 0x10) = countdown;
        if (countdown == 0) {
            _call_via_r1(self, *(s32 *)(self + 0x24));
            return;
        }
    }
    stepDelayTimer(object + 0x20, sprite);
    {
        s32 savedX = *(s32 *)(sprite + 0x18);
        sub_0806D588(sprite, pos);
        *(s32 *)(sprite + 0x18) = savedX;
    }
    if (gameState->state173A == 0x1C || (gameState->flag14ED == 0 && gameState->flag10 != 0)) {
        _call_via_r1(self, *(s32 *)(self + 0x24));
    }
}
