extern u8 D_02021E90[];

/* Advance the expanding-window effect: bump its frame counter, recompute the
 * four edges of the window around its fixed centre (a short window in mode 4,
 * a tall one otherwise), and clear the active flag once the counter hits 0x10. */
void sub_0806111C(void) {
    D_02021E90[0x145E] = D_02021E90[0x145E] + 1;
    if (D_02021E90[0x145F] == 4) {
        D_02021E90[0x1460] = 0x20 - D_02021E90[0x145E] * 2;
        D_02021E90[0x1464] = 0x28 - D_02021E90[0x145E] * 2;
        D_02021E90[0x1462] = D_02021E90[0x145E] * 2 + 0x20;
        D_02021E90[0x1466] = D_02021E90[0x145E] * 2 + 0x28;
    } else {
        D_02021E90[0x1460] = 0x20 - D_02021E90[0x145E] * 2;
        D_02021E90[0x1464] = 0x78 - D_02021E90[0x145E] * 2;
        D_02021E90[0x1462] = D_02021E90[0x145E] * 2 + 0x20;
        D_02021E90[0x1466] = D_02021E90[0x145E] * 2 + 0x78;
    }
    D_02021E90[0x1468] = 0x3F;
    if (D_02021E90[0x145E] == 0x10) {
        D_02021E90[0x145D] = 0;
    }
}
