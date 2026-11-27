void stepAnimationTrack(void *actor, void *data);
s32 updateObjectDisplayState(void *actor, void *enemy);
void sub_080322B0(void *actor, void *enemy);
void sub_080C31E0(void *, s32); /* indirect-call thunk (bx r1) */
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

struct S28 { u8 a; u8 flag; };

/*
 * Entity AI/script update. Fetches the actor and enemy objects stored in self,
 * runs one script step (dispatching through the command table installed at
 * self+0x14), advances animation state, then positions the actor from the
 * enemy's coordinates minus the camera offset.
 */
void sub_08032180(void *self)
{
    void *actor;
    void *enemy;
    void *enemyData;
    struct S28 *animState;
    actor = *(void **)((u8 *)self + 0x38);
    enemy = *(void **)((u8 *)self + 0x3C);
    enemyData = (u8 *)enemy + 0x34;
    animState = *(struct S28 **)((u8 *)enemy + 0x28);
    animState->flag |= 1;
    if (updateObjectDisplayState(actor, enemy) == 0) {
        *(u32 *)((u8 *)self + 0x14) = 0x0866DCBC;
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
        {
            u8 *counter = (u8 *)((s16)(*(u16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
            counter[0x19] = counter[0x19] + 1;
        }
        {
            s32 scriptIndex = (s16)(*(u16 *)((u8 *)self + 0x22)) * 2;
            u8 *cmdPtr = (u8 *)self;
            u8 cmdId;
            cmdPtr += 0x18;
            cmdPtr += scriptIndex;
            cmdId = *cmdPtr;
            sub_080C31E0(self, *(s32 *)((u32)(cmdId * 4) + *(u32 *)((u8 *)self + 0x14)));
        }
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
        if (*(u16 *)((u8 *)self + 2) & 0x8000)
            return;
        stepAnimationTrack(actor, enemyData);
    }
    sub_080322B0(actor, enemy);
    *(u16 *)(*(u8 **)((u8 *)enemy + 0x28) + 0x14) = 0;
    {
        u8 *coordTable = gCameraState;
        u8 *camPtr = gMainWorkspace;
        u32 coordIndex;
        u8 *xTable;
        u8 *yTable;
        camPtr += 0x18A8;
        coordIndex = ((u32)*camPtr + 1) * 0x40;
        xTable = coordTable + 0x1278;
        *(u32 *)((u8 *)actor + 0x14) = *(u32 *)((u8 *)enemy + 8) - ((*(s32 *)(xTable + coordIndex) + 0x8000) & 0xFFFF0000);
        coordIndex = ((u32)*camPtr + 1) * 0x40;
        yTable = coordTable + 0x127C;
        *(u32 *)((u8 *)actor + 0x18) = *(u32 *)((u8 *)enemy + 0xC) - ((*(s32 *)(yTable + coordIndex) + 0xFFFF8000) & 0xFFFF0000);
    }
}
