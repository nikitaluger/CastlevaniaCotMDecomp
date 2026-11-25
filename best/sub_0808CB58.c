extern u8 D_02025368[];

u8 sub_0808CB58(void) {
    u8 r2;
    s32 r1;
    s32 r0;

    r2 = D_02025368[0x94];
    r1 = r2 << 8;
    r0 = D_02025368[0x95];
    r1 = r1 + r0;
    r0 = 0x711;
    if (r1 == r0) goto set3;
    if (r1 > r0) goto big;
    r0 = 0x504;
    if (r1 < r0) goto end;
    r0 = r0 + 1; /* 0x505 */
    if (r1 <= r0) goto set3;
    r0 = r0 + 0x11; /* 0x516 */
    if (r1 > r0) goto end;
    r0 = r0 - 2; /* 0x514 */
    if (r1 < r0) goto end;
    goto set3;

big:
    r0 = 0x90F;
    if (r1 == r0) goto set2;
    if (r1 > r0) goto bigger;
    r0 = r0 - 1; /* 0x90E */
    if (r1 == r0) goto set6;
    goto end;

bigger:
    r0 = 0xA1;
    r0 = r0 << 4; /* 0xA10 */
    if (r1 == r0) goto set2;
    r0 = r0 + 0xF0; /* 0xB00 */
    if (r1 != r0) goto end;
    /* fallthrough set3? target: bne end, so if equal fallthrough to set3? Actually after cmp, bne end; then next is set3 label */
set3:
    r2 = 3;
    goto end;

set6:
    r2 = 6;
    goto end;

set2:
    r2 = 2;
    /* fallthrough */
end:
    return r2;
}
