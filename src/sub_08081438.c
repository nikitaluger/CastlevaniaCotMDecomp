/* Initialize an effect's attached sub-object: clear/configure its fields, attach
 * sprite and frame data from the per-effect tables, place it via the active
 * entity's coordinate-table entry, set the palette and game-work counters, then
 * advance its animation and invoke the selected callback. */
extern u8 D_02021E90[];   /* coordinate-table base */
extern u8 D_02025FF0[];   /* game-work buffer */
extern void sub_08003A6C(void *, u32, void *);  /* init effect descriptor */
extern void sub_0808BBAC(s32, s32, s32);        /* store effect params in game work */
extern void sub_080C31E4(void *, void *, u32);  /* start animation frame */
extern void sub_080C31E0(void *, s32);          /* call an entity callback */

struct EffectEntity {
    u8 _0[0x14];
    u32 *funcTable;    /* 0x14: table of callback pointers */
    u8 _18[0x0A];
    s16 animIndex;     /* 0x22: current animation/effect slot */
    u32 updateFunc;    /* 0x24: update callback (Thumb pointer) */
    u8 _28[0x10];
    u32 *spriteState;  /* 0x38: graphics-state block */
    u8 _3C[0x30];
    u8 *subObject;     /* 0x6C: attached sub-object */
};

void sub_08081438(struct EffectEntity *entity)
{
    u8 *entityBytes = (u8 *)entity;
    u8 *sub = *(u8 **)(entityBytes + 0x6C);
    u8 *subData = sub + 4;
    u32 *sprite = *(u32 **)(entityBytes + 0x38);
    u32 zero = 0;
    u8 *stateBuf;
    u8 *coordTable;
    u8 *baseX;
    u8 *baseY;
    u32 idx;
    u32 *animTable;
    u32 *callbacks;

    *(u32 *)(subData + 0x2C) = zero;
    *(u32 *)(subData + 0x30) = zero;
    *(u32 *)(subData + 0x34) = zero;
    *(u32 *)(subData + 0x38) = zero;
    *(u32 *)(subData + 0x3C) = zero;
    *(u32 *)(subData + 0x18) = *(u32 *)(entityBytes + 0x24);
    *(u32 *)(entityBytes + 0x24) = 0x0808449D; /* Thumb ptr to sub_0808449C */
    *(u32 *)((u8 *)sprite + 0x24) = 0x084F240C; /* sprite data table */
    sub_08003A6C(sub + 0x20, 0, (void *)0x084F24BC); /* frame data */
    coordTable = D_02021E90;
    stateBuf = D_02025FF0;
    idx = ((u32)stateBuf[0x18A8] + 1) * 0x40;
    baseX = coordTable + 0x1278;
    *(u32 *)(sub + 4) = *(u32 *)(baseX + idx) + 0x780000;
    idx = ((u32)stateBuf[0x18A8] + 1) * 0x40;
    baseY = coordTable + 0x127C;
    *(u32 *)(subData + 4) = *(u32 *)(baseY + idx) + 0xC00000;
    *(u32 *)(subData + 0x10) = 0x100;
    *(vu16 *)0x05000000 = 0x190;
    sub_0808BBAC(0x40, 1, 3);
    if (*(s32 *)(stateBuf + 0x1754) <= 0x100) {
        *(s32 *)(stateBuf + 0x1754) = 0x101;
    }
    *(u32 *)(subData + 0x14) = 1;
    {
        u8 *frame = (u8 *) ((((s16) (*((s16 *) (((char *) entityBytes) + 0x22)))) * 2) + ((u32) entityBytes));
        frame[0x19] = zero;
    }
    animTable = (u32 *) 0x08671BB0;
    sub = entityBytes + 0x18; /* reused as the animation-byte cursor */
    sub_080C31E4(sub, entityBytes + 0x22, *animTable);
    {
        u8 *frame = (u8 *) ((((s16) (*((s16 *) (((char *) entityBytes) + 0x22)))) * 2) + ((u32) entityBytes));
        frame[0x19] = frame[0x19] + 1;
    }
    sub = sub + (((s16) (*((s16 *) (((char *) entityBytes) + 0x22)))) * 2);
    {
        u8 slot = *sub;
        callbacks = *(u32 **) (((char *) entityBytes) + 0x14);
        sub_080C31E0(entity, callbacks[slot]);
    }
}
