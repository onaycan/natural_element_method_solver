

class Model 

{
private: 
string Model_name; //can:model name which can be specified by the user 
string Model_commandtab; //command tab for the Model functions 

Hull *Nodalhull; //can:hull of this model, which has only nodal sites 
Hull* NodalGaussianhull; //can:hull of this model which has nodal and gaussian sites 

ifstream Model_Input; //can: the model input file (mainly )
ofstream Model_debugfile; //can:debugfile of the Model 

public: 
//can: very default constructer, which does nothing 
//can: is necessary to open pointer tyoe Model object 
Model (){}

//can:bear yourself function of the model 
void Model_Bear_Yourself();
void GenerateNGinput(string _nodalgaussianhullname);

};