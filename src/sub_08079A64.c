struct SceneState {
    u8 _0[0x10];
    u32 f10;
    u8 _14[0x14ED - 0x14];
    u8 f14ED;
    u8 _14EE[0x173A - 0x14EE];
    u8 f173A;
    u8 _173B[0x18C2 - 0x173B];
    u16 f18C2;
};
extern struct SceneState D_02025FF0;
extern void *D_08671BB0;
extern s32 sub_08003740(void *, void *);
extern void sub_08003A6C(void *, s32, s32);
extern void sub_0806D2F8(void *, void *);
extern s32 sub_0806D518(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, u32);

/* Advance a sub-object's animation counters and step timer, dispatch a script
 * step when the timer expires, then sync its sprite and check scene state to
 * decide whether to keep updating or call the entity's default callback. */
void sub_08079A64(u8 *entity) {
    u8 *obj = *(u8 **)(entity + 0x6C);
    u8 *state = obj + 4;
    u16 *sprite = *(u16 **)(entity + 0x38);
    s32 countdown;
    s32 counter;

    if (sub_0806D518(entity, sprite, state) == 0) {
        counter = *(s32 *)(state + 0xC) + 0x4000;
        *(s32 *)(state + 0xC) = counter;
        if (counter > 0x80000) *(s32 *)(state + 0xC) = 0x80000;
        *(s32 *)(obj + 4) = *(s32 *)(obj + 4) + *(s32 *)(state + 8);
        *(s32 *)(state + 4) = *(s32 *)(state + 4) + *(s32 *)(state + 0xC);
        countdown = *(s32 *)(state + 0x54) - 1;
        *(s32 *)(state + 0x54) = countdown;
        if (countdown == 0) {
            *(s32 *)(state + 0x54) = 0x80;
            (entity + *(s16 *)(entity + 0x22) * 2)[0x19] = (u8)countdown;
            { void **scriptCallbacks = &D_08671BB0; sub_080C31E4(entity + 0x18, entity + 0x22, (u32)*scriptCallbacks); }
        }
        {
            struct SceneState *scene = &D_02025FF0;
            u8 *obj20;
            *sprite = scene->f18C2;
            obj20 = obj + 0x20;
            if (sub_08003740(obj20, sprite) == 0)
                sub_08003A6C(obj20, 0, 0x084DE8A4);
            sub_0806D588(sprite, state);
            if (scene->f173A == 0x1C || (scene->f14ED == 0 && scene->f10 != 0)) {
                sub_080C31E0((s32)entity, *(s32 *)((u8 *)entity + 0x24));
                return;
            }
            sub_0806D2F8(entity, sprite);
        }
    }
}
