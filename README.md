# R-TYPE 
![](https://fs-prod-cdn.nintendo-europe.com/media/images/10_share_images/games_15/virtual_console_wii_u_7/H2x1_WiiUVC_RType.jpg)

## Introduction
The R-Type project goal is to reimagine the classic arcade game "R-Type" through modern software engineering practices. At its core, this project is about building a robust, network-capable game from the ground up using advanced C++ programming.
Primary Goals:
- Multithreaded Server-Client Architecture: Develop a sophisticated server-client system capable of handling networked interactions efficiently. This includes implementing a multithreaded server for handling game logic and client requests, along with a dynamic client capable of delivering a rich graphical experience.
- Custom-Built Game Engine: Construct a game engine specifically tailored for "R-Type", showcasing architectural design patterns and optimization strategies ideal for high-performance gaming.
- Innovative Gameplay Mechanics: Integrate advanced gameplay mechanics, supporting 1-4 players, that challenge traditional arcade gaming norms and offer a unique, interactive experience.
- Educational and Collaborative Platform: Create a comprehensive learning platform for developers, illustrating best practices in network programming, game engine architecture, and real-time graphics rendering.
### Key features:
- Networked Multiplayer Gameplay: Allow for seamless multiplayer experiences over the network, with support for up to four players.
- Custom Game Engine: A bespoke engine designed to handle the specific needs and mechanics of "R-Type", providing a blend of performance and flexibility.
- Advanced Graphics and Sound: Modern graphics and sound systems to enhance the user experience, staying true to the game's retro aesthetic while providing a fresh look.
- Cross-Platform Support: Develop the game to be playable on multiple platforms, ensuring a broad audience can enjoy the revitalized game.
- Developer and User Documentation: Comprehensive documentation aimed at assisting developers in understanding the intricate details of the game's development and aiding users in appreciating the technical intricacies of their favorite game.

## Installation Process
**Supported OS** : Windows, Linux

### Linux
Make sure to clone vcpkg at the root of the project via 
``git clone https://github.com/Microsoft/vcpkg.git``
then just launch our script via
``./install.sh``

### Windows
Make sure to install Visual Studio and linux dependencies.
Then just open the project in Visual Studio and wait for Cmake to compile.
You should now be able to click on play button as shown in the image below.
![](https://i.imgur.com/bGniUvu.png)

## Usage
To launch the client just use
``./r_type_client  <address> <port>``
and for the server 
``./r_type_server  <port>``

## Developer quick start
### Prerequises

- [CMake](https://cmake.org/download/) (>= 3.16)
- [Visual Studio](https://visualstudio.microsoft.com/fr/downloads/) (Windows only)
- [vcpkg](https://vcpkg.io/en/getting-started.html)
- [g++](https://gcc.gnu.org/install/)
- [clang](https://clang.llvm.org/get_started.html)
- [git](https://git-scm.com/downloads)

### Setting Up the Development Environment

1. Clone the repository
```bash
git clone https://github.com/your-username/r-type.git
cd r-type
```
2. build with cmake
```bash
mkdir build
cd build
cmake ..
```
3. compile with make
```bash
make
```

### Running the Development Server

```bash
cd server && ./r_type_server <port>
```

### Running the Development Client

```bash
cd client && ./r_type_client <address> <port>
```

### Contributing to the Project
If you wish to contribute to the R-Type project, follow these steps:

1. Fork the project
2. Create a new branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am "Add some feature"`)
4. Push the branch (`git push origin my-new-feature`)
5. Create a new Pull Request

### Additional ressources
For more in-depth information on the project's architecture, code structure, and development guidelines, refer to the [developer documentation](https://r-type-4.gitbook.io/r-type/).

Feel free to reach out to the core maintainers listed below if you have any questions or need assistance during the development process.


## Core maintainers :sunglasses:

- [Tom DESALMAND](https://github.com/TomDesalmand) / tom.desalmand@epitech.eu
- [Jules DUTEL](https://github.com/jvlxz) / jules.dutel@epitech.eu
- [Lucas HISSINGER](https://github.com/LucasHissinger) / lucas.hissinger@epitech.eu
- [Dylan WINTER](https://github.com/DylanWTR) / dylan.winter@epitech.eu 
- [Kevin CARTTIGUEANE](https://github.com/Kcarttigueane) / kevin.carttigueane@epitech.eu

## Troubleshooting :scream:

If you have any problem launching the game, please contact us with at our email address.
