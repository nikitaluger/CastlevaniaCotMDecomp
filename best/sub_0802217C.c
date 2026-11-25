void sub_0802217C(void *arg0) {
    s32 var_r3;
    void **var_r2;
    void *temp_r1;

    var_r2 = (void **)((u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x58);
    var_r3 = 2;
    do {
        temp_r1 = *var_r2;
        if (temp_r1 != NULL) {
            *(u16 *)((u8 *)temp_r1 + 0x6C) |= 2;
            *var_r2 = NULL;
        }
        var_r2++;
        var_r3--;
    } while (var_r3 >= 0);
}
