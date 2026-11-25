extern void sub_0801604C(void *);

struct S8F5BC_a1 { u16 f0; u16 f2; u8 pad4[0x10]; u32 f14; };
struct S8F5BC_r3 { u16 pad0; u16 f2; u8 pad4[0x3A]; u32 f3c; };

/* Movement collision handling: when the mover's collision flags and speed are
 * set and the collision object at +0x3C allows it, mark its field +0x40 and set
 * status bits 0x200 (and 0x400 when bit 0 is set), then apply the movement. */
void sub_0808F5BC(void *arg0, struct S8F5BC_a1 *a1) {
    struct S8F5BC_r3 *collision;
    u8 *field34;
    collision = *(struct S8F5BC_r3 **)((u8 *)arg0 + 0x3C);
    field34 = (u8 *)collision + 0x34;
    if ((a1->f2 & 6) && a1->f14 != 0 && (a1->f0 & 2) && (collision->f2 & 0x104)) {
        *(u32 *)(field34 + 0xC) = 1;
        a1->f2 = (u16)(a1->f2 | 0x200);
    }
    if (a1->f2 & 1) {
        a1->f2 = (u16)(a1->f2 | 0x400);
    }
    sub_0801604C(a1);
}
