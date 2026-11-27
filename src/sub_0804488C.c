s32 setAnimationFrame(s32, s32, s32, s32);
s32 stepAnimationTrack(s32, s32);
s32 setSpriteFacingToTarget(s32, s32);
s32 sub_080C31E0(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

extern u32 gMainObjTimerCallbacks;
extern u32 gTrigFuncTable;

/* Entity update: offset the enemy's vertical position from a script parameter
 * through a lookup callback, set the sprite's facing from its horizontal
 * position, and when the script timer matches the enemy's state value switch
 * animation, reset motion, clear the parameter and dispatch a callback. */
void sub_0804488C(void *arg0) {
    void *self;
    s32 actor;
    void *enemy;
    void *enemyData;
    void *enemyState;
    u32 paramIndex;
    u32 *pWaveFn;
    u32 *pCallbackFn;
    s32 param;

    self = arg0;
    actor = *(s32 *)((u8 *)arg0 + 0x38);
    enemy = *(void **)((u8 *)arg0 + 0x3C);
    enemyData = (u8 *)enemy + 0x34;
    enemyState = (u8 *)enemy + 0x48;

    pWaveFn = &gTrigFuncTable;
    paramIndex = *(s16 *)((u8 *)self + 0x22);
    param = *((u8 *)self + paramIndex * 2 + 0x19);
    param = (param << 8) + 0x4000;
    *(s32 *)((u8 *)enemy + 0x0C) = *(s32 *)((u8 *)enemy + 0x48) - (sub_080C31E0(param, *pWaveFn) + 0xFFFF0000) * 8;

    stepAnimationTrack(actor, (s32)enemyData);
    setSpriteFacingToTarget(actor, *(s32 *)((u8 *)enemy + 8));

    paramIndex = *(s16 *)((u8 *)self + 0x22);
    param = *((u8 *)self + paramIndex * 2 + 0x19);
    if (param == *(u8 *)((u8 *)enemyState + 4)) {
        setAnimationFrame(actor, (s32)enemyData, 0x15, 0);
        *(s32 *)((u8 *)enemy + 0x14) = 0xFFF9C000;
        paramIndex = *(s16 *)((u8 *)self + 0x22);
        *((u8 *)self + paramIndex * 2 + 0x19) = 0;
        pCallbackFn = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *pCallbackFn);
    }
}
