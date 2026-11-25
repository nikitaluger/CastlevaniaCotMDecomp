extern void *sub_0800355C(void);            /* create the sprite object */
extern s32 sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern void sub_080141F8(void *, void *, void *, s32, s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s32, s32); /* set animation/frame control */
extern void *sub_08016190(void);            /* allocate a part object */
extern void sub_080C31E0(void *, void *);   /* cleanup callback */
extern void sub_08016664(void *, s32);
extern void sub_080C31E4(void *, void *, u32); /* run a script handler */
extern void sub_08014290(void);

extern u8 D_02021E90[];                     /* scroll-offset table */
extern u8 D_02025FF0[];                     /* global game state */
extern u8 D_080CD400[];                     /* frame-control data */
extern u8 D_080CF968[];                     /* part parameter table */
extern u32 D_08671BB0[];                    /* step-script operation */

struct Part {
    u8 _0; u8 f1; u8 f2; u8 f3;
    u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE;
    u32 f10;
    u8 _14[0x0C];
};
struct Entity {
    u8 _0[8];
    u32 f08; u32 f0C;
    u8 _10[0x0C];
    s16 f1C;
    u8 _1E[0x0A];
    struct Part *f28;
    u8 _2C[8];
    u8 f34;
};
struct PartTable { u16 f0; u16 f2; u16 f4; u8 _6[0x0E]; };
extern struct PartTable D_080CB2B8[];

/* Creates a sprite and part object for an entity, configures the part's parameters and
   screen position, then advances the object's first script step. */
void sub_0804A6D0(u8 *arg0) {
    u8 *sprite;
    struct Entity *entity;
    u8 *anim;
    u8 *s;
    struct Part *part;
    s32 param;
    u8 *partParams;
    u8 *scrollTbl, *scrollIdxPtr, *xBase, *yBase;
    u32 scrollIdx;

    param = *(s32 *)(arg0 + 0xAC);
    sprite = sub_0800355C();
    if (sprite == NULL) goto fail;
    *(void **)(arg0 + 0x38) = sprite;
    sub_0800168C(arg0, 0, 0x58, 0);
    if (*(u32 *)(arg0 + 0x3C) == 0) goto fail;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    entity = *(struct Entity **)(arg0 + 0x3C);
    anim = (u8 *)entity + 0x34;
    sub_08014288(arg0, (u8 *)entity, (void *)sub_08014290);
    sub_080141F8(arg0, sprite, (u8 *)entity, param, 0x10);
    sub_0801131C(sprite, anim, (s32)D_080CD400 + *(s16 *)((u8 *)entity + 0x1C) * 0xC);
    sub_08011368(sprite, anim, 0, 0);
    partParams = D_080CF968;
    part = sub_08016190();
    entity->f28 = part;
    if (part == NULL) goto fail;
    goto body;

fail:
    sub_080C31E0(arg0, *(void **)(arg0 + 0x24));
    return;

body:
    part->f1 = 5;
    entity->f28->f2 = 8;
    entity->f28->f3 = 1;
    {
        param = 0;
        entity->f28->f4 = D_080CB2B8[*(s16 *)((u8 *)entity + 0x1C)].f0;
        entity->f28->f6 = *(u16 *)(partParams + 0);
        entity->f28->f8 = *(u16 *)(partParams + 2);
        entity->f28->fA = *(u16 *)(partParams + 4);
        entity->f28->fC = *(u16 *)(partParams + 6);
        entity->f28->fE = D_080CB2B8[*(s16 *)((u8 *)entity + 0x1C)].f4;
    }
    entity->f28->f10 = (u32)sprite;
    {
        scrollTbl = D_02021E90;
        scrollIdxPtr = D_02025FF0;
        scrollIdxPtr += 0x18A8;
        scrollIdx = ((u32)*scrollIdxPtr + 1) * 0x40;
        xBase = scrollTbl + 0x1278;
        *(u32 *)(sprite + 0x14) = *(u32 *)((u8 *)entity + 0x08) - ((*(u32 *)(xBase + scrollIdx) + 0x8000) & 0xFFFF0000);
        scrollIdx = ((u32)*scrollIdxPtr + 1) * 0x40;
        yBase = scrollTbl + 0x127C;
        *(u32 *)(sprite + 0x18) = *(u32 *)((u8 *)entity + 0x0C) - ((*(u32 *)(yBase + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    sub_08016664(arg0, 0);
    {
        u16 h = *(u16 *)(arg0 + 2);
        h |= 0x1000;
        *(u16 *)(arg0 + 2) = h;
    }
    *(u8 *)((u32)(*(s16 *)(arg0 + 0x22) * 2) + (u32)arg0 + 0x19) = (u8)param;
    {
        u32 *wp = (u32 *)D_08671BB0;
        u8 *p18 = arg0 + 0x18;
        sub_080C31E4(p18, arg0 + 0x22, *wp);
        {
            u8 *q2 = (u8 *)((u32)(*(s16 *)(arg0 + 0x22) * 2) + (u32)arg0 + 0x19);
            *q2 = (u8)(*q2 + 1);
            q2 = p18;
            q2 += *(s16 *)(arg0 + 0x22) * 2;
            {
                u8 c = *q2;
                void *fn = ((void **)*(void **)(arg0 + 0x14))[c];
                sub_080C31E0(arg0, fn);
            }
        }
    }
}
