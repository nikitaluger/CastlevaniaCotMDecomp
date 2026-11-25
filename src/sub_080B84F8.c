s32 sub_0808EA0C(void *parent);
void sub_080C31E0(void *entity, s32 callback);

/* If the entity has no kind-0x20E child, run its per-entity cleanup callback. */
void sub_080B84F8(void *entity) {
    if (sub_0808EA0C(entity) == 0) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
