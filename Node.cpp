#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"

//can:constructer
Node::Node(int _nodelabel,ublas::c_vector<double,3> _X)
{
nodelabel=_nodelabel;
X=_X;
nodeborder=0;
nodenormal[0]=0.0;
nodenormal[1]=0.0;
nodenormal[2]=0.0;
nobrotherfacets=0;
nobrothernodes=0;
}

//can:copy constructer 
Node::Node(const Node &_N)
{
nodelabel=_N.nodelabel;
X=_N.X;
}


//can:copy assigment
Node& Node::operator =(const Node &_N) 
{
if(this!=&_N)
{
nodelabel=_N.nodelabel;
X=_N.X;
}
return* this; 
}


/*::START PUSH FUNCTION DEFINITIONS OF CLASS NODE::*/

void Node::Push_homedelaunays(int _delaunaylabel)
{
homedelaunays.push_back(_delaunaylabel); 
}

void Node::Push_nodenormal(ublas::c_vector<double,3> _nodenormal)
{
for(int i=0;i<3;i++)
nodenormal[i]=nodenormal[i]+_nodenormal[i];
nodenormals.push_back(_nodenormal); 
}

void Node::Push_brotherfacets(int _brotherfacet)
{
brotherfacets.push_back(_brotherfacet); 
nobrotherfacets++;
}

void Node::Push_brothernodes(int _brothernode)
{
brothernodes.push_back(_brothernode); 
nobrothernodes++;
}

void Node::Push_brothernodedistances(Node* brotherN)
{
double dis=len(X-brotherN->Get_X());
brothernodedist.push_back(dis);
}

/*::END PUSH FUNCTION DEFINITIONS OF CLASS NODE::*/


//can:START DEFINITIONS OF SET FUNCTIONS OF NODE
void Node::Set_nodeborder(int _nodeborder)
{
nodeborder=_nodeborder;
}

void Node::Set_bsec()
{
bsec=nodenormals.size();
}

void Node::Set_nodefeatured(int _nodefeatured)
{
nodefeatured=_nodefeatured;
}

void Node::Set_nodalyesgaussionno(int _nodalyesgaussionno)
{
nodalyesgaussionno=_nodalyesgaussionno;
}

//can:END DEFINITIONS OF SET FUNCTIONS OF NODE

//can:START DEFINITIONS OF GET FUNCTIONS OF NODE
int Node::Get_nodelabel()
{
return nodelabel;
}

ublas::c_vector<double,3> Node::Get_X()
{
return X;
}

int Node::Get_nodeborder()
{
return nodeborder;
}

int Node::Get_bsec()
{
return bsec;
}

int Node::Get_nodefeatured()
{
return nodefeatured;
}

int Node::Get_nodalyesgaussionno()
{
return nodalyesgaussionno;
}

ublas::c_vector<double,3> Node::Get_nodenormal()
{
return nodenormal;
}

vector< ublas::c_vector<double,3> > Node::Get_nodenormals()
{
return nodenormals; 
}
//can:END DEFINITIONS OF GET FUNCTIONS OF NODE


//can: START DEFINITIONS OF CALCULATE FUNCTIONS OF THE NODE
void Node::Eliminate_illnormals(vector<Delaunay*> Delaunays, vector<Node*> Nodes)
{

//deleting zero node normals 
int i=0; 
while(i<nodenormals.size())
{
if(len(nodenormals[i])<=pow(10.0,-10.0))
{
nodenormals.erase(nodenormals.begin()+i);
i--;
}
i++;
}


int norm=0;

while(norm<nodenormals.size())
{
int hd=0;
int normalfeasibility=1;
ublas::c_vector<double,3> normal; 
normal=nodenormals[norm]/len(nodenormals[norm]); 

while(hd<homedelaunays.size())
{
if(Delaunays[homedelaunays[hd]]->Get_delaunayfeasibility()==1)
{
int check=InsideOutside_tetrahedra_simple(Nodes,Delaunays[homedelaunays[hd]],normal,nodelabel);
if(check!=0)
{
nodenormal=nodenormal-nodenormals[norm];
nodenormals.erase(nodenormals.begin()+norm); 
norm--;
break;
}
}
hd++; 
}

norm++;
}

}


void Node::Gather_nodenormals()
{


int i=0;
int j=0; 
double alpha_coscorelation=0.72; 


if(nodeborder==1)
            while(i<nodenormals.size())
            {
            ublas::c_vector<double,3> normal_i;
            normal_i=nodenormals[i]; 
            if(len(nodenormals[i])>pow(10.0,-10.0))
        while(j<nodenormals.size())
        {
    if(i!=j && len(nodenormals[j])>pow(10.0,-10.0))
    {
double corelation=fabs(prec_inner_prod(normal_i,nodenormals[j]))/len(normal_i)/len(nodenormals[j]);
if(corelation>alpha_coscorelation)
{
ublas::c_vector<double,3> sum;
sum=nodenormals[i]+nodenormals[j];
nodenormals[i]=sum; 


nodenormals.erase(nodenormals.begin()+j);

j--;

}
    }
    j++;
        }
            i++;
            j=i;
            }





i=0; 
while(i<nodenormals.size())
{
if(len(nodenormals[i])<=pow(10.0,-10.0))
{
nodenormals.erase(nodenormals.begin()+i);
i--;
}
i++;
}

}


//can: END DEFINITIONS OF THE CALCULATE FUNCTIONS OF THE NODE