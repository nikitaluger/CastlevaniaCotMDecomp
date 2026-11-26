extern u8 gCameraState[];
extern u8 gMainWorkspace[];

s32 sub_0805F9B4(s32 a, s32 b);
void sub_08005E80(u16 arg0);
void _call_via_r1(void *a, u32 b);
void _call_via_r3(void *a, void *b, s32 c, u32 d);
void sub_080119B4(void *a, s32 b, s32 c, s32 d, s32 e);

static inline u8 andBF(u8 b)
{
    u32 m = 0xBF;
    m &= b;
    return (u8)m;
}

static inline u8 or40(u8 b)
{
    u32 m = 0x40;
    m |= b;
    return (u8)m;
}

void sub_0808F2C0(void *arg0)
{
    void *v10;
    void *v8;
    void *v6;
    u8 *v7;
    u8 *r9_var;
    s32 cond;
    u8 *p;
    u8 *r2;
    s16 idx;
    u8 val;
    s16 idx2;
    u8 zero;
    u16 tmp;
  u16 tmp_web;
    u32 *tbl;
    u32 func;
    s16 idx3;
    u8 b;
    
    u8 *q;
    
    u8 *q2;
    u16 valE;
    u8 *pt;
    u8 *pt1;
    u8 *pb;
    u32 idx4;
    u32 v1;
    u32 v2v;
    u32 mask32;
    u32 *g1;

    v10 = *(void**)(arg0 + 0x38);
    v8 = *(void**)(arg0 + 0xAC);
    v6 = *(void**)(arg0 + 0x3C);
    v7 = (u8*)v6 + 0x34;

    cond = sub_0805F9B4(*(s32*)(v6 + 8), *(s32*)(v6 + 0x0C));
    if (cond == 1) {
        p = *(u8**)(v7 + 8);
        { u8 *__fence_p; do { __fence_p = p; } while (0); __fence_p[1] = 0; }
        r2 = (u8*)v10 + 0x2A;
        *r2 = andBF(*r2);
    } else {
        p = *(u8**)(v7 + 8);
        p[1] = 1;
        r2 = (u8*)v10 + 0x2A;
        *r2 = or40(*r2);

        idx = *(s16*)(arg0 + 0x22);
        val = ((u8*)arg0)[idx * 2 + 0x1A];
        r9_var = (u8*)arg0 + 0x18;

        if (val != 1) {
            if (*(s32*)(v7 + 0x0C) == 1) {
                do { tmp = *(u16*)v8; } while (0);
                zero = 0;
                *(u16*)v8 = tmp | 4;
                sub_08005E80(0x70);
                idx2 = *(s16*)(arg0 + 0x22);
                ((u8*)arg0)[idx2 * 2 + 0x1B] = zero;
                g1 = (u32*)0x08671BDC;
                _call_via_r3(r9_var, (u8*)arg0 + 0x22, 1, *g1);
            }
        }

        *(u32*)(arg0 + 0x14) = 0x0866F914;
        (*(u16*)(arg0 + 0x22))++;
        idx3 = *(s16*)(arg0 + 0x22);
        (idx3 * 2 + (u8*)arg0)[0x19] = (idx3 * 2 + (u8*)arg0)[0x19] + 1;
        b = r9_var[*(s16*)(arg0 + 0x22) * 2];
        tbl = *(u32**)(arg0 + 0x14);
        func = tbl[b];
        _call_via_r1(arg0, func);
        (*(u16*)(arg0 + 0x22))--;

        tmp = *(u16*)(arg0 + 0x02);
        if (!(tmp & 0x8000)) {
            do { do { do { tmp = *(u16*)(v6 + 0x02); } while (0); } while (0); } while (0);
            if (!(tmp & 4)) {
                sub_080119B4(v6, 0x16C1, 0x001F0000, 0x00100000, 0x000F0000);
            }
            do { q = *(u8**)(v7 + 4); } while (0);
            tmp_web = *(u16*)(v6 + 0x0A);
            *(u16*)(q + 4) = tmp_web;
            q2 = *(u8**)(v7 + 4);
            valE = *(u16*)(v6 + 0x0E);
            valE = valE - 0x0F;
            *(u16*)(q2 + 6) = valE;

            mask32 = 0xFFFF0000;
            pt = gCameraState;
            pb = gMainWorkspace;
            pb += 0x18A8;
            idx4 = ((u32)*pb + 1) * 0x40;
            pt1 = pt + 0x1278;
            v1 = *(u32 *)(pt1 + idx4);
            *(u32 *)((u8 *)v10 + 0x14) = *(u32 *)(v6 + 8) - ((v1 + 0x8000) & mask32);
            idx4 = ((u32)*pb + 1) * 0x40;
            pt += 0x127C;
            v2v = *(u32 *)(pt + idx4);
            *(u32 *)((u8 *)v10 + 0x18) = *(u32 *)(v6 + 0x0C) - ((v2v + 0xFFFF8000) & mask32);
        }
    }
}
