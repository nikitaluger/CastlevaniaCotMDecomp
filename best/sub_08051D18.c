void sub_08051D18(void *arg0, void *arg1) {
    if ((*(u16 *)arg1 & 1) == 0) {
        if (*(u16 *)((u8 *)arg0 + 0x28) == 2) {
            *((u8 *)*(void **)((u8 *)arg1 + 0x28) + 1) = 1;
        } else {
            *((u8 *)*(void **)((u8 *)arg1 + 0x28) + 1) = 5;
        }
    }
}
