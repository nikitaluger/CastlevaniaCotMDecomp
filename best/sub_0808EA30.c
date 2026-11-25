extern void sub_080C31E0(void *, void *);
extern void sub_0808EA70(void);

void sub_0808EA30(void *self) {
    u32 c800 = 0x800;
    void *p = *(void **)(*(u8 **)((u8 *)self + 0x28) + 0x38);
    if (p == 0) {
        sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
    } else {
        u32 result;
        u16 zero = 0;
        *(u16 *)((u8 *)p + 4) = 0x100;
        *(u16 *)((u8 *)*(void **)(*(u8 **)((u8 *)self + 0x28) + 0x38) + 6) = 0x100;
        result = c800 | *(u16 *)((u8 *)self + 2);
        *(u16 *)((u8 *)self + 2) = (u16)result;
        *(u16 *)((u8 *)self + 0x22) = zero;
        *(void **)((u8 *)self + 0x14) = sub_0808EA70;
    }
}
