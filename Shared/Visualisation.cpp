#include "Visualisation.h"

Visualisation::Visualisation() : info(new WindowInfo)
{
}

Visualisation::Visualisation(const WindowInfoPtr infoCopy) : 
    info(infoCopy)
{
}

Visualisation::~Visualisation()
{
}
