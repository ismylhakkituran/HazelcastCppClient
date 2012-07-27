#include <iostream>
#include <sstream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <ctime>
#include <sys/time.h>
#include <atomic>
//--------------------------------------------------------------------------------------------------
#include "Client/Foo.hpp"
#include "Client/HazelcastClient.hpp"
#include "Client/ClientConfig.hpp"
#include "Client/Map.hpp"
//--------------------------------------------------------------------------------------------------
int THREAD_COUNT 	 = 200;
int ENTRY_COUNT 	 = 10 * 1000;
int VALUE_SIZE		 = 1000;
int STATS_SECONDS 	 = 10;
int GET_PERCENTAGE 	 = 40;
int PUT_PERCENTAGE 	 = 40;
//--------------------------------------------------------------------------------------------------
struct AtomicCounter {
  std::atomic<int> putValue;
  std::atomic<int> getValue;
   void putIncrement(){
        ++putValue;
    }
   void putDecrement(){
        ++getValue;
    }
};
//--------------------------------------------------------------------------------------------------
int main(int argc,char* argv[])
{	string take;
	std::cout<<"..............Play Hazelcast C++ Library..............\n\n";

	ClientConfig clientConfig;

	clientConfig.addAddress             ("localhost");	
	clientConfig.groupconfig.setProtocolType  ("P01");      
	clientConfig.groupconfig.setName          ("dev"); 	
	clientConfig.groupconfig.setPassword ("dev-pass");            
	HazelcastClient client(clientConfig );

	timeval ta;
    timeval tb;

	std::vector<std::thread> threads;
    Map map (client.connection) ;

    string toWrite;
    for(int g=0;g<130;g++)
    toWrite.push_back('x');

    gettimeofday(&ta, 0);
    for(int i=0; i<THREAD_COUNT ; i++){

    		threads.push_back(std::thread(&Map::startPut,&map,20,toWrite,take ) );
    		threads[i].join();
    }
    /*
    for(auto& thread : threads)
        thread.join();*/
    gettimeofday(&tb, 0);
    double tamill = (ta.tv_sec) * 1000 + (ta.tv_usec) / 1000 ;
    double tbmill = (tb.tv_sec) * 1000 + (tb.tv_usec) / 1000 ;
    std::cout << "\ndifference time: " << (tbmill- tamill ) << " miliseconds.";

    std::cin>>take;

       // std::cout<<"\nHelp: test t200 v130 p10 g85 "<<std::endl;
       // std::cout<<"Means 200 threads, value-size 130 bytes, 10% put, 85% get"<<std::endl;
        std::cout<<"\nStarted Test with "<<std::endl;
        std::cout<<"\n      Thread Count: " << THREAD_COUNT<<std::endl;
        std::cout<<"       Entry Count: " << ENTRY_COUNT<<std::endl;
        std::cout<<"        Value Size: " << VALUE_SIZE<<std::endl;
        std::cout<<"    Get Percentage: " << GET_PERCENTAGE<<std::endl;
        std::cout<<"    Put Percentage: " << PUT_PERCENTAGE<<std::endl;
        std::cout<<" Remove Percentage: " << (100 - (PUT_PERCENTAGE + GET_PERCENTAGE))<<std::endl;

        AtomicCounter ut;
        ut.putValue=0;

              std::cout<<"\n count-> "<<threads.size() ;
//        volatile long aa;    std::cout<<"\n------------waiting--for--ever--anymore----------------";
	    while(true){
		//wait here... ever
	    }
	return 0;
}
//--------------------------------------------------------------------------------------------------
