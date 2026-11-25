void sub_080C31E0(void *obj, void *func);
extern s32 D_020213D8;

/* When no damage-number effect is active, mark the object active (flag 0x800),
 * install its state handler and enter state 1 by invoking the handler. */
void sub_0808D858(void *obj)
{
  s32 flags;
  if (D_020213D8 == 0)
  {
    flags = 0x800 | (*(u16 *) (((s8 *) obj) + 2));
    *((u16 *) (((s8 *) obj) + 2)) = (u16) flags;
    *((void **) (((s8 *) obj) + 0x14)) = (void *)0x0808D88D;
    *((s16 *) (((s8 *) obj) + 0x22)) = 1;
    sub_080C31E0(obj, (void *)0x0808D88D);
  }
}
