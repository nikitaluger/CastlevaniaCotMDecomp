extern s16 D_020279E8;

s32 sub_0808FC10(void) {
    u16 v = (u16)D_020279E8;
    if (v >= 15) return -1;
    switch (v) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    case 4:
    case 5: return 3;
    case 6: return 4;
    case 10: return 5;
    case 12: return 6;
    case 13: return 7;
    case 14: return 8;
    default: return -1;
    }
}
