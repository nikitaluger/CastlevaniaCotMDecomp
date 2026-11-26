struct S_020279D0 { u8 _0x0[2]; u16 count; u8 _0x4[2]; void *head; };
extern struct S_020279D0 D_020279D0;

s32 sub_08016598(void *key, u16 value);
void sub_08016AAC(void *);
void sub_08016B24(void *);

/* Look up/create the registry data for `key` with the new value, then cache the
 * returned data pointer on the child state held at key+0x3C (field +0x30). */
s32 registerScriptObject(void *key, u16 value) {
    void *state = *(void **)((u8 *)key + 0x3C);
    return *(s32 *)((u8 *)state + 0x30) = sub_08016598(key, value);
}

void sub_08016610(s32 arg0) {
    u8 *prev;
    u8 *cur;
    void *n;

    if (D_020279D0.head != NULL) {
        prev = NULL;
        cur = (u8 *)D_020279D0.head;
        do {
            n = *(void **)(cur + 0);
            if (*(s32 *)((u8 *)n + 4) != arg0) {
                prev = cur;
            } else {
                sub_08016B24(n);
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

void sub_08016518(void) {
    u32 *p = (u32 *)0x020202B8;
    if (*p != (u32)0x020202B8) {
        do {
            p = (u32 *)*p;
        } while (*p != (u32)0x020202B8);
    }
}
