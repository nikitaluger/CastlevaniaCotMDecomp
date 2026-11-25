struct EffectEntry { void *ptr; u8 rest[4]; };
struct EffectEntryTable { struct EffectEntry entries[0xDF]; };
extern struct EffectEntryTable D_080DEA88;
s32 sub_08003740(void *, void *);
void sub_08003A6C(void *, s32, void *);
void sub_0806AA64(void *, void *);
s32 sub_0806C4B4(void *, void *);
void sub_0806C5EC(void *, void *, void *, void *);
void sub_0806C6B0(void *, void *, void *, void *);
void *sub_0806D2A0(void *, s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Spawn a paired burst of objects around an entity using its component data,
   then reset the current script step and advance the command script. */
void sub_08066FE0(void *arg0)
{
    void *data;
    void *component;
    void *state;
    void *mainObj;
    void *scriptSteps;
    int zero;
    s32 delta;
    s32 offset;
    s32 count;

    component = *((void **)(((u8 *)arg0) + 0x6C));
    data = ((u8 *)component) + 4;
    mainObj = *((void **)(((u8 *)arg0) + 0x38));
    state = data;
    if (sub_0806C4B4(state, state) == 0) {
        sub_0806C5EC(arg0, mainObj, state, state);
        delta = (*((s32 *)(((u8 *)component) + 0x110))) - (*((s32 *)(((u8 *)state) + 4)));
        if (delta < 0) {
            delta += 0xF;
        }
        *((s32 *)(((u8 *)state) + 4)) = (*((s32 *)(((u8 *)state) + 4))) + (delta >> 4);
        sub_0806AA64(mainObj, state);
        component = ((u8 *)component) + 0x2C;
        if (sub_08003740(component, mainObj) == 0) {
            sub_08003A6C(component, 0, D_080DEA88.entries[0xDE].ptr);
            scriptSteps = ((u8 *)arg0) + 0x18;
            {
                void *scriptIndex = ((u8 *)arg0) + 0x22;
                offset = 0;
                zero = 0;
                count = 7;
                do {
                    void *spawned = sub_0806D2A0(arg0, 0x28, 0xA, 0x12);
                    if (spawned != 0) {
                        *((u32 *)(((u8 *)spawned) + 0x7C)) = (u32)offset;
                        *((u32 *)(((u8 *)spawned) + 0x8C)) = 0;
                    }
                    spawned = sub_0806D2A0(arg0, 0x28, 0xA, 0x12);
                    if (spawned != 0) {
                        *((u32 *)(((u8 *)spawned) + 0x7C)) = (u32)offset;
                        *((u32 *)(spawned + 0x8C)) = 2;
                    }
                    offset += 0x20;
                    count -= 1;
                } while (count >= 0);
                *((u8 *)(((2 * ((u32)((s16)(*((u16 *)(((u8 *)arg0) + 0x22)))))) + ((u32)arg0)) + 0x19)) = zero;
                {
                    void **litPtr = (void **)0x08671BB0;
                    sub_080C31E4(scriptSteps, scriptIndex, (s32)(*litPtr));
                }
            }
        }
        sub_0806C6B0(arg0, mainObj, data, state);
    }
}
