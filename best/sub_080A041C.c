u8 sub_080A041C(u8 *arg0) {
    u8 ret;
    if (arg0) {
        ret = arg0[0x7C];
    } else {
        ret = 0;
    }
    return ret;
}

void sub_080A040C(u8 *arg0) {
    if (arg0) {
        arg0[0x7C] = 1;
    }
    return;
}
