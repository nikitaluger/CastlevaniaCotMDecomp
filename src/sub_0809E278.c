extern void sub_08011528(void *, void *);

struct WaveDeltas { u32 deltas[8]; };
extern struct WaveDeltas D_081019D4;
struct ScriptEntry { u16 a, b; };

/* Advance an animation script; when its value changes, step a fixed-point wave
 * and apply the same delta to two sound accumulators. */
void sub_0809E278(void *ctx, u8 *anim, u8 *soundA, u8 *soundB) {
    struct WaveDeltas wave;
    u32 *scriptTable;
    s32 scriptIndex;
    u16 scriptValue;

    wave = D_081019D4;
    sub_08011528(ctx, anim);
    scriptTable = *(u32 **)(anim + 0x08);
    scriptIndex = *(s16 *)(anim + 0x0E) + *(u8 *)(anim + 0x01);
    scriptValue = ((struct ScriptEntry *)((u8 *)*(u32 **)scriptTable + scriptIndex * 4 - 4))->b;
    if (scriptValue != *(u16 *)(soundB + 0x3E)) {
        *(u16 *)(soundB + 0x3E) = scriptValue;
        *(u32 *)(soundA + 0x0C) += wave.deltas[*(u8 *)(soundB + 0x3C) & 7];
        *(u32 *)(soundB + 0x38) += wave.deltas[*(u8 *)(soundB + 0x3C) & 7];
        *(u8 *)(soundB + 0x3C) = (*(u8 *)(soundB + 0x3C) + 1) & 7;
    }
}
