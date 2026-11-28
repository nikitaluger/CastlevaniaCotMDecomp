struct Ws874 {
    u8 _0[0x174C];
    s32 field;
};
extern struct Ws874 D_02025FF0;
extern s32 sub_08014090(u16);
extern void *spawnBudgetedEffect(s32, s32);
extern u32 nextRandomWord(void);
extern u32 scaleByRandom(u32);

void sub_0803C874(u8 *actor)
{
    u8 __repair_narrow_0;
    u8 *ref;
    u8 *p;
u8 *__repair_phase_p;
    s32 a;
    s32 diff;
    s32 sum;
    s32 i;
    u8 *node;
    u8 *flagPtr;
    s32 t;
    void *obj;
    s32 g;
s32 __repair_phase_g;
    s32 lo;
    s32 hi;
    
s32 __repair_phase_d;
    s32 r3;
    s32 x;
s32 __repair_phase_x;
    s32 y;
s32 __repair_phase_y;
    s32 z;
    s32 choice;

    i = 0;
    do { ref = *(u8 **)(actor + 0xAC); } while (0);
    if (sub_08014090(0x2D) != 0)
        return;
    p = *(u8 **)(ref + 4);
    a = (s32)*(s16 *)(p + 0);
    diff = (a << 16) - (((s32)*(u16 *)(p + 6)) << 16);
    sum = (a << 16) + (((s32)*(u16 *)(p + 6)) << 16);

    g = D_02025FF0.field;
    if (g <= diff) {
        *(u8 *)(actor + 0x3C) = 1;
        return;
    }
    if (g >= sum) {
        *(u8 *)(actor + 0x3C) = 1;
        return;
    }

    do { do { do { node = *(u8 **)(actor + 0x30); } while (0); } while (0);
    if (node != NULL) {
        do {
            i++;
            node = *(u8 **)(node + 0x2C);
        } while (node != NULL);
    }
    if (i > 2)
        return;

    do { do { flagPtr = actor + 0x3C; } while (0); } while (0);
    t = *flagPtr - 1;
    *flagPtr = t;
    if ((s8)t != 0)
        return;

    *flagPtr = 0x5A; } while (0);
    obj = spawnBudgetedEffect((s32)actor, 0xFC);
    if (obj == NULL)
        return;

    __repair_phase_g = D_02025FF0.field;
    lo = __repair_phase_g - 0x680000;
    if (lo < diff)
        lo = diff;
    hi = __repair_phase_g + 0x680000;
    if (hi > sum)
        hi = sum;

    r3 = 0;
    a = __repair_phase_g - lo;
    if (a > 0x3FFFFF) {
        __repair_phase_d = hi - __repair_phase_g;
        if (__repair_phase_d > 0x3FFFFF) {
            r3 = (s32)(nextRandomWord() & 1);
            if (r3 == 0) {
                r3 = 1;
                r3 = -r3;
            }
        } else {
            r3 = 1;
        }
    } else {
        r3 = 1;
    }

    if (r3 != 1)
        goto path_b;

    x = hi - __repair_phase_g - 0x400000;
    y = (s32)scaleByRandom((u32)x);
    *(s32 *)((u8 *)obj + 0x4C) = y + __repair_phase_g + 0x400000;
    goto common;

path_b:
    __repair_phase_x = lo - 0x400000 + __repair_phase_g;
    __repair_phase_y = (s32)scaleByRandom((u32)__repair_phase_x);
    z = __repair_phase_g - __repair_phase_y - 0x400000;
    *(s32 *)((u8 *)obj + 0x4C) = z;

common:
    __repair_phase_p = *(u8 **)(ref + 4);
    choice = (*(u16 *)(__repair_phase_p + 2)) | 7;
    *(s32 *)((u8 *)obj + 0x5C) = choice << 16;
}
