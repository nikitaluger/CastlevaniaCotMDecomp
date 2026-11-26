extern void sub_08005E80(s32);
extern void sub_0805D968(s32, s32, u16);
extern void _call_via_r1(void *, void *);

extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u16 D_080D003A[];
extern u8 D_080D0044[];

#define CALL968() { u8 *fb = gMainWorkspace; sub_0805D968(*(s32 *)(fb + 0x174C), *(s32 *)(fb + 0x1750), D_080D003A[*r6 - 1]); }

void sub_0805D770(void *arg0)
{
    u8 *g = gGameStatus;
    u16 *p = (u16 *)((u8 *)arg0 + 0x4C);
    u8 *r6;
    u8 v;

    if (p[4] <= 4)
    {
        r6 = g + 0x2D8;
        v = *r6;
        if (v)
        {
            if (*(s16 *)(g + 0x8C) == 1)
            {
                if (v == 1)
                {
                    if (p[4] == 2)
                        *(u8 *)(g + 0x2D9) = v;
                    else
                    {
                        *(u8 *)(g + 0x2D9) = 0;
                        CALL968();
                    }
                }
                else
                {
                    *(u8 *)(g + 0x2D9) = 0;
                    CALL968();
                }
            }
            else
                CALL968();
        }

        if (p[4] <= 4)
        {
            u8 t;
            sub_08005E80(0x77);
            t = D_080D0044[p[4]];
            *(u8 *)(g + 0x2D8) = t;
        }
    }

    if ((u16)(p[4] - 5) <= 1)
    {
        u16 v2;
        sub_08005E80(0x75);
        if (p[4] == 5)
        {
            (*(u16 *)(g + 0x2D4))++;
            {
                u8 *fb = gMainWorkspace;
                (*(u16 *)(fb + 0x1504))++;
            }
        }
        v2 = p[4];
        {
            u8 *fb = gMainWorkspace;
            if (v2 == 6)
            {
                *(u16 *)(g + 0x2D4) += 5;
                *(u16 *)(fb + 0x1504) += 5;
            }
            {
                u8 *fb2;
                __builtin_memcpy(&fb2, &fb, 4);
                if (*(u8 *)(fb2 + 0x14ED) == 0x26)
                {
                    if (p[4] == 5)
                    {
                        (*(u16 *)(g + 0x2D4))++;
                        (*(u16 *)(fb2 + 0x1504))++;
                    }
                    if (p[4] == 6)
                    {
                        *(u16 *)(g + 0x2D4) += 5;
                        (*(u16 *)(fb + 0x1504)) += 5;
                    }
                }
            }
        }
        {
            s16 a = *(s16 *)(g + 0x2D4);
            u16 b = *(u16 *)(g + 0x2D6);
            s16 c = *(s16 *)(g + 0x2D6);
            if (a > c)
                *(u16 *)(g + 0x2D4) = b;
        }
    }

    _call_via_r1(arg0, *(void **)((u8 *)arg0 + 0x24));
}
