struct GlobalState {
    u8 pad[0x174C];
    u32 playerX;
    u32 playerY;
};
extern struct GlobalState gMainWorkspace;
extern u16 D_080CE780[];
extern u32 gMainObjTimerCallbacks;

s32 sub_08005910(s32, s32);
void setAnimationFrame(void *, void *, s32, s32);
void sub_080146D0(void *, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Set the entity's pose, then, when its tracking flag is set, give it a fixed-speed
 * velocity in a table-driven direction (mirrored by a direction flag) and advance
 * to the next AI state. The atan2 call is retained from the shared movement code. */
void sub_0801EE84(void *self) {
    void *entity;
    void *work;
    void *gfx;
    u32 *handlerSlot;
    s32 angle;
    s32 dy;
    s32 dx;
    s32 unusedAngle;

    entity = self;
    gfx = *(void **)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    setAnimationFrame(gfx, (u8 *)work + 0x34, 0x13, 0);
    if (*(u16 *)((u8 *)self + 0x5C) & 0x01) {
        dy = gMainWorkspace.playerY - *(s32 *)((u8 *)work + 0x0C);
        dx = gMainWorkspace.playerX - *(s32 *)((u8 *)work + 0x08);
        unusedAngle = sub_08005910(dy, dx);
        angle = D_080CE780[*(s16 *)((u8 *)self + 0x7C)];
        if (*(s16 *)((u8 *)self + 0x84) > 0) {
            angle = (0x8000 - angle) & 0xFFFF;
        }
        sub_080146D0(work, angle, 0x38000);
        *(u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22)) * 2 + 0x19) = 0;
        handlerSlot = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *handlerSlot);
    }
}
