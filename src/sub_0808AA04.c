extern void sub_08003A6C(s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern s32 D_08671BB0[];

/* Spawns this effect entity: points its sprite at the animation data, installs
 * the spawn script with a zeroed initial position, then advances the step byte
 * and dispatches the first state callback. */
void sub_0808AA04(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *params = *(u8 **)(self + 0x6C);
    u8 *params2 = params + 4;
    *(s32 *)(*(u8 **)(self + 0x38) + 0x24) = 0x0850D3F8;
    sub_08003A6C((s32)(params + 0x20), 0, (s32)0x0850D630);
    *(s32 *)(params + 4) = 0;
    *(s32 *)(params2 + 4) = 0;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *scriptHandlers = D_08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    {
        u8 *stepBase = self + 0x18;
        s16 idx = *(s16 *)(self + 0x22);
        stepBase += idx * 2;
        sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *stepBase * 4));
    }
}
