#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"

//main facet constructer 
VoronoiFacet::VoronoiFacet(int _voronoifacetlabel,
                           int _sidenodes[],
                           vector<int> _polyvoronoivertices
                           )
{
voronoifacetlabel=_voronoifacetlabel; 

polyvoronoivertices.resize(_polyvoronoivertices.size()); 
for(int i=0;i<_polyvoronoivertices.size();i++)
polyvoronoivertices[i]=_polyvoronoivertices[i];

for(int i=0;i<2;i++)
sidenodes[i]=_sidenodes[i];

facetborder=0; 
}


VoronoiFacet& VoronoiFacet::operator=(const VoronoiFacet& _VF)
{
if(this!=&_VF)
{
voronoifacetlabel=_VF.voronoifacetlabel; 
for(int i=0;i<2;i++)
sidenodes[i]=_VF.sidenodes[i]; 
for(int i=0;i<polyvoronoivertices.size();i++)
polyvoronoivertices[i]=_VF.polyvoronoivertices[i];

facetborder=_VF.facetborder; 
}
return* this; 
}





//can:START DEFINITIONS OF SET FUNCTIONS OF VORONOIFACET
void VoronoiFacet::Set_facetborder(int _facetborder)
{
facetborder=_facetborder;
}
//can:END DEFINITIONS OF SET FUNCTIONS OF VORONOIFACET



//can:START DEFINITIONS OF GET FUNCTIONS OF VORONOIFACET
vector<int> VoronoiFacet::Get_polyvoronoivertices()
{
return polyvoronoivertices;
}

int VoronoiFacet::Get_facetborder()
{
return facetborder; 
}

ublas::c_vector<double,3> VoronoiFacet::Get_facetcentroid()
{
return facetcentroid;
}


int* VoronoiFacet::Get_sidenodes()
{
return sidenodes;
}
//can:END DEFINITIONS OF GET FUNCTIONS OF VORONOIFACET



//can: START DEFINITIONS OF CALCULATE FUNCTIONS OF VORONOIFACET
void VoronoiFacet::Calculate_FacetProperties(vector<VoronoiVertex*> VoronoiVertices,
                                             vector<Node*> Nodes)
{
facetarea=0.0; 
int numberoftriangles=polyvoronoivertices.size()-2; 

for(int n=0;n<3;n++)
{
facetcentroid[n]=0.0; 
facetleftnormal[n]=0.0; 
}

//calculating the facet area, and assigning an arbitrary normal...
for(int t=0;t<numberoftriangles;t++)
{
int index1=(t+1);
int index2=(t+2);
double currentarea=0.0; 
ublas::c_vector<double,3> v1;
ublas::c_vector<double,3> v2;
ublas::c_vector<double,3> v1crossv2;
ublas::c_vector<double,3> currentcentroid; 
v1=VoronoiVertices[polyvoronoivertices[0]]->Get_Vertex_X()-VoronoiVertices[polyvoronoivertices[index1]]->Get_Vertex_X();
v2=VoronoiVertices[polyvoronoivertices[index1]]->Get_Vertex_X()-VoronoiVertices[polyvoronoivertices[index2]]->Get_Vertex_X();
v1crossv2=cross(v1,v2); 
facetleftnormal=v1crossv2; 
currentarea=len(v1crossv2)*0.5;
facetarea=facetarea+currentarea;
currentcentroid=(VoronoiVertices[polyvoronoivertices[0]]->Get_Vertex_X()+
                 VoronoiVertices[polyvoronoivertices[index1]]->Get_Vertex_X()+
                 VoronoiVertices[polyvoronoivertices[index2]]->Get_Vertex_X())/3.0;
facetcentroid=facetcentroid+currentcentroid*currentarea; 
}
if(facetarea!=0.0)
facetcentroid=facetcentroid/facetarea; 
double normnormal=len(facetleftnormal);
facetleftnormal=facetleftnormal/normnormal; 

ublas::c_vector<double,3> node_to_centroid; 
node_to_centroid=facetcentroid-Nodes[sidenodes[0]]->Get_X(); 
if(prec_inner_prod(node_to_centroid,facetleftnormal)>0.0)
facetleftnormal=facetleftnormal*facetarea; 
else
facetleftnormal=-facetleftnormal*facetarea; 
}
//can: END DEFINITIONS OF CALCULATE FUNCTIONS OF VORONOIFACET