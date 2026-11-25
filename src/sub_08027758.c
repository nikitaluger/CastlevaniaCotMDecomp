extern void *sub_0805FAEC(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

struct Fill { u16 a; u8 pad1[8]; u16 b; };
struct ObjFields {
    u8 pad0[0x4C];
    s16 x;
    u8 pad1[6];
    s16 y;
    u8 pad2[6];
    u16 flag;
    u8 pad3[0xE];
    u16 val;
};
static inline s32 fixedToInt(s32 xval) { if (xval < 0) xval += 0xFFFF; return xval >> 16; }

/* Fills a five-entry position table from the entity's coordinates, spawns two
 * child objects at that position, clears its pose byte and runs a script. */
void sub_08027758(u8 *entity) {
    u8 *data;
    s32 i;
    struct Fill *fill;
    u8 *child, *child2;
    s32 x, y, x2, y2;
    s32 *scriptTable;
    struct ObjFields *childFields, *child2Fields;

    data = *(u8 **)(entity + 0x3C);
    fill = (struct Fill *)(data + 0x5C);
    i = 4;
    do {
        fill->a = *(s32 *)(data + 8);
        fill->b = *(s32 *)(data + 0xC);
        fill = (struct Fill *)((u8 *)fill + 2);
        i--;
    } while (i >= 0);

    child = sub_0805FAEC((s32)entity, 0xB2);
    if (child != 0) {
        childFields = (struct ObjFields *)child;
        x = fixedToInt(*(s32 *)(data + 8));
        childFields->x = x;
        y = fixedToInt(*(s32 *)(data + 0xC));
        childFields->y = y;
        childFields->flag = 0;
        childFields->val = *(u16 *)(data + 0x1C);
        child2 = sub_0805FAEC((s32)child, 0xB2);
        if (child2 != 0) {
            child2Fields = (struct ObjFields *)child2;
            x2 = fixedToInt(*(s32 *)(data + 8));
            child2Fields->x = x2;
            y2 = fixedToInt(*(s32 *)(data + 0xC));
            child2Fields->y = y2;
            child2Fields->flag = 1;
            child2Fields->val = *(u16 *)(data + 0x1C);
        }
    }
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
    scriptTable = (s32 *)0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *scriptTable);
}
