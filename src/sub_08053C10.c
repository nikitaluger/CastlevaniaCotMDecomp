s32 setAnimationFrame(s32, s32, s32, s32);
s32 getSpriteFacingSign(s32);
s32 sub_080C31E4(void *, void *, s32);

extern u32 gScriptStepCallbackTable;

/* Enemy lunge update: start the wind-up animation, and when the animation
 * control flags fire, step the enemy in its facing direction with a velocity,
 * drop it vertically, set its state, switch animation, clear the script
 * parameter and dispatch the callback. */
void sub_08053C10(void *arg0) {
    void *self;
    s32 actor;
    void *enemy;
    void *enemyData;
    void *enemyState;
    s16 paramIndex;
    s32 zero;
    u32 *pCallback;

    self = arg0;
    actor = *(s32 *)((u8 *)arg0 + 0x38);
    enemy = *(void **)((u8 *)arg0 + 0x3C);
    enemyData = (u8 *)enemy + 0x34;
    enemyState = (u8 *)enemy + 0x48;

    setAnimationFrame(actor, (s32)enemyData, 4, 0);
    if (!(*(u8 *)enemyData & 2)) return;

    if (getSpriteFacingSign(actor) < 0) {
        *(s32 *)((u8 *)enemy + 8) += 0xFFEC0000;
        *(s32 *)((u8 *)enemy + 0x10) = 0xFFFF0000;
    } else {
        *(s32 *)((u8 *)enemy + 8) += 0x140000;
        *(s32 *)((u8 *)enemy + 0x10) = 0x10000;
    }
    *(s32 *)((u8 *)enemy + 0x0C) += 0xFFEC0000;
    zero = 0;
    *(s16 *)((u8 *)enemyState + 4) = 6;
    setAnimationFrame(actor, (s32)enemyData, 8, 0);
    paramIndex = *(s16 *)((u8 *)self + 0x22);
    *((u8 *)self + paramIndex * 2 + 0x19) = (u8)zero;
    pCallback = &gScriptStepCallbackTable;
    sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *pCallback);
}
