extern void sub_0802279C(void);
extern void sub_080161F0(void *);
extern void sub_080C31E0(void *, s32);
extern s32 sub_08014114(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_08020E78(void *arg0)
{
    void **p = (void **)(*(u8 **)((u8 *)arg0 + 0x3C) + 0x58);
    s32 i = 2;
    do
    {
        void *q = *p;
        if (q != 0)
        {
            *(u16 *)((u8 *)q + 0x6C) |= 2;
            *p = 0;
        }
        p++;
        i--;
    } while (i >= 0);
}

/* Tear down an object: run the global cleanup, free its optional sub-objects
 * (+0x28 and the two at +0x7C), then dispatch the callback at +0x24. */
void sub_08022760(void *obj)
{
    u8 *fields = *(u8 **)((u8 *)obj + 0x3C);
    void **slots;
    s32 remaining;

    sub_0802279C();
    if (*(void **)(fields + 0x28) != 0)
        sub_080161F0(*(void **)(fields + 0x28));

    slots = (void **)(fields + 0x7C);
    remaining = 1;
    do
    {
        if (*slots != 0)
            sub_080161F0(*slots);
        slots++;
        remaining--;
    } while (remaining >= 0);

    sub_080C31E0(obj, *(s32 *)(fields + 0x24));
}

void sub_08022DD4(void *arg0)
{
    u8 *r1 = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *r5 = r1 + 0x48;

    if (*(s16 *)(r5 + 0x0A) != 0)
    {
        if (sub_08014114(*(s32 *)(r1 + 8), *(s32 *)(r1 + 0x0C), -0x30, 0x30) != 0)
        {
            u8 *p = (u8 *)arg0;
            *(u16 *)(r5 + 0x0C) = 0;
            *(u8 *)(p + *(s16 *)(p + 0x22) * 2 + 0x19) = 0;
            {
                void **pp = (void **)0x08671BB0;
                sub_080C31E4(p + 0x18, p + 0x22, (s32)*pp);
            }
        }
    }
}

void sub_08022FBC(void *arg0)
{
    u8 *p = (u8 *)arg0;
    u8 *q = *(u8 **)(p + 0x3C) + 0x48;
    u8 zero = 0;

    *(u16 *)(q + 8) = 0x10;
    *(u16 *)(q + 0x0E) = 0x0A;
    *(u16 *)(q + 0x12) = 0x3C;
    *(u16 *)(q + 0x10) = 0;
    *(u8 *)(p + *(s16 *)(p + 0x22) * 2 + 0x19) = zero;
    {
        void **pp = (void **)0x08671BB0;
        sub_080C31E4(p + 0x18, p + 0x22, (s32)*pp);
    }
}
