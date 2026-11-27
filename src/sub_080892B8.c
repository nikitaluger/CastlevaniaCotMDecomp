/* Enemy/boss per-frame update: when the global scene state reaches 0x1A,
 * queue a delayed graphics load for this entity and install its callback;
 * always align the sprite to its sub-object's 3D position. */
extern void startEffectTimer(void *, s32, void *);
extern void stepDelayTimer(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_080892B8(void *entity) {
    u8 *self;
    u8 *subObj;
    u8 *position;
    void *sprite;
    u8 *gameState;
    s32 *cbTable;
    self = (u8 *)entity;
    subObj = *(u8 **)(self + 0x6C);
    position = subObj + 4;
    sprite = *(void **)(self + 0x38);
    gameState = (u8 *)0x02025FF0;
    if (*(s32 *)(gameState + 0x14) == 0x1A) {
        u8 *gfxReq = subObj + 0x20;
        startEffectTimer(gfxReq, 0, (void *)0x08500D6C);
        *(s32 *)(gameState + 0x1C) = 2;
        stepDelayTimer(gfxReq, sprite);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        cbTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *cbTable);
    }
    sub_0806D588(sprite, position);
}
