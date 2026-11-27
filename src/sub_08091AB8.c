extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, void *);
extern s32 sub_08014114(s32, s32, s32, s32, s32, s32);
extern void sub_080C31E0(void *, void *);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Drop a view-bound object that leaves the active camera area; otherwise
 * advance its display state and animation, then place its sprite at the
 * object's world position minus the current scroll offset. */
void sub_08091AB8(void *arg0)
{
    u8 *camState;
    u8 *scroll;
    void *extra;
    u8 *state;
    void *anim;
    void *sprite;

    sprite = *(void **)((u8 *)arg0 + 0x38);
    state = *(u8 **)((u8 *)arg0 + 0x3C);
    anim = (void *)(0x34 + (u32)state);
    extra = state;
    extra += 0x48;

    if (sub_08014114(*(s32 *)(state + 8), *(s32 *)(state + 0xC), -8, 8, -8, 8) == 0) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }

    advanceMotion(state, *(s32 *)((u8 *)extra + 4));
    stepAnimationTrack(sprite, anim);

    scroll = gCameraState;
    camState = gMainWorkspace;
    camState += 0x18A8;

    {
        u32 idx;
        u8 *xTable;
        u8 *yTable;

        idx = ((u32)*camState + 1) * 0x40;
        xTable = scroll + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)(state + 8) - ((*(u32 *)(xTable + idx) + 0x8000) & 0xFFFF0000);

        idx = ((u32)*camState + 1) * 0x40;
        yTable = scroll + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)(state + 0xC) - ((*(u32 *)(yTable + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
