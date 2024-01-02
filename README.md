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


## More details 
You can see more detailed docs on how our games works on this [link](https://r-type-4.gitbook.io/r-type/)

## Core maintainers :sunglasses:

- [Tom DESALMAND] (https://github.com/TomDesalmand) / tom.desalmand@epitech.eu
- [Jules DUTEL](https://github.com/jvlxz) / jules.dutel@epitech.eu
- [Lucas HISSINGER](https://github.com/LucasHissinger) / lucas.hissinger@epitech.eu
- [Dylan WINTER](https://github.com/DylanWTR) / dylan.winter@epitech.eu 
- [Kevin CARTTIGUEANE] (https://github.com/Kcarttigueane) / kevin.carttigueane@epitech.eu

## Troubleshooting :scream:

If you have any problem launching the game, please contact us with at our email address.
