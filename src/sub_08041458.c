extern void sub_080C31F0(void *);
extern void sub_0804148D(void);

/* Copy the parent object's position into both sub-parts, install the follow-up
 * script and run its first step. */
void sub_08041458(void *entity) {
    void *work;
    void *handler;
    u32 i;
    void *parent;
    void *part;
    work = *(void **)((u8 *)entity + 0x3C);
    i = 0;
    handler = (void *)sub_0804148D;
    parent = *(void **)((u8 *)entity + 0x28);
    part = (u8 *)work + 4;
    do {
        *(s32 *)part = *(s32 *)((u8 *)parent + 0x4C);
        *(s32 *)((u8 *)part + 8) = *(s32 *)((u8 *)parent + 0x5C);
        part = (u8 *)part + 4;
        i += 1;
    } while (i <= 1U);
    *(void **)((u8 *)entity + 0x14) = handler;
    *(u16 *)((u8 *)entity + 0x22) = 1;
    sub_080C31F0(entity);
}
