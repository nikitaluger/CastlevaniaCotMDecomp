void stepAnimationTrack(void *, void *);
s32 isPointInActiveCameraBounds(s32, s32, s32, s32, s32, s32);
s32 isOutsideCameraBounds(s32, s32);
void sub_080C31E0(void *, s32);

struct GameState { u8 _pad[0x10]; u32 mode; };
extern struct GameState gMainWorkspace;
extern u8 gCameraState[];

/* Keeps an entity updated while it is inside the active region; once it leaves,
 * dispatches the destruction callback stored at self+0x24. While active it
 * integrates velocity/acceleration and recomputes screen coordinates. */
void sub_0808E27C(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 *body = *(u8 **)(self + 0x3C);
    u8 *motion = body + 0x14;

    if (gMainWorkspace.mode == 1) {
        if (isPointInActiveCameraBounds(*(s32 *)(body + 0x14), *(s32 *)(motion + 4), -0x10, 0x10, -0x10, 0x10) != 0)
            goto updates;
    } else {
        if (isOutsideCameraBounds(*(s32 *)(body + 0x14), *(s32 *)(motion + 4)) != 1)
            goto updates;
    }
    sub_080C31E0(self, *(s32 *)(self + 0x24));
    return;

updates:
    *(s32 *)(motion + 0) = *(s32 *)(motion + 0) + *(s32 *)(motion + 8);
    *(s32 *)(motion + 4) = *(s32 *)(motion + 4) + *(s32 *)(motion + 0xC);
    *(s32 *)(motion + 0xC) = *(s32 *)(motion + 0xC) + *(s32 *)(motion + 0x10);
    stepAnimationTrack(gfx, body);

    {
        u8 *pt = gCameraState;
        u8 *pb = (u8 *)&gMainWorkspace;
        u8 *xTable;
        u8 *yTable;
        u32 idx;

        pb += 0x18A8;

        idx = ((u32)*pb + 1) * 0x40;
        xTable = pt + 0x1278;
        *(u32 *)(gfx + 0x14) = *(u32 *)(motion + 0) - ((*(u32 *)(xTable + idx) + 0x8000) & 0xFFFF0000);

        idx = ((u32)*pb + 1) * 0x40;
        yTable = pt + 0x127C;
        *(u32 *)(gfx + 0x18) = *(u32 *)(motion + 4) - ((*(u32 *)(yTable + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
