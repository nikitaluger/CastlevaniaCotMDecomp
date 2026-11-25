extern void sub_08084428(void *, s16, s16);
extern s16 D_080E1648[];

/* Set up an effect's five display parts for the given frame group: each slot
 * naming a sprite part has that part configured, empty slots have their flag
 * byte cleared. */
void sub_080843E0(void *arg0, s32 arg1) {
    s32 i;
    s16 *table;
    s16 *idPtr;
    s16 partId;
    u32 off;
    u32 *partSlot;

    i = 0;
    table = D_080E1648;
    idPtr = &table[arg1 * 5];
    do {
        partId = *idPtr;
        if (partId != -1) {
            sub_08084428(arg0, partId, (s16)i);
        } else {
            off = i * 4;
            partSlot = (u32 *)((u8 *)arg0 + 0x2C);
            partSlot = (u32 *)((u8 *)partSlot + off);
            *(u8 *)(*partSlot + 1) = 0;
        }
        idPtr++;
        i++;
    } while (i <= 4);
}
