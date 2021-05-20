#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <experimental/filesystem>
#include <vector>
#include <stdio.h>
#include <sys/utsname.h>
#include <math.h>

#define PORT 54000
#define PING 10 //ms
#define PINGSERVER 10

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080

#define NOCHOICE 0
#define MOUSE 1
#define KEYBOARD 2
#define PLAY 3
#define QUIT 4

