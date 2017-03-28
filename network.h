#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <boost/algorithm/string.hpp>

#include <boost/asio.hpp>

int download(const char *server, const char *path, std::string &data);
std::string makeURLSafe(std::string s);