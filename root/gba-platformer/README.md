# GBA Platformer

A from-scratch GBA homebrew platformer, built entirely through GitHub
Actions - no local toolchain needed.

## How the build works

Both workflows run inside devkitPro's official `devkitpro/devkitarm`
Docker image, which already has the toolchain installed - no install step
needed. (An earlier version of this used the `apt.devkitpro.org` pacman
installer script directly on the runner; devkitPro's own docs ask you not
to do that in CI - it's unreliable for automated requests - and to use
the Docker images instead. This project does that from the start now.)

- **`.github/workflows/build.yml`** - runs on every push/PR to `main` (and
  can be triggered manually from the Actions tab). Builds `platformer.gba`
  and uploads it as a workflow artifact.
- **`.github/workflows/release.yml`** - runs when you push a tag like
  `v1.0.0`. Builds the ROM and attaches it to a GitHub Release. Prefer this
  for grabbing a copy on your phone - artifacts expire after 90 days,
  Release assets don't.

To cut a release: tag and push, e.g. from the GitHub web/mobile UI's tag
creation flow, or `git tag v1.0.0 && git push origin v1.0.0`.

## Testing the ROM

Download `platformer.gba` from the Actions artifact or Release, and open
it in any GBA emulator (including your own mGBA-based build). Controls:
D-pad to move, A to jump.

## Project structure

```
source/
  main.c          - game loop: init, then poll/update/draw each frame
  engine/         - hardware layer. Nothing outside this folder touches
                    a register or VRAM address directly.
    video.h/.c    - display mode, BG tiles/map, OAM sprites, vblank wait
    input.h/.c    - key polling with held/pressed/released edge detection
    fixed.h       - Q8.8 fixed-point math (no FPU on GBA)
  game/           - game logic, hardware-agnostic
    entity.h      - generic Entity struct + update/draw function pointers
    player.h/.c   - player input, jump, and rendering
    physics.h/.c  - gravity + axis-separated tile collision
    level.h/.c    - tilemap data and solidity queries
    camera.h/.c   - follow + clamp to level bounds
```

The split between `engine/` (hardware) and `game/` (logic) is deliberate:
`game/` code never sees a register address, so you can add new entity
types, levels, or even port the logic to a different platform without
touching `engine/`.

## Current scope (v1)

- One screen-block level (32x32 tiles, 256x256px) - fits in a single BG
  regsize-0 background, so no tile-streaming complexity yet.
- 8x8 solid-color placeholder tiles/sprite - proves the pipeline without
  needing an art asset pipeline yet.
- Movement, gravity, jump, tile collision, camera follow+clamp.

## Extending it

- **Real art**: devkitPro's `grit` tool converts PNGs to tile/palette C
  data at build time. Add PNGs under a `gfx/` folder, a `.grit` config per
  image, and a Makefile rule to run `grit` before compiling; swap the
  `video_upload_bg_tile`/`video_upload_obj_tile` calls in `main.c` for the
  generated data.
- **Bigger levels**: bump to BG regsize 1 (64x32 tiles) or add horizontal
  tile streaming so you're not limited to one screen block.
- **More entities**: give each new type its own `update`/`draw` pair
  matching `EntityUpdateFn`/`EntityDrawFn` in `entity.h` - enemies,
  collectibles, etc. all slot into the same loop as the player.

## A note on this first build

This was written without a local devkitARM install to compile against, so
the very first GitHub Actions run is the first real compile. If it fails,
paste the build log back and it's a quick fix - the architecture (engine/
vs game/ split, entity system, collision) is the part worth getting right;
register-level typos are cheap to patch.
