extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08005E80(s32);
extern void spawnVariant2Effect(s32, s32, s32);

void sub_0804964C(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s16 idx;
    s32 off;
    u8 *base18;

    *(u32 *)(self + 0x14) = 0x0866E3A0;
    *(u16 *)(self + 0x22) += 1;

    idx = *(s16 *)(self + 0x22);
    *(u8 *)(self + idx * 2 + 0x19) += 1;

    idx = *(s16 *)(self + 0x22);
    off = idx * 2;
    base18 = self + 0x18;
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)(base18 + off) * 4));

    *(u16 *)(self + 0x22) -= 1;
}

void sub_08049692(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s16 idx;
    s32 off;
    u8 *base18;

    *(u32 *)(self + 0x14) = 0x0866E3B4;
    *(u16 *)(self + 0x22) += 1;

    idx = *(s16 *)(self + 0x22);
    *(u8 *)(self + idx * 2 + 0x19) += 1;

    idx = *(s16 *)(self + 0x22);
    off = idx * 2;
    base18 = self + 0x18;
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)(base18 + off) * 4));

    *(u16 *)(self + 0x22) -= 1;
}

/* Starts the animation in the object's current animation slot: sets up the
 * slot through the IWRAM helper, advances its frame counter and calls the
 * handler registered for the new frame. */
void sub_08049894(void *obj)
{
    void *started = obj + 0x6C;
    u8 zero = 0;
    void *slot;
    const u32 *frameRoutine;
    *(u8 *)started = 1;
    *(u8 *)(obj + (s32)*(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
    frameRoutine = (const u32 *)0x08671BB0;
    slot = obj + 0x18;
    sub_080C31E4(slot, obj + 0x22, *frameRoutine);
    *(u8 *)(obj + (s32)*(s16 *)(obj + 0x22) * 2 + 0x19) += 1;
    slot += (s32)*(s16 *)(obj + 0x22) * 2;
    sub_080C31E0(obj, *(u32 *)((u8 *)*(u32 *)((u8 *)obj + 0x14) + *(u8 *)slot * 4));
}

void sub_0804A070(void *arg0)
{
    u8 *r1;
    u8 v;
    s32 add;

    r1 = *(u8 **)((u8 *)arg0 + 0x3C);
    v = *(u8 *)(r1 + 0x48 + 0x0A);
    add = (-(s32)v | v) >> 31;
    add &= 0x100000;
    spawnVariant2Effect(*(s32 *)(r1 + 8), *(s32 *)(r1 + 0x0C) + add, 8);
    sub_08005E80(0x88);
    sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
