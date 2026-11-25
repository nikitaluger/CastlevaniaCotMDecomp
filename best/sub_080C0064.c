struct S2 {
    u8 f00; u8 _01[3];
    u32 f04;
    s8 f08; u8 f09; u8 _0A[6]; u8 f10; u8 f11; u8 _12[3];
    u8 f15; u8 _16[5]; u8 f1B; u8 f1C; u8 f1D; u16 f1E;
    void *f20; u8 f24; u8 _25[3]; void *f28; void *f2C; u8 _30[0x10]; u8 *f40;
};
struct B2 { u8 f0; u8 f1; u8 f2; u8 f3; u32 f4; u32 f8; };
struct Entry {
    u8 f00; u8 f01; s8 f02; s8 f03; u32 f04; u8 f08; u8 _09[3];
    u16 f0C; u8 _0E[2]; u32 f10; u8 _14[10]; u8 f1E; u8 f1F;
    u32 f20; u32 f24; u8 _28[4];
    struct S2 *f2C; struct Entry *f30; struct Entry *f34;
};
struct SP4 { u8 _0[6]; u8 f06; u8 _07[0x15]; void *f1C; u8 _20[0x10]; void *f30; u8 _34[0x1C]; struct Entry f50[1]; };
s32 sub_080C0010(s32, s32, u8, void *);
void sub_080C02B0(u8, void *);
s32 sub_080C0300(u32, s32, u8);
void sub_080C0744(void *);
void sub_080C0C30(void *, void *);
extern u8 D_0810C8AC[];

void sub_080C0064(void *arg0, void *arg1, void *arg2) {
    void *volatile sp0 = arg1;
    void *volatile sp4 = *(void **)0x03007FF0;
    volatile u32 sp8, spC, sp10;
    struct S2 *a2 = arg2;
    u8 *p;
    u32 b, flags, idx, v, mode, tmp, ret;
    u32 r3val;
    u32 minval, found;
    s32 i;
    struct B2 *r9, *work;
    struct Entry *ent, *bestEnt;
    struct S2 *best;
    s32 angle;
    u8 st;

    ((u8 *)&a2->f04)[0] = D_0810C8AC[(s32)arg0];
    p = a2->f40;
    b = (u32)p[0];
    if (0x80U <= b) goto no_parse;
    ((u8 *)&a2->f04)[1] = (u8)b;
    p++;
    b = (u32)p[0];
    if (0x80U <= b) goto store_p;
    ((u8 *)&a2->f04)[2] = (u8)b;
    p++;
    b = (u32)p[0];
    if (0x80U > b) {
        ((u8 *)&a2->f04)[0] = (u8)(((u8 *)&a2->f04)[0] + b);
        p++;
    }
store_p:
    a2->f40 = p;
no_parse:
    flags = (u32)*((u8 *)a2 + 0x24);
    if (0xC0u & flags) {
        idx = (u32)((u8 *)&a2->f04)[1];
        if (0x40u & flags) idx = (u32)*((u8 *)a2->f2C + idx);
        r9 = (struct B2 *)((u8 *)a2->f28 + idx * 12);
        if (0xC0u & (u32)r9->f0) goto end;
        if (0x80u & flags) {
            v = (u32)r9->f3;
            if (0x80u & v) {
                a2->f15 = (u8)((v - 0xC0) << 1);
                a2->f00 = (u8)(a2->f00 | 3);
            }
            r3val = (u32)r9->f1;
        } else {
            r3val = (u32)((u8 *)&a2->f04)[1];
        }
    } else {
        r9 = (struct B2 *)((u8 *)a2 + 0x24);
        r3val = (u32)((u8 *)&a2->f04)[1];
    }
    sp8 = r3val;
    sp10 = (u32)a2->f1D + (u32)((struct S2 *)sp0)->f09;
    if (sp10 > 0xFF) sp10 = 0xFF;
    mode = (u32)r9->f0 & 7u;
    spC = mode;
    if (mode != 0) {
        struct Entry *e;
        if (((struct SP4 *)sp4)->f1C == NULL) goto end;
        e = (struct Entry *)((u8 *)((struct SP4 *)sp4)->f1C + ((mode - 1) << 6));
        st = e->f00;
        if (!(0xC7u & (u32)st)) goto end;
        if (0x40u & (u32)st) goto end;
        if ((u32)((u8 *)&e->f10)[3] < sp10) goto alloc;
        if ((u32)((u8 *)&e->f10)[3] == sp10) {
            if ((u32)e->f2C < (u32)a2) goto alloc;
        }
        goto end;
    } else {
        minval = sp10;
        best = a2;
        found = 0;
        bestEnt = NULL;
        i = (s32)((struct SP4 *)sp4)->f06;
        ent = (struct Entry *)((u8 *)sp4 + 0x50);
        while (1) {
            st = ent->f00;
            if (0xC7u & (u32)st) {
                if (0x40u & (u32)st) {
                    if (found == 0) {
                        found = 1;
                        minval = (u32)((u8 *)&ent->f10)[3];
                        best = ent->f2C;
                        goto mark;
                    }
                    goto next;
                }
                if (found == 0) {
                    v = (u32)((u8 *)&ent->f10)[3];
                    if (v < minval) {
                        minval = v;
                        best = ent->f2C;
                        goto mark;
                    }
                    if (v == minval) {
                        if ((u32)ent->f2C > (u32)best) {
                            best = ent->f2C;
                            goto mark;
                        }
                        if ((u32)ent->f2C == (u32)best) {
mark:                           bestEnt = ent;
                        }
                    }
                }
next:
                ent = (struct Entry *)((u8 *)ent + 0x40);
                i--;
                if (i > 0) continue;
                ent = bestEnt;
                if (ent == NULL) goto end;
                goto alloc;
            }
            goto alloc;
        }
    }
alloc:
    sub_080C0744(ent);
    ent->f30 = NULL;
    ent->f34 = a2->f20;
    if (ent->f34 != NULL) ent->f34->f30 = ent;
    a2->f20 = ent;
    ent->f2C = a2;
    a2->f1C = a2->f1B;
    if (a2->f1B != 0) sub_080C02B0(a2->f1B, a2);
    sub_080C0C30(sp0, a2);
    ent->f10 = a2->f04;
    ((u8 *)&ent->f10)[3] = (u8)sp10;
    ent->f08 = (u8)sp8;
    ent->f01 = r9->f0;
    tmp = r9->f8;
    ent->f04 = tmp;
    tmp = r9->f4;
    ent->f24 = tmp;
    ent->f0C = a2->f1E;
    ent->f02 = (s8)(((s32)(u8)((u8 *)&ent->f10)[2] * (s32)(u8)a2->f10) >> 7);
    ent->f03 = (s8)(((s32)(u8)((u8 *)&ent->f10)[2] * (s32)(u8)a2->f11) >> 7);
    angle = (s32)(u8)ent->f08 + (s32)(s8)a2->f08;
    angle = (angle < 0) ? 0 : angle;
    if (spC != 0) {
        u8 v2;
        ent->f1E = r9->f2;
        v2 = r9->f3;
        if ((0x80u & (u32)v2) || !(0x70u & (u32)v2)) v2 = 8;
        ent->f1F = v2;
        ret = (u32)sub_080C0010((s32)spC, angle, a2->f09, ((struct SP4 *)sp4)->f30);
    } else {
        ret = (u32)sub_080C0300(r9->f4, angle, a2->f09);
    }
    ent->f20 = ret;
    ent->f00 = 0x80;
    a2->f00 = (u8)(a2->f00 & 0xF0);
end:
    ;
}
