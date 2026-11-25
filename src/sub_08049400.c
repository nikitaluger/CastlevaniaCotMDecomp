extern void sub_08011368(void *, s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_08005910(s32, s32);
extern void sub_08014668(void *, s32);
extern s16 D_080CF904[];

void sub_080492B8(void *arg0, void *arg1, s32 arg2)
{
    u8 *a0 = (u8 *)arg0;
    u8 *a1 = (u8 *)arg1;
    s32 tmp;
    s32 v;
    s32 r6;

    tmp = sub_08005910(*(s32 *)(a1 + 0x14), *(s32 *)(a1 + 0x10));
    r6 = tmp + 0x800;
    sub_08014668(arg0, *(s32 *)(a1 + 0x10));

    v = *(s32 *)(a1 + 0x14);
    if (v != 0) {
        if (v < 0) {
            *(u16 *)(a0 + 2) = 0x20 | *(u16 *)(a0 + 2);
        } else {
            *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) & 0xFFDF;
        }
    }

    sub_08011368(arg0, arg2, D_080CF904[(u32)(r6 & 0xF000) >> 12], 0);
}

void sub_08049360(void *arg0)
{
    void *r5;
    const u32 *lit;
    *(u8 *)(arg0 + 0x40) = 0;
    *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
    lit = (const u32 *)0x08671BB0;
    r5 = arg0 + 0x18;
    sub_080C31E4(r5, arg0 + 0x22, *lit);
    *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) += 1;
    r5 += (s32)*(s16 *)(arg0 + 0x22) * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)((u8 *)arg0 + 0x14) + *(u8 *)r5 * 4));
}

/* Starts the animation in the object's current animation slot: sets up the
 * slot through the IWRAM helper, advances its frame counter and calls the
 * handler registered for the new frame. */
void sub_08049400(void *obj)
{
    void *started = obj + 0x40;
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

void sub_0804964C(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s16 idx;

    *(u32 *)(self + 0x14) = 0x0866E3A0;
    *(u16 *)(self + 0x22) += 1;

    idx = *(s16 *)(self + 0x22);
    *(u8 *)(self + idx * 2 + 0x19) += 1;

    idx = *(s16 *)(self + 0x22);
    {
        u8 *base18 = self + 0x18;
        sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *(u8 *)(base18 + idx * 2) * 4));
    }

    *(u16 *)(self + 0x22) -= 1;
}
