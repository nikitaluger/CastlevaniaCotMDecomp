extern void sub_080085D8(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u8 D_02025368[];
extern u8 D_02021E90[];
extern u16 D_080CA8D0[];
extern u32 D_0866CA7C[];
extern u32 D_08671BB0[];
extern u16 D_03000830[];

struct Pair { s32 v[2]; };

void sub_0800822C(u8 *self)
{
    u8 *base = D_02025368;
    u8 *obj = *(u8 **)(self + 0x3C);
    u16 *tbl;
    u8 *d;
    s32 count;

    count = *(s32 *)(obj + 0x00) + 1;
    *(s32 *)(obj + 0x00) = count;
    tbl = D_080CA8D0;

    if (tbl[*(s32 *)(obj + 0x04)] == count)
    {
        u32 *funcs = D_0866CA7C;
        u16 *p = tbl;
        while (p[*(s32 *)(obj + 0x04)] == *(s32 *)(obj + 0x00))
        {
            s32 i = *(s32 *)(obj + 0x04) + 1;
            *(s32 *)(obj + 0x04) = i;
            sub_080C31E0(obj, (void *)funcs[p[i]]);
        }
    }

    if (D_080CA8D0[*(s32 *)(obj + 0x04)] == 0)
        goto cleanup;

    {
        u8 v = base[0x0A];
        d = D_02021E90;
        if (v == 0
            || (*(u16 *)(d + 0x146C) & 8) == 0
            || *(s32 *)(obj + 0x14) + *(s32 *)(obj + 0x18) != 0x10)
            goto mode;
    }

cleanup:
    sub_080085D8(obj);
    *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
    {
        u32 *fn = D_08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, (void *)fn[0]);
    }
    return;

mode:
    if ((*(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) & 3) == 0)
    {
        switch (*(s32 *)(obj + 0x0C))
        {
        case 1:
        {
            ((struct Pair *)(obj + 0x14))->v[*(s32 *)(obj + 0x10)] += 1;
            ((struct Pair *)(obj + 0x14))->v[(*(s32 *)(obj + 0x10) + 1) & 1] -= 1;
            break;
        }
        case 2:
        {
            ((struct Pair *)(obj + 0x14))->v[*(s32 *)(obj + 0x10)] -= 1;
            break;
        }
        }
        if (*(s32 *)(obj + 0x0C) != 0)
        {
            s32 *arr = (s32 *)(obj + 0x14);
            u32 i;
            for (i = 0; i <= 1; i++)
            {
                s32 v = arr[i];
                if (v > 0x10)
                    arr[i] = 0x10;
                else if (v < 0)
                    arr[i] = 0;
            }
        }
    }

    D_03000830[3] = (u16)((*(s32 *)(obj + 0x18) << 8) | *(s32 *)(obj + 0x14));

    {
        s32 v = *(s32 *)(d + 0x127C) + *(s32 *)(obj + 0x08);
        *(s32 *)(d + 0x127C) = v;
        if (*(s32 *)(obj + 0x08) == 0 && v > 0x09000000)
            *(u16 *)(d + 0x1260) |= 0x2000;
    }
}
