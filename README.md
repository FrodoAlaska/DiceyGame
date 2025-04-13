# Play Dice With Me, Will Ya?
Play dice in an immersive 3D world and go against unique opponents each with their own challenges. 

## Dependencies 

- [Nikola](https://github.com/FrodoAlaska/Nikola.git)

## Build Instructions

This game uses CMake so it should be easy to configure and build. First, however, the repo should be cloned.

```bash
git clone --recursive https://github.com/FrodoAlaska/DiceyGame.git
```

Make sure to pass the `--recursive` flag since this repo uses submodules to manage its dependencies. After that, we can build the game normally. 

```bash
mkdir build 
cd build 

cmake .. 
cmake --build . 
```

The commands above should clone the repo and its dependencies, create a build directory, generate some helpful CMake files, build everything for you, and then create a `dice_will_ya` executable that can be used as you wish. 
