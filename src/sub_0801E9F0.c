struct GlobalState {
    u8 pad[0x174C];
    u32 playerX;
    u32 playerY;
};
extern struct GlobalState gMainWorkspace;
extern u32 gMainObjTimerCallbacks;

s32 sub_08005910(s32, s32);
void setAnimationFrame(void *, void *, s32, s32);
void sub_080146D0(void *, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Pick the entity's animation pose, then, when its tracking flag is set, aim its
 * velocity at the player's position and advance to the next AI state. */
void sub_0801E9F0(void *self) {
    void *gfx;
    void *work;
    void *anim;
    void *aim;
    s32 dy;
    s32 dx;
    s32 angle;
    u32 *ptr;

    gfx = *(void **)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    anim = (u8 *)work + 0x34;
    aim = (u8 *)work + 0x48;
    if (*(s16 *)((u8 *)aim + 2) == 0) {
        setAnimationFrame(gfx, anim, 0x0B, 0);
        if (*(u8 *)anim & 0x02) {
            *(s16 *)((u8 *)aim + 2) = 1;
        }
    } else {
        setAnimationFrame(gfx, anim, 0x0F, 1);
    }
    if (*(u16 *)((u8 *)self + 0x5C) & 0x01) {
        dy = gMainWorkspace.playerY - *(s32 *)((u8 *)work + 0x0C);
        dx = gMainWorkspace.playerX - *(s32 *)((u8 *)work + 0x08);
        angle = sub_08005910(dy, dx);
        sub_080146D0(work, angle, 0x90 << 10);
        *(u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22)) * 2 + 0x19) = 0;
        ptr = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *ptr);
    }
}
