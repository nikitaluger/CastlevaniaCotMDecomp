extern void sub_080C31E0(void *, void *);
extern void sub_0808EA70(void);

typedef struct { u16 v; } Field_u16;
typedef struct { u8 * v; } Field_u8;
typedef struct { void * v; } Field_void;
void sub_0808EA30(void *self) {
    u32 c800 = 0x800;
    void *p = *(void **)((((Field_u8 *) ((u8 *)self + 0x28))->v) + 0x38);
    if (p == 0) {
        sub_080C31E0(self, (((Field_void *) ((u8 *)self + 0x24))->v));
    } else {
        u32 result;
        u16 zero = 0;
        (((Field_u16 *) ((u8 *)p + 4))->v) = 0x100;
        *(u16 *)((u8 *)*(void **)((((Field_u8 *) ((u8 *)self + 0x28))->v) + 0x38) + 6) = 0x100;
        result = 0x800 | (((Field_u16 *) ((u8 *)self + 2))->v);
        (((Field_u16 *) ((u8 *)self + 2))->v) = (u16)result;
        (((Field_u16 *) ((u8 *)self + 0x22))->v) = zero;
        (((Field_void *) ((u8 *)self + 0x14))->v) = sub_0808EA70;
    }
}
