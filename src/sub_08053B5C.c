struct S_02025FF0 { u8 _[0x18C2]; u16 flag; };
extern struct S_02025FF0 gMainWorkspace;
s32 setAnimationFrame(void *, s32, s32, s32);
s32 signOf(s32);
s32 sub_08016238(void *);
s32 sub_0808DBF8(s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* When the scripted entity lands a hit, play the hit effect, set its hit
 * graphic and facing flag, clear the script timer and dispatch the callback. */
void sub_08053B5C(void *script) {
    void *sprite;
    void *body;
    void *anim;
    void *extra;
    u8 zero;
    s32 side;
    sprite = *(void **)((u8 *)script + 0x38);
    body = *(void **)((u8 *)script + 0x3C);
    anim = (void *)((s32)body + 0x34);
    extra = (void *)(0x48 + (s32)body);
    *(u8 *)((u8 *)*(void **)((u8 *)body + 0x28) + 1) = 4;
    setAnimationFrame(sprite, (void *)anim, 0, 1);
    if (sub_08016238(*(void **)((u8 *)body + 0x28)) != 0) {
        setAnimationFrame(sprite, (void *)anim, 4, 0);
        sub_0808DBF8(*(s32 *)((u8 *)body + 8), *(s32 *)((u8 *)body + 0xC), 0xD);
        *(u16 *)((u8 *)sprite + 0) = *(u16 *)((u8 *)sprite + 0) | gMainWorkspace.flag;
        *(s32 *)((u8 *)sprite + 0x1C) = 0x8000000A;
        side = signOf(*(s32 *)((u8 *)body + 8));
        *(u16 *)((u8 *)sprite + 2) = side > 0
            ? (*(u16 *)((u8 *)sprite + 2) | 0x10)
            : (*(u16 *)((u8 *)sprite + 2) & 0xFFEF);
        zero = 0;
        *(u16 *)((u8 *)extra + 6) = 0x1E;
        *(u8 *)((u8 *)script + (*(s16 *)((u8 *)script + 0x22)) * 2 + 0x19) = zero;
        {
            s32 *nv = (s32 *)0x08671BB0;
            sub_080C31E4(script + 0x18, script + 0x22, *nv);
        }
    }
}
