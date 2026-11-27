extern s32 checkGlobalStateChange(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void stepDelayTimer(void *, void *);
extern void cullOffscreenEntity(void *, void *);
extern void sub_080C31E0(void *, void *);

struct S_02025FF0 {
    u8 _0[0x10];
    u32 f10;
    u8 _14[0x14ED - 0x14];
    u8 f14ED;
    u8 _14EE[0x173A - 0x14EE];
    u8 f173A;
};
extern struct S_02025FF0 gMainWorkspace;

struct S_inner { u8 _0[4]; u16 f04; u16 f06; };
struct S_arg0 {
    u8 _0[0x24];
    void *fallbackScript;
    u8 _28[0x10];
    struct S_inner *child;
    u8 _3C[0x30];
    u32 work;
};

/* Advance a script step's child actor: after capacity and sprite-range checks,
 * bump both of its display fields by 0x40, set its position from the work data
 * and tick the work timer, then abort on bad global state or validate bounds. */
void sub_0807BB2C(struct S_arg0 *actor) {
    u32 work;
    u8 *position;
    struct S_inner *child;
    struct S_02025FF0 *globals;

    work = actor->work;
    position = (u8 *)(work + 4);
    child = actor->child;
    if (checkGlobalStateChange(actor, child, position) != 0) goto end;
    if ((s16)child->f04 > 0x3FF) goto fail;
    child->f04 += 0x40;
    child->f06 += 0x40;
    sub_0806D588(child, position);
    stepDelayTimer((u8 *)(work + 0x20), child);
    globals = &gMainWorkspace;
    if (globals->f173A == 0x1C) goto fail;
    if (globals->f14ED != 0) goto ok;
    if (globals->f10 == 0) goto ok;
fail:
    sub_080C31E0(actor, actor->fallbackScript);
    goto end;
ok:
    cullOffscreenEntity(actor, child);
end:;
}
