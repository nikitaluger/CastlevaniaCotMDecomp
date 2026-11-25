extern void sub_0801165C(void *, s32);
extern void sub_080C31E0(void *, void *);

struct S_02025FF0_18A8 { u8 _0[0x18A8]; u8 v; };
extern struct S_02025FF0_18A8 D_02025FF0;
extern u8 D_02021E90[];

/* At step 0x18 this callback stops; otherwise it integrates the entity's motion
 * state and sets its companion's X/Y velocity to the (rounded) difference
 * between the motion coordinates and the current target entry in the runtime
 * table D_02021E90, indexed by the global target number. */
void sub_080A5368(void *entity)
{
    void *companion;
    void *motion;
    u8 *table;
    u32 index;
    u8 *xEntry;
    u8 *yEntry;

    companion = *(void **)((u8 *)entity + 0x38);
    motion = *(void **)((u8 *)entity + 0x3C);

    if (*(s16 *)((u8 *)entity + 0x22) == 0x18)
    {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }

    sub_0801165C(motion, 0);

    table = D_02021E90;
    index = (D_02025FF0.v + 1) * 0x40;
    xEntry = table + 0x1278;
    *(s32 *)((u8 *)companion + 0x14) = *(s32 *)((u8 *)motion + 0x08) - ((*(s32 *)(xEntry + index) + 0x8000) & 0xFFFF0000);

    index = (D_02025FF0.v + 1) * 0x40;
    yEntry = table + 0x127C;
    *(s32 *)((u8 *)companion + 0x18) = *(s32 *)((u8 *)motion + 0x0C) - ((*(s32 *)(yEntry + index) + 0xFFFF8000) & 0xFFFF0000);
}
