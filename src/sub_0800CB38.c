extern s32 D_0866CF24[];  /* area tileset pointer table */
extern s32 D_080E0738[];   /* EXP required for level n (indexed by level - 1) */
extern u16 D_080CAFD0[];   /* tile numbers of the status-screen item grid */
extern u8 D_02025368[];    /* game/player status block */

extern s32 sub_080C2F20(s32, s32);           /* Div: quotient */
extern s32 sub_080C2F24(s32, s32);           /* Div: remainder */
extern void sub_0800FD54(s32, s32, s16 *);   /* print decimal digits */
extern void sub_0800FDC8(s32, s32, s32, s16 *); /* print fixed digit count */
extern u32 sub_0800FEF0(u32);                /* frames -> packed hh:mm:ss */
extern void sub_080063D4(u32, s32);          /* LZ77 decompress to VRAM */
extern void sub_0805FDF0(void);              /* reset map render state */
extern void sub_0805FE8C(s32, s32, s32);     /* set map layer params */
extern void sub_0805FEB4(s32);               /* set pending screen transition */
extern void sub_080C31E4(u8 *, u8 *, u32);   /* call via r2 */
extern void sub_080C31E0(u8 *, u32);         /* call via r1 */

/* Live values kept by the status screen. Offsets are load-bearing. */
struct Game {
    u8 pad00[0x8C];
    s16 sheet;       /* 0x08C: graphics/area index into D_0866CF24 */
    u8 pad8E[2];
    u32 playTime;    /* 0x090: play time in frames */
    u8 pad94[0x18];
    u16 rooms;       /* 0x0AC: rooms visited, completion = rooms*1000/980 */
    u8 padAE[0x21A];
    s16 stat2C8[4];  /* 0x2C8: status values drawn on the screen */
    s16 stat2D0[3];  /* 0x2D0 */
    s16 stat2D6;     /* 0x2D6 */
    u8 pad2D8[0x24];
    s16 level;       /* 0x2FC */
    u32 exp;         /* 0x300 */
    u8 pad304[8];
    u8 items[20];    /* 0x30C: 2x10 item grid, 0 = empty slot */
};

/* Status-screen step: loads the area tileset, draws level, EXP, EXP to next
 * level, map completion, play time and the three status values, redraws the
 * item-grid icons, then advances the task's state machine. */
void sub_0800CB38(u8 *task)
{
    struct Game *g;
    vu32 *dma;
    s16 *levelPtr;
    s32 *expPtr;
    u8 *stateData;
    u8 *stateIndex;
    s32 completion;
    s32 rooms;
    s32 expToNext;
    u32 timePacked;
    u32 hours;
    u32 minutes;
    u32 seconds;
    u32 rowIdx;
    u32 entry;
    u32 rowBase;
    u32 col;
    u32 nextRow;
    u32 zero;
    u32 byteOffset;
    s32 stateId;
    u16 *itemTiles;
    u16 *tilePtr;

    g = (struct Game *)D_02025368;
    dma = (vu32 *)0x040000D4;
    dma[0] = D_0866CF24[g->sheet];
    dma[1] = 0x06003E60;
    dma[2] = 0x800000D0;
    (void)dma[2];

    rooms = g->rooms;
    completion = sub_080C2F20(((((rooms << 5) - rooms) << 2) + rooms) << 3, 0x3D4);
    sub_0800FD54(sub_080C2F24(completion, 10), 0x511C, (s16 *)0x060068F6);
    sub_0800FD54(sub_080C2F20(completion, 10), 0x511C, (s16 *)0x060068F2);
    levelPtr = &g->level;
    sub_0800FD54(levelPtr[0], 0x511C, (s16 *)0x060068CE);

    timePacked = sub_0800FEF0(g->playTime);
    hours = (timePacked >> 16) & 0xFF;
    minutes = (timePacked >> 8) & 0xFF;
    seconds = timePacked & 0xFF;
    sub_0800FD54(hours, 0x511C, (s16 *)0x0600686C);
    sub_0800FDC8(minutes, 2, 0x511C, (s16 *)0x06006872);
    sub_0800FDC8(seconds, 2, 0x511C, (s16 *)0x06006878);

    expPtr = (s32 *)&g->exp;
    sub_0800FD54(*expPtr, 0x511C, (s16 *)0x06006A78);
    expToNext = D_080E0738[levelPtr[0] - 1];
    if (expToNext > 0x05F5E0FF || expToNext < *expPtr)
        expToNext = 0;
    else
        expToNext -= *expPtr;
    sub_0800FD54(expToNext, 0x511C, (s16 *)0x06006AB8);
    {
        s16 *p = (s16 *)((u8 *)g + 0x2C8);
        sub_0800FD54(p[1], 0x511C, (s16 *)0x06006978);
    }
    {
        s16 *p = (s16 *)((u8 *)g + 0x2D0);
        sub_0800FD54(p[1], 0x511C, (s16 *)0x060069B8);
    }
    sub_0800FD54(g->stat2D6, 0x511C, (s16 *)0x060069F8);

    rowIdx = 0;
    stateData = task + 0x18;
    stateIndex = task + 0x22;
    itemTiles = D_080CAFD0;
    for (; rowIdx <= 1; rowIdx = nextRow)
    {
        col = 0;
        rowBase = rowIdx * 4;
        nextRow = rowIdx + 1;
        entry = rowBase + rowIdx;
        tilePtr = (u16 *)(entry * 4 + (u32)itemTiles);
        for (; col <= 9; col++)
        {
            if (g->items[col + entry * 2] == 0)
                sub_080063D4(0x086403A8, *tilePtr * 32 + 0x06008000);
            tilePtr++;
        }
    }

    zero = 0;
    {
        s16 *p = (s16 *)((u8 *)g + 0x2C8);
        sub_0800FD54(p[1], 0x511C, (s16 *)0x06007078);
    }
    {
        s16 *p = (s16 *)((u8 *)g + 0x2D0);
        sub_0800FD54(p[1], 0x511C, (s16 *)0x060070B8);
    }
    sub_0800FD54(g->stat2D6, 0x511C, (s16 *)0x060070F8);
    sub_0805FDF0();
    sub_0805FE8C(0, 1, 1);
    sub_0805FEB4(0);
    *(u8 *)(task + *(s16 *)(task + 0x22) * 2 + 0x19) = zero;
    sub_080C31E4(stateData, stateIndex, *(u32 *)0x08671BB0);
    (*(u8 *)(task + *(s16 *)(task + 0x22) * 2 + 0x19))++;
    byteOffset = *(s16 *)(task + 0x22) * 2;
    stateId = stateData[byteOffset];
    sub_080C31E0(task, *(u32 *)(*(u32 *)(task + 0x14) + stateId * 4));
}
