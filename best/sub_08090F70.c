struct S908_C { u8 _0[6]; u16 idx; };
struct S908_A { u8 _0[4]; struct S908_C *c; };
struct S908_B { u8 _0[0xAC]; struct S908_A *a; };
struct S908_E { u8 _0[8]; };

extern u8 D_02025368[];
extern struct S908_E D_08100470[], D_08100480[], D_08100490[], D_081004A0[];
extern struct S908_E D_081004C0[], D_081004C8[], D_081004E8[], D_081004F8[];
extern struct S908_E D_08100518[], D_08100540[], D_08100550[], D_08100570[];
extern struct S908_E D_08100578[], D_081005A0[];

u32 sub_08090F70(struct S908_B *arg)
{
    u32 result;
    u8 *selp = &D_02025368[0x94];
    struct S908_A *a = arg->a;
    switch (*selp) {
    case 0: result = (u32)&D_08100470[a->c->idx]; break;
    case 1: result = (u32)&D_08100480[a->c->idx]; break;
    case 2: result = (u32)&D_08100490[a->c->idx]; break;
    case 3: result = (u32)&D_081004A0[a->c->idx]; break;
    case 4: result = (u32)&D_081004C0[a->c->idx]; break;
    case 5: result = (u32)&D_081004C8[a->c->idx]; break;
    case 6: result = (u32)&D_081004E8[a->c->idx]; break;
    case 7: result = (u32)&D_081004F8[a->c->idx]; break;
    case 8: result = (u32)&D_08100518[a->c->idx]; break;
    case 9: result = (u32)&D_08100540[a->c->idx]; break;
    case 10: result = (u32)&D_08100550[a->c->idx]; break;
    case 11: result = (u32)&D_08100570[a->c->idx]; break;
    case 12: result = (u32)&D_08100578[a->c->idx]; break;
    case 13: result = (u32)&D_081005A0[a->c->idx]; break;
    }
    return result;
}
