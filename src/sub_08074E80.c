extern s32 sub_0806D35C(void *, s32, void *);
extern void sub_0806D588(s32, void *);
extern s32 sub_08003740(void *, s32);
extern void sub_0806E114(s32, s32, s32, s32);
extern void sub_080722E0(void *, u8);

/* Partial view of the shared game state used by this effect. */
struct S_74E80_Data {
    u8 _pad0[0x14ED];
    u8 byte14ED;
    u8 _pad1[0x174C - 0x14EE];
    s32 word174C;
    s32 word1750;
    u8 _pad2[0x18C2 - 0x1754];
    u16 word18C2;
};
extern struct S_74E80_Data D_02025FF0;

/* Update an orbiting effect: advance its angle/phase, steer it toward a moving
 * target, convert its world position to screen space, run its delay callback and
 * periodically spawn a kind-0x2C projectile at its position. */
void sub_08074E80(void *arg0) {
    u8 *data;
    s32 obj;
    u8 *cur;
    struct S_74E80_Data *gameState;
    s32 phase, step, targetX, targetY, delta, x, y, counter;

    data = (u8 *)*(void **)((u8 *)arg0 + 0x6C) + 4;
    obj = *(s32 *)((u8 *)arg0 + 0x38);
    cur = data;
    if (sub_0806D35C(arg0, obj, cur) != 0)
        return;
    counter = (*(s32 *)((u8 *)cur + 0x54) + 1) & 0xFF;
    *(s32 *)((u8 *)cur + 0x54) = counter;
    phase = (*(s32 *)((u8 *)cur + 0x58) + 1) & 0x1FF;
    *(s32 *)((u8 *)cur + 0x58) = phase;
    if (phase & 0x100)
        step = (0x100 - (phase & 0xFF)) >> 4;
    else
        step = (phase & 0xFF) >> 4;
    sub_080722E0(cur, (u8)*(s32 *)((u8 *)data + 0x54));

    gameState = &D_02025FF0;
    targetX = gameState->word174C + *(s32 *)((u8 *)cur + 8) * (step + 0x18);
    targetY = gameState->word1750 + *(s32 *)((u8 *)cur + 0x0C) * (step + 0x18);

    x = *(s32 *)((u8 *)cur + 0);
    delta = targetX - x;
    if (delta < 0)
        delta += 7;
    *(s32 *)((u8 *)cur + 0) = x + (delta >> 3);

    y = *(s32 *)((u8 *)cur + 4);
    delta = targetY - y;
    if (delta < 0)
        delta += 7;
    *(s32 *)((u8 *)cur + 4) = y + (delta >> 3);

    sub_0806D588(obj, cur);
    *(u16 *)obj = gameState->word18C2;
    if (sub_08003740((u8 *)data + 0x1C, obj) == 0) {
        ((void (*)(void *))(*(void **)((u8 *)arg0 + 0x24)))(arg0);
        return;
    }
    counter = *(s32 *)((u8 *)cur + 0x10) - 1;
    *(s32 *)((u8 *)cur + 0x10) = counter;
    if (counter == 0) {
        sub_0806E114(*(s32 *)((u8 *)arg0 + 0x28), 0x0F, *(s32 *)cur, *(s32 *)((u8 *)cur + 0x04));
        *(s32 *)((u8 *)cur + 0x10) = 0x10;
    }
    if (gameState->byte14ED != 0x31) {
        ((void (*)(void *))(*(void **)((u8 *)arg0 + 0x24)))(arg0);
    }
}
