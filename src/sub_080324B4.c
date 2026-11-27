extern void sub_08013C5C(void *, void *);
extern void sub_080141AC(void *, void *);
extern s32 sub_08013558(void *, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_080142C0(void *, void *);
extern void sub_08013AC4(void *);
extern void sub_08014414(void *);
extern s32 updateObjectDisplayState(void *, void *);
extern void sub_08013C8C(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Update an entity: refresh its main-object flags and camera visibility, handle
   contact with the target (spawning hit effects), then advance its command
   script when allowed and copy the state's world coordinates back. */
void sub_080324B4(void *arg0) {
    u8 *mainObj = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *state = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *obj = (u8 *)arg0;

    sub_08013C5C(arg0, mainObj);
    sub_080141AC(mainObj, state);
    if (sub_08013558(mainObj, state, *(void **)(state + 0x28)) != 0) {
        sub_08013978(arg0, *(void **)(state + 0x28));
    }
    sub_080142C0(arg0, *(void **)(state + 0x28));

    if (*(u16 *)state & 1) {
        sub_08013AC4(obj);
        if (*(u8 **)(obj + 0x30) != 0) {
            (*(u8 **)(obj + 0x30))[0x7C] = 1;
        }
        sub_08014414(obj);
        {
            s32 scriptOffset;
            u8 *scriptBase;
            s32 *litPtr;
            u8 cmd;

            scriptOffset = *(s16 *)(obj + 0x22) * 2;
            *(u8 *)((u32)scriptOffset + (u32)obj + 0x19) = 0;
            litPtr = (s32 *)0x08671BB0;
            scriptBase = obj;
            scriptBase += 0x18;
            sub_080C31E4(scriptBase, obj + 0x22, *litPtr);
            scriptOffset = *(s16 *)(obj + 0x22) * 2;
            *(u8 *)((u32)scriptOffset + (u32)obj + 0x19) = *(u8 *)((u32)scriptOffset + (u32)obj + 0x19) + 1;
            scriptOffset = *(s16 *)(obj + 0x22) * 2;
            scriptBase += scriptOffset;
            cmd = *(u8 *)scriptBase;
            sub_080C31E0(obj, *(void **)(cmd * 4 + *(u32 *)(obj + 0x14)));
        }
        return;
    }

    if (updateObjectDisplayState(mainObj, state) == 0) {
        s32 scriptOffset;
        u8 *scriptBase;
        u8 cmd;
        *(u32 *)(obj + 0x14) = 0x0866DCCC;
        *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
        scriptOffset = *(s16 *)(obj + 0x22) * 2;
        *(u8 *)((u32)scriptOffset + (u32)obj + 0x19) = *(u8 *)((u32)scriptOffset + (u32)obj + 0x19) + 1;
        scriptOffset = *(s16 *)(obj + 0x22) * 2;
        scriptBase = obj;
        scriptBase += 0x18;
        scriptBase += scriptOffset;
        cmd = *(u8 *)scriptBase;
        sub_080C31E0(obj, *(void **)(cmd * 4 + *(u32 *)(obj + 0x14)));
        *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
    }
    sub_08013C8C(obj, mainObj);
}
