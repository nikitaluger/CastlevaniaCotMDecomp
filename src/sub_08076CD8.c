extern s32 checkGlobalStateChange(void *self, void *sprite, void *pos);
extern s32 sub_0806D6B4(void *pos);
extern void sub_0806D588(void *sprite, void *pos);
extern void *spawnEntity(s32 kind, s32 param1, s32 param2, s32 param3);
extern void cullOffscreenEntity(void *self, void *sprite);
extern s32 sub_080C31E0(void *self, void *handler);

struct GameState_76CD8 {
    u8 _pad0[0x10];
    u32 field10;
    u8 _pad1[0x14ED - 0x14];
    u8 byte14ED;
    u8 _pad2[0x173A - 0x14EE];
    u8 byte173A;
};
extern struct GameState_76CD8 gMainWorkspace;

/* Moving spawner: gate on global flags, slide its position with collision,
 * keep its sprite aligned, emit a child object every 5 ticks, then leave via
 * the state-change handler if room state or bounds say so. */
void sub_08076CD8(void *self) {
    void *mover;
    void *pos;
    void *sprite;
    u32 timer;
    void *spawned;
    struct GameState_76CD8 *gs;

    mover = *(void **)((u8 *)self + 0x6C);
    pos = (u8 *)mover + 4;
    sprite = *(void **)((u8 *)self + 0x38);

    if (checkGlobalStateChange(self, sprite, pos) != 0)
        goto end;
    if (sub_0806D6B4(pos) != 0)
        goto block_9;
    sub_0806D588(sprite, pos);
    timer = *(u32 *)((u8 *)pos + 0x54) - 1;
    *(u32 *)((u8 *)pos + 0x54) = timer;
    if (timer == 0) {
        spawned = spawnEntity(*(s32 *)((u8 *)self + 0x28), 0x3F, 0xA, 0x12);
        if (spawned != NULL) {
            *(u32 *)((u8 *)spawned + 0x7C) = *(u32 *)((u8 *)mover + 4);
            *(u32 *)((u8 *)spawned + 0x8C) = *(u32 *)((u8 *)pos + 4);
        }
        *(u32 *)((u8 *)pos + 0x54) = 5;
    }
    gs = &gMainWorkspace;
    if (gs->byte173A == 0x1C || (gs->byte14ED == 0 && gs->field10 != 0))
        goto block_9;
    goto block_5c;
block_9:
    sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
    goto end;
block_5c:
    cullOffscreenEntity(self, sprite);
end:
    ;
}
