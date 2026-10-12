# Modifications to Wine-Assembly (Upstream Library)

This document tracks all custom modifications made to the imported [Wine-Assembly (`berrry-wine`)](https://github.com/vgrichina/berrry-wine) engine to support *Melty Blood Actress Again Current Code* (MBAACC).

- **Upstream Repository**: `https://github.com/vgrichina/berrry-wine`
- **Upstream Base Commit**: `64fdf6993b60004b16405bb06de9c3be46264e23`

---

## Overview of Changes

To run MBAACC in the browser, changes were required across five subsystems:
1. **Virtual Filesystem (VFS) & Overlapped I/O** (Resolving multi-threaded asset streaming failures)
2. **Direct3D 9 & WebGL Graphics** (Supporting fighting game texture formats & shaders)
3. **Thread Management & Cooperative Scheduling** (Audio and worker thread scheduling)
4. **GDI & Font Outline Rasterization** (Menu text rendering)
5. **Win32 Runtime & Application Launch Profile** (Launch configuration and missing API stubs)

---

## Detailed File Modifications

### 1. Virtual Filesystem & Overlapped I/O
- **`lib/filesystem.js`**:
  - **Isolated Positional Reads (`VirtualFS.readFileAt`)**: Added a dedicated positional read path that reads strictly by offset without mutating or rewinding the shared file cursor `fh.pos`. Previously, `fs_read_file_at` temporarily mutated `fh.pos` inside a `try/finally` block. When an HTTP Range request missed the cache and yielded (`997 ERROR_IO_PENDING`), the `finally` block restored the cursor prematurely, causing subsequent retries to read incorrect data or fail.
  - **Positional Retry & Fault Isolation**: Added `_posRetries` and `_posFaults` maps keyed by `${handle}:${offset}` so concurrent threads reading from the same `.p` pack files (`0002.p`, `0005.p`) do not overwrite each other's retry records.
  - **Progressive Scatter Resumption**: Updated `io._readProgress` in `fs_read_file_at` to resume multi-chunk positional reads cleanly upon network fill completion.
  - **EOF & Result Reporting**: Conformed `fs_read_file_at` to report `ERROR_HANDLE_EOF (38)` when reading at or past EOF, and write bytes read to `*lpBytesRead` / `OVERLAPPED.InternalHigh`.
- **`src/09a7d-handlers-shell-file.wat`**:
  - **`handle_ReadFile` OVERLAPPED Branch**: Updated to handle `OVERLAPPED` reads via `host_fs_read_file_at`. On lazy chunk cache miss (`997`), parks the thread with `call $io_block (i32.const 0)` without popping the stdcall frame, allowing seamless re-execution once the range lands.
  - **`handle_GetOverlappedResult`**: Reports transferred byte count from `OVERLAPPED.InternalHigh` and returns `TRUE`.

### 2. Direct3D 9 & WebGL Rendering
- **`lib/d3d9-host.js`**:
  - Expanded texture creation format validation to handle 2D fighting game sprite formats, including paletted (`D3DFMT_P8 = 41`) and alpha-only (`D3DFMT_A8 = 28`) formats.
- **`src/09ad-handlers-d3d9.wat` & `src/09ae-d3d9-resources.wat`**:
  - Implemented texture surface pitch calculations and texel byte widths for 8-bit alpha/paletted surfaces.
  - Added support for flexible vertex format (FVF) declarations with pre-transformed vertices (`D3DFVF_XYZRHW`).

### 3. Thread Management & Scheduling
- **`lib/thread-manager.js`**:
  - Added audio thread classification and slice budgeting to prioritize DirectSound BGM streaming worker threads.
  - Connected `_fillIoRead` to handle lazy VFS range filling asynchronously during thread yields.

### 4. GDI & TrueType Font Rasterization
- **`src/10b-gdi-font.wat` & `src/10c-truetype.wat`**:
  - Improved font outline retrieval in `GetGlyphOutlineA` for menu text rendering.

### 5. Application Launch Profile & Win32 API Stubs
- **`lib/apps.js`**:
  - Added the `mbaa` application entry, specifying command-line flags, memory configuration, and archive mounts (`0000.p` through `0006.p`).
- **`lib/dll-registry.js`**:
  - Added registration stub for `reg.dll` used by MBAACC's anti-tamper / configuration checks.
- **`src/api_table.json`, `src/01b-api-hashes.generated.wat`, `src/09b2-dispatch-table.generated.wat`**:
  - Generated export hashes and dispatch stubs for 32 additional Win32 APIs queried by `MBAA.exe` during startup and input processing.
