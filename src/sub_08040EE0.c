s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 sub_08013B5C(void *, void *);
void sub_08013C5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080141AC(void *, void *);
void sub_080142C0(void *, void *);
void sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

/* Update an entity: refresh flags and visibility, handle target contact and hit
   effects, run a one-off script step when triggered, then advance the command
   script and copy state coordinates to the main object. */
void sub_08040EE0(void *obj) {
    void *mainObj;
    void *state;
    u8 *scriptStep;
    u8 cmd;
    u32 cmdTable;
    s32 cmdFunc;
    s32 scriptOffset;
    u16 dirFlag;

    mainObj = *(void **)((u8 *)obj + 0x38);
    state = *(void **)((u8 *)obj + 0x3C);
    sub_08013C5C(obj, mainObj);
    *(u32 *)((u8 *)obj + 0x4C) = *(u32 *)((u8 *)state + 8);
    *(u32 *)((u8 *)obj + 0x5C) = *(u32 *)((u8 *)state + 0x0C);
    dirFlag = 0x10 & *(u16 *)((u8 *)mainObj + 2);
    if (dirFlag != 0) {
        *(u8 *)((u8 *)obj + 0x6C) = 1;
    } else {
        *(u8 *)((u8 *)obj + 0x6C) = (s8)dirFlag;
    }
    if (sub_080141AC(mainObj, state) == 1) {
        return;
    }
    if (sub_08013558(mainObj, state, *(void **)((u8 *)state + 0x28)) != 0)
        sub_08013978(obj, *(void **)((u8 *)state + 0x28));
    sub_080142C0(obj, *(void **)((u8 *)state + 0x28));
    if (*(u16 *)state & 1) {
        if (*(u8 *)(2 * (u32)(s16)*(u16 *)((u8 *)obj + 0x22) + (u32)obj + 0x1A) != 7) {
            sub_08013AC4(obj);
            *(u8 *)(2 * (u32)(s16)*(u16 *)((u8 *)obj + 0x22) + (u32)obj + 0x1B) = 0;
            {
                u32 *litPtr = (u32 *)0x08671BDC;
                sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 7, *litPtr);
            }
        }
    }
    if (sub_08013B5C(mainObj, state) == 0) {
        *(u32 *)((u8 *)obj + 0x14) = 0x0866E114;
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) + 1;
        scriptStep = (u8 *)(2 * (u32)(s16)*(u16 *)((u8 *)obj + 0x22) + (u32)obj);
        *(u8 *)(scriptStep + 0x19) = *(u8 *)(scriptStep + 0x19) + 1;
        scriptOffset = (s32)(s16)*(u16 *)((u8 *)obj + 0x22) * 2;
        {
            u8 *scriptBase = (u8 *)obj;
            scriptBase += 0x18;
            scriptBase += scriptOffset;
            cmd = *scriptBase;
        }
        cmdTable = *(u32 *)((u8 *)obj + 0x14);
        cmdFunc = *(s32 *)((u32)(cmd * 4) + cmdTable);
        sub_080C31E0((s32)obj, cmdFunc);
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) - 1;
    }
    sub_08013C8C(obj, mainObj);
}
