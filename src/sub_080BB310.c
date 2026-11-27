extern s32 sub_08005E80(s32);
extern s32 advanceMotion(void *, s32);
extern s32 sub_08014848(s32, s32, s32, s32, s32, s32);
extern s32 sub_080BB8C0(void *, void *);
extern s32 sub_080BB900(void *, void *);
extern s32 sub_080BBB60(void *);
extern s32 sub_080BE8B8(s32);
extern s32 sub_080BE8C0(s32);

/* Advances an actor's horizontal velocity from its control direction, handles
 * a direction reversal (sound + effect + contact update), and finishes the
 * script step when its counter reaches 0x5A. */
void sub_080BB310(void *arg0) {
    s32 oldVelocity;
    s8 direction;
    s8 dir;
    void *componentData;
    void *component;
    void *control;

    component = *((void **)((s8 *)arg0 + 0x3C));
    componentData = (void *)((s8 *)component + 0x48);
    control = *((void **)((s8 *)arg0 + 0x4C));
    sub_080BBB60(component);
    oldVelocity = *((s32 *)((s8 *)component + 0x10));
    *((s32 *)((s8 *)component + 0x10)) = (s32)(oldVelocity + (*((s8 *)((s8 *)control + 0x35)) * 0x2800));
    advanceMotion(component, 0);
    direction = *((s8 *)((s8 *)control + 0x35));
    if (((direction == -1) && (*((s32 *)((s8 *)component + 0x10)) < 0)) || ((direction == 1) && (*((s32 *)((s8 *)component + 0x10)) > 0))) {
        if (((oldVelocity < 0) && (*((s32 *)((s8 *)component + 0x10)) > 0)) || ((oldVelocity > 0) && (*((s32 *)((s8 *)component + 0x10)) < 0))) {
            sub_08005E80(0x1AE);
            sub_080BE8B8(*((s32 *)((s8 *)componentData + 0x34)));
            sub_080BB8C0(component, componentData);
        }
        if (!(3 & *((u8 *)((s8 *)arg0 + (*((s16 *)((s8 *)arg0 + 0x22)) * 2) + 0x19)))) {
            dir = *((s8 *)((s8 *)control + 0x35));
            sub_08014848(1, 3, *((s32 *)((s8 *)component + 0x08)) + (dir * 0x90000), *((s32 *)((s8 *)component + 0x0C)) - (dir * 0x30000), 0xC0000, 0x2E0000);
        }
    }
    if (*((u8 *)((s8 *)arg0 + (*((s16 *)((s8 *)arg0 + 0x22)) * 2) + 0x19)) == 0x5A) {
        sub_080BE8C0(*((s32 *)((s8 *)componentData + 0x34)));
        sub_080BB900(component, componentData);
        *((s8 *)((s8 *)arg0 + (*((s16 *)((s8 *)arg0 + 0x22)) * 2) + 0x19)) = 0;
        ((void (*)(void *, void *))(*(u32 *)0x08671BB0))((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22);
    }
}
