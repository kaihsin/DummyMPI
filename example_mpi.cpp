#include <iostream>
#include "MPI_Handler.hpp"
#include "SSE_Type.hpp"
#include <vector>

using namespace std;


int main(int argc,char* argv[]){


    ///declare MPI Handler:
    MPI_Handler mpih;
    
    ///initialize first :
    mpih.Initialize(argc,argv);

    /*

      Some parallel section

    */

    //  Synchronize:
    mpih.Synchronize();


    ///  Gather 
    // combine all small segments to rank 1 :
    // only the destination will return an valid vector
    // other rank will return a empty vector
    vector<int> Segs(12);
    vector<int> result;
    int dest = 1;
    
    result = mpih.Gather(Segs,Segs.size(),Segs.size(),dest);
    

    //  Sequential_Print (handy for debug using):
    mpih.Sequencial_Print(result.size());

    //output :
    //+=====================+
    //[Rank 00] 0
    //[Rank 01] 12*mpih.NProc
    //[Rank 02] 0
    // .... 
    //+=====================+


    ///  Broadcast
    // copy Seg from rank 1 to all ranks :
    vector<int> Seg;
    int source = 1;

    if(mpih.Rank==source) Seg.resize(10); // only rank 1 have 10 elems
			     
    mpih.Boradcast(Seg,source);
    
    //  Sequential_Print (handy for debug using):
    mpih.Sequencial_Print(result.size());

    //output :
    //+=====================+
    //[Rank 00] 10
    //[Rank 01] 10
    //[Rank 02] 10
    // .... 
    //+=====================+

   

    ///finalize before end program
    mpih.Finalize();
}
