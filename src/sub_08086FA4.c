extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);

/* Low part of the main game state: current scene index and the scene's data
 * pointers/cursors. */
struct S_02025FF0_Low {
    u8 _pad[0x10];
    u32 sceneIndex;
    u32 sceneCursor;
    u32 sceneData;
    u32 sceneEnd;
};
extern struct S_02025FF0_Low gMainWorkspace;
extern s32 D_0866F534[]; /* per-scene data block pointers */
extern void *gMainObjTimerCallback;

/* Script step: switch to the data block of the current scene, reset the scene
 * cursors and the actor's position, then advance the entity's script and tail
 * dispatch the handler for the new step. */
void sub_08086FA4(u8 *arg0) {
    u8 *actor = *(u8 **)(arg0 + 0x6C);
    u32 off, off2;
    u8 opcode;
    u8 *base18;

    gMainWorkspace.sceneCursor = 0;
    gMainWorkspace.sceneEnd = 0;
    gMainWorkspace.sceneData = D_0866F534[gMainWorkspace.sceneIndex - 1];
    *(u32 *)(actor + 4) = 0;

    off = *(s16 *)(arg0 + 0x22);
    off <<= 1;
    off += (u32)arg0;
    *(u8 *)(off + 0x19) = 0;

    {
        void **fnaddr = &gMainObjTimerCallback;
        base18 = arg0 + 0x18;
        sub_080C31E4(base18, arg0 + 0x22, *fnaddr);
    }

    off2 = *(s16 *)(arg0 + 0x22);
    off2 <<= 1;
    off2 += (u32)arg0;
    opcode = *(u8 *)(off2 + 0x19);
    *(u8 *)(off2 + 0x19) = opcode + 1;

    off = *(s16 *)(arg0 + 0x22);
    base18 = base18 + off * 2;
    opcode = *base18;
    sub_080C31E0(arg0, *(void **)(*(u8 **)(arg0 + 0x14) + opcode * 4));
}
