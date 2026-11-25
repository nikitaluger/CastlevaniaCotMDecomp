extern s32 sub_080141AC(void *, void *);
extern s32 sub_08013558(void *, void *, void *);
extern void sub_080142FC(void *, void *);
extern void sub_08013CF4(void *, s32, s32);
extern void sub_08013EEC(void *);
extern s32 sub_08013B5C(void *, void *);
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_0803F24C(void *);
struct S28 { u8 a; u8 flag; u8 pad[0x12]; u16 flag2; };
extern u8 D_02021E90[];
extern u8 D_02025FF0[];

void sub_0803ECF0(void *arg0)
{
    void *p38; void *vAC; void *p3C; void *p34; void *p48;
    struct S28 *t;
    u8 *pt; u8 *pb; u32 idx; u8 *p1; u8 *p2;

    p38 = *(void **)((u8 *)arg0 + 0x38);
    vAC = *(void **)((u8 *)arg0 + 0xAC);
    p3C = *(void **)((u8 *)arg0 + 0x3C);
    p34 = (u8 *)p3C + 0x34;
    p48 = (u8 *)p3C + 0x48;

    if (sub_080141AC(p38, p3C) == 1) return;

    *(u16 *)((u8 *)p38 + 0) = (*(u16 *)((u8 *)p38 + 0) & 0xFFF) | ((*(u16 *)((u8 *)p3C + 0x22) + 8) << 12);

    if (*(u16 *)((u8 *)p3C + 0) & 1)
        (*(struct S28 **)((u8 *)p3C + 0x28))->flag = 0;
    else
        (*(struct S28 **)((u8 *)p3C + 0x28))->flag |= 5;

    if (sub_08013558(p38, p3C, *(void **)((u8 *)p3C + 0x28)) != 0) {
        if (*(u16 *)((u8 *)p3C + 0) & 0xC)
            *(u16 *)((u8 *)p3C + 0) = (0xFFF3 & *(u16 *)((u8 *)p3C + 0)) | 1;
    }

    sub_080142FC(arg0, *(void **)((u8 *)p3C + 0x28));

    if ((*(u16 *)((u8 *)p3C + 0) & 1) && ((u8*)((u8*)arg0 + *(s16*)((u8*)arg0+0x22)*2))[0x1A] != 5) {
        t = *(struct S28 **)((u8 *)p3C + 0x28);
        {
            s32 a = (*(s16 *)((u8 *)t + 0x30) << 16) + 0x8000;
            pt = D_02021E90; pb = D_02025FF0; pb += 0x18A8;
            idx = ((u32)*pb + 1) * 0x40;
            p1 = pt + 0x1278;
            a += *(s32 *)(p1 + idx);
            {
                s32 b = (*(s16 *)((u8 *)t + 0x32) << 16) + (s32)0xFFFF8000;
                p2 = pt + 0x127C;
                b += *(s32 *)(p2 + idx);
                sub_08013CF4(p3C, a, b);
            }
        }
        sub_08013EEC(p3C);
        {
            u32 zero = 0;
            *(u16 *)vAC |= 4;
            sub_0803F24C(arg0);
            *((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x1B) = zero;
            {
                s32 *p = (s32 *)0x08671BDC;
                sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 5, *p);
            }
        }
    }

    if (sub_08013B5C(p38, p3C) != 0) goto coord_end;
    *(u32 *)((u8 *)arg0 + 0x14) = 0x0866E060;
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
    {
        u8 *p = (u8 *)((s16)(*(u16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        p[0x19] = p[0x19] + 1;
    }
    {
        s32 idx2 = (s16)(*(u16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *q = (u8 *)arg0; u8 val;
        q += 0x18; q += idx2; val = *q;
        sub_080C31E0(arg0, *(s32 *)(*(u32 *)((u8 *)arg0 + 0x14) + (u32)(val * 4)));
    }
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
    if (*(u16 *)((u8 *)arg0 + 2) & 0x8000) return;
    sub_080113A8(p38, p34);
    sub_0801165C(p3C, 0);

coord_end:
    pt = D_02021E90; pb = D_02025FF0; pb += 0x18A8;
    idx = ((u32)*pb + 1) * 0x40;
    p1 = pt + 0x1278;
    *(u32 *)((u8 *)p38 + 0x14) = *(u32 *)((u8 *)p3C + 8) - ((*(s32 *)(p1 + idx) + 0x8000) & 0xFFFF0000);
    idx = ((u32)*pb + 1) * 0x40;
    p2 = pt + 0x127C;
    *(u32 *)((u8 *)p38 + 0x18) = (*(u32 *)((u8 *)p3C + 0xC) + *(u32 *)((u8 *)p48 + 8)) - ((*(s32 *)(p2 + idx) + 0xFFFF8000) & 0xFFFF0000);
}
