extern void sub_080C31E0(void *a, void *b);

struct SceneState {
    u8 pad0[0x14EC];
    u8 sceneFlag;
    u8 pad1[0x1780 - 0x14ED];
    u32 objects[1];
};
extern struct SceneState gMainWorkspace;

/* Release the entity's slot in the scene object table: clear the shared scene
 * flag when it is still set (the transition is over), then run the entity's
 * current handler. */
void sub_0807192C(void *arg0)
{
    u8 *obj = (u8 *)arg0;
    u8 *sub = *(u8 **)(obj + 0x6C) + 4;

    if (gMainWorkspace.sceneFlag == 1)
        gMainWorkspace.sceneFlag = 0;

    *(&gMainWorkspace.objects[*(s32 *)(obj + 0xAC)]) = 0;
    sub_080C31E0(arg0, *(void **)(sub + 0x18));
}
