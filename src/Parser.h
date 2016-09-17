#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <sstream>
#include "SceneConfiguration.h"

class Parser
{
public:
    static SceneConfiguration parse(const std::string &fileName);
    static bool readvals (std::stringstream &s, int numvals, float *values);
};

#endif // PARSER_H
