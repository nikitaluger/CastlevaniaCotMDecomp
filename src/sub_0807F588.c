extern u8 D_084EBFC4[];
extern u32 gScriptStepCallbacks[];
extern void startEffectTimer(void *, s32, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

struct S_02025FF0 {
    u8 _0x000[0x14F4];
    u32 state1;
    u32 state2;
};
extern struct S_02025FF0 gMainWorkspace;

/* Script command: start the animation described by D_084EBFC4 on the subject,
 * clear two global game-state words, clear the current step's progress byte,
 * then advance the script with command 2. */
void sub_0807F588(void *self, void *subject) {
    u8 *actor = (u8 *)self;
    startEffectTimer((u8 *)subject + 0x1C, 0, D_084EBFC4);
    gMainWorkspace.state1 = 0;
    gMainWorkspace.state2 = 0;
    *(u8 *)(actor + (s32)*(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
    {
        u32 *scriptFnTable = gScriptStepCallbacks;
        sub_080C31E8(actor + 0x18, actor + 0x22, 2, *scriptFnTable);
    }
}
