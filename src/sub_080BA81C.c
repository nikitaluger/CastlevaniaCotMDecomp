/*
 * Depth sort step: take the actor's X/Y depth bands from the player's
 * position, store the band's world X/Y in the work object, and set the linked
 * subject's sprite priority to front, per band, or back.
 */
extern u32 D_08102ED4[];  /* world X of each depth band */
extern u32 D_08102EE0[];  /* world Y of each depth band */
void sub_080988B8(void *subject, u32 worldX);
u32 sub_080BE8D4(void);  /* the player's X depth band */
u32 sub_080BE938(void);  /* the player's Y depth band */

void sub_080BA81C(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *layer = work + 0x48;  /* depth record: X band +0x5C, Y band +0x60, sort layer +0x64 */
    u8 *subject = *(u8 **)((u8 *)arg0 + 0x4C);
    u32 snappedX;
    u32 band;

    *(u32 *)(layer + 0x5C) = sub_080BE8D4();
    *(u32 *)(layer + 0x60) = sub_080BE938();

    snappedX = D_08102ED4[*(u32 *)(layer + 0x5C)];
    *(u32 *)(work + 0x08) = snappedX;
    *(u32 *)(work + 0x0C) = D_08102EE0[*(u32 *)(layer + 0x60)];

    band = *(u32 *)(layer + 0x5C);
    switch (band) {
    case 0:
        {
            u8 *p = subject + 0x35;  /* sprite priority: 1 front, 0xFF back */
            u32 zero;
            zero = 0;
            *p = 1;
            *(u32 *)(layer + 0x64) = zero;
        }
        break;
    case 1:
        sub_080988B8(subject, snappedX);
        *(u32 *)(layer + 0x64) = 1;
        break;
    case 2:
        {
            u8 *p = subject + 0x35;
            *p = 0xFF;
            *(u32 *)(layer + 0x64) = 0;
        }
        break;
    }
}
