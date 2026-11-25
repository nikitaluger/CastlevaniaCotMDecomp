extern void sub_0808DBF8(s32 x, s32 y, s32 id); /* spawn an effect entity */
extern void sub_08051D3C(void *actor, void *buf, u16 frame, s32 mode);
extern void sub_08051F98(void *actor, void *state, s32 c, s32 d, s32 e);

/* Afterimage command: stop the actor's sprite, spawn effect 0x202 just below
 * the actor, clear the afterimage timer, build the trail buffer and start the
 * 6/8 trail configuration before running the next command. */
void sub_08050FC8(u8 *arg0)
{
    u8 *work = *(u8 **)(arg0 + 0x3C);
    u8 *trail = work + 0x48;
    u8 *sprite = *(u8 **)(work + 0x28);
    s32 zero = 0;
    sprite[1] = 0;
    sub_0808DBF8(*(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0x80000, 8);
    *(u16 *)trail = 0;
    sub_08051D3C(arg0, work + 0xF0, 0, 0);
    sub_08051F98(arg0, trail, 6, 8, zero);
}
