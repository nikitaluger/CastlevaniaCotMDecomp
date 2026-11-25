extern s32 sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern void sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 D_02025FF0;

void sub_0808A744(u8 *arg0) {
    u8 *newobj;
    u8 *base18;

    if (sub_0800168C(arg0, 0, 0x3C, 3) == 0 || (newobj = sub_0800355C()) == NULL) {
        sub_080C31E0((s32)arg0, *(s32 *)(arg0 + 0x24));
        return;
    }

    *(u8 **)(arg0 + 0x38) = newobj;
    *(s32 *)(newobj + 0x1C) = (s32)0x80000006;
    {
        u32 z = 0;
        u16 w = D_02025FF0.w;
        *(u16 *)(newobj + 0) = w;
        {
            u16 h = 0x800;
            *(u16 *)(newobj + 4) = h;
            *(u16 *)(newobj + 6) = h;
        }
        *(u16 *)(newobj + 8) = 0;
        *(u16 *)(newobj + 2) = *(u16 *)(newobj + 2) | 0x10;
        {
            s32 idx = *(s16 *)(arg0 + 0x22);
            *(u8 *)(arg0 + idx * 2 + 0x19) = (u8)z;
        }
    }
    {
        s32 *nv = (s32 *)0x08671BB0;
        base18 = arg0 + 0x18;
        sub_080C31E4(base18, arg0 + 0x22, *nv);
    }
    {
        u8 *p = (u8 *)((u32)(*(s16 *)(arg0 + 0x22) * 2) + (u32)arg0);
        *(u8 *)(p + 0x19) = *(u8 *)(p + 0x19) + 1;
    }
    base18 += *(s16 *)(arg0 + 0x22) * 2;
    sub_080C31E0((s32)arg0, *(s32 *)(*(u32 *)(arg0 + 0x14) + *(u8 *)base18 * 4));
}
