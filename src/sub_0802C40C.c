extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014EF4(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gScriptStepCallbacks;

/* Run one step of an object's behavior script: dispatch the current opcode,
 * and when its animation finishes pick a random horizontal direction and hand
 * the script state to the script-end handler. */
void sub_0802C40C(void *arg0)
{
    u8 *obj = (u8 *)arg0;
    void *sprite = *(void **)(obj + 0x38);
    u8 *host = *(u8 **)(obj + 0xAC);
    u8 *state = *(u8 **)(obj + 0x3C);
    u8 *anim = state + 0x34;
    s16 pc;

    setAnimationFrame(sprite, anim, 5, 0);
    *(u32 *)(state + 0x10) = 0;
    *(u32 *)(obj + 0x14) = 0x0866DB40;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;

    pc = *(s16 *)(obj + 0x22);
    obj[pc * 2 + 0x19]++;
    pc = *(s16 *)(obj + 0x22);
    {
        s32 pcOffset = pc * 2;
        u8 *script = obj;
        script += 0x18;
        script += pcOffset;
        sub_080C31E0(arg0, *(void **)((u8 *)*(void **)(obj + 0x14) + script[0] * 4));
    }

    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;

    if (anim[0] & 2) {
        if (!(*(u16 *)(*(u8 **)(host + 4) + 6) & 0x10)) {
            if (sub_08014EF4(0x1388) == 1)
                *(u32 *)(state + 0x10) = 0x4000;
            else
                *(u32 *)(state + 0x10) = 0xFFFFC000;
        }
        pc = *(s16 *)(obj + 0x22);
        obj[pc * 2 + 0x19] = 0;
        {
            void **jumpTable = &gScriptStepCallbacks;
            sub_080C31E8(obj + 0x18, obj + 0x22, 0, *jumpTable);
        }
    }
}
