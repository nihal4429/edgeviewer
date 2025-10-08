# Android + OpenCV (C++) + OpenGL ES + Web (TypeScript) — Edge Viewer

This is a **ready-to-code** project for the assessment:
- Android app that captures camera frames (Camera2), sends them to **C++ via JNI**, processes with **OpenCV** (Canny / grayscale), and renders with **OpenGL ES 2.0** as a texture.
- A minimal **TypeScript** web viewer that displays a static processed frame & updates simple stats.

> **Note:** To fully enable OpenCV C++ processing, install the **OpenCV Android SDK** and set `OpenCV_DIR` before building. Without it, the native code falls back to a simple grayscale (no Canny).

## Quick Start

### Prerequisites
- Android Studio (latest), Android SDK, **NDK**, CMake, LLDB
- OpenCV Android SDK (download `opencv-4.x-android-sdk.zip` from opencv.org)
- Node.js (for the web viewer), TypeScript

### Android: How to run
1. Download and unzip OpenCV Android SDK (e.g., `OpenCV-android-sdk` folder).
2. In **Android Studio**, open the `android/` folder (this Gradle project).
3. In **File > Settings > Build Tools > CMake** ensure CMake is installed.
4. Set the environment variable `OpenCV_DIR` to point to the SDK's `sdk/native/jni` folder. For example:
   - Windows (PowerShell):
     ```powershell
     $env:OpenCV_DIR="C:\path\to\OpenCV-android-sdk\sdk\native\jni"
    
5. Sync Gradle. Build & run on a real device.
6. Grant camera permission when prompted.
7. Use the toggle button to switch between **Raw** and **Edges**; FPS is shown on-screen.

### Web viewer
```bash
cd web
npm install
npm run build
# Serve index.html (e.g., with VS Code Live Server or `npx http-server`)
```
Open `index.html` in a browser; it displays a sample processed frame (base64) and updates stats.

## Project Layout
```
/android        # Android app (Kotlin + OpenGL + NDK/JNI + C++)
  app/src/main/cpp          # C++ native code (OpenCV hook)
  app/src/main/java/...     # Camera2, GL renderer, JNI bridge
  app/src/main/res/raw      # GLSL shaders
/web            # TypeScript minimal viewer
```

## How it works (Android)
- **Camera2Helper** acquires frames in **NV21** (YUV) format.
- **NativeProcessor** calls `native processFrame()` passing the byte array + width/height.
- In C++, we **convert NV21 → BGR**, apply **Canny** (if OpenCV available), else fallback to **grayscale**.
- Output is an 8-bit single-channel image returned to Kotlin.
- **GLRenderer** uploads this as a **LUMINANCE**-like texture and renders a full-screen quad (ES 2.0).

## Troubleshooting
- **Linker/OpenCV errors**: ensure `OpenCV_DIR` points to `.../sdk/native/jni`, then *Invalidate Caches & Restart* in Android Studio.
- If your device preview is rotated: tweak `Camera2Helper`’s rotation or texture coords in `GLRenderer`.
- If FPS < 10–15: lower the preview size in `Camera2Helper` or reduce processing cost.

## License
MIT (for this template). OpenCV is licensed separately (BSD-style); follow its license when distributing.




<img width="1919" height="1025" alt="Screenshot 2025-10-08 024750" src="https://github.com/user-attachments/assets/44660222-8852-4e34-b010-9386f73450e0" />


![WhatsApp Image 2025-10-08 at 17 59 42_c14b6877](https://github.com/user-attachments/assets/52d8bfbf-7ce9-4ef7-962f-aa66a8832ab7)
![WhatsApp Image 2025-10-08 at 17 58 59_33a70494](https://github.com/user-attachments/assets/e7cb0510-a6cd-44f0-a038-25e2fbbb8cdb)


