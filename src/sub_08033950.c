extern void copyPoseAttrs(void *, void *);

/* Copy a four-halfword attribute record from the table at 0x080CEC8C into the
 * object held at arg1+0x28. The record is chosen from the id at arg0+0x28:
 * ids 0x43..0x47 map to records 1..5, everything else uses record 0. */
void sub_08033950(void *arg0, void *arg1) {
    u16 id;
    u32 idIndex;
    u32 recordIndex;
    u32 dest;

    recordIndex = 0;
    id = *(u16 *)((u8 *)arg0 + 0x28);
    idIndex = id - 0x43;
    if (idIndex <= 4) {
        switch (idIndex) {
            case 0: recordIndex = 1; break;
            case 1: recordIndex = 2; break;
            case 2: recordIndex = 3; break;
            case 3: recordIndex = 4; break;
            case 4: recordIndex = 5; break;
        }
    }
    dest = *(u32 *)((u8 *)arg1 + 0x28);
    copyPoseAttrs((void *)dest, (void *)(0x080CEC8C + recordIndex * 8));
}
