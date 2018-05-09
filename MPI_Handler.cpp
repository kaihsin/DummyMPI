#include "MPI_Handler.hpp"


#include "mpi.h"
#include <iostream>
using namespace std;






void MPI_Handler::Initialize(int &argc,char *argv[]){
    if(IsInit == 0){
        MPI_Init(&argc, &argv);                   //MPI initialize
        MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
        MPI_Comm_size(MPI_COMM_WORLD, &NProc);
        if(Rank==0){
            cout << "==========================================" <<endl;
            cout << "Using MPI   : " << NProc << endl;
            cout << "==========================================" <<endl;
            cout.flush();
        }
        IsInit = 1;


    }else{
        if(Rank==0) cout << "[WARNING!] MPI Already Initialize. Ignore.\n";
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

void MPI_Handler::Finalize(){
    if(IsInit == 1){
        MPI_Finalize();
        IsInit = 0;
    }else{
        cout << "[WARNING!] MPI Already Finalized. Ignore.\n";
    }

}

void MPI_Handler::Synchronize(){

    MPI_Barrier(MPI_COMM_WORLD);

}


void MPI_Handler::Abort(const int &err_code){
    MPI_Abort(MPI_COMM_WORLD,err_code);
}



vector<double> MPI_Handler::Gather(vector<double> &SubSegments,const unsigned int &NElemsFrom,const int &DestRank){
    vector<double> Rev;
    if(NElemsFrom > SubSegments.size()){ cout << "[Rank " << Rank << " ]" << "[ERROR][MPI_Handler::Gather] NElemsFrom exceed SubSegments.size().\n"; Abort(1); }

    if(Rank==DestRank){
        Rev.resize(NProc*NElemsFrom);
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_DOUBLE,&Rev[0],NElemsFrom,MPI_DOUBLE,DestRank,MPI_COMM_WORLD);
    }else{
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_DOUBLE,NULL,NElemsFrom,MPI_DOUBLE,DestRank,MPI_COMM_WORLD);
    }
    return Rev;

}

vector<float> MPI_Handler::Gather(vector<float> &SubSegments,const unsigned int &NElemsFrom,const int &DestRank){
    vector<float> Rev;
    if(NElemsFrom > SubSegments.size()){ cout << "[Rank " << Rank << " ]" << "[ERROR][MPI_Handler::Gather] NElemsFrom exceed SubSegments.size().\n"; Abort(1); }


    if(Rank==DestRank){
        Rev.resize(NProc*NElemsFrom);
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_FLOAT,&Rev[0],NElemsFrom,MPI_FLOAT,DestRank,MPI_COMM_WORLD);
    }else{
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_FLOAT,NULL,NElemsFrom,MPI_FLOAT,DestRank,MPI_COMM_WORLD);
    }
    return Rev;

}

vector<int> MPI_Handler::Gather(vector<int> &SubSegments,const unsigned int &NElemsFrom,const int &DestRank){
    vector<int> Rev;
    if(NElemsFrom > SubSegments.size()){ cout << "[Rank " << Rank << " ]" << "[ERROR][MPI_Handler::Gather] NElemsFrom exceed SubSegments.size().\n"; Abort(1); }

    if(Rank==DestRank){
        Rev.resize(NProc*NElemsFrom);
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_INT,&Rev[0],NElemsFrom,MPI_INT,DestRank,MPI_COMM_WORLD);
    }else{
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_INT,NULL,NElemsFrom,MPI_INT,DestRank,MPI_COMM_WORLD);
    }
    return Rev;

}

vector<unsigned int> MPI_Handler::Gather(vector<unsigned int> &SubSegments,const unsigned int &NElemsFrom,const int &DestRank){
    vector<unsigned int> Rev;
    if(NElemsFrom > SubSegments.size()){ cout << "[Rank " << Rank << " ]" << "[ERROR][MPI_Handler::Gather] NElemsFrom exceed SubSegments.size().\n"; Abort(1); }

    if(Rank==DestRank){
        Rev.resize(NProc*NElemsFrom);
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_UNSIGNED,&Rev[0],NElemsFrom,MPI_UNSIGNED,DestRank,MPI_COMM_WORLD);
    }else{
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_UNSIGNED,NULL,NElemsFrom,MPI_UNSIGNED,DestRank,MPI_COMM_WORLD);
    }
    return Rev;

}

vector<long long> MPI_Handler::Gather(vector<long long> &SubSegments,const unsigned int &NElemsFrom,const int &DestRank){
    vector<long long > Rev;
    if(NElemsFrom > SubSegments.size()){ cout << "[Rank " << Rank << " ]" << "[ERROR][MPI_Handler::Gather] NElemsFrom exceed SubSegments.size().\n"; Abort(1); }

    if(Rank==DestRank){
        Rev.resize(NProc*NElemsFrom);
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_LONG_LONG,&Rev[0],NElemsFrom,MPI_LONG_LONG,DestRank,MPI_COMM_WORLD);
    }else{
        MPI_Gather(&SubSegments[0],NElemsFrom,MPI_LONG_LONG,NULL,NElemsFrom,MPI_LONG_LONG,DestRank,MPI_COMM_WORLD);
    }
    return Rev;

}



void MPI_Handler::Broadcast(vector<double> &obj,const int &ResRank){
    unsigned int cnt = obj.size();

    ///Get the count from Resource:
    MPI_Bcast(&cnt,1,MPI_UNSIGNED,ResRank,MPI_COMM_WORLD);

    if(cnt != 0){
        if(Rank!=ResRank) obj.resize(cnt);
        MPI_Bcast(&obj[0],cnt,MPI_DOUBLE,ResRank,MPI_COMM_WORLD);
    }

}

void MPI_Handler::Broadcast(vector<int> &obj,const int &ResRank){

    unsigned int cnt = obj.size();
    ///Get the count from Resource:
    MPI_Bcast(&cnt,1,MPI_UNSIGNED,ResRank,MPI_COMM_WORLD);

    if(cnt != 0){
        if(Rank!=ResRank) obj.resize(cnt);
        MPI_Bcast(&obj[0],cnt,MPI_INT,ResRank,MPI_COMM_WORLD);
    }

}

void MPI_Handler::Broadcast(vector<unsigned int> &obj,const int &ResRank){

    unsigned int cnt = obj.size();
    ///Get the count from Resource:
    MPI_Bcast(&cnt,1,MPI_UNSIGNED,ResRank,MPI_COMM_WORLD);

    if(cnt != 0){
        if(Rank!=ResRank) obj.resize(cnt);
        MPI_Bcast(&obj[0],cnt,MPI_UNSIGNED,ResRank,MPI_COMM_WORLD);
    }

}

void MPI_Handler::Broadcast(vector<float> &obj,const int &ResRank){

    unsigned int cnt = obj.size();
    ///Get the count from Resource:
    MPI_Bcast(&cnt,1,MPI_UNSIGNED,ResRank,MPI_COMM_WORLD);

    if(cnt != 0){
        if(Rank!=ResRank) obj.resize(cnt);
        MPI_Bcast(&obj[0],cnt,MPI_FLOAT,ResRank,MPI_COMM_WORLD);
    }

}

void MPI_Handler::Broadcast(vector<long long> &obj,const int &ResRank){

    unsigned int cnt = obj.size();
    ///Get the count from Resource:
    MPI_Bcast(&cnt,1,MPI_UNSIGNED,ResRank,MPI_COMM_WORLD);

    if(cnt != 0){
        if(Rank!=ResRank) obj.resize(cnt);
        MPI_Bcast(&obj[0],cnt,MPI_LONG_LONG,ResRank,MPI_COMM_WORLD);
    }

}

void MPI_Handler::SendReceive(std::vector<double> &SendData, const int &DestRank, std::vector<double> &RecvData, const int &ResRank, const unsigned int &NElems){
	MPI_Status status;
	MPI_Sendrecv(&SendData[0], NElems, MPI_DOUBLE,
				DestRank,0, &RecvData[0], NElems, MPI_DOUBLE,
                ResRank, 0,
                MPI_COMM_WORLD,&status);


}
