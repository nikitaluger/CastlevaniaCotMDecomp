struct S_16A2C { u8 pad[8]; void *field8; };
s32 sub_08016A2C(void) {
    void *head;
    void *next;
    s32 ret;
    head = *(void **)0x02020BD0;
    if (head == NULL) {
        ret = 0;
    } else {
        next = *(void **)((u8 *)head + 4);
        *(void **)0x02020BD0 = next;
        if (next == NULL)
            *(void **)0x02020BD0 = ((struct S_16A2C *)0x020279D0)->field8;
        ret = *(s32 *)head;
    }
    return ret;
}
