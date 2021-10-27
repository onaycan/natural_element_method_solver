#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"

//can: This function acts as a longly defined constructer 
void Model::Model_Bear_Yourself()
{
//can:getting the model name 
Model_Input.open("inputs//Model_Input.inp");
getline(Model_Input,Model_name); 
Model_commandtab=Model_name+":"; 

cout<<Model_commandtab<<"Start bearing the model "<<endl;
Nodalhull=new Hull();
string nodalhullname=Model_name+"NHull"; //can: hull name is an internal issue,
//-can: but I keep the hull name to be different for each case, for the 
//-can: futuring contact modeling
Nodalhull->Hull_Bear_Yourself(nodalhullname);
string nodalgaussianhullname=Model_name+"NGHull";
GenerateNGinput(nodalgaussianhullname);
NodalGaussianhull=new Hull();
NodalGaussianhull->Hull_Bear_Yourself(nodalgaussianhullname);

string nodalhulloutputtype="static";
Nodalhull->Hull_ShowYourself(nodalhulloutputtype);

string nodalgaussianhulloutputtype="static";
NodalGaussianhull->Hull_ShowYourself(nodalgaussianhulloutputtype);


cout<<Model_commandtab<<"End bearing the model "<<endl;
}

void Model::GenerateNGinput(string _nodalgaussianhullname)
{

string NGCloudFolderDirectory="inputs\\"+_nodalgaussianhullname+"_inputs\\";
std::wstring NGCloudFolderDirectoryytemp=s2ws(NGCloudFolderDirectory);
CreateDirectory(NGCloudFolderDirectoryytemp.c_str(),NULL);


string NGCloudFileDirectory=NGCloudFolderDirectory+_nodalgaussianhullname+"cloudFeatured_input.inp";
string NGFeaturingInfoFileDirectory=NGCloudFolderDirectory+_nodalgaussianhullname+"featuringinfo.info";

ofstream NGfeaturedinput;
NGfeaturedinput.open(NGCloudFileDirectory.c_str()); 

ofstream NGfeaturinginfo; 
NGfeaturinginfo.open(NGFeaturingInfoFileDirectory.c_str());

NGfeaturinginfo<<"label|||bordery|||featuring|||nodal/gaussian"<<endl;

NGfeaturedinput<<_nodalgaussianhullname<<endl;
NGfeaturedinput<<"Coordinates"<<endl; 
int nodesoriginalsize=Nodalhull->Hull_Get_Hull_nonodes_original();
int nodessize=Nodalhull->Hull_Get_Hull_nonodes();
int facetssize=Nodalhull->Hull_Get_Hull_nofacets();

for(int no=0;no<nodesoriginalsize;no++)
{
ublas::c_vector<double,3> currentX=Nodalhull->Hull_Get_Hull_Nodes()[no]->Get_X();
int currentbordery=Nodalhull->Hull_Get_Hull_Nodes()[no]->Get_nodeborder();
NGfeaturedinput<<no+1<<'\t';
NGfeaturedinput<<currentX[0]<<'\t';
NGfeaturedinput<<currentX[1]<<'\t';
NGfeaturedinput<<currentX[2]<<endl;
NGfeaturinginfo<<no<<'\t'<<currentbordery<<'\t'<<0<<'\t'<<1<<endl;
}


int facetcounter=nodesoriginalsize+1; 
for(int f=0;f<facetssize;f++)
{
if(Nodalhull->Hull_Get_Hull_VoronoiFacets()[f]->Get_facetborder()==0)
{
ublas::c_vector<double,3> currentX;
currentX=Nodalhull->Hull_Get_Hull_VoronoiFacets()[f]->Get_facetcentroid(); 
NGfeaturedinput<<facetcounter<<'\t';
NGfeaturedinput<<currentX[0]<<'\t';
NGfeaturedinput<<currentX[1]<<'\t';
NGfeaturedinput<<currentX[2]<<endl;
NGfeaturinginfo<<facetcounter-1<<'\t'<<0<<'\t'<<0<<'\t'<<0<<endl;
facetcounter++;
}
else
{
ublas::c_vector<double,3> currentX;
int _sidenodes[2];
_sidenodes[0]=Nodalhull->Hull_Get_Hull_VoronoiFacets()[f]->Get_sidenodes()[0];
_sidenodes[1]=Nodalhull->Hull_Get_Hull_VoronoiFacets()[f]->Get_sidenodes()[1];
currentX=(Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[0]]->Get_X()+
          Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[1]]->Get_X())/2.0;
NGfeaturedinput<<facetcounter<<'\t';
NGfeaturedinput<<currentX[0]<<'\t';
NGfeaturedinput<<currentX[1]<<'\t';
NGfeaturedinput<<currentX[2]<<endl;
NGfeaturinginfo<<facetcounter-1<<'\t'<<1<<'\t'<<0<<'\t'<<0<<endl;
facetcounter++;
}
}


int featurecounter=nodesoriginalsize+facetssize+1;
double tolerance=Nodalhull->Get_featuringtolerance();
for(int nb=0;nb<nodesoriginalsize;nb++)
{

int currentbordery=Nodalhull->Hull_Get_Hull_Nodes()[nb]->Get_nodeborder();
if(currentbordery==1)
{
ublas::c_vector<double,3> featuredX;
for(int norm=0;norm<Nodalhull->Hull_Get_Hull_Nodes()[nb]->Get_nodenormals().size();norm++)
{
ublas::c_vector<double,3> currentnormal=Nodalhull->Hull_Get_Hull_Nodes()[nb]->Get_nodenormals()[norm];
featuredX=Nodalhull->Hull_Get_Hull_Nodes()[nb]->Get_X()+tolerance*currentnormal/len(currentnormal);
NGfeaturedinput<<featurecounter<<'\t';
NGfeaturedinput<<featuredX[0]<<'\t';
NGfeaturedinput<<featuredX[1]<<'\t';
NGfeaturedinput<<featuredX[2]<<endl;
NGfeaturinginfo<<featurecounter-1<<'\t'<<-1<<'\t'<<1<<'\t'<<-1<<endl;
featurecounter++;
}
}
}


for(int fb=0;fb<facetssize;fb++)
{
if(Nodalhull->Hull_Get_Hull_VoronoiFacets()[fb]->Get_facetborder()==1)
{
ublas::c_vector<double,3> featuredX;
ublas::c_vector<double,3> currentnormal;
int _sidenodes[2];
int _sidebsecs[2];

_sidenodes[0]=Nodalhull->Hull_Get_Hull_VoronoiFacets()[fb]->Get_sidenodes()[0];
_sidenodes[1]=Nodalhull->Hull_Get_Hull_VoronoiFacets()[fb]->Get_sidenodes()[1];
_sidebsecs[0]=Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[0]]->Get_bsec();
_sidebsecs[1]=Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[1]]->Get_bsec();

int choice=min(_sidebsecs[0],_sidebsecs[1]); 
switch(choice)
{
case 1: 
if(_sidebsecs[0]==1)
currentnormal=Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[0]]->Get_nodenormal();
else if(_sidebsecs[1]==1)
currentnormal=Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[1]]->Get_nodenormal();
else
cout<<"Error: bsec signs have some problem in case 1"<<endl;
featuredX=0.5*(Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[0]]->Get_X()+
               Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[1]]->Get_X())+
               tolerance*currentnormal/len(currentnormal);
NGfeaturedinput<<featurecounter<<'\t';
NGfeaturedinput<<featuredX[0]<<'\t';
NGfeaturedinput<<featuredX[1]<<'\t';
NGfeaturedinput<<featuredX[2]<<endl;
NGfeaturinginfo<<featurecounter-1<<'\t'<<-1<<'\t'<<1<<'\t'<<-1<<endl;
featurecounter++;
break; 
case 2:
if(_sidebsecs[0]==2)
for(int norm=0;norm<2;norm++)
{
currentnormal=Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[0]]->Get_nodenormals()[norm];
featuredX=0.5*(Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[0]]->Get_X()+
               Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[1]]->Get_X())+
               tolerance*currentnormal/len(currentnormal);
NGfeaturedinput<<featurecounter<<'\t';
NGfeaturedinput<<featuredX[0]<<'\t';
NGfeaturedinput<<featuredX[1]<<'\t';
NGfeaturedinput<<featuredX[2]<<endl;
NGfeaturinginfo<<featurecounter-1<<'\t'<<-1<<'\t'<<1<<'\t'<<-1<<endl;
featurecounter++;
}
else if(_sidebsecs[1]==2)
for(int norm=0;norm<2;norm++)
{
currentnormal=Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[0]]->Get_nodenormals()[norm];
featuredX=0.5*(Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[0]]->Get_X()+
               Nodalhull->Hull_Get_Hull_Nodes()[_sidenodes[1]]->Get_X())+
               tolerance*currentnormal/len(currentnormal);
NGfeaturedinput<<featurecounter<<'\t';
NGfeaturedinput<<featuredX[0]<<'\t';
NGfeaturedinput<<featuredX[1]<<'\t';
NGfeaturedinput<<featuredX[2]<<endl;
NGfeaturinginfo<<featurecounter-1<<'\t'<<-1<<'\t'<<1<<'\t'<<-1<<endl;
featurecounter++;
}
else
cout<<"Error: bsec signs have some problem in case 2"<<endl;
break; 

case 3: 
cout<<"Error: bsec signs have some problem in case 3"<<endl;

default: 
    cout<<"Error: bsec signs have some problem in default case"<<endl;
}

}
}


NGfeaturedinput<<"end Coordinates"<<endl; 

}

