#include "stdafx.h"
#include "Nem3dCan.h"
#include "ClassHeaders.h"

void Hull::Hull_Bear_Yourself(string _Hull_name)
{
//can:I define a command tab for the hull
Hull_commandtab="   "+_Hull_name+":"; 
cout<<Hull_commandtab<<"Start bearing the hull"<<endl; 
Hull_name.append(_Hull_name); //can: appending the name of the hull
griping_sequence=-1;
Hull_Manipulate_Gripes();
if(griping_sequence==0)
{
Hull_HaveInitialGripe();
Hull_Manipulate_Gripes();
}
if(griping_sequence==1)
Hull_HaveFeaturedGripe();



cout<<Hull_commandtab<<"End bearing the hull"<<endl; 



}

void Hull::Hull_Manipulate_Gripes()
{
//can::commandtab is extended 
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start manipulating the hull gripes"<<endl; 
//can:I define an input folder directory for this hull 
string CurrentCloudFolderDirectory="inputs\\"+Hull_name+"_inputs\\";
std::wstring CurrentCloudFolderDirectorytemp=s2ws(CurrentCloudFolderDirectory);
string CurrentCloudFileDirectory;
std::wstring CurrentCloudFileDirectorytemp;
string Model_Input_FileDirectory="inputs//Model_Input.inp";
std::wstring Model_Input_FileDirectorytemp = s2ws(Model_Input_FileDirectory);

switch(Hull_name[Hull_name.size()-5])
{
case 'N':
    griping_sequence++;
    if(griping_sequence==0)
    {
    CurrentCloudFileDirectory=CurrentCloudFolderDirectory+Hull_name+"cloudOriginal_input.inp";
    CurrentCloudFileDirectorytemp=s2ws(CurrentCloudFileDirectory);
    CreateDirectory(CurrentCloudFolderDirectorytemp.c_str(),NULL);
    CopyFile(Model_Input_FileDirectorytemp.c_str(),CurrentCloudFileDirectorytemp.c_str(),NULL);
    Hull_Manipulate_inoutfiles(CurrentCloudFileDirectory);
    }
    if(griping_sequence==1)
    {
    CurrentCloudFileDirectory=CurrentCloudFolderDirectory+Hull_name+"cloudFeatured_input.inp";
    CurrentCloudFileDirectorytemp=s2ws(CurrentCloudFileDirectory);
    Hull_GenerateFeaturedInputNhull(CurrentCloudFileDirectory);
    Hull_Manipulate_inoutfiles(CurrentCloudFileDirectory);
    }
    break;
case 'G':
    griping_sequence=griping_sequence+2;
    if(griping_sequence==1)
    {
    CurrentCloudFileDirectory=CurrentCloudFolderDirectory+Hull_name+"cloudFeatured_input.inp";
    Hull_Manipulate_inoutfiles(CurrentCloudFileDirectory);
    }
    break;
default:
    {
    cout<<Hull_commandtab<<"Error, your hull is neither nodal nor ngaussian"<<endl;
    cout<<Hull_name<<endl; 
    break;
    }
}



cout<<Hull_commandtab<<"End manipulating the hull gripes"<<endl; 
//can:commandtab is shorten back 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);
}


void Hull::Hull_Manipulate_inoutfiles(string _CurrentCloudFileDirectory)
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start manipulating the input output files"<<endl; 

Hull_convertintoqhullinput(_CurrentCloudFileDirectory); 

//can:conditioning the file generation 
int condition_of_file_generation=0; 

if(griping_sequence==0 && Hull_name[Hull_name.size()-5]=='N')
condition_of_file_generation=1;
if(griping_sequence==1 && Hull_name[Hull_name.size()-5]=='G')
condition_of_file_generation=1;

if(condition_of_file_generation==1)
{
string Hull_outputfolderDirectory="outputs//"+Hull_name+"_outputs//";
std::wstring Hull_outputfolderDirectorytemp=s2ws(Hull_outputfolderDirectory);
CreateDirectory(Hull_outputfolderDirectorytemp.c_str(),NULL);
string Hull_debugfileDirectory=Hull_outputfolderDirectory+Hull_name+"_debugfile.txt";
Hull_debugfile.open(Hull_debugfileDirectory.c_str()); 
string Hull_GiDvoronoifileDirectory=Hull_outputfolderDirectory+Hull_name+"_GiDvoronoifile.post.msh";
Hull_GiDvoronoifile.open(Hull_GiDvoronoifileDirectory.c_str()); 
string Hull_GiDvoronoifile_postDirectory=Hull_outputfolderDirectory+Hull_name+"_GiDvoronoifile.post.res";
Hull_GiDvoronoifile_post.open(Hull_GiDvoronoifile_postDirectory.c_str()); 
string Hull_GiDdelaunayfileDirectory=Hull_outputfolderDirectory+Hull_name+"_GiDdelaunayfile.post.msh";
Hull_GiDdelaunayfile.open(Hull_GiDdelaunayfileDirectory.c_str()); 
string Hull_GiDdelaunayfile_postDirectory=Hull_outputfolderDirectory+Hull_name+"_GiDdelaunayfile.post.res";
Hull_GiDdelaunayfile_post.open(Hull_GiDdelaunayfile_postDirectory.c_str()); 
string Hull_GmshfileDirectory=Hull_outputfolderDirectory+Hull_name+"_Gmshfile.msh";
Hull_Gmshfile.open(Hull_GmshfileDirectory.c_str()); 
}




cout<<Hull_commandtab<<"Start: Generating "<<Hull_name<<"_qhull_run_bat file"<<endl;
string Hull_qhullrunDirectory="qhull-2010.1//"+Hull_name+"_qhull_run.bat";
Hull_qhullrun.open(Hull_qhullrunDirectory.c_str()); 
string DirectoryfileDirectory="inputs//Directoryfile.txt";
ifstream Directoryfile(DirectoryfileDirectory.c_str());
//qhull bat file opening 
Generate_qhullrunbat(Directoryfile);
cout<<Hull_commandtab<<"End: Generating "<<Hull_name<<"_qhull_run.bat file"<<endl;

cout<<Hull_commandtab<<"Start:System Call for "<<Hull_name<<" qhull cloud"<<endl;
cout<<endl<<endl;
int system_bool; 
string currentdirectory; 
getline(Directoryfile,currentdirectory); 
currentdirectory=currentdirectory+"//qhull-2010.1//"+Hull_name+"_qhull_run.bat"; 
system_bool=system(currentdirectory.c_str()); 
cout<<endl<<endl;
if(system_bool==0)
cout<<Hull_commandtab<<"Sytem return: "<<Hull_name<<"_qhull_run.bat had succesfully returned by system"<<endl; 
else
cout<<Hull_commandtab<<"Sytem return: "<<Hull_name<<"_qhull_run.bat had a problem"<<endl; 
cout<<Hull_commandtab<<"End:System Call for "<<Hull_name<<" qhull cloud"<<endl;


cout<<Hull_commandtab<<"Start:Opening the "<<Hull_name<<" Voronoi&Delaunay input files"<<endl;
string Hull_meshlessinputDirectory="qhull-2010.1//"+Hull_name+"meshless_input.txt";
Hull_meshlessinput.open(Hull_meshlessinputDirectory.c_str()); 
string Hull_delaunayinputDirectory="qhull-2010.1//"+Hull_name+"delaunay_input.txt";
Hull_delaunayinput.open(Hull_delaunayinputDirectory.c_str()); 
string Hull_voronoiinputDirectory="qhull-2010.1//"+Hull_name+"voronoi_input.txt";
Hull_voronoiinput.open(Hull_voronoiinputDirectory.c_str()); 
cout<<Hull_commandtab<<"End:Opening the "<<Hull_name<<" Voronoi&Delaunay input files"<<endl;

Directoryfile.close();



cout<<Hull_commandtab<<"End manipulating the input output files"<<endl; 
//can:commandtab is shorten back 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);

}

void Hull::Hull_convertintoqhullinput(std::string _CurrentCloudFileDirectory)
{
//ifstream msh_file;
ofstream Hull_CloudTemporaryOut; //the node coordinates file as output 
ifstream Hull_CloudTemporaryIn; //the node coordinates as input 
ifstream currentHull_cloudinput(_CurrentCloudFileDirectory.c_str());

string Hull_CloudTemporaryOutDirectory="inputs//"+Hull_name+"_inputs//"+Hull_name+"cloudTemporary.msh";
Hull_CloudTemporaryOut.open(Hull_CloudTemporaryOutDirectory.c_str());
Hull_CloudTemporaryOut.clear();


string Hull_qhulltypeinputDirectory="qhull-2010.1//"+Hull_name+"meshless_input.txt";
Hull_qhulltypeinput.open(Hull_qhulltypeinputDirectory.c_str()); 
Hull_qhulltypeinput.clear(); 



char commentline[256];
int numberofN=0; 
currentHull_cloudinput.getline(commentline,256); 
currentHull_cloudinput.getline(commentline,256); 


char e; 
do
{
currentHull_cloudinput>>e;
	if(e!='e')
	{
		numberofN++; 
		currentHull_cloudinput.putback(e); 
	    int label; 
		currentHull_cloudinput>>label; 
		ublas::c_vector<double,3> coord; 
    
		for(int i=0;i<3;i++)
			currentHull_cloudinput>>coord[i]; 

      Hull_CloudTemporaryOut<<coord[0]<<'\t';
			Hull_CloudTemporaryOut<<coord[1]<<'\t';
			Hull_CloudTemporaryOut<<coord[2]<<endl;

	}

}while(e!='e');


Hull_qhulltypeinput<<3<<endl; 
Hull_qhulltypeinput<<numberofN<<endl; 

Hull_CloudTemporaryIn.open(Hull_CloudTemporaryOutDirectory.c_str());

for(int i=0;i<numberofN;i++)
{
ublas::c_vector<double,3> coord; 
for(int j=0;j<3;j++)
Hull_CloudTemporaryIn>>coord[j];

Hull_qhulltypeinput<<coord[0]<<'\t';
Hull_qhulltypeinput<<coord[1]<<'\t';
Hull_qhulltypeinput<<coord[2]<<endl;



}


currentHull_cloudinput.close(); 
Hull_CloudTemporaryIn.close(); 
Hull_CloudTemporaryOut.close(); 


}


void Hull::Generate_qhullrunbat(ifstream &Directoryfile)
{
string currentdirectory;
getline(Directoryfile,currentdirectory); 
currentdirectory=currentdirectory+"\\qhull-2010.1";
Hull_qhullrun<<"@echo off"<<endl;
Hull_qhullrun<<"echo"<<endl;
Hull_qhullrun<<"echo ========= qhull_run.bat voronoits your population ==========="<<endl;
Hull_qhullrun<<"echo."<<endl;
Hull_qhullrun<<"cd "<<currentdirectory<<endl;
Hull_qhullrun<<"if exist %qvoronoi.exe goto spring"<<endl;
Hull_qhullrun<<"echo There is nothing like qvoronoi.exe under this directory says CAN"<<endl;

Hull_qhullrun<<"REM This file reads the group of points in meshless_input.txt,"<<endl;
Hull_qhullrun<<"REM calls the programm qhull to calculate the voronoi diagramm freaky fast, "<<endl;
Hull_qhullrun<<"REM writes the result in voronoi_input.txt and delaunayinput.txt"<<endl;
Hull_qhullrun<<"REM The order line by line "<<endl;
Hull_qhullrun<<"REM (1),(2),(3)comments"<<endl;
Hull_qhullrun<<"REM (5) check the existance of the executable (qvoronoi.exe)"<<endl;
Hull_qhullrun<<"REM (8) spring to the existance condition statement (you can replace spring statement with something else) "<<endl;
Hull_qhullrun<<"REM (9) show in the command prompt that you are alright till now..."<<endl; 
Hull_qhullrun<<"REM (10) syntax-in the voronoi think. "<<endl;
Hull_qhullrun<<"REM (10) you first enter the executable, then the input file (the point cloud), and output file. "<<endl;
Hull_qhullrun<<"REM (10)For better understanding of this sytax refer to the qhull documentation"<<endl;
Hull_qhullrun<<"REM (11) Remarks: copy the written file, into the input directiory of your meshless program. was done before"<<endl;
Hull_qhullrun<<"REM (11) /Y overwrites the file(voronoi_input.txt) without asking you for further replacement"<<endl;

Hull_qhullrun<<"goto ENDE"<<endl;
Hull_qhullrun<<":spring"<<endl;
Hull_qhullrun<<"echo The current qvoronoi.exe is under this directory of yours"<<endl;
Hull_qhullrun<<"qvoronoi<"<<Hull_name<<"meshless_input.txt Qt s o Fv TO "<<Hull_name<<"voronoi_input.txt"<<endl;
Hull_qhullrun<<"qdelaunay<"<<Hull_name<<"meshless_input.txt Qt i Fa TO "<<Hull_name<<"delaunay_input.txt"<<endl;
Hull_qhullrun<<"REM xcopy E:\meshless\fromDesktop\meshless3D1\meshless3D1\qhull-2010.1\Nvoronoi_input.txt  E:\meshless\fromDesktop\meshless3D1\meshless3D1\inputs\N_inputs /Y "<<endl;
Hull_qhullrun<<"REM xcopy E:\meshless\fromDesktop\meshless3D1\meshless3D1\qhull-2010.1\Ndelaunay_input.txt  E:\meshless\fromDesktop\meshless3D1\meshless3D1\inputs\N_inputs /Y "<<endl;
Hull_qhullrun<<"cd ."<<endl;
Hull_qhullrun<<":ENDE "<<endl;
Hull_qhullrun<<"echo."<<endl;
Hull_qhullrun<<"echo ========= qhull_run.bat finished with or withhout errors ==========="<<endl;
Hull_qhullrun.close(); 
}

void Hull::Hull_HaveInitialGripe()
{
//can: reading in the node and delaunay information 
Hull_InitialNodeDelaunay_Reader(); 
//can: reading in the voronoi information for the featuring information
Hull_InitialVoronoi_Reader();
//can: calculating the nodal normals via delaunay tetrahedras
Hull_CalculateNodeNormalsviaDelaunay();
//can: eliminating the ill nodal normals via delaunay tetrahedras
Hull_Eliminate_illnormals();
//can: gathering node normals 
Hull_Gather_nodenormals();
//can:Setting bsec 
Hull_Set_bsec();



}

void Hull::Hull_InitialNodeDelaunay_Reader()
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start reading the nodes & delaunays "<<endl; 
//can:commandtab is shorten back 

//NODE READER STARTS//
//node reader declerations 
int dimension; 
ublas::c_vector<double,3> currentX; 
Hull_meshlessinput>>dimension; 


//node reader allocation 
Hull_meshlessinput>>Hull_nonodes;
Hull_Nodes.resize(Hull_nonodes); 


if(griping_sequence==0)
Hull_nonodes_original=Hull_nonodes; 

//reading & constructing nodes 

for(int n=0;n<Hull_nonodes;n++)
{
Hull_meshlessinput>>currentX[0];
Hull_meshlessinput>>currentX[1];
Hull_meshlessinput>>currentX[2];
Hull_Nodes[n]=new Node(n,currentX); 
}

//NODE READER ENDS//

//DELAUNAY READER STARTS//
//delaunay reader declerations 
double current_delaunayvolume; 
ublas::c_vector<int,4> current_delaunaynodes;

//delaunay reader allocation 
Hull_delaunayinput>>Hull_nodelaunays; 
Hull_Delaunays.resize(Hull_nodelaunays); 


//reading & constructing delaunays
//int current_delaunayfeatured; 
for(int d=0;d<Hull_nodelaunays;d++)
{
//current_delaunayfeatured=1;
Hull_delaunayinput>>current_delaunaynodes[0]; 
Hull_delaunayinput>>current_delaunaynodes[1]; 
Hull_delaunayinput>>current_delaunaynodes[2];
Hull_delaunayinput>>current_delaunaynodes[3];
//if(current_delaunaynodes[0]<Hull_nonodes_original &&
//   current_delaunaynodes[1]<Hull_nonodes_original &&
//   current_delaunaynodes[2]<Hull_nonodes_original &&
//   current_delaunaynodes[3]<Hull_nonodes_original)
//current_delaunayfeatured=0; 
Hull_Delaunays[d]=new Delaunay(d,current_delaunaynodes); 

if(griping_sequence==0)
for(int n=0;n<4;n++)
Hull_Nodes[current_delaunaynodes[n]]->Push_homedelaunays(d); 
}


Hull_delaunayinput>>Hull_nodelaunays; 


ifstream constrains("inputs//Constrains.con");
string line; 
string selection; 
getline(constrains,line);
getline(constrains,selection);


for(int d=0;d<Hull_nodelaunays;d++)
{
Hull_delaunayinput>>current_delaunayvolume; 
Hull_Delaunays[d]->Set_delaunayvolume(current_delaunayvolume); 
}

if(selection[0]=='y')
Hull_Calculate_DelaunayProperties(); 


cout<<Hull_commandtab<<"Average delaunay volume:"<<averagedelaunayvolume<<endl;
cout<<Hull_commandtab<<"Average vertex to center value:"<<averagevertextocenter<<endl;

cout<<Hull_commandtab<<"End reading the nodes & delaunays "<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);

}


void Hull::Hull_Calculate_DelaunayProperties()
{
averagedelaunayvolume=0.0; 
averagevertextocenter=0.0; 
for(int d=0;d<Hull_nodelaunays;d++)
{
if(Hull_Delaunays[d]->Get_delaunayfeatured()==0)
{
averagedelaunayvolume=averagedelaunayvolume+Hull_Delaunays[d]->Get_delaunayvolume(); 
double delaunayX[12];
for(int i=0;i<4;i++)
for(int j=0;j<3;j++)
delaunayX[i*3+j]=Hull_Nodes[Hull_Delaunays[d]->Get_delaunaynodes()[i]]->Get_X()[j];
double volume_calc=Calculate_tetrahedravolume(delaunayX);
Hull_Delaunays[d]->Set_delaunayvolume_calc(volume_calc); 
}
}

averagedelaunayvolume=averagedelaunayvolume/Hull_nodelaunays; 

//finding the origins of the delaunay set 
for(int d=0;d<Hull_nodelaunays;d++)
if(Hull_Delaunays[d]->Get_delaunayfeatured()==0)
{

//decleration of the variables 
double current_delaunaynodecoord[12];//the coordinates of the nodes of the delaunay triangles 
ublas::c_matrix<double,3,3> A;
ublas::c_matrix<double,3,3> A_inv;
ublas::c_vector<double,3> b; 
ublas::c_vector<double,3> current_delaunayorigin;
ublas::c_vector<double,3> current_delaunaygeocenter;
double current_delaunayradius; 
double current_vertextocenter=0.0; 


//assigning the current nodal coordinates of delaunay connectivities bey get functions 
for(int cdnc=0;cdnc<12;cdnc++)
current_delaunaynodecoord[cdnc]=Hull_Nodes[Hull_Delaunays[d]->Get_delaunaynodes()[cdnc/3]]->Get_X()[cdnc%3]; 


current_delaunaygeocenter[0]=(current_delaunaynodecoord[0]+current_delaunaynodecoord[3]+
                              current_delaunaynodecoord[6]+current_delaunaynodecoord[9])/4.0; 
current_delaunaygeocenter[1]=(current_delaunaynodecoord[1]+current_delaunaynodecoord[4]+
                              current_delaunaynodecoord[7]+current_delaunaynodecoord[10])/4.0; 
current_delaunaygeocenter[2]=(current_delaunaynodecoord[2]+current_delaunaynodecoord[5]+
                              current_delaunaynodecoord[8]+current_delaunaynodecoord[11])/4.0; 

Hull_Delaunays[d]->Set_delaunaygeocenter(current_delaunaygeocenter); 

A(0,0)=2.0*(current_delaunaynodecoord[0]-current_delaunaynodecoord[3]);
A(0,1)=2.0*(current_delaunaynodecoord[1]-current_delaunaynodecoord[4]);
A(0,2)=2.0*(current_delaunaynodecoord[2]-current_delaunaynodecoord[5]);

A(1,0)=2.0*(current_delaunaynodecoord[0]-current_delaunaynodecoord[6]);
A(1,1)=2.0*(current_delaunaynodecoord[1]-current_delaunaynodecoord[7]);
A(1,2)=2.0*(current_delaunaynodecoord[2]-current_delaunaynodecoord[8]);

A(2,0)=2.0*(current_delaunaynodecoord[0]-current_delaunaynodecoord[9]);
A(2,1)=2.0*(current_delaunaynodecoord[1]-current_delaunaynodecoord[10]);
A(2,2)=2.0*(current_delaunaynodecoord[2]-current_delaunaynodecoord[11]);

int _inversioninfo=0;
double _detA; 
A_inv=MatrixInv(A,_detA);
if(_detA!=0.0)
_inversioninfo=1;

Hull_Delaunays[d]->Set_inversioninfo(_inversioninfo); 


b[0]=(current_delaunaynodecoord[0]*current_delaunaynodecoord[0])-
     (current_delaunaynodecoord[3]*current_delaunaynodecoord[3])+
     (current_delaunaynodecoord[1]*current_delaunaynodecoord[1])-
     (current_delaunaynodecoord[4]*current_delaunaynodecoord[4])+
     (current_delaunaynodecoord[2]*current_delaunaynodecoord[2])-
     (current_delaunaynodecoord[5]*current_delaunaynodecoord[5]);

b[1]=(current_delaunaynodecoord[0]*current_delaunaynodecoord[0])-
     (current_delaunaynodecoord[6]*current_delaunaynodecoord[6])+
     (current_delaunaynodecoord[1]*current_delaunaynodecoord[1])-
     (current_delaunaynodecoord[7]*current_delaunaynodecoord[7])+
     (current_delaunaynodecoord[2]*current_delaunaynodecoord[2])-
     (current_delaunaynodecoord[8]*current_delaunaynodecoord[8]);

b[2]=(current_delaunaynodecoord[0]*current_delaunaynodecoord[0])-
     (current_delaunaynodecoord[9]*current_delaunaynodecoord[9])+
     (current_delaunaynodecoord[1]*current_delaunaynodecoord[1])-
     (current_delaunaynodecoord[10]*current_delaunaynodecoord[10])+
     (current_delaunaynodecoord[2]*current_delaunaynodecoord[2])-
     (current_delaunaynodecoord[11]*current_delaunaynodecoord[11]);

//calculate the delaunay origin
current_delaunayorigin=prod(A_inv,b);

//set the delaunay origin
Hull_Delaunays[d]->Set_delaunayorigin(current_delaunayorigin); 
if(_inversioninfo==1)
{
current_vertextocenter=len(current_delaunayorigin-current_delaunaygeocenter); 
Hull_Delaunays[d]->Set_vertextocenter(current_vertextocenter);
averagevertextocenter=averagevertextocenter+current_vertextocenter; 
}
//calculating and setting the current delaunay radius
current_delaunayradius=sqrt((current_delaunaynodecoord[0]-current_delaunayorigin[0])*(current_delaunaynodecoord[0]-current_delaunayorigin[0])+
                            (current_delaunaynodecoord[1]-current_delaunayorigin[1])*(current_delaunaynodecoord[1]-current_delaunayorigin[1])+
                            (current_delaunaynodecoord[2]-current_delaunayorigin[2])*(current_delaunaynodecoord[2]-current_delaunayorigin[2]));
Hull_Delaunays[d]->Set_delaunayradius(current_delaunayradius); 


}
averagevertextocenter=averagevertextocenter/Hull_nodelaunays;
}



void Hull::Hull_InitialVoronoi_Reader()
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start reading the voronoi vertices for featuring "<<endl; 

int dimension; 
int _novertices; 
int _nofacets;
int dummy_int;
int current_nopolyvertices;
int nounfeasibles=0; 
int current_sidenodes[2];
double alpha_vertextocenter;
double alpha_longesttwoedges;
double alpha_cosangle;
std::vector<int> vertexfeasibility; //can:the integer array of vertex feasibility; 
std::vector<int> current_polyvertices; //can:polygon vertices vertices of the current facet 
Hull_Constrains.open("inputs//Constrains.con");

Hull_voronoiinput>>dimension; 
Hull_voronoiinput>>_novertices; 
Hull_voronoiinput>>Hull_nonodes; 
Hull_voronoiinput>>dummy_int; 

string dummy_line; 
for(int v=0;v<_novertices+Hull_nonodes;v++)
{
getline(Hull_voronoiinput,dummy_line); 
dummy_line.clear();
}
getline(Hull_voronoiinput,dummy_line);
dummy_line.clear();

for(int i=0;i<3;i++)
{
getline(Hull_Constrains,dummy_line);
dummy_line.clear();
}

Hull_Constrains>>alpha_vertextocenter; 
getline(Hull_Constrains,dummy_line);
dummy_line.clear();
getline(Hull_Constrains,dummy_line);
dummy_line.clear();
Hull_Constrains>>alpha_longesttwoedges; 
getline(Hull_Constrains,dummy_line);
dummy_line.clear();
getline(Hull_Constrains,dummy_line);
dummy_line.clear();
Hull_Constrains>>alpha_cosangle; 
getline(Hull_Constrains,dummy_line);
dummy_line.clear();
getline(Hull_Constrains,dummy_line);
dummy_line.clear();
Hull_Constrains>>featuringtolerance; 

cout<<Hull_commandtab<<"Tolerance of featuring:"<<featuringtolerance<<endl;

alpha_cosangle=cos(alpha_cosangle*PI/180.0);

vertexfeasibility.resize(Hull_nodelaunays+1); 
vertexfeasibility[0]=0;
for(int d=0;d<Hull_nodelaunays;d++)
{
Hull_Delaunays[d]->Delaunay_unfeasibilizer(Hull_Nodes,
                                           alpha_vertextocenter,
                                           alpha_longesttwoedges,
                                           alpha_cosangle
                                           ); 
vertexfeasibility[d+1]=Hull_Delaunays[d]->Get_delaunayfeasibility();
if(vertexfeasibility[d+1]==0)
nounfeasibles++;
}
cout<<Hull_commandtab<<nounfeasibles<<" delaunays are unfeasible"<<endl;
Hull_voronoiinput>>_nofacets; 

for(int f=0;f<_nofacets;f++)
{

Hull_voronoiinput>>current_nopolyvertices;
current_nopolyvertices=current_nopolyvertices-2; 
Hull_voronoiinput>>current_sidenodes[0];
Hull_voronoiinput>>current_sidenodes[1];

current_polyvertices.resize(current_nopolyvertices); 

for(int pv=0;pv<current_nopolyvertices;pv++) 
Hull_voronoiinput>>current_polyvertices[pv];


for(int pv=0;pv<current_nopolyvertices;pv++)
{
int current_ridgefeasibility=1; 
int left=pv;
int right=(pv+1)%current_nopolyvertices; 


if(vertexfeasibility[current_polyvertices[left]]==0)
if(vertexfeasibility[current_polyvertices[right]]==0)
current_ridgefeasibility=0; 

if(current_polyvertices[left]==0)
if(vertexfeasibility[current_polyvertices[right]]==0)
current_ridgefeasibility=0; 

if(current_polyvertices[right]==0)
if(vertexfeasibility[current_polyvertices[left]]==0)
current_ridgefeasibility=0; 

if(current_ridgefeasibility==1)
if(vertexfeasibility[current_polyvertices[left]]==0 || vertexfeasibility[current_polyvertices[right]]==0)
{
Hull_Nodes[current_sidenodes[0]]->Set_nodeborder(1); 
Hull_Nodes[current_sidenodes[1]]->Set_nodeborder(1); 
}

}

current_polyvertices.clear();


}
vertexfeasibility.clear();
cout<<Hull_commandtab<<"End reading the voronoi vertices for featuring "<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);

}



void Hull::Hull_CalculateNodeNormalsviaDelaunay()
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start calculating the nodal normals via Delaunays "<<endl; 
for(int d=0;d<Hull_nodelaunays;d++)
Hull_Delaunays[d]->Calculate_NodeNormalsviaDelaunay(Hull_Nodes); 
cout<<Hull_commandtab<<"End calculating the nodal normals via Delaunays "<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);
}


void Hull::Hull_Eliminate_illnormals()
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start Eliminating Ill conditioned/nonmatching node normals"<<endl; 
for(int n=0;n<Hull_nonodes;n++)
if(Hull_Nodes[n]->Get_nodeborder()==1)
Hull_Nodes[n]->Eliminate_illnormals(Hull_Delaunays,Hull_Nodes); 
cout<<Hull_commandtab<<"End Eliminating Ill conditioned/nonmatching node normals"<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);
}


void Hull::Hull_Gather_nodenormals()
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start Gathering nodenormals "<<endl; 
for(int n=0;n<Hull_nonodes;n++)
Hull_Nodes[n]->Gather_nodenormals(); 
cout<<Hull_commandtab<<"End Garhering nodenormals"<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);
}

void Hull::Hull_Set_bsec()
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start Setting bsec "<<endl; 
for(int n=0;n<Hull_nonodes;n++)
Hull_Nodes[n]->Set_bsec(); 
cout<<Hull_commandtab<<"End Setting bsec"<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);
}



void Hull::Hull_GenerateFeaturedInputNhull(string _CurrentCloudFileDirectory)
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start Generating the Featured output  "<<endl; 
Hull_cloudFeaturedoutput.open(_CurrentCloudFileDirectory.c_str()); 


Hull_cloudFeaturedoutput<<Hull_name<<"Featured"<<endl; 
Hull_cloudFeaturedoutput<<"Label & Coordinates"<<endl; 
for(int n=0;n<Hull_nonodes;n++)
{
Hull_cloudFeaturedoutput<<n+1<<'\t'<<Hull_Nodes[n]->Get_X()[0]<<'\t';
Hull_cloudFeaturedoutput<<'\t'<<Hull_Nodes[n]->Get_X()[1]<<'\t';
Hull_cloudFeaturedoutput<<'\t'<<Hull_Nodes[n]->Get_X()[2]<<endl;
}
Hull_nonodes_original=Hull_nonodes;



int nb=Hull_nonodes+1;
for(int n=0;n<Hull_nonodes;n++)
{
if(Hull_Nodes[n]->Get_nodeborder()==1)
{
ublas::c_vector<double,3> featured_nodeX; 
for(int i=0;i<Hull_Nodes[n]->Get_bsec();i++)
{
Hull_cloudFeaturedoutput<<nb<<'\t'; 
nb++; 
featured_nodeX=Hull_Nodes[n]->Get_X()+featuringtolerance*Hull_Nodes[n]->Get_nodenormals()[i]/len(Hull_Nodes[n]->Get_nodenormals()[i]);
Hull_cloudFeaturedoutput<<featured_nodeX[0]<<'\t';
Hull_cloudFeaturedoutput<<featured_nodeX[1]<<'\t';
Hull_cloudFeaturedoutput<<featured_nodeX[2]<<endl;
}
}
}
Hull_cloudFeaturedoutput<<"end coordinates"<<endl; 



cout<<Hull_commandtab<<"Start:Closing the "<<Hull_name <<" output files"<<endl;
Hull_cloudFeaturedoutput.close(); 
Hull_qhulltypeinput.close();
cout<<Hull_commandtab<<"End:Closing the "<<Hull_name <<" output files"<<endl;


cout<<Hull_commandtab<<"Start:Closing the "<<Hull_name <<" input files"<<endl;
Hull_meshlessinput.close();
Hull_delaunayinput.close(); 
Hull_voronoiinput.close();
Hull_cloudOriginalinput.close(); 
cout<<Hull_commandtab<<"End:Closing the "<<Hull_name <<" input files"<<endl;


cout<<Hull_commandtab<<"End Generating the Featured output"<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);
}


void Hull::Hull_HaveFeaturedGripe()
{
if(Hull_name[Hull_name.size()-5]=='G')
Hull_FeaturedNodeDelaunay_Reader();

Hull_FeaturedVoronoi_Reader();
Hull_Calculate_FacetProperties();

}




void Hull::Hull_FeaturedVoronoi_Reader()
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start reading the featured voronoi diagramm "<<endl; 

int dimension; 
int dummy_int;
int current_nopolyvertices;
int facetscounter=0;
int nounfeasibles=0; 
int current_sidenodes[2];
std::vector<int> current_polyvertices; //can:polygon vertices vertices of the current facet 
ublas::c_vector<double,3> current_VertexX; //can: current coordinate of the vertex
string dummy_line; 

Hull_voronoiinput>>dimension; 
Hull_voronoiinput>>Hull_novertices; 
Hull_voronoiinput>>Hull_nonodes; //this is not the number of nodes original 
Hull_voronoiinput>>dummy_int; 

Hull_VoronoiVertices.resize(Hull_novertices); 
for(int v=0;v<Hull_novertices;v++)
{
Hull_voronoiinput>>current_VertexX[0]; 
Hull_voronoiinput>>current_VertexX[1]; 
Hull_voronoiinput>>current_VertexX[2]; 
Hull_VoronoiVertices[v]=new VoronoiVertex(v,current_VertexX);
}
cout<<Hull_commandtab<<"The size of the voronoi vertices"<<Hull_VoronoiVertices.size()<<endl; 

//can: storage of the vertices in facets & nodes is unnecessary, therefore it is passed  
for(int n=0;n<Hull_nonodes+1;n++)
{
getline(Hull_voronoiinput,dummy_line); 
dummy_line.clear();
}

Hull_voronoiinput>>Hull_nofacets; 
cout<<Hull_commandtab<<"The size of the voronoi facets"<<Hull_nofacets<<endl; 


for(int f=0;f<Hull_nofacets;f++)
{
int current_facetfeasibility=1; 
Hull_voronoiinput>>current_nopolyvertices;
current_nopolyvertices=current_nopolyvertices-2; 
Hull_voronoiinput>>current_sidenodes[0];
Hull_voronoiinput>>current_sidenodes[1];

current_polyvertices.resize(current_nopolyvertices); 

for(int pv=0;pv<current_nopolyvertices;pv++) 
Hull_voronoiinput>>current_polyvertices[pv];


for(int pv=0;pv<current_nopolyvertices;pv++)
{
int current_ridgefeasibility=1; 
int left=pv;
int right=(pv+1)%current_nopolyvertices; 



if(current_polyvertices[left]==0 || current_polyvertices[right]==0)
current_ridgefeasibility=0; 

if(current_sidenodes[0]>=Hull_nonodes_original || current_sidenodes[1]>=Hull_nonodes_original)
current_ridgefeasibility=0;



if(current_ridgefeasibility==0)
current_facetfeasibility=0; 

}

if(current_facetfeasibility==1)
{
VoronoiFacet* current_facet=new VoronoiFacet(facetscounter,current_sidenodes,current_polyvertices); 
Hull_VoronoiFacets.push_back(current_facet); 

Hull_Nodes[current_sidenodes[0]]->Push_brotherfacets(facetscounter); 
Hull_Nodes[current_sidenodes[1]]->Push_brotherfacets(facetscounter); 
Hull_Nodes[current_sidenodes[0]]->Push_brothernodes(current_sidenodes[1]);
Hull_Nodes[current_sidenodes[1]]->Push_brothernodes(current_sidenodes[0]);
Hull_Nodes[current_sidenodes[0]]->Push_brothernodedistances(Hull_Nodes[current_sidenodes[1]]);
Hull_Nodes[current_sidenodes[1]]->Push_brothernodedistances(Hull_Nodes[current_sidenodes[0]]);
int _facetborder=Hull_Nodes[current_sidenodes[0]]->Get_nodeborder()+Hull_Nodes[current_sidenodes[1]]->Get_nodeborder();
if(_facetborder==2)
Hull_VoronoiFacets[facetscounter]->Set_facetborder(1); 
facetscounter++; 
}
current_polyvertices.clear();
}

Hull_nofacets=facetscounter; 
cout<<Hull_commandtab<<"feasible no of facets:"<<Hull_nofacets<<endl;

cout<<Hull_commandtab<<"End reading featured voronoi diagramm "<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);

}


void Hull::Hull_Calculate_FacetProperties()
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start calculating the facet properties "<<endl; 
for(int f=0;f<Hull_nofacets;f++)
Hull_VoronoiFacets[f]->Calculate_FacetProperties(Hull_VoronoiVertices,Hull_Nodes);
cout<<Hull_commandtab<<"End Calculating the facet properties "<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);
}





void Hull::Hull_FeaturedNodeDelaunay_Reader()
{
Hull_commandtab="   "+Hull_commandtab;
cout<<Hull_commandtab<<"Start reading the nodes & delaunays "<<endl; 
//can:commandtab is shorten back 

//NODE READER STARTS//
//node reader declerations 
int dimension; 
ublas::c_vector<double,3> currentX; 
Hull_meshlessinput>>dimension; 


//node reader allocation 
Hull_meshlessinput>>Hull_nonodes;
//Hull_Nodes.resize(Hull_nonodes); 



//reading & constructing nodes 
ifstream featuringinfo; 
string featuringinfofiledirectory="inputs\\"+Hull_name+"_inputs\\"+Hull_name+"featuringinfo.info";
featuringinfo.open(featuringinfofiledirectory.c_str());
string dummy_line; 
int dummy_int; 
getline(featuringinfo,dummy_line); 

int current_bordery=0;
int n=0;
while(current_bordery!=-1)
{
int current_featuring; 
int current_nodalgaussian; 
featuringinfo>>dummy_int; 
featuringinfo>>current_bordery; 
featuringinfo>>current_featuring; 
featuringinfo>>current_nodalgaussian; 
if(current_bordery==-1)
Hull_nonodes_original=dummy_int; 
else
{
Hull_meshlessinput>>currentX[0];
Hull_meshlessinput>>currentX[1];
Hull_meshlessinput>>currentX[2];
Node* currentNode= new Node(n,currentX); 
Hull_Nodes.push_back(currentNode);
Hull_Nodes[n]->Set_nodeborder(current_bordery); 
Hull_Nodes[n]->Set_nodefeatured(current_featuring); 
Hull_Nodes[n]->Set_nodalyesgaussionno(current_nodalgaussian); 
n++;
}
}

Hull_nonodes=Hull_Nodes.size();


//NODE READER ENDS//
/* 
//DELAUNAY READER STARTS//
//delaunay reader declerations 
double current_delaunayvolume; 
ublas::c_vector<int,4> current_delaunaynodes;

//delaunay reader allocation 
Hull_delaunayinput>>Hull_nodelaunays; 
Hull_Delaunays.resize(Hull_nodelaunays); 


//reading & constructing delaunays
int current_delaunayfeatured; 
for(int d=0;d<Hull_nodelaunays;d++)
{
current_delaunayfeatured=1;
Hull_delaunayinput>>current_delaunaynodes[0]; 
Hull_delaunayinput>>current_delaunaynodes[1]; 
Hull_delaunayinput>>current_delaunaynodes[2];
Hull_delaunayinput>>current_delaunaynodes[3];

Hull_Delaunays[d]=new Delaunay(d,current_delaunaynodes); 

int cumul_featuring=0;
for(int n=0;n<4;n++)
{
Hull_Nodes[current_delaunaynodes[n]]->Push_homedelaunays(d); 
cumul_featuring=cumul_featuring+Hull_Nodes[current_delaunaynodes[n]]->Get_nodefeatured();
}
if(cumul_featuring==0)
current_delaunayfeatured=0; 
Hull_Delaunays[d]->Set_delaunayfeatured(current_delaunayfeatured); 
}


Hull_delaunayinput>>Hull_nodelaunays; 


for(int d=0;d<Hull_nodelaunays;d++)
{
Hull_delaunayinput>>current_delaunayvolume; 
Hull_Delaunays[d]->Set_delaunayvolume(current_delaunayvolume); 
}


Hull_Calculate_DelaunayProperties(); 


cout<<Hull_commandtab<<"Average delaunay volume:"<<averagedelaunayvolume<<endl;
cout<<Hull_commandtab<<"Average vertex to center value:"<<averagevertextocenter<<endl;
*/
cout<<Hull_commandtab<<"End reading the nodes & delaunays "<<endl; 
Hull_commandtab.erase(Hull_commandtab.begin(),Hull_commandtab.begin()+3);

}