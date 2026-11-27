extern void sub_080A3E8C(void *a, void *b, void *c, void *d);
extern void forceAnimationFrame(void *a, void *b, s16 c, s32 d);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern s16 D_08101C60[];

/* When a state reaches its final value, clear its value, launch the effect
 * listed for it in a table, play a sound, and end the state. */
void sub_080A3624(u8 *self) {
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 *entity = *(u8 **)(self + 0x3C);
    u8 *anim = entity + 0x34;
    u8 *state = entity + 0x48;
    sub_080A3E8C(gfx, anim, entity, state);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x78) {
        s32 zero = 0;
        s32 stateIndex;
        s16 effectId;
        *(s32 *)(state + 0x6C) = zero;
        {
            s16 *effectTable = D_08101C60;
            u32 off;
            stateIndex = *(s32 *)(entity + 0x48);
            off = (u32)stateIndex * 4;
            effectTable += 1;
            effectId = *(s16 *)((u8 *)((u32)off + (u32)effectTable));
            forceAnimationFrame(gfx, anim, effectId, 0);
            sub_08005E80(0x165);
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
            {
                s32 *cbTable = (s32 *)0x08671BB0;
                sub_080C31E4(self + 0x18, self + 0x22, *cbTable);
            }
        }
    }
}
