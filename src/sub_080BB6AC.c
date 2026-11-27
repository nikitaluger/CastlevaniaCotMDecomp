extern void sub_08014848(s32,s32,s32,s32,s32,s32);
extern void sub_080BE99C(void);
extern void sub_080BEA94(void);
extern s32 divideInt(s32,s32);
extern u16 gCrossfadeGfxState[];

/* Effect tick: nudge the state object left/right from a per-frame direction
 * flag, decay a counter into gCrossfadeGfxState[3], periodically draw an effect and
 * spawn particles, and on counter 0x97 run the node callbacks and dispatch the
 * completion callback. */
void sub_080BB6AC(void *self) {
    u8 *state;
    u8 *fx;
    void *node;

    state = *(u8 **)((char *)self + 0x3C);
    fx = state + 0x48;

    if (*(u8 *)((u32)(*(s16 *)((char *)self + 0x22) << 1) + (u32)self + 0x19) & 0x02) {
        *(s32 *)(state + 8) += 0x10000;
    } else {
        *(s32 *)(state + 8) += 0xFFFF0000;
    }

    if ((*(u8 *)((u32)(*(s16 *)((char *)self + 0x22) << 1) + (u32)self + 0x19) & 0x1F) == 0) {
        s32 *timer = (s32 *)(fx + 0x88);
        *timer -= 1;
        if (*timer < 0) *timer = 0;
        gCrossfadeGfxState[3] = (u16)(*timer | ((0x10 - *timer) << 8));
    }

    if (!(*(u8 *)((u32)(*(s16 *)((char *)self + 0x22) << 1) + (u32)self + 0x19) & 0x03)) {
        s32 *count = (s32 *)(fx + 0x84);
        s32 shift;
        s32 baseY;
        s32 spawnY;
        *count += 1;
        sub_080BE99C();
        shift = (divideInt(*count, 8) << 19) + (s32)0xFFC00000;
        baseY = *(s32 *)(state + 0xC);
        spawnY = baseY - shift;
        if (spawnY > baseY + (s32)0xFFC00000) {
            sub_08014848(1, 3, *(s32 *)(state + 8), spawnY, 0x300000, 0x40000);
        }
        if (*count == 0x97) {
            sub_080BEA94();
            node = *(void **)((char *)self + 0x30);
            while (node != NULL) {
                ((void (*)(void *))*(u32 *)((char *)node + 0x24))(node);
                node = *(void **)((char *)node + 0x2C);
            }
            *(u8 *)((u32)(*(s16 *)((char *)self + 0x22) << 1) + (u32)self + 0x19) = 0;
            ((void (*)(void *, void *))*(u32 *)0x08671BB0)((char *)self + 0x18, (char *)self + 0x22);
        }
    }
}
