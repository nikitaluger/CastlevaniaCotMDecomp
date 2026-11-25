void sub_08003A6C(void *, s32, const void *);
void sub_08003740(void *, void *);
void sub_0806D588(void *, void *);
void sub_0806D6B4(void *);
void sub_080C31E4(void *, void *, u32);
extern u32 D_02025FF0[];
extern const void D_085063F0; /* sprite animation frame table */
extern u32 D_08671BB0[];

/* Move the entity with collision, and unless the game is in state 0x11, reset its
 * script/animation and velocity, then tick the script and place the sprite. */
void sub_08088064(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *actor = *(u8 **)(self + 0x6C);
    u8 *motion = actor + 4;
    u8 *view = *(u8 **)(self + 0x38);
    sub_0806D6B4(motion);
    if (D_02025FF0[5] != 0x11) {
        const void *handlerTable;
        sub_08003A6C(actor + 0x20, 0, &D_085063F0);
        *(s32 *)(motion + 8) = 0;
        *(s32 *)(motion + 0xC) = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        handlerTable = D_08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *(u32 *)handlerTable);
    }
    sub_08003740(actor + 0x20, view);
    sub_0806D588(view, motion);
}
