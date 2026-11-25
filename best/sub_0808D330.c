extern u8 D_02025FF0[];
struct N330 { s16 id; u8 pad[0x2A]; struct N330 *next; };
struct P330 { u8 pad[0x30]; struct N330 *head; };
s32 sub_0808D330(void) {
    struct P330 *p = *(struct P330 **)(D_02025FF0 + 0x1874);
    struct N330 *n = p->head;
    if (n != 0) {
        do {
            if (n->id == 0x212) return 0;
            n = n->next;
        } while (n != 0);
    }
    return 1;
}
