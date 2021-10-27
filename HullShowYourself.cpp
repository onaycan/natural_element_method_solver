#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"


void Hull::Hull_ShowYourself(string outputtype)
{
Hull_GiD_delaunaymesh();
Hull_GiD_voronoimesh();
if(outputtype=="static")
Hull_GiD_delaunaypost_static();
//if(outputtype=="dynamic")
//Hull_GiDdelaunayfile_post<<"GiD Post Results File 1.0"<<endl; 
}

void Hull::Hull_GiD_delaunaymesh()
{

int current_label;
double current_X; 

if(Hull_name[Hull_name.size()-5]=='N')
Hull_GiDdelaunayfile<<"MESH "<<Hull_name<<"delaunay dimension 3 ElemType Tetrahedra  Nnode 4"<<endl; 
if(Hull_name[Hull_name.size()-5]=='G')
Hull_GiDdelaunayfile<<"MESH "<<Hull_name<<"delaunay dimension 3 ElemType Point  Nnode 1"<<endl; 


Hull_GiDdelaunayfile<<"Coordinates"<<endl; 

for(int n=0;n<Hull_Nodes.size();n++)
{
current_label=Hull_Nodes[n]->Get_nodelabel()+1; 
Hull_GiDdelaunayfile<<current_label<<'\t'; 

for(int c=0;c<3;c++)
{
current_X=Hull_Nodes[n]->Get_X()[c];
Hull_GiDdelaunayfile<<current_X<<'\t';
}
Hull_GiDdelaunayfile<<0<<endl; 
}
Hull_GiDdelaunayfile<<"End Coordinates"<<endl;

if(Hull_name[Hull_name.size()-5]=='N')
{
Hull_GiDdelaunayfile<<"Elements"<<endl; 

int feasible_d=1; 
for(int d=0;d<Hull_Delaunays.size();d++)
{
if(Hull_Delaunays[d]->Get_delaunayfeasibility()==1)
if(Hull_Delaunays[d]->Get_delaunayfeatured()==0)
{
Hull_GiDdelaunayfile<<feasible_d<<'\t'; 
for(int c=0;c<4;c++)
{
current_label=Hull_Delaunays[d]->Get_delaunaynodes()[c]+1; 
Hull_GiDdelaunayfile<<current_label<<'\t';
}
Hull_GiDdelaunayfile<<endl; 
feasible_d++; 
}
}
Hull_GiDdelaunayfile<<"End Elements"<<endl; 
}

if(Hull_name[Hull_name.size()-5]=='G')
{
Hull_GiDdelaunayfile<<"Elements"<<endl; 
for(int n=0;n<Hull_Nodes.size();n++)
{
current_label=Hull_Nodes[n]->Get_nodelabel()+1; 
Hull_GiDdelaunayfile<<current_label<<'\t'<<current_label<<endl; 
}
Hull_GiDdelaunayfile<<"End Elements"<<endl; 
}


}



void Hull::Hull_GiD_delaunaypost_static()
{
Hull_GiDdelaunayfile_post<<"GiD Post Results File 1.0"<<endl; 


//can: scalar results 
Hull_GiDdelaunayfile_post<<"Result nodeborder Time_step ";
Hull_GiDdelaunayfile_post<<0<<" Scalar OnNodes"<<endl; 
Hull_GiDdelaunayfile_post<<"Values"<<endl; 
for(int n=0;n<Hull_Nodes.size();n++)
{
int current_label=Hull_Nodes[n]->Get_nodelabel()+1; 
int current_bordery=(Hull_Nodes[n]->Get_nodeborder()); 
Hull_GiDdelaunayfile_post<<current_label<<'\t'<<current_bordery<<endl;
}
Hull_GiDdelaunayfile_post<<"End Values"<<endl; 

Hull_GiDdelaunayfile_post<<"Result bsec Time_step ";
Hull_GiDdelaunayfile_post<<0<<" Scalar OnNodes"<<endl; 
Hull_GiDdelaunayfile_post<<"Values"<<endl; 
for(int n=0;n<Hull_Nodes.size();n++)
{
int current_label=Hull_Nodes[n]->Get_nodelabel()+1; 
int current_bsec=(Hull_Nodes[n]->Get_bsec()); 
Hull_GiDdelaunayfile_post<<current_label<<'\t'<<current_bsec<<endl;
}
Hull_GiDdelaunayfile_post<<"End Values"<<endl; 



Hull_GiDdelaunayfile_post<<"Result nodal/gaussian Time_step ";
Hull_GiDdelaunayfile_post<<0<<" Scalar OnNodes"<<endl; 
Hull_GiDdelaunayfile_post<<"Values"<<endl; 
for(int n=0;n<Hull_Nodes.size();n++)
{
int current_label=Hull_Nodes[n]->Get_nodelabel()+1; 
int current_nodalgaussian=(Hull_Nodes[n]->Get_nodalyesgaussionno()); 
Hull_GiDdelaunayfile_post<<current_label<<'\t'<<current_nodalgaussian<<endl;
}
Hull_GiDdelaunayfile_post<<"End Values"<<endl; 



//can: vectoral results
Hull_GiDdelaunayfile_post<<"Result NodeNormals Time_step ";
Hull_GiDdelaunayfile_post<<"0 "<<" Vector OnNodes"<<endl; 
Hull_GiDdelaunayfile_post<<"Values"<<endl; 

for(int n=0;n<Hull_Nodes.size();n++)
{
ublas::c_vector<double,3> current_nodenormals=Hull_Nodes[n]->Get_nodenormal(); 
int current_label=Hull_Nodes[n]->Get_nodelabel()+1; 
Hull_GiDdelaunayfile_post<<current_label<<'\t';
Hull_GiDdelaunayfile_post<<current_nodenormals[0]<<'\t';
Hull_GiDdelaunayfile_post<<current_nodenormals[1]<<'\t';
Hull_GiDdelaunayfile_post<<current_nodenormals[2]<<endl;
}
Hull_GiDdelaunayfile_post<<"End Values"<<endl; 

}



void Hull::Hull_GiD_voronoimesh()
{

int current_label;
ublas::c_vector<double,3> current_X; 

Hull_GiDvoronoifile<<"MESH "<<Hull_name<<"voronoi dimension 3 ElemType Linear Nnode 2"<<endl; 
Hull_GiDvoronoifile<<"Coordinates"<<endl; 


for(int vv=0;vv<Hull_VoronoiVertices.size();vv++)
{
current_label=Hull_VoronoiVertices[vv]->Get_voronoivertexlabel()+Hull_nonodes_original+1;
current_X=Hull_VoronoiVertices[vv]->Get_Vertex_X();
Hull_GiDvoronoifile<<current_label<<'\t';
Hull_GiDvoronoifile<<current_X[0]<<'\t';
Hull_GiDvoronoifile<<current_X[1]<<'\t';
Hull_GiDvoronoifile<<current_X[2]<<endl;
}
      
Hull_GiDvoronoifile<<"End Coordinates"<<endl;


Hull_GiDvoronoifile<<"Elements"<<endl; 
int lastelementlabel;
if(Hull_name[Hull_name.size()-5]=='N')
lastelementlabel=Hull_nodelaunays;
if(Hull_name[Hull_name.size()-5]=='G')
lastelementlabel=Hull_nonodes_original;

for(int f=0;f<Hull_nofacets;f++)
{
    int current_polyvoronoivertices=Hull_VoronoiFacets[f]->Get_polyvoronoivertices().size();
    for(int fv=0;fv<current_polyvoronoivertices;fv++)
    {
Hull_GiDvoronoifile<<lastelementlabel<<'\t';
int left=fv; 
int right=(fv+1)%current_polyvoronoivertices;
Hull_GiDvoronoifile<<Hull_VoronoiFacets[f]->Get_polyvoronoivertices()[left]+Hull_nonodes_original+1<<'\t';
Hull_GiDvoronoifile<<Hull_VoronoiFacets[f]->Get_polyvoronoivertices()[right]+Hull_nonodes_original+1<<endl;
lastelementlabel++; 
    }

}
Hull_GiDvoronoifile<<"End Elements"<<endl; 
}
