#include "team.h"

team::team()
{
}

int team::start()
{
    return ((rand()%2)+1);
}