#//! user_eg3.cpp -- Invoke rbox and qhull from C++

#include "RboxPoints.h"
#include "QhullError.h"
#include "QhullQh.h"
#include "QhullFacet.h"
#include "QhullFacetList.h"
#include "QhullLinkedList.h"
#include "QhullVertex.h"
#include "Qhull.h"

#include <cstdio>   /* for printf() of help message */
#include <ostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

using orgQhull::Qhull;
using orgQhull::QhullError;
using orgQhull::QhullFacet;
using orgQhull::QhullFacetList;
using orgQhull::QhullQh;
using orgQhull::RboxPoints;
using orgQhull::QhullVertex;
using orgQhull::QhullVertexSet;

int main(int argc, char **argv);
int user_eg3(int argc, char **argv);

char prompt[]= "\n\
user_eg3 -- demonstrate calling rbox and qhull from C++.\n\
\n\
  eg-100                       Run the example in qh-code.htm\n\
  rbox \"200 D4\" ...          Generate points from rbox\n\
  qhull \"d p\" ...            Run qhull and produce output\n\
  qhull-cout \"o\" ...         Run qhull and produce output to cout\n\
\n\
For example\n\
  user_eg3 rbox qhull\n\
  user_eg3 rbox qhull d\n\
  user_eg3 rbox \"10 D2\"  \"2 D2\" qhull  \"s p\"\n\
\n\
";


/*--------------------------------------------
-user_eg3-  main procedure of user_eg3 application
*/
int main(int argc, char **argv) {

    if(argc==1){
        cout << prompt;
        return 1;
    }
    try{
        return user_eg3(argc, argv);
    }catch(QhullError &e){
        cerr << e.what() << std::endl;
        return e.errorCode();
    }
}//main

int user_eg3(int argc, char **argv)
{
    if(strcmp(argv[1], "eg-100")==0){
        RboxPoints rbox;
        rbox.appendPoints("100");
        Qhull qhull;
        qhull.runQhull(rbox, "");
        QhullFacetList facets= qhull.facetList();
        cout << facets;
        return 0;
    }
    RboxPoints rbox;
    Qhull qhull;
    int readingRbox= 0;
    int readingQhull= 0;
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "rbox")==0){
            if(readingRbox!=0 || readingQhull!=0){
                cerr << "user_eg3 -- \"rbox\" must be first" << endl;
                return 1;
            }
            readingRbox++;
        }else if(strcmp(argv[i], "qhull")==0
        || strcmp(argv[i], "qhull-cout")==0){
            if(readingQhull){
                cerr << "user_eg3 -- only one \"qhull\" or \"qhull-cout\" allowed." << endl;
                return 1;
            }
            readingQhull++;
            readingRbox= 0;
            if(strcmp(argv[i], "qhull-cout")==0){
                qhull.setOutputStream(&cout);
            }
        }else if(readingRbox){
            readingRbox++;
            cerr << "rbox " << argv[i] << endl;
            rbox.appendPoints(argv[i]);
            if(rbox.hasRboxMessage()){
                cerr << "user_eg3 " << argv[i] << " -- " << rbox.rboxMessage();
                return rbox.rboxStatus();
            }
        }else if(readingQhull){
            if(rbox.isEmpty()){
                cerr << "Enter dimension count coordinates.  End with ^Z (Windows) or ^D (Unix).\n";
                rbox.appendPoints(cin);
            }
            if(readingQhull==1){
                qhull.runQhull(rbox, argv[i]);
                qhull.outputQhull();
            }else{
                qhull.outputQhull(argv[i]);
            }
            readingQhull++;
            if(qhull.hasQhullMessage()){
                cerr << "\nResults of " << argv[i] << "\n" << qhull.qhullMessage();
                qhull.clearQhullMessage();
            }
        }else{
            cerr << "user_eg3 error: Expecting qhull, qhull-cout, or rbox.  Got " << argv[i] << endl;
            return 1;
        }
    }//foreach argv
    if(readingRbox){
        cout << rbox;
        return 0;
    }
    if(readingQhull==1){ // e.g., rbox 10 qhull
        if(rbox.isEmpty()){
            rbox.appendPoints("10 D2");
        }
        qhull.runQhull(rbox, "");
        qhull.outputQhull();
        if(qhull.hasQhullMessage()){
            cerr << "\nResults of qhull\n" << qhull.qhullMessage();
            qhull.clearQhullMessage();
        }
    }
    if(qhull.useOutputStream){
        return 0;
    }
    QhullFacetList facets= qhull.facetList();
    cout << "\nFacets created by Qhull::runQhull()\n" << facets;
    return 0;
}//user_eg3

