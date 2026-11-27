extern void sub_08051F40(void *, s32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 randomSignedOffset(s32);
extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);
void *spawnBudgetedEffect(u32, s32);
struct S_02025FF0_187C { u8 _p[0x187C]; u32 v; };
extern struct S_02025FF0_187C gMainWorkspace;

void sub_08051F98(void *arg0, void *arg1, s32 arg2, s16 arg3, s32 arg4) {
    u8 *p = (u8 *)arg1;
    s32 zero = 0;
    s32 v5 = 0;
    p[4] = 0;
    p[5] = (u8)arg2;
    p[6] = (u8)arg4;
    *(s16 *)(p + 2) = arg3;
    sub_08051F40(arg1, arg2);
    *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) = 0;
    {
        u32 *lit = (u32 *)0x08671BD0;
        sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 5, *lit);
    }
}

void sub_0805C268(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *p38 = *(void **)(self + 0x38);
    u8 *r6 = *(u8 **)(self + 0x3C);
    u8 *r5 = r6 + 0x48;
    setAnimationFrame(p38, r6 + 0x34, 0, 1);
    if (sub_08014A04(r6, *(s32 *)(r5 + 8), *(s32 *)(r5 + 0xC), 0x80000, 0x80000) == 1) {
        s32 v = randomSignedOffset(0x200000);
        *(s32 *)(r5 + 8) = *(s32 *)(r6 + 0x48) + v;
        *(s32 *)(r5 + 0xC) = *(s32 *)(r5 + 4) + randomSignedOffset(0x200000);
    }
    sub_08014B1C(r6, r6 + 0x58, *(s32 *)(r5 + 8), *(s32 *)(r5 + 0xC));
}

/* Spawn an entity of type 0x1E9 and initialise its two variant words (+0x4C,
 * +0x54) plus the +0x5C flag. Returns the new entity, or NULL on failure. */
void *sub_0805F104(u16 variantA, u16 variantB) {
    void *obj;
    obj = spawnBudgetedEffect(gMainWorkspace.v, 0x1E9);
    if (obj == NULL) return NULL;
    *(u16 *)((u8 *)obj + 0x4C) = variantA;
    *(u16 *)((u8 *)obj + 0x54) = variantB;
    *(u16 *)((u8 *)obj + 0x5C) = 1;
    return obj;
}

s32 sub_08060370(void) {
    u8 *base = (u8 *)0x02021E90;
    *(u32 *)(base + 0x1454) += 1;
    {
        u8 t = *(u8 *)(base + 0x145C);
        t |= 4;
        *(u8 *)(base + 0x145C) = t;
        if (t & 2) {
            *(u8 *)(base + 0x145C) = t & 0xFD;
            *(u8 *)(base + 0x143C) = *(u8 *)(base + 0x1444);
        }
    }
    return 0;
}
