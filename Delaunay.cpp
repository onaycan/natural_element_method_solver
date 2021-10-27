#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"

// main constructer 
Delaunay::Delaunay(int _delaunaylabel,ublas::c_vector<int,4> _delaunaynodes)
{
delaunaylabel=_delaunaylabel;
delaunaynodes=_delaunaynodes;
delaunayfeatured=0;
delaunayfeasibility=1;
}

//copy constructer 
Delaunay::Delaunay(const Delaunay& _D)
{
delaunaylabel=_D.delaunaylabel;
delaunaynodes=_D.delaunaynodes;
delaunayfeatured=_D.delaunayfeatured;
delaunayfeasibility=_D.delaunayfeasibility;
}


//copy assignment 
Delaunay& Delaunay::operator=(const Delaunay& _D)
{
if(this!=&_D)
{
delaunaylabel=_D.delaunaylabel;
delaunaynodes=_D.delaunaynodes;
delaunayfeatured=_D.delaunayfeatured;
delaunayfeasibility=_D.delaunayfeasibility;
}
return* this; 
}

//can:START DEFINITIONS OF SET FUNCTIONS OF DELAUNAY
void Delaunay::Set_delaunayvolume(double _delaunayvolume)
{
delaunayvolume=_delaunayvolume; 
}

void Delaunay::Set_delaunayvolume_calc(double _delaunayvolume_calc)
{
delaunayvolume_calc=_delaunayvolume_calc; 
}

void Delaunay::Set_inversioninfo(int _inversioninfo)
{
inversioninfo=_inversioninfo; 
}

void Delaunay::Set_delaunaygeocenter(ublas::c_vector<double,3> _delaunaygeocenter)
{
delaunaygeocenter=_delaunaygeocenter; 
}

void Delaunay::Set_delaunayorigin(ublas::c_vector<double,3> _delaunayorigin)
{
delaunayorigin=_delaunayorigin;
}

void Delaunay::Set_delaunayradius(double _delaunayradius)
{
delaunayradius=_delaunayradius; 
}

void Delaunay::Set_vertextocenter(double _vertextocenter)
{
vertextocenter=_vertextocenter; 
}

void Delaunay::Set_delaunayfeatured(int _delaunayfeatured)
{
delaunayfeatured=_delaunayfeatured;
}
//can:END DEFINITIONS OF SET FUNCTIONS OF DELAUNAY

//can:START DEFINITIONS OF GET FUNCTIONS OF DELAUNAY
int Delaunay::Get_delaunayfeatured()
{
return delaunayfeatured;
}

double Delaunay::Get_delaunayvolume()
{
return delaunayvolume;
}

ublas::c_vector<int,4> Delaunay::Get_delaunaynodes()
{
return delaunaynodes; 
}

int Delaunay::Get_delaunayfeasibility()
{
return delaunayfeasibility;
}
//can:END DEFINITIONS OF GET FUNCTIONS OF DELAUNAY

//can: START DEFINITIONS OF THE CALCULATE TYPE FUNCTIONS 
void Delaunay::Delaunay_unfeasibilizer(vector<Node*> Nodes,
                                       double _alpha_vertextocenter,
                                       double _alpha_longesttwoedges,
                                       double _alpha_cosangle)
{

//can:feasibility according to the vertex to geocenter distances
if(vertextocenter>_alpha_vertextocenter)
delaunayfeasibility=0;



//can:feasibility according to the longest two edges 
double firstlongest=0.0; 
if(delaunayfeasibility!=0)
{
double secondlongest=0.0; 
double shortest=100.0;
for(int i=0;i<3;i++)
for(int j=i+1;j<4;j++)
{
ublas::c_vector<double,3> v; 
double len_v;
v=Nodes[delaunaynodes[i]]->Get_X()-Nodes[delaunaynodes[j]]->Get_X();
len_v=len(v); 
if(len_v>firstlongest)
{
secondlongest=firstlongest;
firstlongest=len_v; 
}
else if(len_v>secondlongest)
secondlongest=len_v; 

if(len_v<shortest)
shortest=len_v;

}
double sum_longest=firstlongest+secondlongest;
if(sum_longest>_alpha_longesttwoedges)
delaunayfeasibility=0;
}


//can:feasibility according to the angles 
if(delaunayfeasibility!=0)
{
int corner=0;
while(corner<4)
{

    double current_cosangle;
    ublas::c_vector<double,3> v1; 
    ublas::c_vector<double,3> v2; 
    ublas::c_vector<double,3> v3; 
    v1=Nodes[delaunaynodes[corner]]->Get_X()-Nodes[delaunaynodes[(corner+1)%4]]->Get_X(); 
    v2=Nodes[delaunaynodes[corner]]->Get_X()-Nodes[delaunaynodes[(corner+2)%4]]->Get_X(); 
    v3=Nodes[delaunaynodes[corner]]->Get_X()-Nodes[delaunaynodes[(corner+3)%4]]->Get_X();
    current_cosangle=fabs(inner_prod(v1,v2))/len(v1)/len(v2); 
    if(current_cosangle>_alpha_cosangle)
    {delaunayfeasibility=0;; break; }
    current_cosangle=fabs(inner_prod(v1,v3))/len(v1)/len(v3); 
    if(current_cosangle>_alpha_cosangle)
    {delaunayfeasibility=0;; break; }
    current_cosangle=fabs(inner_prod(v3,v2))/len(v3)/len(v2); 
    if(current_cosangle>_alpha_cosangle)
    {delaunayfeasibility=0;; break; }
    corner++; 
}
}


}

void Delaunay::Delaunay_postunfeasibilizer()
{
if(inversioninfo==0)
delaunayfeasibility=0;
}


void Delaunay::Calculate_NodeNormalsviaDelaunay(std::vector<Node*> Nodes)
{
int delaunaypurebulk=0;
if(Nodes[delaunaynodes[0]]->Get_nodeborder()==0 && 
   Nodes[delaunaynodes[1]]->Get_nodeborder()==0 && 
   Nodes[delaunaynodes[2]]->Get_nodeborder()==0 &&
   Nodes[delaunaynodes[3]]->Get_nodeborder()==0)
delaunaypurebulk=1; 

//can:delaunay post unfeasibilizer is not implemented yet
Delaunay_postunfeasibilizer(); 
if(delaunaypurebulk==0 && delaunayfeasibility==1)
for(int c=0;c<4;c++)
{
if(Nodes[delaunaynodes[(c+1)%4]]->Get_nodeborder()==1 && 
   Nodes[delaunaynodes[(c+2)%4]]->Get_nodeborder()==1 && 
   Nodes[delaunaynodes[(c+3)%4]]->Get_nodeborder()==1 )
{
ublas::c_vector<double,3> v1; 
ublas::c_vector<double,3> v2; 
ublas::c_vector<double,3> current_center;
v1=Nodes[delaunaynodes[(c+1)%4]]->Get_X()-Nodes[delaunaynodes[(c+2)%4]]->Get_X();
v2=Nodes[delaunaynodes[(c+2)%4]]->Get_X()-Nodes[delaunaynodes[(c+3)%4]]->Get_X();
ublas::c_vector<double,3> current_normal;
current_normal=cross(v1,v2); 
current_center=(Nodes[delaunaynodes[(c+1)%4]]->Get_X()+
                Nodes[delaunaynodes[(c+2)%4]]->Get_X()+
                Nodes[delaunaynodes[(c+3)%4]]->Get_X())/3.0;
if(prec_inner_prod(Nodes[delaunaynodes[c]]->Get_X()-current_center,current_normal)>0.0)
current_normal=-current_normal; 
Nodes[delaunaynodes[(c+1)%4]]->Push_nodenormal(current_normal); 
Nodes[delaunaynodes[(c+2)%4]]->Push_nodenormal(current_normal); 
Nodes[delaunaynodes[(c+3)%4]]->Push_nodenormal(current_normal); 
}
}

}

//can: END DEFINITIONS OF THE CALCULATE TYPE FUNCTIONS 

