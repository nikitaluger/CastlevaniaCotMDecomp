extern void sub_080C25B8(s32*,void*);
extern void *sub_080C2634(void*,void*,void*);
extern s32 sub_080C2500(void*);

/* Software floating-point subtraction: unpack both binary32 bit patterns into
 * their four-word parts, flip the right operand's sign, add and repack. */
s32 sub_080C27DC(s32 lhs, s32 rhs) {
    s32 a, b;
    u32 lhsParts[4], rhsParts[4], sumParts[4];
    a = lhs; b = rhs;
    sub_080C25B8(&a, lhsParts);
    sub_080C25B8(&b, rhsParts);
    rhsParts[1] ^= 1;
    return sub_080C2500(sub_080C2634(lhsParts, rhsParts, sumParts));
}
