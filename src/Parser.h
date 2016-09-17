#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "SceneConfiguration.h"

class Parser
{
public:
    static SceneConfiguration parse(const std::string &fileName);
};

#endif // PARSER_H
