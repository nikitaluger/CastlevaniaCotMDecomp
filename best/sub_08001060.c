void *sub_08001034(void);

struct Node { u32 p0; s16 p4; s16 p6; };

extern u8 D_02021EA8[];

s32 sub_08001060(s32 arg0, void *arg1) {
    u8 *base8 = D_02021EA8;
    struct Node *base = (struct Node *)base8;
    u8 *hdr;
    u8 *ptab;
    s32 ret = 0;
    struct Node *new;
    struct Node *cur;
    struct Node *prev;
    s32 k;

    new = sub_08001034();
    if (new == 0) return -1;
    new->p4 = arg0;
    new->p0 = (u32)arg1;
    hdr = base8;
    hdr -= 0x18;
    *(u32 *)hdr |= 0x40000000;
    ptab = base8 + 0x100;
    cur = *(struct Node **)(ptab + *(u16 *)(hdr + 0xC) * 4);
    if (cur != 0) {
        k = cur->p4;
        if (arg0 <= k) {
            if (arg0 == k) goto block_15;
            new->p6 = ((s32)cur - (s32)base) >> 3;
            *(struct Node **)(ptab + *(u16 *)(hdr + 0xC) * 4) = new;
            return 0;
        }
        prev = cur;
        if (cur->p6 != -1) {
            if (k <= arg0) {
loop_9:
                prev = cur;
                cur = (struct Node *)((u8 *)base + prev->p6 * 8);
                if (cur->p6 != -1) {
                    if (cur->p4 > arg0) goto block_11;
                    goto loop_9;
                }
            } else {
block_11:
                if (cur->p6 != -1) cur = prev;
            }
        }
        if (cur->p4 != arg0) {
            new->p6 = cur->p6;
            cur->p6 = ((s32)new - (s32)base) >> 3;
            goto done;
        }
block_15:
        new->p0 = 0;
        ret = cur->p0;
        cur->p0 = (u32)arg1;
    } else {
        new->p6 = 0xFFFF;
        *(struct Node **)(ptab + *(u16 *)(hdr + 0xC) * 4) = new;
    }
done:
    return ret;
}
