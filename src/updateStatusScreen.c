extern s32 gAreaTilesetTable[];  /* area tileset pointer table */
extern s32 gLevelExpTable[];   /* EXP required for level n (indexed by level - 1) */
extern u16 gStatusItemTiles[];   /* tile numbers of the status-screen item grid */
extern u8 gGameStatus[];    /* game/player status block */
extern u32 gMainObjTimerCallbacks;

extern s32 divideInt(s32, s32);           /* Div: quotient */
extern s32 moduloInt(s32, s32);           /* Div: remainder */
extern void drawDecimal(s32, s32, s16 *);   /* print decimal digits */
extern void drawPaddedDecimal(s32, s32, s32, s16 *); /* print fixed digit count */
extern u32 formatPlayTime(u32);                /* frames -> packed hh:mm:ss */
extern void decompressToVram(u32, s32);          /* LZ77 decompress to VRAM */
extern void resetMapRender(void);              /* reset map render state */
extern void setMapLayerParams(s32, s32, s32);     /* set map layer params */
extern void setScreenTransition(s32);               /* set pending screen transition */
extern void sub_080C31E4(u8 *, u8 *, u32);   /* call via r2 */
extern void sub_080C31E0(u8 *, u32);         /* call via r1 */

/* Live values kept by the status screen. Offsets are load-bearing. */
struct Game {
    u8 pad00[0x8C];
    s16 sheet;       /* 0x08C: graphics/area index into gAreaTilesetTable */
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
void updateStatusScreen(u8 *task)
{
    struct Game *g;
    vu32 *dma;
    s16 *levelPtr;
    s32 *expPtr;
    u8 *stateData;
    u8 *stateIndex;
    u32 *callbackPtr;
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

    g = (struct Game *)gGameStatus;
    dma = (vu32 *)0x040000D4;
    dma[0] = gAreaTilesetTable[g->sheet];
    dma[1] = 0x06003E60;
    dma[2] = 0x800000D0;
    (void)dma[2];

    rooms = g->rooms;
    completion = divideInt(((((rooms << 5) - rooms) << 2) + rooms) << 3, 0x3D4);
    drawDecimal(moduloInt(completion, 10), 0x511C, (s16 *)0x060068F6);
    drawDecimal(divideInt(completion, 10), 0x511C, (s16 *)0x060068F2);
    levelPtr = &g->level;
    drawDecimal(levelPtr[0], 0x511C, (s16 *)0x060068CE);

    timePacked = formatPlayTime(g->playTime);
    hours = (timePacked >> 16) & 0xFF;
    minutes = (timePacked >> 8) & 0xFF;
    seconds = timePacked & 0xFF;
    drawDecimal(hours, 0x511C, (s16 *)0x0600686C);
    drawPaddedDecimal(minutes, 2, 0x511C, (s16 *)0x06006872);
    drawPaddedDecimal(seconds, 2, 0x511C, (s16 *)0x06006878);

    expPtr = (s32 *)&g->exp;
    drawDecimal(*expPtr, 0x511C, (s16 *)0x06006A78);
    expToNext = gLevelExpTable[levelPtr[0] - 1];
    if (expToNext > 0x05F5E0FF || expToNext < *expPtr)
        expToNext = 0;
    else
        expToNext -= *expPtr;
    drawDecimal(expToNext, 0x511C, (s16 *)0x06006AB8);
    {
        s16 *p = (s16 *)((u8 *)g + 0x2C8);
        drawDecimal(p[1], 0x511C, (s16 *)0x06006978);
    }
    {
        s16 *p = (s16 *)((u8 *)g + 0x2D0);
        drawDecimal(p[1], 0x511C, (s16 *)0x060069B8);
    }
    drawDecimal(g->stat2D6, 0x511C, (s16 *)0x060069F8);

    rowIdx = 0;
    stateData = task + 0x18;
    stateIndex = task + 0x22;
    itemTiles = gStatusItemTiles;
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
                decompressToVram(0x086403A8, *tilePtr * 32 + 0x06008000);
            tilePtr++;
        }
    }

    zero = 0;
    {
        s16 *p = (s16 *)((u8 *)g + 0x2C8);
        drawDecimal(p[1], 0x511C, (s16 *)0x06007078);
    }
    {
        s16 *p = (s16 *)((u8 *)g + 0x2D0);
        drawDecimal(p[1], 0x511C, (s16 *)0x060070B8);
    }
    drawDecimal(g->stat2D6, 0x511C, (s16 *)0x060070F8);
    resetMapRender();
    setMapLayerParams(0, 1, 1);
    setScreenTransition(0);
    *(u8 *)(task + *(s16 *)(task + 0x22) * 2 + 0x19) = zero;
    callbackPtr = &gMainObjTimerCallbacks;
    sub_080C31E4(stateData, stateIndex, *callbackPtr);
    (*(u8 *)(task + *(s16 *)(task + 0x22) * 2 + 0x19))++;
    byteOffset = *(s16 *)(task + 0x22) * 2;
    stateId = stateData[byteOffset];
    sub_080C31E0(task, *(u32 *)(*(u32 *)(task + 0x14) + stateId * 4));
}
