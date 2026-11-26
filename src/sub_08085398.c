/* Scene id at gMainWorkspace+0x14ED identifies the current room. */
struct SceneIdFF0 { u8 _[0x14ED]; u8 sceneId; };
extern struct SceneIdFF0 gMainWorkspace;

/* Per-run state: a counter, a base value used to derive entity stats, and the
 * current room-grid cell. */
struct RunState {
    u8 _0[0x2CC];
    s32 counter;
    u8 _1[0x2E0 - 0x2D0];
    u16 baseValue;
    u8 _2[0x304 - 0x2E2];
    u8 cellX;
    u8 cellY;
};
extern struct RunState gGameStatus;

extern void sub_0806D2A0(s32, s32, s32, s32);
extern s32 sub_0806D62C(s32, s32);
extern void sub_08086E28(void);
extern u8 D_080E47E8[];

/* Configures an entity on entering a room. Room 0x58 spawns an extra object,
 * scales its stats, adjusts the run counter from the room table and marks the
 * room visited; all other rooms only scale one stat. */
void sub_08085398(s32 spawnArg, u8 *entity) {
    struct RunState *run = &gGameStatus;

    if (gMainWorkspace.sceneId == 0x58) {
        sub_0806D2A0(spawnArg, 0x41, 0x0A, 0x12);
        *(u16 *)(((u32 *)(entity + 0x130))[0] + 0x0E) = sub_0806D62C(run->baseValue, 0x32);
        *(u16 *)(((u32 *)(entity + 0x130))[0] + 0x18) = 0x4F;
        {
            s32 *counterPtr = &run->counter;
            u8 *roomTable = D_080E47E8;
            s32 col = run->cellX - 1;
            s32 colBytes = col * 12;
            s32 row = run->cellY - 1;
            s32 offset = colBytes + row * 120;
            u8 *entries = roomTable + 4;
            *counterPtr -= *(s32 *)(entries + offset);
        }
        sub_08086E28();
    } else {
        *(u16 *)(((u32 *)(entity + 0x130))[0] + 0x0E) = sub_0806D62C(run->baseValue, 0x20);
    }
}
