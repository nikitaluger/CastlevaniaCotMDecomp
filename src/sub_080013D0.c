extern u32 D_02025B7C;
extern u32 D_02025B78;
extern u32 D_02025B74;
extern u16 D_02025750[];

/* Reset the object pool: clear the 0x212-entry u16 table at D_02025750,
 * clear the first word of every 0xBC-byte record between the pool start
 * and end, then mark the used range as empty. */
void sub_080013D0(void) {
    u32 zero;
    u32 *poolStartPtr;
    u32 *poolEndPtr;
    u32 *poolUsedPtr;
    u16 *table;
    u32 count;
    u32 first;
    u32 *endPtr;
    u32 slot;
    poolStartPtr = &D_02025B7C;
    poolEndPtr = &D_02025B78;
    poolUsedPtr = &D_02025B74;
    zero = 0;
    table = D_02025750;
    count = 0x212;
    do { *table++ = zero; count--; } while (count != 0);
    first = *poolStartPtr;
    endPtr = poolEndPtr;
    if (first < *endPtr) {
        slot = first;
        do { *(u32 *)slot = 0; slot += 0xBC; } while (slot < *endPtr);
    }
    *poolUsedPtr = *poolStartPtr;
}
