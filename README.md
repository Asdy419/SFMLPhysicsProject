# Kinemechanics

A physics simulator built with SFML covering projectile motion and elastic/inelastic collisions.

## Features

- Projectile motion simulator with step-by-step kinematic equation solving
- Elastic and inelastic collision simulator
- Save and load simulation states to `.txt` files

## Requirements

- [CMake](https://cmake.org/download/) 3.16 or newer
- [Visual Studio 2022](https://visualstudio.microsoft.com/) with the **Desktop development with C++** workload
- [Git](https://git-scm.com/) (used by CMake to fetch SFML automatically)

> SFML is downloaded and compiled automatically — no manual installation needed.

## Building

```bash
git clone https://github.com/your-username/SFMLPhysicsProject.git
cd SFMLPhysicsProject

cmake --preset default
cmake --build --preset debug
```

The executable will be at `build/Debug/Kinemechanics.exe`.

> The first build will take a few minutes as SFML is compiled from source. Subsequent builds are fast.

### Alternative (manual CMake)

```bash
cmake -B build -A x64
cmake --build build --config Debug
```

## Running

You can run the executable directly from `build/Debug/`. Assets are automatically copied there during the build step, so no extra setup is needed.

Simulation saves are stored as `.txt` files in the same directory as the executable.

## Project Structure

```
SFMLPhysicsProject/
├── CMakeLists.txt              # Build configuration
├── Kinemechanics assets/       # Images and fonts
│   ├── Menu/
│   ├── Collisions/
│   └── Projectile motion/
└── SFMLPhysicsProject/         # Source code
    ├── main.cpp
    ├── StatesManager.cpp/.h    # Main simulation logic
    ├── Button.cpp/.h           # Input button component
    └── CheckBox.cpp/.h         # Checkbox component
```
