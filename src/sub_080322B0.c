/* Table of four 4-u16 parameter sets, one per sprite state. */
extern u16 D_080CEBB0[];

/* Picks the state-specific set of four u16 values from D_080CEBB0 (keyed by the
 * sprite's state at +0x28) and writes them into the sprite definition at
 * enemy+0x28 (fields +6/+8/+A/+C); for unknown states it also clears bit 0 of
 * that definition's flag byte at +1. */
void sub_080322B0(void *sprite, void *enemy)
{
    u16 *params = D_080CEBB0;

    switch (*(u16 *)((u8 *)sprite + 0x28)) {
    case 0x2E:
        break;
    case 0x2F:
        params += 4;
        break;
    case 0x32:
        params += 8;
        break;
    case 0x38:
        params += 12;
        break;
    default:
    {
        u8 *flagByte = *(u8 **)((u8 *)enemy + 0x28);
        flagByte[1] &= 0xFE;
        break;
    }
    }
    *(u16 *)((u8 *)*(void *volatile *)((u8 *)enemy + 0x28) + 0x06) = params[0];
    *(u16 *)((u8 *)*(void *volatile *)((u8 *)enemy + 0x28) + 0x08) = params[1];
    *(u16 *)((u8 *)*(void *volatile *)((u8 *)enemy + 0x28) + 0x0A) = params[2];
    *(u16 *)((u8 *)*(void *volatile *)((u8 *)enemy + 0x28) + 0x0C) = params[3];
}
