struct In {
    u8 _0[0x146C];
    u16 c146C;
    u8 _1[2];
    u16 c1470;
};
struct St {
    u8 _0[0x48];
    u32 *p48;
    u8 _1[0x69 - 0x4C];
    u8 c69;
    s8 c6A;
    u8 c6B[1];
    u8 _2[0x6F - 0x6C];
    u8 c6F[1];
    u8 _3[0x73 - 0x70];
    u8 c73[1];
    u8 _4[0xF3 - 0x74];
    u8 cF3[1];
};
extern struct In gCameraState;
extern struct St gMenuState;
extern u32 gGameStatus[];
extern void *gScriptStepCallbackTable;
extern void *D_08671BC0;

void playSound(s32);
void sub_0800EDAC(s32);
void sub_0800EF3C(s32);
void sub_0800F124(u32);
void sub_0800F1D8(u32, u32);
void sub_0800F3C8(u32, u32);
void sub_0806D930(struct St *);
void sub_080C2E68(struct St *, u8 *, u32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, void *);

void sub_0800D860(u8 *a)
{
    u32 *tbl;
    struct St *g;
    s8 *p6A;
    s32 idx;
    u32 r;
    u32 r_1_;
    u32 r_1;
    u32 r_2;
    u32 r_3;
    u32 r_4;
    u16 v;
    s32 i;
    u32 t;
    u16 temp;
    u16 temp2;
    tbl = gGameStatus;
    g = &gMenuState;
    p6A = &g->c6A;
    idx = *p6A;

    r_1_ = 0x300 & gCameraState.c1470;
    v = 0x300;
    if (r_1_ == v) goto D9A4;
    if (r_1_ != 0) {
        sub_080C2E68(g, (u8 *)&tbl[0xB1], 0x48);
        sub_0806D930(g);
    }
    temp = gCameraState.c1470;
    r_1 = 0x200;
    r_1 &= temp;
    if (r_1 != 0) {
        s32 i_arm;
        *p6A = *p6A - 1;
        if ((s8)*p6A < 0) *p6A = 3;
        i_arm = *p6A;
        if (g->cF3[i_arm] == 0) *p6A = *p6A - 1;
        if ((s8)*p6A < 0) *p6A = 3;
    }
    temp2 = gCameraState.c1470;
    r_2 = 0x100;
    r_2 &= temp2;
    if (r_2 != 0) {
        *p6A = *p6A + 1;
        if ((s8)*p6A > 3) *p6A = 0;
        i = *p6A;
        if (g->cF3[i] == 0) *p6A = *p6A + 1;
        if ((s8)*p6A > 3) *p6A = 0;
    }
    r = 0x300;
    r &= gCameraState.c1470;
    if (r != 0) {
        u32 t_arm;
        playSound(0xA7 * 2);
        g->c69 = (g->c69 + 1) & 1;
        sub_0800F124((u8)*p6A);
        sub_0800F1D8((u8)*p6A, g->c69);
        sub_0800F3C8(g->c69, 0);
        sub_0800EDAC(0);
        i = *p6A;
        t_arm = (s8)g->c6B[i];
        t_arm = t_arm + (i << 5);
        sub_0800EF3C(*(u8 *)((u8 *)g + 0x73 + t_arm));
        return;
    }
D9A4:
    {
        u32 r_arm;
        u8 *q = &g->c6B[idx];
        s32 saved;
        saved = (s8)*q;
        r_arm = 0xC0;
        r_arm &= gCameraState.c1470;
        if (r_arm != 0xC0) {
            r_arm = 0x40;
            r_arm &= gCameraState.c1470;
            if (r_arm != 0) {
                if ((s8)*q > 1) *q = *q - 2;
            }
        }
        r_arm = 0x80;
        r_arm &= gCameraState.c1470;
        if (r_arm != 0) {
            s32 a1;
            u8 lim = g->cF3[idx];
            a1 = (s8)*q + 2;
            if (a1 < lim) *q = *q + 2;
            else if (lim & 1) *q = lim - 1;
        }
        r_arm = 0x30;
        r_arm &= gCameraState.c1470;
        if (r_arm != 0x30 && r_arm != 0) {
            u8 x;
            x = *q;
            *q = (x & 1) ? x - 1 : x + 1;
            if ((s8)*q == (s8)g->cF3[idx]) *q = *q - 1;
        }
        if (saved != (s8)*q) {
            playSound(0x139);
            sub_0800EDAC(0);
            sub_0800EF3C(g->c73[idx * 32 + (s8)*q]);
        }
        {
            u8 *rp = &g->c6F[idx];
            s32 dir;
            u32 dv;
            dir = 0;
            dv = *rp;
            if ((s8)*q < (s8)*rp) {
                dir = -1;
                dv = *rp - 2;
            } else {
                s32 df;
                df = (s8)*q - (s8)*rp;
                if (df > 7) {
                    dir = 1;
                    dv = *rp + 2;
                }
            }
            if (dir != 0) {
                *rp = dv;
                g->c69 = (g->c69 + 1) & 1;
                sub_0800F1D8((u8)g->c6A, g->c69);
                sub_0800F3C8(g->c69, 0);
            }
        }
    }
    v = gCameraState.c146C;
    r_3 = 2;
    r_3 &= v;
    t = (u16)r_3;
    if (t != 0) {
        void **pp;
        void *obj;
        pp = &g->p48;
        obj = *pp;
        playSound(0x14F);
        if (obj != 0) sub_080C31E0(obj, *(void **)((u8 *)obj + 0x24));
        *pp = NULL;
        sub_0800EDAC(1);
        sub_0800EF3C(0xFF);
        {
            u8 *d;
            d = a + ((s16)*(u16 *)(a + 0x22) << 1);
            d[0x19] = 0;
        }
        sub_080C31E4(a + 0x18, a + 0x22, *(void **)&D_08671BC0);
        return;
    }
    r_4 = 1;
    r_4 &= v;
    if (r_4 != 0) {
        u8 *d;
        d = a + ((s16)*(u16 *)(a + 0x22) << 1);
        d[0x19] = 0;
        sub_080C31E4(a + 0x18, a + 0x22, *(void **)&gScriptStepCallbackTable);
    }
}
