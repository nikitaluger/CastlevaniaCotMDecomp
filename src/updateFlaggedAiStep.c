extern s32 isGameStatusFlagSet(u16);
extern void sub_08011344(u32, u32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s16 D_081003E4[];
extern u32 gScriptStepCallbacks;

struct S_Obj { u8 _0[0x14]; u32 f14; u8 _1[0x22-0x18]; s16 f22; u8 _2[0x38-0x24]; u32 f38; u32 f3C; };
struct S_Params { s32 f00; u32 f04; u8 _p[0x1c-8]; u32 f1c; u32 f20; };
struct S_Sub { u8 _0[0x19]; u8 f19; };

void updateFlaggedAiStep(struct S_Obj *obj)
{
    u32 animChannel;
    struct S_Params *params;
    u32 animInfo;
    s32 r6;

    animChannel = obj->f38;
    params = (struct S_Params *)obj->f3C;
    animInfo = 0x20 + (u32)params;
    r6 = isGameStatusFlagSet(*(u16 *)(*(u32 *)((u8 *)params + 0x1c) + 2));
    if (r6 != 0) {
        u8 *stepData; u8 *cursor; u8 step; u32 callback; u32 *cmdTable;
        s16 *actionTable; u32 tableOff; u32 zero; u32 v; u8 *p;
        actionTable = D_081003E4;
        tableOff = params->f00 * 4;
        actionTable += 1;
        sub_08011344(animChannel, animInfo, *(s16 *)((u8 *)actionTable + tableOff), 0);
        p = (u8 *)(*(volatile u32 *)((u8 *)params + 4));
        zero = 0;
        *(s16 *)(p + 6) = 10;
        *(s16 *)(*(volatile u32 *)((u8 *)params + 4) + 8) = 6;
        *(s16 *)(*(volatile u32 *)((u8 *)params + 4) + 10) = 4;
        p = (u8 *)(*(volatile u32 *)((u8 *)params + 4));
        v = 0xFFFA;
        *(u16 *)(p + 12) = v;
        ((struct S_Sub *)((u8 *)obj + obj->f22 * 2))->f19 = zero;
        cmdTable = &gScriptStepCallbacks;
        stepData = (u8 *)obj + 0x18;
        sub_080C31E8(stepData, (u8 *)obj + 0x22, 4, *cmdTable);
        ((struct S_Sub *)((u8 *)obj + obj->f22 * 2))->f19++;
        cursor = stepData + obj->f22 * 2;
        step = *cursor;
        callback = *(u32 *)((u8 *)obj->f14 + step * 4);
        sub_080C31E0(obj, callback);
    } else {
        u8 *stepData; u8 *cursor; u8 step; u32 callback; u32 *cmdTable;
        s16 *actionTable; u32 tableOff; u32 zero; u32 v; u8 *p;
        actionTable = D_081003E4;
        tableOff = params->f00 * 4;
        sub_08011344(animChannel, animInfo, *(s16 *)((u8 *)actionTable + tableOff), 0);
        p = (u8 *)(*(volatile u32 *)((u8 *)params + 4));
        zero = 0;
        *(s16 *)(p + 6) = 4;
        *(s16 *)(*(volatile u32 *)((u8 *)params + 4) + 8) = 10;
        *(s16 *)(*(volatile u32 *)((u8 *)params + 4) + 10) = (s16)r6;
        p = (u8 *)(*(volatile u32 *)((u8 *)params + 4));
        v = 0xFFF6;
        *(u16 *)(p + 12) = v;
        ((struct S_Sub *)((u8 *)obj + obj->f22 * 2))->f19 = zero;
        cmdTable = &gScriptStepCallbacks;
        stepData = (u8 *)obj + 0x18;
        sub_080C31E8(stepData, (u8 *)obj + 0x22, 1, *cmdTable);
        ((struct S_Sub *)((u8 *)obj + obj->f22 * 2))->f19++;
        cursor = stepData + obj->f22 * 2;
        step = *cursor;
        callback = *(u32 *)((u8 *)obj->f14 + step * 4);
        sub_080C31E0(obj, callback);
    }
}
