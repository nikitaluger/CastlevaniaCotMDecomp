extern void *sub_0800355C(void);
extern s32 sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern void sub_080141F8(void *, void *, void *, void *, s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_08016664(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08014290(void);

extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_080CD400[];
extern u8 D_080CF564[];
extern u8 D_080CF554[];
extern u32 D_08671BB0[];

/* Extra data record allocated for the entity. */
struct Extra {
    u8 _0; u8 kind; u8 state; u8 subState;
    u16 gfxIdx; u16 param6; u16 param8; u16 paramA; u16 paramC; u16 paramE;
    u32 gfxObj;
};
/* Animation/actor record held at self+0x3C. */
struct Anim {
    u8 _0[8];
    u32 x; u32 y;
    u8 _10[0x0C];
    s16 animIndex;
    u8 _1E[0x0A];
    struct Extra *extra;
};
struct Entry { u8 _0[4]; void *info; };
struct GfxDef { u16 f0; u16 f2; u16 f4; u8 _6[0x0E]; };
extern struct GfxDef D_080CB2B8[];
struct ObjFlags { u8 pad[2]; u16 flags; };

/* Creates and initialises a child entity: allocates its graphics and
 * animation records, wires up animation data and an extra data record,
 * places it in the world and advances its initial state callback. */
void sub_08043B0C(u8 *self) {
    u8 *gfxObj;
    struct Anim *anim;
    u8 *animData;
    struct Extra *extra;
    void *entry;
    s32 zero;
    u8 *stackTable;
    u8 *paramTable;
    u8 *pt, *pb, *base1, *base2;
    u32 idx;

    entry = *(void **)(self + 0xAC);
    gfxObj = sub_0800355C();
    if (gfxObj == NULL) goto fail;
    *(void **)(self + 0x38) = gfxObj;
    sub_0800168C(self, 0, 0x4C, 0);
    if (*(u32 *)(self + 0x3C) == 0) goto fail;
    *(u32 *)(gfxObj + 0x1C) = 0x8000000A;
    anim = *(struct Anim **)(self + 0x3C);
    animData = (u8 *)anim + 0x34;
    sub_08014288(self, (u8 *)anim, (void *)sub_08014290);
    stackTable = D_080CF564;
    {
        s32 stacked = *(s16 *)(stackTable + *(u8 *)(self + 0x4C) * 4);
        sub_080141F8(self, gfxObj, (u8 *)anim, entry, stacked);
    }
    sub_0801131C(gfxObj, animData, (s32)D_080CD400 + *(s16 *)((u8 *)anim + 0x1C) * 0xC);
    sub_08011368(gfxObj, animData, 0, 0);
    if (*(u16 *)((u8 *)((struct Entry *)entry)->info + 6) == 0) {
        *(u16 *)(gfxObj + 2) &= 0xFFEF;
    } else {
        ((struct ObjFlags *)gfxObj)->flags |= 0x10;
    }
    paramTable = D_080CF554;
    extra = sub_08016190();
    anim->extra = extra;
    if (extra == NULL) goto fail;
    goto body;

fail:
    sub_080C31E0(self, *(void **)(self + 0x24));
    return;

body:
    extra->kind = 5;
    anim->extra->state = 8;
    anim->extra->subState = 1;
    {
        zero = 0;
        anim->extra->gfxIdx = D_080CB2B8[*(s16 *)((u8 *)anim + 0x1C)].f0;
        anim->extra->param6 = *(u16 *)(paramTable + 0);
        anim->extra->param8 = *(u16 *)(paramTable + 2);
        anim->extra->paramA = *(u16 *)(paramTable + 4);
        anim->extra->paramC = *(u16 *)(paramTable + 6);
        anim->extra->paramE = D_080CB2B8[*(s16 *)((u8 *)anim + 0x1C)].f4;
    }
    anim->extra->gfxObj = (u32)gfxObj;
    {
        pt = D_02021E90;
        pb = D_02025FF0;
        pb += 0x18A8;
        idx = ((u32)*pb + 1) * 0x40;
        base1 = pt + 0x1278;
        *(u32 *)(gfxObj + 0x14) = *(u32 *)((u8 *)anim + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
        idx = ((u32)*pb + 1) * 0x40;
        base2 = pt + 0x127C;
        *(u32 *)(gfxObj + 0x18) = *(u32 *)((u8 *)anim + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
    sub_08016664(self, 0);
    {
        u16 h = *(u16 *)(self + 2);
        h |= 0x1000;
        *(u16 *)(self + 2) = h;
    }
    *(u8 *)((u32)(*(s16 *)(self + 0x22) * 2) + (u32)self + 0x19) = (u8)zero;
    {
        u32 *wp = (u32 *)D_08671BB0;
        u8 *slots = self + 0x18;
        sub_080C31E4(slots, self + 0x22, *wp);
        {
            u8 *statePtr = (u8 *)((u32)(*(s16 *)(self + 0x22) * 2) + (u32)self + 0x19);
            *statePtr = (u8)(*statePtr + 1);
            statePtr = slots;
            statePtr += *(s16 *)(self + 0x22) * 2;
            {
                u8 stateIndex = *statePtr;
                void *nextFn = ((void **)*(void **)(self + 0x14))[stateIndex];
                sub_080C31E0(self, nextFn);
            }
        }
    }
}
