extern void sub_08003A6C(s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern s32 gMainObjTimerCallback[];

/* Spawns this effect entity: points its sprite at the animation data, installs
 * the spawn script with the initial position (7.0, 8.0 in 16.16 fixed point),
 * then advances the step byte and dispatches the first state callback. */
void sub_08088A70(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *params = *(u8 **)(self + 0x6C);
    u8 *params2 = params + 4;
    *(s32 *)(*(u8 **)(self + 0x38) + 0x24) = 0x084FEB68;
    sub_08003A6C((s32)(params + 0x20), 0, (s32)0x084FEBF0);
    *(s32 *)(params + 4) = 0x00700000;
    *(s32 *)(params2 + 4) = 0x00800000;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *scriptHandlers = gMainObjTimerCallback;
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
