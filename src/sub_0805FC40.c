extern void sub_08061F38(void);
extern void sub_0805FCFC(void);
extern void sub_080C31E0(void *, void *);
extern void sub_0805FC70(void);

/* Read the u16 at p+offset with bit 0x800 forced on. */
static inline u16 withFlag800(s8 *p, int offset) {
    return (u16)(0x800 | (*((u16 *)(p + offset))));
}

/* Initialise an object: set flag 0x800, install sub_0805FC70 as its update
 * handler at +0x14, set the slot index at +0x22 to 1, then register it. */
void sub_0805FC40(void *arg0) {
    s8 *self;
    sub_08061F38();
    self = (s8 *)arg0;
    sub_0805FCFC();
    *((u16 *)(((s8 *)arg0) + 2)) = withFlag800(self, 2);
    *((void **)(((s8 *)arg0) + 0x14)) = (void *)sub_0805FC70;
    *((s16 *)(((s8 *)arg0) + 0x22)) = 1;
    sub_080C31E0(arg0, (void *)sub_0805FC70);
}
