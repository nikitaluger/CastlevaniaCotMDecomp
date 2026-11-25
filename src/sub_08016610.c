struct S_020279D0 { u8 _0x0[2]; u16 count; void *head; };
extern struct S_020279D0 D_020279D0;

void sub_08016AAC(void *); /* release an object's memory */
void sub_08016B24(void *); /* unregister an object from the keyed list */

/* Remove every object of the given type from the active-object list: for each
 * matching entry, unregister its payload, release the payload, unlink and clear
 * the entry, and decrement the list count. */
void sub_08016610(s32 arg0) {
    u8 *cur = (u8 *)D_020279D0.head;
    u8 *prev = NULL;
    void *payload;

    if (cur != NULL) {
        do {
            payload = *(void **)(cur + 0);
            if (*(s32 *)((u8 *)payload + 4) != arg0) {
                prev = cur;
            } else {
                sub_08016B24(payload);
                sub_08016AAC(*(void **)(cur + 0));
                if (prev == NULL) {
                    D_020279D0.head = *(void **)(cur + 4);
                } else {
                    *(void **)(prev + 4) = *(void **)(cur + 4);
                }
                *(u32 *)(cur + 0) = 0;
                *(u32 *)(cur + 4) = 0;
                D_020279D0.count = D_020279D0.count - 1;
            }
            cur = *(u8 **)(cur + 4);
        } while (cur != NULL);
    }
}
