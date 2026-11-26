extern s32 sub_08005820(s32);
extern s32 sub_080133A4(s32, s32);
extern void sub_0805D92C(s32, s32, s32);
extern void sub_0805E6A8(s32, s32, u16, s16);
extern void sub_0805EBB8(s32, s32, u16);
extern s32 sub_080C364C(s32, s32);
extern u16 sub_080C3824(u16, s32);
extern u16 sub_080C389C(u16, s32);
extern u8 gMainWorkspace[];
struct Entry { u8 pad0[0x0C]; u16 unk0C; s16 unk0E; u16 unk10; s16 unk12; };
void sub_08013CF4(void *arg0, s32 arg1, s32 arg2)
{
    u8 * volatile sp0;
    struct Entry *tbl;
    void *r4;
    s32 r8;
    s32 r9;
    u16 r10v;
    u16 sp4v;
    u16 sp8v;
    u16 spCv;
    struct Entry *e0;
    struct Entry *e1;
    s32 g2f8;
    s32 v1, v2, rnd;
    s32 t0, t1;
    s32 tmp;
    int temp;

    r4 = arg0;
    r8 = arg1;
    r9 = arg2;
    sp0 = (u8 *)0x02025368;
    tbl = (struct Entry *)0x080CB2B8;

    e0 = &tbl[*(s16 *)((u8 *)r4 + 0x1C)];
    r10v = e0->unk0C;
    sp4v = e0->unk10;
    spCv = (u16)(*(s16 *)((u8 *)r4 + 0x22) * 2);
    sp8v = spCv;

    if (r10v == 0)
        return;

    if (sub_080133A4(r8, r9) == 1)
        return;

    e1 = &tbl[*(s16 *)((u8 *)r4 + 0x1C)];

    t0 = e1->unk0E;
    tmp = *(s16 *)(sp0 + 0x2F8);
    g2f8 = tmp - 100;
    v1 = sub_080C364C(t0 * g2f8, 200);
    v1 += t0;
    if (v1 > 0x1388)
        v1 = 0x1388;

    t1 = e1->unk12;
    v2 = sub_080C364C(t1 * g2f8, 200);
    v2 += t1;
    if (v2 > 0x9C4)
        v2 = 0x9C4;

    rnd = sub_08005820(0x2710);
    if (rnd < v1)
    {
        if (r10v <= 0x36)
        {
            sub_0805E6A8(r8, r9, r10v, (s16)spCv);
        }
        else
        {
            u16 t = r10v - 0x37;
            u16 a = sub_080C389C(t, 10);
            u16 b = sub_080C3824(t, 10);
            {
                u8 *bp = sp0;
                
                g2f8 = b * 10;
                temp = 0x30C + a;
                if (*(u8 *)((bp + temp) + g2f8) == 1 || *(s16 *)(bp + 0x8C) == 3)
                {
                    sub_0805D92C(r8, r9, 6);
                    r10v = 0x4B;
                }
                else
                {
                    sub_0805EBB8(r8, r9, t);
                }
            }
        }
        { u8 *g = gMainWorkspace; *(u16 *)(g + 0x1506) = r10v; }
    }
    else if (sp4v != 0)
    {
        if (rnd < v1 + v2)
        {
            if (sp4v <= 0x36)
            {
                s32 tmp4 = ((s32)sp8v << 16) | 0x10000;
                sub_0805E6A8(r8, r9, sp4v, (s16)(tmp4 >> 16));
            }
            else
            {
                u16 t = sp4v - 0x37;
                u16 a = sub_080C389C(t, 10);
                u16 b = sub_080C3824(t, 10);
                {
                    u8 *bp = sp0;
                    if (*(u8 *)((bp + b * 10) + (0x30C + a)) == 1 || *(s16 *)(bp + 0x8C) == 3)
                    {
                        sub_0805D92C(r8, r9, 6);
                        sp4v = 0x4B;
                    }
                    else
                    {
                        sub_0805EBB8(r8, r9, t);
                    }
                }
            }
            { u8 *g = gMainWorkspace; *(u16 *)(g + 0x1506) = sp4v; }
        }
    }
}
