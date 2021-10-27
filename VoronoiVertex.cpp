#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"

//can:Main constructer of the voronoi vertex 
VoronoiVertex::VoronoiVertex(int _voronoivertexlabel,ublas::c_vector<double,3> _Vertex_X)
{
voronoivertexlabel=_voronoivertexlabel,
Vertex_X=_Vertex_X;
}


//copy assignment 
VoronoiVertex& VoronoiVertex::operator =(const VoronoiVertex &_VV) 
{
if(this!=&_VV)
{
voronoivertexlabel=_VV.voronoivertexlabel; 
Vertex_X=_VV.Vertex_X; 
}
return* this; 
}


//can:START DEFINITIONS OF GET FUNCTIONS OF VORONOIVERTEX
int VoronoiVertex::Get_voronoivertexlabel()
{
return voronoivertexlabel;
}

ublas::c_vector<double,3> VoronoiVertex::Get_Vertex_X()
{
return Vertex_X; 
}
//can:END DEFINITIONS OF GET FUNCTIONS OF VORONOIVERTEX