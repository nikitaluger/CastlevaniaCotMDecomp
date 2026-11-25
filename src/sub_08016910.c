/* Effect pool root at 0x020279D0:
 *   +0 u8  next serial id, +1 u8 active count, +2 u16 registry count
 *   +4 registry list head (node: data at +0, next at +4)
 *   +8 active-effect list head (node: object at +0, next at +4)
 * D_02020BC0/D_02020BC8 are the registry cursor and its saved copy;
 * D_02020BC4/D_02020BCC are the active-list cursor and its saved copy. */
struct EffectPool {
    u8 _pad[4];
    s32 registryHead;
    s32 activeHead;
};
extern struct EffectPool D_020279D0;
extern u32 D_02020BC0;
extern s32 D_02020BC4;
extern u32 D_02020BC8;
extern s32 D_02020BCC;

/* Pop the next registry entry and advance the cursor. */
s32 sub_080168E0(void) {
    void *node = (void *)D_02020BC0;
    s32 data;
    if (node != NULL) {
        D_02020BC0 = (u32)*(void **)((u8 *)node + 4);
        data = *(s32 *)node;
    } else {
        data = 0;
    }
    return data;
}

/* Rewind the active-effect cursor to the start of its list. */
void sub_080168C4(void) {
    s32 head = D_020279D0.activeHead;
    D_02020BC4 = head;
    D_02020BCC = head;
}

/* Rewind the registry cursor to the start of its list. */
void sub_080168A8(void) {
    s32 head = D_020279D0.registryHead;
    D_02020BC0 = (u32)head;
    D_02020BC8 = (u32)head;
}

void sub_080168A8(void);
s32 sub_080168E0(void);

/* Pop the next registry entry; if the list is exhausted, rewind it. Otherwise
 * re-anchor the cursor on the node that holds the entry just returned. */
void sub_08016910(void) {
    s32 data;
    void *node;
    data = sub_080168E0();
    if (data == 0) {
        sub_080168A8();
        return;
    }
    node = (void *)D_020279D0.registryHead;
    if (node != NULL) {
        do {
            if (*(s32 *)node == data) {
                D_02020BC0 = (u32)node;
                D_02020BC8 = (u32)node;
                break;
            }
            node = *(void **)((u8 *)node + 4);
        } while (node != NULL);
    }
}
