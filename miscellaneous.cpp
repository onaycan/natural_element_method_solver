#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"


//can:START DECLERATIONS OF CALCULATE FUNCTIONS OF MISCELLANEOUS
double Calculate_tetrahedravolume(double _Coord[])
{
double volume=0.0; 
double currentdet; 
double M[3][3];

M[0][0]=_Coord[3];
M[0][1]=_Coord[6];
M[0][2]=_Coord[9];
M[1][0]=_Coord[4];
M[1][1]=_Coord[7];
M[1][2]=_Coord[10];
M[2][0]=_Coord[5];
M[2][1]=_Coord[8];
M[2][2]=_Coord[11];
Matrixdet(M,currentdet);
volume=volume+currentdet; 
currentdet=0.0; 

M[0][0]=_Coord[0];
M[0][1]=_Coord[6];
M[0][2]=_Coord[9];
M[1][0]=_Coord[1];
M[1][1]=_Coord[7];
M[1][2]=_Coord[10];
M[2][0]=_Coord[2];
M[2][1]=_Coord[8];
M[2][2]=_Coord[11];
Matrixdet(M,currentdet);
volume=volume-currentdet; 
currentdet=0.0; 

M[0][0]=_Coord[0];
M[0][1]=_Coord[3];
M[0][2]=_Coord[9];
M[1][0]=_Coord[1];
M[1][1]=_Coord[4];
M[1][2]=_Coord[10];
M[2][0]=_Coord[2];
M[2][1]=_Coord[5];
M[2][2]=_Coord[11];
Matrixdet(M,currentdet);
volume=volume+currentdet; 
currentdet=0.0; 

M[0][0]=_Coord[0];
M[0][1]=_Coord[3];
M[0][2]=_Coord[6];
M[1][0]=_Coord[1];
M[1][1]=_Coord[4];
M[1][2]=_Coord[7];
M[2][0]=_Coord[2];
M[2][1]=_Coord[5];
M[2][2]=_Coord[8];
Matrixdet(M,currentdet);
volume=volume-currentdet; 
currentdet=0.0; 


volume=fabs(volume)/6.0;
return volume; 

}


int InsideOutside_tetrahedra_simple(vector<Node*> &Nodes, 
                                    Delaunay *_tetrahedra,
                                    ublas::c_vector<double,3> _normal,
                                    int corner)
{
int result=0; 
int c=0; 
while(c<4)
{
if(corner==_tetrahedra->Get_delaunaynodes()[c])
{
    ublas::c_vector<double,3> mid; 
    ublas::c_vector<double,3> midtocorner; 
    mid=(Nodes[_tetrahedra->Get_delaunaynodes()[(c+1)%4]]->Get_X()+
         Nodes[_tetrahedra->Get_delaunaynodes()[(c+2)%4]]->Get_X()+
         Nodes[_tetrahedra->Get_delaunaynodes()[(c+3)%4]]->Get_X())/3.0;
    midtocorner=Nodes[_tetrahedra->Get_delaunaynodes()[c]]->Get_X()-mid; 
if(inner_prod(midtocorner,_normal)<0.0)
result=1; 
break; 
}
c++; 
}
return result;
}



//can:END DECLERATIONS OF CALCULATE FUNCTIONS OF MISCELLANEOUS