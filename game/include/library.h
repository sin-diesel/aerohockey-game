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

#define PORT 54000
#define PING 10 //ms
#define PINGSERVER 10