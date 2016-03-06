[![Stories ready](https://badge.waffle.io/msecret/space-gun.svg?label=ready&title=Open)](http://waffle.io/msecret/space-gun)

# space-gun
A game built using SDL.

## Development
1. Install SDL libraries
2. Install Box2d
3. Install googletest and googlemock
4. Build and execute tests: `make test`
5. Build project: `make`

### Install Box2d
Ensure `glut` and `glfw` are installed as dev dependencies.

Clone the latest version of Box2d from the github repository:

```
git clone git@github.com:erincatto/Box2D.git
```

Check out the 2.3.1 tag, just in case there are newer changes on HEAD:

```
git checkout tags/v2.3.1 -b v2.3.1
```

Download the latest version of premake4

```
wget http://sourceforge.net/projects/premake/files/Premake/4.4/premake-4.4-beta5-linux.tar.gz/download
```

(Optional) Place premake4 in a binary file location on your system

```
sudo cp premake4 /usr/bin
```

Go into the Box2D repository and then the Box2D directory.

```
cd /path/to/Box2D/Box2D
```

Run premake4 with your desired configuration (I'm using gmake)

```
premake4 gmake
```

Go into the Build directory

```
cd Build/
```

Edit the Makefile to remove building the TestBed

```
vim gmake/Makefile
# Remove TestBed from PROJECTS
```

Build the project

```
make config=debug
```

Move the resulting library file into a correct place on your system(or project directory)

```
sudo cp gmake/bin/Debug/libBox2D.a /usr/lib
```

