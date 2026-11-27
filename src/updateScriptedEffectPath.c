/* Advance one scripted effect through its path-driven state machine: wait for
 * the target to come into camera range, steer it with a base+velocity path,
 * keep its animation ticking, then sway it vertically and snap it to a fixed
 * X velocity before finishing. Returns 1 on the last step, 0 otherwise. */
extern s32 fixedPointDistance(s32, s32);
extern void advanceMotion(void *, s32);
extern void stepAnimationTimer(s32, s32, void *, s32, s32);
extern void randomizeAnimationDelay(void *, s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern s32 gTrigFuncTable[];
extern struct PathFxWorkspace gMainWorkspace;

s32 updateScriptedEffectPath(struct PathFxOwner *owner, struct PathFxMotion *target,
                             struct PathFxScript *script, s32 sprite, s32 status,
                             struct PathFxPoint *path, s32 pathFromTable) {
    s32 finished = 0;
    s32 step;
    s32 displacement;

    switch (script->phase) {
    case PATHFX_PHASE_APPROACH:
        if (pathFromTable == 0) {
            s32 distance = fixedPointDistance(gMainWorkspace.camX - target->x,
                                              gMainWorkspace.camY - target->y);
            if (distance <= PATHFX_APPROACH_RANGE) {
                struct PathFxChild *child;
                script->phase = script->phase + 1;
                child = (struct PathFxChild *)owner->child;
                if (child != NULL) {
                    do {
                        child->active = 1;
                        child = (struct PathFxChild *)child->next;
                    } while (child != NULL);
                }
            }
        } else {
            if (((struct PathFxChild *)owner)->active != 0) {
                script->phase = PATHFX_PHASE_MOVE;
            }
        }
        break;
    case PATHFX_PHASE_MOVE:
        stepAnimationTimer(sprite, status, script, 4, 4);
        displacement = path->velX * script->step;
        target->vx = path->baseX + displacement;
        displacement = path->velY * script->step;
        target->vy = path->baseY + displacement;
        advanceMotion(target, 0);
        step = script->step + 1;
        script->step = step;
        if (step == PATHFX_MOVE_LAST_STEP) {
            script->phase = script->phase + 1;
            script->step = 0;
            script->savedY = target->y;
            randomizeAnimationDelay(script, 0xC, 8);
        }
        break;
    case PATHFX_PHASE_HOLD:
        stepAnimationTimer(sprite, status, script, 0xC, 8);
        step = script->step + 1;
        script->step = step;
        if (step == PATHFX_HOLD_LAST_STEP) {
            script->phase = script->phase + 1;
            script->step = 0;
        }
        break;
    case PATHFX_PHASE_SWAY:
        stepAnimationTimer(sprite, status, script, 0xC, 8);
        {
            s32 *trigFunc;
            trigFunc = gTrigFuncTable;
            target->y = script->savedY + (sub_080C31E0(script->step << PATHFX_SWAY_ANGLE_SHIFT, *trigFunc) * 2);
        }
        step = script->step + 1;
        script->step = step;
        if (step == PATHFX_SWAY_LAST_STEP) {
            s32 zero;
            finished = 1;
            zero = 0;
            script->phase = zero;
            script->step = zero;
            target->vx = PATHFX_FINAL_X;
            target->vy = zero;
        }
        break;
    }
    return finished;
}
