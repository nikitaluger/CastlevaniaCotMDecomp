/* Returns 1 if p points into the pool of 0x2C-byte entity records, else 0. */
#define gEntityPool (*(u32 *)0x03002E34)
#define gEntityPoolCount (*(s32 *)0x03002694)

s32 sub_080035AC(u32 p) {
    s32 inPool;
    u32 base;

    inPool = 0;
    base = gEntityPool;
    if ((base <= p) && (p < (u32) (base + (0x2C * gEntityPoolCount)))) {
        inPool = 1;
    }
    return inPool;
}
