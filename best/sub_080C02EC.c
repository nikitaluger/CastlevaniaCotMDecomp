extern void sub_080C02B0(void);
extern void sub_080C02CC(s32 a, void *arg1);

void sub_080C02EC(s32 a, void *arg1) {
    sub_080C02CC(a, arg1);
    if (*(u8 *)((u8 *)arg1 + 0x17) == 0) {
        sub_080C02B0();
    }
}
