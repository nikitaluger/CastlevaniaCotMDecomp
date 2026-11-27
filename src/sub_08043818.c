extern s32 updateObjectDisplayState(void *a, void *b);
extern void stepAnimationTrack(void *a, void *b);
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 sub_080C31E0(void *a, void *b);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Entity update: despawn when off-camera or when the animation-control flags
 * signal a removal; otherwise apply the display state and advance the
 * animation and motion when not already handled, then store camera-relative
 * coordinates into the sprite actor. */
void sub_08043818(void *arg0) {
    void *selfCopy = arg0;
    void *actor = *(void **)((u8 *)arg0 + 0x38);
    void *enemy = *(void **)((u8 *)arg0 + 0x3C);
    void *enemyData = (u8 *)enemy + 0x34;

    if (isOutsideCameraBounds(*(s32 *)((u8 *)enemy + 8), *(s32 *)((u8 *)enemy + 0xC)) == 1) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }
    if (updateObjectDisplayState(actor, enemy) != 0) {
        /* fall through to bottom */
    } else {
        stepAnimationTrack(actor, enemyData);
        if (*(u8 *)enemyData & 2) {
            sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
            return;
        }
    }

    {
        u8 *coordTable = gCameraState;
        u8 *scroll = gMainWorkspace;
        u8 *xTable;
        u8 *yTable;
        u32 idx;

        scroll += 0x18A8;

        idx = ((u32)*scroll + 1) * 0x40;
        xTable = coordTable + 0x1278;
        *(s32 *)((u8 *)actor + 0x14) = *(s32 *)((u8 *)enemy + 0x08) - ((*(s32 *)(xTable + idx) + 0x8000) & 0xFFFF0000);

        idx = ((u32)*scroll + 1) * 0x40;
        yTable = coordTable + 0x127C;
        *(s32 *)((u8 *)actor + 0x18) = *(s32 *)((u8 *)enemy + 0x0C) - ((*(s32 *)(yTable + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
