extern u8 gMainWorkspace[];
extern u8 gTilemapPages[];
extern s32 gMainObjTimerCallback;
extern s32 sub_08005E80(s32);
extern s32 sub_08007DD8(s32, s32, s32);
extern void sub_0806D2F8(void *, void *);
extern s32 sub_0806D518(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_0806E114(s32, s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct WarpTarget { u8 _0[4]; u16 x; u16 y; u16 flag; };

/* Behaviour callback: advance the point along its velocity, and on a tile contact set
 * the target's warp destination and velocity, dispatch the next script command. */
void sub_0806EB2C(void *behav) {
    u8 *params;
    u8 *point;
    u8 *target;
    s32 hitFlag;
    s32 tile;
    s32 velocity;
    s32 dirMask;
    u8 zero;
    params = *(u8 **)((u8 *)behav + 0x6C);
    point = params + 4;
    target = *(u8 **)((u8 *)behav + 0x38);
    if (sub_0806D518(behav, target, point) == 0) {
        *(s32 *)(params + 4) = *(s32 *)(params + 4) + *(s32 *)(point + 8);
        *(s32 *)(point + 4) = *(s32 *)(point + 4) + *(s32 *)(point + 0xC);
        sub_0806D588(target, point);
        hitFlag = 1 & *(u16 *)(*(void **)(point + 0x3C) + 0x14);
        if (hitFlag != 0) {
            sub_0806E114(*(s32 *)((u8 *)behav + 0x28), 8, *(s32 *)(params + 4), *(s32 *)(point + 4));
            sub_080C31E0(behav, *(s32 *)((u8 *)behav + 0x24));
            return;
        }
        tile = sub_08007DD8((s32)&gTilemapPages[gMainWorkspace[0x18A8] << 6], *(s32 *)(params + 4), *(s32 *)(point + 4));
        if ((u16)tile != 0) {
            zero = 0;
            ((struct WarpTarget *)target)->x = 0x100;
            ((struct WarpTarget *)target)->y = 0x100;
            ((struct WarpTarget *)target)->flag = hitFlag;
            dirMask = 0x10 & *(u16 *)(target + 2);
            velocity = 0xFFFE0000;
            if (dirMask != 0) {
                velocity = 0x80 << 0x0A;
            }
            *(s32 *)(point + 8) = velocity;
            *(s32 *)(point + 0xC) = 0xFFFC0000;
            *(u8 *)(*(void **)(point + 0x3C) + 1) = zero;
            sub_08005E80(0x90);
            *(u8 *)((u8 *)behav + (*(s16 *)((u8 *)behav + 0x22)) * 2 + 0x19) = zero;
            {
                s32 *cmdTable = &gMainObjTimerCallback;
                sub_080C31E4((u8 *)behav + 0x18, (u8 *)behav + 0x22, *cmdTable);
            }
        }
        sub_0806D2F8(behav, target);
    }
}
