extern void sub_080C31E4(void *, void *, s32);
void *createChildObject(void *arg, s32 size);

struct S {
    u8 pad[0x608];
    void *children[8];
    void *firstChild;
    void *secondChild;
    void *thirdChild;
};

/* Spawn ten child objects for the owner: one primary, eight numbered slots,
 * and two extras. Tag each child with its kind and slot index, then invoke
 * the owner's callback. */
void sub_0800A030(void *owner)
{
    struct S *mgr;
    void *a;
    void *b;
    void *c;
    void *d;
    u32 i;
    u32 zero;
    s32 *lit;

    mgr = *(struct S **)(owner + 0x3C);
    a = createChildObject(owner, 0x18);
    mgr->firstChild = a;
    *(u8 *)(a + 0x3C) = 0;
    i = 0;
loop:
    b = createChildObject(owner, 0x18);
    mgr->children[i] = b;
    *(u8 *)(b + 0x3C) = 1;
    *(u8 *)(mgr->children[i] + 0x44) = i;
    i = i + 1;
    if ((u32)i <= 7)
        goto loop;
    c = createChildObject(owner, 0x18);
    mgr->secondChild = c;
    *(u8 *)(c + 0x3C) = (zero = 0, 2);
    d = createChildObject(owner, 0x18);
    mgr->thirdChild = d;
    *(u8 *)(d + 0x3C) = 3;
    *(u8 *)(owner + (s32)(*(s16 *)(owner + 0x22)) * 2 + 0x19) = zero;
    lit = (s32 *)0x08671BB0;
    sub_080C31E4(owner + 0x18, owner + 0x22, *lit);
}
