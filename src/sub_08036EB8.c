extern void sub_08011344(s32, void *, s32, s32);
extern void sub_08014668(s32, s32);
extern void sub_0803B0D0(void *);
extern void sub_0803B0D8(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Sets up a movement and animation from the entity's data block, updates the
 * facing flag, then dispatches the entity's current script step and its
 * indexed action callback. */
void sub_08036EB8(void *arg0) {
    u8 *self;
    u8 *data;
    u8 *anim;
    s32 param;
    u8 *motion;
    u8 *scriptArgs;
    s32 zero;
    s32 *scriptTable;
    self = (u8 *)arg0;
    param = *(s32 *)(self + 0x38);
    data = *(u8 **)(self + 0x3C);
    anim = data + 0x34;
    motion = data + 0x48;
    sub_0803B0D0(motion);
    zero = 0;
    *(u8 *)(motion + 0x18) = zero;
    sub_0803B0D8(data, motion, 0x4000);
    *(s32 *)(data + 0x10) = *(s32 *)(data + 0x48);
    sub_08011344(param, anim, 0, 1);
    sub_08014668(param, *(s32 *)(data + 0x10));
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    scriptTable = (s32 *)0x08671BB0;
    scriptArgs = self + 0x18;
    sub_080C31E4(scriptArgs, self + 0x22, *scriptTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    scriptArgs += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(arg0, *(s32 *)(*(s32 *)(self + 0x14) + *(u8 *)scriptArgs * 4));
}
