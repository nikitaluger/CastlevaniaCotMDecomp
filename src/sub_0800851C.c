/* Bump the 32-bit counter at +4 and set the 32-bit state/id field at +8 to
 * the fixed value 0x5D9F. */
void sub_0800851C(void *arg0) {
    u8 *obj = (u8 *)arg0;
    *(s32 *)(obj + 4) = (s32)(*(s32 *)(obj + 4) + 1);
    *(s32 *)(obj + 8) = 0x5D9F;
}
