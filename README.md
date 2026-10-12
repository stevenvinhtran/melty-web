# melty-web

A browser-native WebAssembly port of *Melty Blood Actress Again Current Code* (MBAACC v1.07 Rev 1.4.0) running in the browser via an x86-to-WebAssembly compatibility layer.

---

## Architecture Overview

The repository is organized into the following components:

- **`wine-assembly/`**: The browser runtime engine, based on [Wine-Assembly (`berrry-wine`)](https://github.com/vgrichina/berrry-wine). It translates Windows x86 PE binaries and Win32/DirectX APIs into WebAssembly, WebGL, and Web Audio.
- **`src/`**: Native C++ core types and testing scaffolding.
- **`assets/`**: Asset descriptors and game bundle manifests. Proprietary game assets (`assets/raw/`) are excluded from version control.
- **`docs/`**: Technical documentation, including details on modifications made to the upstream runtime engine.

For a detailed breakdown of all changes made to the base Wine-Assembly runtime, see [docs/CHANGES_TO_UPSTREAM.md](docs/CHANGES_TO_UPSTREAM.md).

---

## Known Issues & Roadmap

Active bug reports and performance tracking are documented in the [GitHub Issue Tracker](https://github.com/stevenvinhtran/melty-web/issues):

- [#1: [Bug] Character sprites, stages, and battle visual assets fail to load](https://github.com/stevenvinhtran/melty-web/issues/1)
- [#2: [Bug] DirectSound streaming BGM audio cuts out permanently on scene transitions](https://github.com/stevenvinhtran/melty-web/issues/2)
- [#3: [Performance] Character Select and Options menus suffer significant framerate drops (~20 FPS)](https://github.com/stevenvinhtran/melty-web/issues/3)
- [#4: [Bug] Screen resolution and display mode toggle in Options Menu causes crash/freeze](https://github.com/stevenvinhtran/melty-web/issues/4)

---

## Quick Start

### Prerequisites
- Node.js (v18+)
- Web browser with WebAssembly SIMD and WebGL 2 support (Chrome, Edge, Firefox, or Safari)

### Running Locally
1. Start the local development server:
   ```bash
   cd wine-assembly
   node tools/dev-server.js
   ```
2. Open `http://127.0.0.1:8080/` in your browser.
3. Select **Melty Blood Actress Again Current Code** from the application catalog.
