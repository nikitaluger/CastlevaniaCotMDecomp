extern s32 sub_08003740(void *, s32);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_08005E80(s32);
extern s32 sub_08007DD8(s32, s32);
extern void sub_0806D2F8(void *, s32);
extern s32 sub_0806D518(void *, s32, void *);
extern void sub_0806D588(s32, void *);
extern void sub_080719EC(void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gMainWorkspace[];

void sub_0806F78C(void *arg0v)
{
    u8 *arg0 = (u8 *)arg0v;
    s32 new_var2;
    u8 *P = *((u8 **)(arg0 + 0x6C));
    u8 *p4b = P + 4;
    s32 Q = *((s32 *)(arg0 + 0x38));
    u8 *p4 = p4b;
    u8 *p30;
    u8 *base;
    u8 *new_var;
    s32 has48;
    s32 rr2;
    u16 rr;
    s32 t;
    s32 hit;
    u32 off;

    if (sub_0806D518(arg0, Q, p4) != 0)
        return;
    sub_080719EC(arg0, p4, p4);
    has48 = *((s32 *)(p4 + 0x48));
    p30 = P + 0x30;
    new_var2 = 0xFFFA;
    if (has48 != 0) {
        s32 velocity;
        t = *((s32 *)(p4 + 0x0C));
        t += has48;
        *((s32 *)(p4 + 0x0C)) = t;
        if (t > 0x80000)
            *((s32 *)(p4 + 0x0C)) = 0x80000;
        velocity = *((s32 *)(p4 + 0x04));
        velocity += *((s32 *)(p4 + 0x0C));
        *((s32 *)(p4 + 0x04)) = velocity;
        off = 0x18A8;
        base = (u8 *)(off + ((u32)gMainWorkspace));
        hit = sub_08007DD8((s32)(((u8 *)0x02023130) + ((*base) << 6)), *((s32 *)(P + 4))) << 16;
        p30 = P + 0x30;
        if (hit != 0) {
            P = base;
            new_var = P;
            do {
                velocity = *((s32 *)(p4 + 0x04));
                velocity -= 0x10000;
                *((s32 *)(p4 + 0x04)) = velocity;
                rr = (u16)sub_08007DD8((s32)(((u8 *)0x02023130) + ((*new_var) << 6)), *((s32 *)(p4 + 0)));
            } while (rr != 0);
            *((s32 *)(p4b + 0x48)) = rr;
            *((s32 *)(p4 + 0x0C)) = rr;
        }
    }
    sub_0806D588(Q, p4);
    rr2 = sub_08003740(p30, Q);
    if (rr2 == 0) {
        void *res;
        void *res_b1;
        void *res_b2;
        void *res_b3;
        void **fp;
        s32 zero;
        sub_08003A6C(p30, 0, (void *)0x08472AD4);
        zero = 0;
        *((s32 *)(p4 + 0x10)) = 0x12C;
        res = *((void * volatile *)(p4b + 0x3C));
        *((s16 *)((u8 *)res + 0x6)) = 0xA | zero;
        res_b1 = *((void * volatile *)(p4b + 0x3C));
        *((s16 *)((u8 *)res_b1 + 0x8)) = 6;
        res_b2 = *((void * volatile *)(p4b + 0x3C));
        *((s16 *)((u8 *)res_b2 + 0xA)) = (s16)rr2;
        res_b3 = *((void * volatile *)(p4b + 0x3C));
        *((u16 *)((u8 *)res_b3 + 0xC)) = new_var2;
        *((u8 *)((arg0 + (2 * (*((s16 *)(arg0 + 0x22))))) + 0x19)) = (u8)zero;
        fp = (void **)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, (s32)(*fp));
    }
    t = (*((s32 *)(p4 + 0x14))) - 1;
    *((s32 *)(p4 + 0x14)) = t;
    if (t == 0) {
        sub_08005E80(0x96);
        *((s32 *)(p4 + 0x14)) = 0x0F;
    }
    sub_0806D2F8(arg0, Q);
}
