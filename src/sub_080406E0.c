s32 sub_080141AC(void *, void *);
s32 sub_08016238(void *);
void sub_08005E80(s32);
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

extern u32 D_08671BB0;
extern u32 D_0866E0F0;

struct ObjFlag { u16 flag; };

/* Update an entity: when off-camera, dispatch its alternate command and stop;
   otherwise look for a target, spawn an effect when triggered, advance the
   command script when allowed, and copy state coordinates to the main object. */
void sub_080406E0(void *arg0) {
    void *mainObj;
    void *state;
    u8 *obj = (u8 *)arg0;

    mainObj = *(void **)(obj + 0x38);
    state = *(void **)(obj + 0x3C);

    if (sub_080141AC(mainObj, state) == 1) {
        sub_080C31E0((s32)arg0, *(s32 *)(obj + 0x24));
        return;
    }

    if (sub_08016238(*(void **)((u8 *)state + 0x28)) != 0) {
        ((struct ObjFlag *)state)->flag |= 1;
    }
    if (*(u16 *)(*(u8 **)((u8 *)state + 0x28) + 0x14) & 1) {
        ((struct ObjFlag *)state)->flag |= 1;
    }

    if (((struct ObjFlag *)state)->flag & 1) {
        u32 *litPtr;
        u8 *scriptBase;
        u8 cmd;
        s32 scriptOffset;
        sub_08005E80(0x189);
        {
            u8 *scriptStep;
            scriptStep = (u8 *)((u32)(*(s16 *)(obj + 0x22)) * 2 + (u32)obj);
            *(u8 *)(scriptStep + 0x19) = 0;
        }
        litPtr = &D_08671BB0;
        scriptBase = obj + 0x18;
        sub_080C31E4(scriptBase, obj + 0x22, *litPtr);
        {
            u8 *scriptStep;
            scriptStep = (u8 *)((u32)(*(s16 *)(obj + 0x22)) * 2 + (u32)obj);
            *(u8 *)(scriptStep + 0x19) = *(u8 *)(scriptStep + 0x19) + 1;
        }
        scriptOffset = (s32)(s16)(*(s16 *)(obj + 0x22)) * 2;
        scriptBase += scriptOffset;
        cmd = *scriptBase;
        sub_080C31E0((s32)arg0, *(s32 *)((u32)(cmd * 4) + *(u32 *)(obj + 0x14)));
        return;
    }

    if (sub_08013B5C(mainObj, state) == 0) {
        u8 *scriptBase;
        u8 cmd;
        s32 scriptOffset;
        *(u32 *)(obj + 0x14) = (u32)&D_0866E0F0;
        *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
        {
            u8 *scriptStep;
            scriptStep = (u8 *)((u32)(*(s16 *)(obj + 0x22)) * 2 + (u32)obj);
            *(u8 *)(scriptStep + 0x19) = *(u8 *)(scriptStep + 0x19) + 1;
        }
        scriptOffset = (s32)(s16)(*(s16 *)(obj + 0x22)) * 2;
        scriptBase = obj;
        scriptBase += 0x18;
        scriptBase += scriptOffset;
        cmd = *scriptBase;
        sub_080C31E0((s32)arg0, *(s32 *)((u32)(cmd * 4) + *(u32 *)(obj + 0x14)));
        *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
    }
    sub_08013C8C(arg0, mainObj);
}
