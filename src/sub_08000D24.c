/* Splice the chain beginning at `chain` into a doubly-linked list just before
 * `node`; nodes link forward at +0 and back at +4. */
void sub_08000D24(void *node, void *chain) {
    void *tail = chain;
    void *prev;
    void *p;
    if (chain != NULL) {
        p = *(void **)chain;
        prev = *(void **)((u8 *)node + 4);
        if (p != NULL) {
            do {
                tail = *(void **)tail;
            } while (*(void **)tail != NULL);
        }
        *(void **)((u8 *)chain + 4) = prev;
        *(void **)prev = chain;
        *(void **)((u8 *)node + 4) = tail;
        *(void **)tail = node;
    }
}
