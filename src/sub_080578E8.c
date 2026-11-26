struct S_02025FF0 { u8 _0[0x18C2]; u16 baseAttr; };
extern struct S_02025FF0 gMainWorkspace;
extern s16 gPairedEffectKindTable[];
extern u16 D_080CFD40[];
typedef void (*UpdateFn)(void *);

void allocWorkSlot(void *, s32, s32, s32);
void *allocSpriteObject(void);
s32 findKindIndex(s16);
extern void sub_080579A8(void);

/* Allocates an entity's secondary effect object, fills in its sprite attributes
 * from the entity's element id, then installs and immediately runs its update
 * callback. On allocation or lookup failure it calls the entity's fail callback. */
void sub_080578E8(u8 *entity) {
    void *fx;
    s32 tableIdx;
    s16 elem;
    s16 idx;
    u32 idxU;
    u32 attr;
    u16 flags;
    allocWorkSlot(entity, 0, 0x14, 0);
    if (*(void **)(entity + 0x3C) == 0) {
        ((UpdateFn)*(void **)(entity + 0x24))(entity);
        return;
    }
    fx = allocSpriteObject();
    if (fx == 0) {
        ((UpdateFn)*(void **)(entity + 0x24))(entity);
        return;
    }
    *(void **)(entity + 0x38) = fx;
    elem = gPairedEffectKindTable[*(u8 *)(entity + 0x4C) * 2];
    tableIdx = findKindIndex(elem);
    idxU = ((u32)tableIdx << 16) >> 16;
    if (((s32)(tableIdx << 16)) < 0) {
        ((UpdateFn)*(void **)(entity + 0x24))(entity);
        return;
    }
    idx = (s16)idxU;
    attr = ((idx << 6) + 0x200) | ((idx + 8) << 12);
    *(u16 *)fx = attr;
    *(u16 *)fx = attr | gMainWorkspace.baseAttr;
    *(s32 *)((u8 *)fx + 0x24) = D_080CFD40[*(u8 *)(entity + 0x7C)] * 8 + 0x083C3B60;
    *(s32 *)((u8 *)fx + 0x1C) = 0x8000000A;
    flags = 0x800 | *(u16 *)(entity + 0x02);
    *(u16 *)(entity + 0x02) = flags;
    *(void **)(entity + 0x14) = (void *)sub_080579A8;
    *(u16 *)(entity + 0x22) = 1;
    ((UpdateFn)sub_080579A8)(entity);
}
