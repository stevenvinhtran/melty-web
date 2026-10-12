# melty-web

A browser-native WebAssembly port of *Melty Blood Actress Again Current Code* (MBAACC v1.07 Rev 1.4.0) running in the browser via an x86-to-WebAssembly compatibility layer.

---

## Architecture Overview

The repository is organized into the following components:

- **`wine-assembly/`**: The browser runtime engine, linked as a Git submodule to our custom fork [`stevenvinhtran/wine-assembly`](https://github.com/stevenvinhtran/wine-assembly) (derived from upstream [Wine-Assembly / `vgrichina/berrry-wine`](https://github.com/vgrichina/berrry-wine)). It translates Windows x86 PE binaries and Win32/DirectX APIs into WebAssembly, WebGL, and Web Audio.
- **`net/`**: WebRTC peer-to-peer transport layer and network adapters for rollback netcode.
- **`assets/`**: Asset descriptors and game bundle manifests. Proprietary game assets (`assets/raw/`) are excluded from version control.
- **`docs/`**: Technical documentation:
  - [docs/CHANGES_TO_UPSTREAM.md](docs/CHANGES_TO_UPSTREAM.md): Full breakdown of all engine enhancements made to base Wine-Assembly.
  - [docs/P2P_NETPLAY_PLAN.md](docs/P2P_NETPLAY_PLAN.md): Architecture and roadmap for WebRTC P2P rollback netplay.

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
- **Game Files**: You must supply your own copy of *Melty Blood Actress Again Current Code* (MBAACC v1.07). Proprietary game archives and binaries (`0000.p`–`0006.p`, `MBAA.exe`, etc.) are not distributed with this repository.

### Setting Up Game Assets
Place your legally acquired MBAACC installation into `assets/raw/MBAACC/` (or symlink it to `wine-assembly/binaries/mbaa`):
```bash
mkdir -p assets/raw/MBAACC
# Copy your MBAACC installation files (MBAA.exe, *.p, *.dat, etc.) into assets/raw/MBAACC/
```

### Running Locally
1. Start the local development server:
   ```bash
   cd wine-assembly
   node tools/dev-server.js
   ```
2. Open `http://127.0.0.1:8080/` in your browser.
3. Select **Melty Blood Actress Again Current Code** from the application catalog.
