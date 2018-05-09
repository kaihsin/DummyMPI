#ifndef MPI_HANDLER_HPP_INCLUDED
#define MPI_HANDLER_HPP_INCLUDED

#include <iostream>
#include <vector>
class MPI_Handler{

    public :
        int Rank;
        int NProc;
        bool IsInit;

        MPI_Handler(){
            Rank  = 0;
            NProc = 1;
            IsInit = 0;
        };

        void Initialize(int &argc,char *argv[]);
        void Synchronize();
        void Finalize();
        void Abort(const int &err_code);


        template<class T>
        void Sequencial_Print(const T &str){
            for(int i=0;i<NProc;i++){
                if(i==Rank) std::cout << "[Rank "<< Rank << " ] " << str << std::endl;
                Synchronize();
            }
        }


        /**
           @Title :       Gather function :  (Overloaded double, int, unsigned int, float,long long )
           @Description : Perform Gather with homogenious length vectors(segments) from each process (rank) to Destination Rank.
           @Requirement :
           @Return      : The vector with gathered data. Only the Process that assigned as DestRank will return a gathered vector.
                          Other processes will return a vector with 0 element.
           @Arguments   :
                          std::vector<T>     &SubSegments : The sub-segments of each process that is going to be gathered.
                          const unsgined int &NElemsFrom  : The number of elements that is going to be send. (Where the gathered vector will have length "NProc*NElemsFrom" )
                          const int          &DestRank    : The Destination (root) rank.
        */
        std::vector<double>       Gather(std::vector<double> &SubSegments,const unsigned int &NElemsFrom,const int &DestRank);
        std::vector<int>          Gather(std::vector<int>    &SubSegments,const unsigned int &NElemsFrom,const int &DestRank);
        std::vector<float>        Gather(std::vector<float>  &SubSegments,const unsigned int &NElemsFrom,const int &DestRank);
        std::vector<unsigned int> Gather(std::vector<unsigned int> &SubSegments,const unsigned int &NElemsFrom,const int &DestRank);
        std::vector<long long>    Gather(std::vector<long long> &SubSegments,const unsigned int &NElemsFrom,const int &DestRank);


        /**
           @Title :       Bcast function :  (Overloaded double, int, unsigned int, float,long long )
           @Description : Perform Bcast to all processes for the assigned Rank.
           @Requirement :
           @Return      : [ In argument return. ]
           @Arguments   :
                          std::vector<T>     &obj : Serve as [input/output. Boardcast the obj from assigned rank (ResRank) to other rank.
                                                    Note that the obj of other ranks as reciver are not need to initialize obj.

                          const int          &ResRank    : The Resource (root) rank.
        */
        void Broadcast(std::vector<double> &obj,const int &ResRank);
        void Broadcast(std::vector<float> &obj,const int &ResRank);
        void Broadcast(std::vector<int> &obj,const int &ResRank);
        void Broadcast(std::vector<unsigned int> &obj,const int &ResRank);
        void Broadcast(std::vector<long long> &obj,const int &ResRank);

        /**
           @Title :       Sendrecv function :  (Overloaded double )
           @Description : Perform Send to destinate process and recive from source process for a same amount of data and same type .
           @Requirement :
           @Return      : [ In argument return. ]
           @Arguments   :

        */
        void SendReceive(std::vector<double> &SendData, const int &DestRank, std::vector<double> &RecvData, const int &ResRank, const unsigned int &NElems);


};


#endif // MPI_HANDLER_HPP_INCLUDED
