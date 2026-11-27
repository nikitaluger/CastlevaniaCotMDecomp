/*
 * Actor script step: on the end code, clear the timer display, advance the
 * script and switch to its next state; otherwise load the timer display from a
 * lookup table indexed by the script byte.
 */
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);

extern u16 gCrossfadeGfxState[];
extern u8 D_080C98A6[];
extern u32 gScriptStepCallbackTable;

#define END_BYTE     0x0A
#define COUNT_START  0x10

void sub_08005C24(void *arg0) {
    s16 scriptIndex = *(s16 *)((u8 *)arg0 + 0x22);
    u8 *scriptEntry = (u8 *)((s32)(scriptIndex * 2) + (s32)arg0);
    u8 *scriptPtr;
    u32 *callbackTable;

    if (scriptEntry[0x19] == END_BYTE) {
        gCrossfadeGfxState[4] = 0;
        {
            s16 i = *(s16 *)((u8 *)arg0 + 0x22);
            *(u8 *)((u8 *)arg0 + i * 2 + 0x19) = 0;
        }
        callbackTable = &gScriptStepCallbackTable;
        scriptPtr = (u8 *)arg0 + 0x18;
        sub_080C31E4(scriptPtr, (u8 *)arg0 + 0x22, *callbackTable);
        {
            s16 i = *(s16 *)((u8 *)arg0 + 0x22);
            u8 *scriptBytePtr = (u8 *)((s32)(i * 2) + (s32)arg0);
            scriptBytePtr[0x19] = scriptBytePtr[0x19] + 1;
        }
        {
            s16 i = *(s16 *)((u8 *)arg0 + 0x22);
            u8 scriptByte;
            u32 *stateTable;
            scriptPtr += i * 2;
            scriptByte = scriptPtr[0];
            stateTable = *(u32 **)((u8 *)arg0 + 0x14);
            sub_080C31E0(arg0, stateTable[scriptByte]);
        }
    } else {
        volatile u16 *timerDisplay = gCrossfadeGfxState;
        u8 *lookupTable = D_080C98A6;
        u8 scriptValue = scriptEntry[0x19];
        s32 tableIndex = (s32)scriptValue - 1;
        u8 displayValue = lookupTable[tableIndex];
        timerDisplay[4] = (u16)(COUNT_START - displayValue);
    }
}
