extern u32 gMainWorkspace[];
extern u8 gFacingFrameTable[];
extern u8 gFacingOrderTable[];
void _call_via_r1(void *, s32);
void setObjectAnimationFrame(void *, void *, s32, s32);
s32 nextRandomWord(void);
void *spawnBudgetedEffect(s32, s32);

static inline u16 or10(u16 v) { u32 m = 0x10; m |= v; return (u16)m; }
static inline u16 or30(u16 v) { u32 m = 0x30; m |= v; return (u16)m; }

/* Run a scripted AI step: count down a timer, advance a phase, pick a random
 * facing direction from tables, and spawn a follow-up object when triggered. */
void updateRandomFacingEffect(void *arg0) {
    u8 *obj = (u8 *)arg0;
    u8 *entity = *(u8 **)(obj + 0x38);
    u8 *state = *(u8 **)(obj + 0x3C);
    u8 *stateField34 = state + 0x34;
    u8 *scriptState = state + 0x48;
    s32 resetCount;
    s32 val;
    s32 timer = *(u8 *)(scriptState + 2) - 1;
    *(u8 *)(scriptState + 2) = timer;
    if ((timer << 24) == 0) {
        s32 phase = *(u8 *)(scriptState + 3) + 1;
        *(u8 *)(scriptState + 3) = phase;
        resetCount = 3;
        *(u8 *)(scriptState + 2) = resetCount;
        if ((s8)phase == 4) {
            _call_via_r1(arg0, *(s32 *)(obj + 0x24));
            return;
        }
        {
            u8 *dirTable = gFacingFrameTable;
            u8 *indexTable = gFacingOrderTable;
            s32 tableIdx = *(s8 *)(scriptState + 3);
            s32 dirIndex;
            s32 direction;
            tableIdx += *(u8 *)(scriptState + 1) * 4;
            dirIndex = indexTable[tableIdx];
            direction = *(s16 *)(dirTable + dirIndex * 2);
            setObjectAnimationFrame(entity, stateField34, direction, 0);
            val = nextRandomWord() & resetCount;
            switch (val) {
            case 0: *(u16 *)(entity + 2) = 0xFFCF & *(u16 *)(entity + 2); break;
            case 1: {
                u16 v = *(u16 *)(entity + 2);
                *(u16 *)(entity + 2) = or10(v) & 0xFFDF;
                break;
            }
            case 2: *(u16 *)(entity + 2) = (0xFFEF & *(u16 *)(entity + 2)) | 0x20; break;
            case 3: {
                u16 v = *(volatile u16 *)(entity + 2);
                *(u16 *)(entity + 2) = or30(v);
                break;
            }
            }
        }
    }
    if ((*(u32 *)scriptState & 0xFF0000FF) == 0x01000000 && *(s32 *)(obj + 0x6C) != 2) {
        void *spawned;
        *(u8 *)scriptState = 1;
        {
            u32 fieldOffset = 0x1870;
            u8 *globalBase = gMainWorkspace;
            spawned = spawnBudgetedEffect(*(s32 *)(globalBase + fieldOffset), 0xBF * 2);
        }
        if (spawned != NULL) {
            *(s32 *)((u8 *)spawned + 0x4C) = *(s32 *)(state + 8);
            *(s32 *)((u8 *)spawned + 0x5C) = *(s32 *)(state + 0x0C) + 0x200000;
            *(s32 *)((u8 *)spawned + 0x6C) = *(s32 *)(obj + 0x6C) + 1;
        }
    }
}
