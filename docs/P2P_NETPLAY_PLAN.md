# P2P Netplay Architecture & Implementation Plan

This document outlines the architecture for implementing peer-to-peer (P2P) rollback netplay for *Melty Blood Actress Again Current Code* in the browser.

---

## 1. Background & Protocol Requirements

- **Desktop Standard**: MBAACC netplay is powered by **CCCaster**, an external Win32 wrapper that intercepts game input, state, and Winsock UDP packets (`sendto` / `recvfrom`) to provide rollback netcode between players.
- **Browser Constraints**: Browsers cannot open raw UDP or TCP sockets.
- **Solution**: **WebRTC DataChannels** provide low-latency, peer-to-peer, out-of-order/unreliable binary messaging directly between browser clients—matching UDP semantics.

---

## 2. System Architecture

```
+-------------------------------------------------------------+
|                     Browser Session                         |
|                                                             |
|  +--------------------+        +-------------------------+  |
|  |     MBAA.exe       |        |   CCCaster / Netplay    |  |
|  |  (x86 Executable)  |        |    Input / Rollback     |  |
|  +---------+----------+        +------------+------------+  |
|            |                                |               |
|            v                                v               |
|  +-------------------------------------------------------+  |
|  |               Wine-Assembly Runtime                   |  |
|  | - Win32 Winsock Subsystem (src/09d-winsock.wat)       |  |
|  | - Host Socket Bridge (lib/winsock-host.js)            |  |
|  +---------------------------+---------------------------+  |
|                              |                              |
+------------------------------|------------------------------+
                               v
               +-------------------------------+
               |    WebRTC DataChannel Mesh    |
               | (Peer-to-Peer UDP Emulation)  |
               +---------------+---------------+
                               |
                               v
                     Remote Peer Browser
```

---

## 3. Implementation Phases

### Phase 1: WebRTC Transport Layer (`net/webrtc.js`)
- Implement WebRTC peer connection setup with STUN/TURN traversal.
- Establish an unordered, unreliable data channel (`maxRetransmits: 0`) for frame-by-frame input data (UDP equivalent).
- Establish an ordered, reliable data channel for match handshake, state verification, and chat.
- Create lightweight room-based signaling (WebSocket lobby or manual SDP offer/answer exchange).

### Phase 2: Wine-Assembly Winsock Shim
- Hook into Wine-Assembly's Winsock handlers (`sendto`, `recvfrom`, `select`, `WSAAsyncSelect`).
- Redirect simulated loopback/LAN UDP sockets to WebRTC DataChannel payloads.
- Map virtual IP/port bindings so the guest application communicates transparently without code changes.

### Phase 3: Rollback Synchronization
- Synchronize deterministic game frame ticks with requestAnimationFrame / audio clocks.
- Support input delay buffering (0–2 frames) and speculative frame simulation.
- Frame state snapshots and rollback execution on desynchronization.
