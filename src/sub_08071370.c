/* Spawn/init this entity's AI: allocate a 0x34-byte work slot, fill its state
 * and callbacks from global tables, then run the first state-script step. */
extern void sub_08003A6C(void *, s32, void *);
extern void *sub_08016190(void);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_0807199C(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern u32 D_08474A7C;
extern u32 D_08474ABC;
extern s32 D_08671BB0;
struct AIWorkSlot { u8 _0[0x3C]; u8 * volatile resource; };

void sub_08071370(u8 *entity) {
    u32 zero;
    u32 two;
    u32 c;
    u8 *work = *(u8 **)(entity + 0x6C);
    u8 *state = work + 4;
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *base2 = D_02025368;
    void *res;
    struct AIWorkSlot *s = (struct AIWorkSlot *)state;

    res = sub_08016190();
    s->resource = res;
    if (res == NULL) {
        sub_0806D2D0(entity);
        return;
    }
    zero = 0;
    *(u8 *)(res + 1) = zero;
    {
        u8 *rr = s->resource;
        two = 2;
        *(u8 *)(rr + 2) = two;
    }
    *(u8 *)(s->resource + 3) = 8;
    *(u16 *)(s->resource + 4) = zero;
    *(u16 *)(s->resource + 6) = 6;
    *(u16 *)(s->resource + 8) = 6;
    *(u16 *)(s->resource + 0xA) = zero;
    *(u16 *)(s->resource + 0xC) = zero;
    *(u16 *)(s->resource + 0xE) = sub_0806D62C(*(u16 *)(base2 + 0x2DE), 0x64);
    {
        u8 *rp = s->resource;
        *(void **)(rp + 0x10) = sprite;
        *(u16 *)(rp + 0x16) = 0xF;
    }
    *(u16 *)(s->resource + 0x18) = 0x7F;
    *(u32 *)(state + 0x18) = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)&sub_0807199C;
    *(u32 *)(sprite + 0x24) = (u32)&D_08474A7C;
    sub_08003A6C(work + 0x30, 0, &D_08474ABC);
    {
        u8 *base = D_02025FF0;
        *(s32 *)(work + 4) = *(s32 *)(base + 0x1728);
        *(s32 *)(state + 4) = *(s32 *)(base + 0x172C) + 0xFFEC0000;
        *(u32 *)(state + 0x10) = 0x2BF;
        *(u8 *)(base + 0x14EC) = two;
        c = 0x80 << 3;
        *(u16 *)(sprite + 4) = c;
        *(u16 *)(sprite + 6) = c;
        *(u16 *)(sprite + 8) = zero;
        *(u32 *)(sprite + 0x1C) = 0x80000006;
        *(u16 *)(sprite + 0) = *(u16 *)(base + 0x18C2);
    }
    *(u32 *)(state + 0x4C) = *(u32 *)(entity + 0x7C);
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = zero;
    {
        s32 *scriptTable = &D_08671BB0;
        u8 *framePtr = entity + 0x18;
        sub_080C31E4(framePtr, entity + 0x22, *scriptTable);
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) + 1;
        framePtr += *(s16 *)(entity + 0x22) * 2;
        {
            u8 stateByte = *framePtr;
            sub_080C31E0(entity, *(s32 *)(stateByte * 4 + *(u32 *)(entity + 0x14)));
        }
    }
}
