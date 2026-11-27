void startEffectTimer(void *, s32, u32);
void *sub_0806D2A0(void *, s32, s32, s32);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

struct ResourceEntry { u32 first; u32 second; };
extern struct ResourceEntry D_080DEA88[];
struct GameStateFlags { u8 _0[0x24]; u32 useAlt; u8 _1[2]; volatile u16 flags; };
extern struct GameStateFlags gMainWorkspace;
struct AltGameStateFlags { u8 _pad[0x146E]; volatile u16 flags; };
extern struct AltGameStateFlags gCameraState;

/* Runs one step of an actor's behaviour script: triggers its attached effect,
 * follows scroll-direction flags on its parent, then dispatches the next opcode. */
void sub_0806697C(u8 *arg0) {
    u8 *state;
    u8 *parent;
    void *spawned;

    state = *(u8 **)(arg0 + 0x6C);
    parent = *(u8 **)(arg0 + 0x38);

    startEffectTimer(state + 0x2C, 0, D_080DEA88[0xD9].first);
    spawned = sub_0806D2A0(arg0, 0x27, 0x0A, 0x12);
    if (spawned != 0) {
        *(u32 *)((u8 *)spawned + 0x7C) = *(u32 *)(state + 0xBC);
    }

    if ((gMainWorkspace.useAlt != 0 ? gMainWorkspace.flags : gCameraState.flags) & 0x10) {
        if (*(u16 *)(parent + 2) & 0x10)
            *(u16 *)(parent + 2) &= 0xFFEF;
    }

    if ((gMainWorkspace.useAlt != 0 ? gMainWorkspace.flags : gCameraState.flags) & 0x20) {
        if ((*(u16 *)(parent + 2) & 0x10) == 0)
            *(u16 *)(parent + 2) |= 0x10;
    }

    {
        u8 *scriptPtr;
        u8 opcode;
        s32 pcOffset;
        u32 *callTarget;
        *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) = 0;
        callTarget = (u32 *)0x08671BB0;
        scriptPtr = arg0 + 0x18;
        sub_080C31E4(scriptPtr, arg0 + 0x22, *callTarget);
        {
            u8 *stepPtr;
            stepPtr = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(stepPtr + 0x19) = *(u8 *)(stepPtr + 0x19) + 1;
        }
        pcOffset = (s32)(s16)(*(s16 *)(arg0 + 0x22)) * 2;
        scriptPtr += pcOffset;
        opcode = *scriptPtr;
        sub_080C31E0((s32)arg0, *(s32 *)((u32)(opcode * 4) + *(u32 *)(arg0 + 0x14)));
    }
}
