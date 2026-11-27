/* Update a scripted attack: if its hit box has left the room, run the exit
 * script; otherwise handle a target hit, advance and dispatch one script
 * opcode, then re-anchor the attacker to the current room's coordinates. */
extern s32 sub_0805F9B4(s32, s32);
extern void sub_080113A8(void *, void *);
extern s32 hitTestEntities(void *);
extern void sub_08005E80(s32);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866F9A0[];
extern s32 sScriptStepCallbacks;

void sub_080912A0(u8 *script) {
    u8 *attacker;
    u8 *attack;
    u8 *attackData14;
    u8 *scriptPc;
    s16 scriptStep;
    s32 scriptIndex;
    u8 opcode;

    attacker = *(u8 **)(script + 0x38);
    attack = *(u8 **)(script + 0x3C);
    attackData14 = attack + 0x14;

    if (sub_0805F9B4(*(s32 *)(attack + 0x04), *(s32 *)(attack + 0x08)) == 1) {
        sub_080C31E0(script, *(s32 *)(script + 0x24));
        return;
    }

    scriptStep = *(s16 *)(script + 0x22);
    if (*(u8 *)(script + scriptStep * 2 + 0x1A) == 1) {
        scriptPc = script + 0x18;
    } else {
        scriptPc = script + 0x18;
        if (hitTestEntities(*(void **)(attack + 0x10)) != 0) {
            *(u8 *)(*(u8 **)(attack + 0x10) + 1) = 0;
            sub_08005E80(0x6E);
            *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x1B) = 0;
            {
                s32 *cmdTableAddr = &sScriptStepCallbacks;
                sub_080C31E8(scriptPc, script + 0x22, 1, *cmdTableAddr);
            }
        }
    }

    *(u32 *)(script + 0x14) = (u32)D_0866F9A0;
    *(s16 *)(script + 0x22) = *(s16 *)(script + 0x22) + 1;
    *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) = *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) + 1;
    scriptIndex = *(s16 *)(script + 0x22) * 2;
    opcode = *(u8 *)((u32)scriptPc + (u32)scriptIndex);
    sub_080C31E0(script, *(s32 *)(*(u32 *)(script + 0x14) + opcode * 4));
    *(s16 *)(script + 0x22) = *(s16 *)(script + 0x22) - 1;

    if (*(u16 *)(script + 2) & 0x8000)
        return;

    sub_080113A8(attacker, attackData14);

    {
        u8 *coordTable = gCameraState;
        u8 *roomIndexPtr = gMainWorkspace;
        u8 *coordXTable;
        u8 *coordYTable;
        u32 roomOffset;

        roomIndexPtr += 0x18A8;

        roomOffset = ((u32)*roomIndexPtr + 1) * 0x40;
        coordXTable = coordTable + 0x1278;
        *(u32 *)(attacker + 0x14) = *(u32 *)(attack + 0x04) - ((*(u32 *)(coordXTable + roomOffset) + 0x8000) & 0xFFFF0000);

        roomOffset = ((u32)*roomIndexPtr + 1) * 0x40;
        coordYTable = coordTable + 0x127C;
        *(u32 *)(attacker + 0x18) = *(u32 *)(attack + 0x08) - ((*(u32 *)(coordYTable + roomOffset) + 0xFFFF8000) & 0xFFFF0000);
    }
}
