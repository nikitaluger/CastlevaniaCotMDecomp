struct S_02025FF0 { u8 _[0x18C2]; u16 w; };
extern struct S_02025FF0 D_02025FF0;
s32 sub_0800168C(void *, s32, s32, s32);
void *sub_0800355C(void);
void sub_0806D2D0(void *);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
void sub_08075DA4(void *arg0) {
    void *temp;
    u8 zero;
    u16 mv;
    if (sub_0800168C(arg0, 0, 0x68, 3) == 0) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    temp = sub_0800355C();
    if (temp == NULL) {
        sub_0806D2D0(arg0);
        return;
    }
    *(void **)((u8 *)arg0 + 0x38) = temp;
    *(s32 *)((u8 *)temp + 0x1C) = 0x80000005;
    mv = (u16)((*(u16 *)((u8 *)*(void **)((u8 *)*(void **)((u8 *)arg0 + 0x28) + 0x38) + 2) & 0x10) | *(u16 *)((u8 *)temp + 2));
    zero = 0;
    *(u16 *)((u8 *)temp + 2) = mv;
    *(u16 *)temp = D_02025FF0.w;
    *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
    {
        s32 *nv = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *nv);
    }
    {
        u8 *p2 = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        p2[0x19] = (u8)(p2[0x19] + 1);
    }
    {
        s32 idx2 = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *base = (u8 *)arg0 + 0x18;
        u8 b = *(base + idx2);
        u8 **tbl = *(u8 **)((u8 *)arg0 + 0x14);
        sub_080C31E0(arg0, (s32)tbl[b]);
    }
}
