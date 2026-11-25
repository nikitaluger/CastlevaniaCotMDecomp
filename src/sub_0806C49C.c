extern void sub_0806A7AC(void *obj, void *work, s32 form);

struct WorkArea {
    u8 _0[0x78];
    s32 f78;
    s32 f7C;
    s32 f80;
};

/* Clear the work area's cached fields at 0x78/0x7C/0x80, then re-init the
 * entity's form from the definition tables with form index 0. */
void sub_0806C49C(void *obj, void *work) {
    struct WorkArea *w = (struct WorkArea *)work;
    u8 *p;
    w->f7C = 0;
    w->f78 = 0;
    p = (u8 *)w;
    p += 0x80;
    *(s32 *)p = 0;
    sub_0806A7AC(obj, work, 0);
}
