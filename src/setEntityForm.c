void sub_0806A7C4(void *, void *, s32);
void sub_0806A800(void *, s32);

/* Set an entity's form from the definition tables: install its graphics and
 * sprite config, then load the matching actor definition into its work state. */
void setEntityForm(void *obj, void *work, s32 form) {
    sub_0806A7C4(obj, work, form);
    sub_0806A800(work, form);
}
