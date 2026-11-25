void sub_08058978(void *arg0, void *arg1) {
    void *var_r3;
    var_r3 = (void *)0x080CFD60;
    if ((u32)(u16)(*(u16 *)((u8 *)arg0 + 0x28) - 4) <= 3U) {
        var_r3 = (void *)0x080CFD68;
    }
    *(u16 *)((u8 *)*(void *volatile *)((u8 *)arg1 + 0x28) + 6) = *(u16 *)((u8 *)var_r3 + 0);
    *(u16 *)((u8 *)*(void *volatile *)((u8 *)arg1 + 0x28) + 8) = *(u16 *)((u8 *)var_r3 + 2);
    *(u16 *)((u8 *)*(void *volatile *)((u8 *)arg1 + 0x28) + 0xA) = *(u16 *)((u8 *)var_r3 + 4);
    *(u16 *)((u8 *)*(void *volatile *)((u8 *)arg1 + 0x28) + 0xC) = *(u16 *)((u8 *)var_r3 + 6);
}
