#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"

//can: START DEFINITIONS OF GET FUNCTIONS OF THE HULL


int Hull::Hull_Get_Hull_nonodes_original()
{
return Hull_nonodes_original;
}

int Hull::Hull_Get_Hull_nonodes()
{
return Hull_nonodes;
}

int Hull::Hull_Get_Hull_nofacets()
{
return Hull_nofacets; 
}

double Hull::Get_featuringtolerance()
{
return featuringtolerance;
}

vector<Node*> Hull::Hull_Get_Hull_Nodes()
{
return Hull_Nodes; 
}

vector<VoronoiFacet*> Hull::Hull_Get_Hull_VoronoiFacets()
{
return Hull_VoronoiFacets;
}


//can: END DEFINITIONS OF GET FUNCTIONS OF THE HULL