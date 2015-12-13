#include <stdlib.h>

#include "vmci_sockets.h"
#include <stdio.h>
#include <sys/socket.h>

#define VMWARE_PLAYER_HOST_CID 0
#define VMWARE_ESXI_HOST_CID 2

//
// Connection-oriented 
//
int try_connection(int CID, int port)
{
   int afVMCI = VMCISock_GetAFValue();

   int sockfd_stream;

   fprintf(stderr, "vmci connecting to=[CID]%u:%u\n", CID, port);

   sockfd_stream = socket(afVMCI, SOCK_STREAM, 0);
   if (sockfd_stream < 0) {
     perror("error creating socket\n");  
     exit(1);
   }

   fprintf(stderr, "vmci socket=%d\n", sockfd_stream);

   struct sockaddr_vm my_addr = {0};
   my_addr.svm_family = afVMCI;
   my_addr.svm_cid = VMADDR_CID_ANY;
   my_addr.svm_port = VMADDR_PORT_ANY;

   if (bind(sockfd_stream, (struct sockaddr *) &my_addr, sizeof my_addr) == -1) {
     perror("bind");
     close(sockfd_stream);
     exit(1);
   }

   struct sockaddr_vm their_addr = {0};
   their_addr.svm_family = afVMCI;
   their_addr.svm_cid = CID;
   their_addr.svm_port = port;
   if ((connect(sockfd_stream, (struct sockaddr *) &their_addr, sizeof their_addr)) == -1) {
     perror("connect");
     fprintf( stderr, "Closing vmci socket %u\n", sockfd_stream );
     close(sockfd_stream);
     return -1;
   }

   return sockfd_stream;
}

// Connection-oriented port scan
//
int host_port_scan(int CID)
{
   int i;

   printf("Scanning vsocket ports for CID=%u...\n", CID);

   for(i=0;i<70000;i++)
   {

      // Fork due to ESXi socket leakage problem

      if ( fork()== 0 ) {

	      int sock = try_connection( CID, i);
	      if (sock > 0) {
	        printf("-+-host port %d open\n",i);
	        close(sock);
	      } else {
	        //printf("---host port %d closed\n",i);   
	      }

	      exit(0);

      } else {
        int status;

	wait(&status);
      }
   }

}





int try_listen(int port)
{
   int afVMCI = VMCISock_GetAFValue();

   int sockfd_stream;

   fprintf(stderr, "vmci listening in port %d\n", port);

   sockfd_stream = socket(afVMCI, SOCK_STREAM, 0);
   if (sockfd_stream < 0) {
     perror("error creating socket\n");  
     exit(1);
   }

   fprintf(stderr, "vmci socket=%d\n", sockfd_stream);

   struct sockaddr_vm my_addr = {0};
   my_addr.svm_family = afVMCI;
   my_addr.svm_cid = VMADDR_CID_ANY;
   my_addr.svm_port = port;

   if (bind(sockfd_stream, (struct sockaddr *) &my_addr, sizeof my_addr) == -1) {
     perror("bind");
     close(sockfd_stream);
     return -1;
   }

   if (listen(sockfd_stream, 100) == -1) {
      perror("listen");
     return -1;
   }

   return sockfd_stream;
   return -1;
}





int dump_vsocket_properties()
{

   int afVMCI = VMCISock_GetAFValue();

   fprintf(stderr, "VMware vsockets environment properties\n");
   fprintf(stderr, "=======================================\n");

   fprintf(stderr, "vmci address familly=%d\n", afVMCI);

   if (afVMCI > 0) {

     fprintf(stderr, "vmci is present\n", afVMCI);

     int localCID = VMCISock_GetLocalCID();
     fprintf(stderr, "vmci local CID=%d\n", localCID);

     if (localCID == VMWARE_PLAYER_HOST_CID) {
        fprintf(stderr, "vmware player host machine detected (CID=0)\n");
     } else if (localCID == VMWARE_ESXI_HOST_CID) {
        fprintf(stderr, "vmware ESXi host machine detected (CID=0)\n");
     } else {
	fprintf(stderr, "guest machine detected (CID=%u)\n", localCID);
     }

     return 1;

   } else {
 
    fprintf(stderr, "vmci is NOT present\n", afVMCI);
    return 0;
   }

}