/* identical to sub_0801CCE4 (matched), with its names changed by decompdecomp */
extern s32 sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 D_08671BFC;
extern u32 gMainObjTimerCallback;
extern u32 D_08671BDC;
struct S_02025FF0_CC { u8 _0[0x18A8]; u8 f18A8; };
extern struct S_02025FF0_CC gMainWorkspace;
struct S_02021E90_CC { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90_CC gCameraState;

/* When flag 8 is set, update the companion sprite's position from the script
 * parameters, apply the camera-relative correction, and end the script step. */
void sub_08019540(u8 *obj)
{
    u32 zero;
    u8 *sprite;
    u8 *scriptState;
    u8 *control;
    u8 *params;
    u8 *coordTable;
    s32 result;
    u8 *stepCounterPtr;
    u8 *stepFlagPtr;
    u8 *scriptPtr;
    u8 *stepIndexPtr;
    u32 *handlerTablePtr;
    u32 *paramTablePtr;

    sprite = *(u8 **)(obj + 0x38);
    scriptState = *(u8 **)(obj + 0x3C);
    control = scriptState + 0x48;
    if (*(u16 *)(obj + 0x64) & 8) {
        paramTablePtr = &D_08671BFC;
        result = sub_080C31E0((void *)((u32) * (u16 *)(*(u8 **)(control + 0x10) + 4)), (void *)*paramTablePtr);
        params = *(u8 **)(control + 0x10);
        *(s32 *)(scriptState + 8) = *(s32 *)(scriptState + 0x48) + *(s16 *)(params + 6) * result;
        *(s32 *)(scriptState + 0x0C) = *(s32 *)(control + 4) + (*(s16 *)(params + 2) << 16);
        *(u32 *)(control + 0x0C) = *(u16 *)(params + 4);
        coordTable = (u8 *)&gCameraState;
        { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = *(u32 *)(scriptState + 8) - ((*(u32 *)(coordTable + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
        { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = *(u32 *)(scriptState + 0x0C) - ((*(u32 *)(coordTable + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
        stepCounterPtr = (u8 *)(*(s16 *)(obj + 0x22) * 2 + (u32)obj);
        zero = 0;
        stepCounterPtr[0x19] = (u8)zero;
        handlerTablePtr = &gMainObjTimerCallback;
        scriptPtr = obj + 0x18;
        stepIndexPtr = obj + 0x22;
        sub_080C31E4(scriptPtr, stepIndexPtr, (s32)*handlerTablePtr);
        stepFlagPtr = (u8 *)(*(s16 *)(obj + 0x22) * 2 + (u32)obj);
        stepFlagPtr[0x1B] = (u8)zero;
        sub_080C31E8(scriptPtr, stepIndexPtr, 0, (s32)D_08671BDC);
    }
}
