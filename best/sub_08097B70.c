extern void allocWorkSlot(void *, s32, s32, s32);
extern void *sub_0805FB24(s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 D_02027860;
extern u16 D_020213DC;
extern s32 gScriptStepCallbackTable;
extern u8 sub_08097CF4[];

typedef struct {
    u32 ptr;
    u32 pad;
} Slot;

typedef struct {
    u8 _0[0xC];
    Slot slots[31];
    u8 _104[4];
    s16 count;
} Main;

void sub_08097B70(void *arg0)
{
    s32 *g0;
    u16 *g1;
    u8 *self = (u8 *)arg0;
    Main *m = (Main *)*(u8 **)(self + 0x3C);
    s32 i = 0;
    u8 *node = *(u8 **)(*(u8 **)m);

    if (!(*(u16 *)(node + 0x0A) & 0x8000)) {
        u32 eight = 8;
        u8 *walker = (u8 *)m;
        do {
            *(u16 *)(walker + 8) = eight;
            *(u8 **)(walker + 0x0C) = node;
            walker += 8;
            i++;
            node += 0x0C;
        } while (!(*(u16 *)(node + 0x0A) & 0x8000));
    }

    m->count = (s16)i;

    for (i = 0; i < m->count; i++) {
        void *obj;
        g0 = &D_02027860;
        g1 = &D_020213DC;
        node = (u8 *)m->slots[i].ptr;
        obj = sub_0805FB24(*g0, *(s16 *)(node + 4));
        if (obj != 0) {
            u8 *p = (u8 *)obj;
            allocWorkSlot(p, 0, 8, 7);
            {
                u8 *ac = *(u8 **)(p + 0xAC);
                if (ac == 0) {
                    sub_080C31E0(p, *(s32 *)(p + 0x24));
                    return;
                }
                *(u16 *)ac = 0;
                *(u8 **)(ac + 4) = node;
                *g1 = *g1 + 1;
                *(u32 *)(p + 0x24) = (u32)sub_08097CF4;
            }
        }
    }

    {
        u8 *p18;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            u32 *fp = &gScriptStepCallbackTable;
            p18 = self + 0x18;
            sub_080C31E4(p18, self + 0x22, *fp);
        }
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        {
            s32 off = *(s16 *)(self + 0x22) * 2;
            sub_080C31E0(self, *(s32 *)(*(u8 **)(self + 0x14) + *(u8 *)(p18 + off) * 4));
        }
    }
}
