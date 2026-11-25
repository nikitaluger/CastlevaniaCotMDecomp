extern void *sub_0800355C(void);
extern s32 sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern void sub_080141F8(void *, void *, void *, s32, s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_080409FC(void *, void *, void *, u32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_08016664(void *, s32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08014290(void);

extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_080CD400[];
extern u8 D_080CF468[];
extern u8 D_080CF470[];
extern u8 D_080CF450[];
extern u32 D_08671BB0[];

/* Small sub-effect allocated from the effect pool. */
struct SubEffect {
    u8 _0; u8 kind; u8 f2; u8 f3;          /* 0x00-0x03 */
    u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; /* 0x04-0x0F: parameters */
    u32 owner;                              /* 0x10 */
};
/* Effect part at entity+0x3C. Field names keep the original byte offsets. */
struct Part {
    u8 _0[8];
    u32 x; u32 y;                           /* 0x08, 0x0C */
    u8 _10[0x0C];
    s16 animId;                             /* 0x1C */
    u8 _1E[0x0A];
    struct SubEffect *effect;               /* 0x28 */
    u8 _2C[8];
    u8 animStart;                           /* 0x34 */
};
/* 20-byte animation definition in D_080CB2B8. */
struct AnimDef { u16 p0; u16 p2; u16 p4; u8 _6[0x0E]; };
extern struct AnimDef D_080CB2B8[];

/* Spawn a sprite and its effect part for an entity: initialise the animation
 * from the variant tables, attach a sub-effect, place it relative to the
 * camera, then advance the entity's animation step and dispatch its handler. */
void sub_0803F934(u8 *entity) {
    u8 *sprite;
    struct Part *part;
    u8 *anim;
    u8 *ext;
    struct SubEffect *effect;
    s32 spawnId;
    u8 *effectParams;
    u8 *animTable;
    u8 *animTable2;
    u8 *variantPtr;
    u8 *pt, *pb, *base1, *base2;
    u32 idx;

    spawnId = *(s32 *)(entity + 0xAC);
    sprite = sub_0800355C();
    if (sprite == NULL) goto fail;
    *(void **)(entity + 0x38) = sprite;
    sub_0800168C(entity, 0, 0x50, 0);
    if (*(u32 *)(entity + 0x3C) == 0) goto fail;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    part = *(struct Part **)(entity + 0x3C);
    anim = (u8 *)part + 0x34;
    ext = (u8 *)part + 0x48;
    sub_08014288(entity, (u8 *)part, (void *)sub_08014290);
    animTable = D_080CF468;
    variantPtr = entity + 0x4C;
    sub_080141F8(entity, sprite, (u8 *)part, spawnId, *(s16 *)(animTable + *variantPtr * 4));
    sub_0801131C(sprite, anim, (s32)D_080CD400 + *(s16 *)((u8 *)part + 0x1C) * 0xC);
    animTable2 = D_080CF470;
    sub_080409FC(sprite, anim, ext, *(u16 *)(animTable2 + *variantPtr * 2));
    effectParams = D_080CF450;
    effect = sub_08016190();
    part->effect = effect;
    if (effect == NULL) goto fail;
    goto body;

fail:
    sub_080C31E0(entity, *(void **)(entity + 0x24));
    return;

body:
    effect->kind = 5;
    part->effect->f2 = 8;
    part->effect->f3 = 1;
    {
        spawnId = 0;
        part->effect->f4 = D_080CB2B8[*(s16 *)((u8 *)part + 0x1C)].p0;
        part->effect->f6 = *(u16 *)(effectParams + 0);
        part->effect->f8 = *(u16 *)(effectParams + 2);
        part->effect->fA = *(u16 *)(effectParams + 4);
        part->effect->fC = *(u16 *)(effectParams + 6);
        part->effect->fE = D_080CB2B8[*(s16 *)((u8 *)part + 0x1C)].p4;
    }
    part->effect->owner = (u32)sprite;
    {
        pt = D_02021E90;
        pb = D_02025FF0;
        pb += 0x18A8;
        idx = ((u32)*pb + 1) * 0x40;
        base1 = pt + 0x1278;
        *(u32 *)(sprite + 0x14) = *(u32 *)((u8 *)part + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
        idx = ((u32)*pb + 1) * 0x40;
        base2 = pt + 0x127C;
        *(u32 *)(sprite + 0x18) = *(u32 *)((u8 *)part + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
    sub_08016664(entity, 0);
    {
        u16 flags = *(u16 *)(entity + 2);
        flags |= 0x1000;
        *(u16 *)(entity + 2) = flags;
    }
    *(u8 *)((u32)(*(s16 *)(entity + 0x22) * 2) + (u32)entity + 0x19) = (u8)spawnId;
    {
        u32 *table = (u32 *)D_08671BB0;
        u8 *p18 = entity + 0x18;
        sub_080C31E4(p18, entity + 0x22, *table);
        {
            u8 *p19 = (u8 *)((u32)(*(s16 *)(entity + 0x22) * 2) + (u32)entity + 0x19);
            *p19 = (u8)(*p19 + 1);
            p19 = p18;
            p19 += *(s16 *)(entity + 0x22) * 2;
            {
                u8 step = *p19;
                void *handler = ((void **)*(void **)(entity + 0x14))[step];
                sub_080C31E0(entity, handler);
            }
        }
    }
}
