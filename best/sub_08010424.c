extern u8 D_02025358[];
void sub_08010424(void) {
    u8 v = D_02025358[0xC];
    u8 n = v + 1;
    if (v > 3) n = 1;
    D_02025358[0xC] = n;
}
