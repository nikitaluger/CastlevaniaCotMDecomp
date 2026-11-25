extern void sub_08002C74(void);
typedef void (*Fn)(void);

/* Switch the object over to the main per-frame update handler (sub_08002C74),
 * advance one script step, then run that handler for this frame. */
void sub_08002C5C(void *obj)
{
    Fn fp = sub_08002C74;
    *(Fn *)((u8 *)obj + 0x14) = fp;
    *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) + 1;
    fp();
}
