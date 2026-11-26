extern void sub_080C31E4(void *, void *, s32);
extern u32 D_08102064[];
extern s32 gMainObjTimerCallback;

struct EffectState {
    u8 pad[0xEE];
    u8 selector;
    u8 pad2[0x39];
    s32 sequence;
    s32 counter;
};

/* Cycle the effect's selector byte: every 6 frames advance the sequence index
 * through the 4-entry ping-pong table (0,1,2,1) and copy its value into the
 * state; when the script step reads 0x48, reset it and advance the script. */
void sub_080A76E8(void *entity) {
    struct EffectState *state = *(struct EffectState **)((u8 *)entity + 0x3C);
    s32 ticks;

    ticks = ++state->counter;
    if (ticks == 6) {
        s32 index;
        state->counter = 0;
        index = ++state->sequence;
        if (index == 4) {
            state->sequence = 0;
        }
        state->selector = (u8)D_08102064[state->sequence];
    }
    if (*(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) == 0x48) {
        s32 *scriptTable;
        *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
        scriptTable = &gMainObjTimerCallback;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptTable);
    }
}
