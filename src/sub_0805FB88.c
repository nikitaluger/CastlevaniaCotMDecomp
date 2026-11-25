extern void sub_08002D7C(void *);

/* Hide the entity's sprite (OAM mode 2, 4bpp), return its pool slot to the
 * free counter at 0x020279E4, then destroy the entity and its children. */
void sub_0805FB88(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u16 *oamAttr = *(u16 **)(self + 0xAC);
    *oamAttr = (*oamAttr & 0xFFF6) | 2;
    *(vu16 *)0x020279E4 += 1;
    sub_08002D7C(arg0);
}
