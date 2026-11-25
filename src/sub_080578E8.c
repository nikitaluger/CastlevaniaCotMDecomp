struct S_02025FF0 { u8 _0[0x18C2]; u16 baseAttr; };
extern struct S_02025FF0 D_02025FF0;
extern s16 D_080CFC98[];
extern u16 D_080CFD40[];
typedef void (*UpdateFn)(void *);

void sub_0800168C(void *, s32, s32, s32);
void *sub_0800355C(void);
s32 sub_08013C2C(s16);
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
    sub_0800168C(entity, 0, 0x14, 0);
    if (*(void **)(entity + 0x3C) == 0) {
        ((UpdateFn)*(void **)(entity + 0x24))(entity);
        return;
    }
    fx = sub_0800355C();
    if (fx == 0) {
        ((UpdateFn)*(void **)(entity + 0x24))(entity);
        return;
    }
    *(void **)(entity + 0x38) = fx;
    elem = D_080CFC98[*(u8 *)(entity + 0x4C) * 2];
    tableIdx = sub_08013C2C(elem);
    idxU = ((u32)tableIdx << 16) >> 16;
    if (((s32)(tableIdx << 16)) < 0) {
        ((UpdateFn)*(void **)(entity + 0x24))(entity);
        return;
    }
    idx = (s16)idxU;
    attr = ((idx << 6) + 0x200) | ((idx + 8) << 12);
    *(u16 *)fx = attr;
    *(u16 *)fx = attr | D_02025FF0.baseAttr;
    *(s32 *)((u8 *)fx + 0x24) = D_080CFD40[*(u8 *)(entity + 0x7C)] * 8 + 0x083C3B60;
    *(s32 *)((u8 *)fx + 0x1C) = 0x8000000A;
    flags = 0x800 | *(u16 *)(entity + 0x02);
    *(u16 *)(entity + 0x02) = flags;
    *(void **)(entity + 0x14) = (void *)sub_080579A8;
    *(u16 *)(entity + 0x22) = 1;
    ((UpdateFn)sub_080579A8)(entity);
}
