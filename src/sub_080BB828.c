extern void sub_08014588(s32, void *);
extern u8 D_08102E18[];

/* Chooses one of three pose tables from the source's state, then copies the
 * table's six 8-byte records into the owner and its five linked slots. */
void sub_080BB828(u8 *source, u8 *owner, s32 *slots) {
    s32 *slotList = slots;
    s32 tableIndex = 1;
    u8 state = *(u8 *)(source + 0x24);
    u8 *p;
    s32 *cursor;
    u32 i;
    s32 off;
    s32 first;

    switch (state) {
    case 2: case 3: case 4: case 5: case 6:
        if (*(u8 *)(source + 0x25) == 0) goto set2;
        if (*(u8 *)(source + 0x25) == 2) goto set0;
        goto end;
    case 1:
        if (*(u8 *)(source + 0x25) == 0) goto set2;
        if (*(u8 *)(source + 0x25) != 2) goto end;
        goto set0;
    default: goto end;
    }
set2:
    tableIndex = 2;
    goto end;
set0:
    tableIndex = 0;
end:
    first = *(s32 *)(owner + 0x28);
    off = tableIndex * 0x30;
    sub_08014588(first, D_08102E18 + off);
    i = 0;
    p = D_08102E18 + off + 8;
    cursor = slotList;
    for (; i <= 4; i++) {
        sub_08014588(*cursor++, p);
        p += 8;
    }
}
