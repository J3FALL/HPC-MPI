// HPC-MPI.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "mpi.h"
#include <iostream>
#include <cmath>

int BUF_LENGTH[] = {10, 100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
int RSEND_BUF_LENGTH[] = { 10, 100, 200, 300, 400, 500, 1000 };
int SIZE = sizeof(BUF_LENGTH) / sizeof(*BUF_LENGTH);
int RSEND_SIZE = sizeof(RSEND_BUF_LENGTH) / sizeof(*RSEND_BUF_LENGTH);

int ITERATIONS = 10000;

void sendRecvExperiment(int procRank, int* sentBuf, int* recievedBuf, int bufLength, int iterations) {

	MPI_Status status;
	double startTime, finishTime;

	if (procRank == 0) {
		std::cout << "\n Send & Recv methods \n";
	}

	startTime = MPI_Wtime();

	for (int i = 0; i < iterations; i++) {
		if (procRank == 0) {
			MPI_Send(sentBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD);
			MPI_Recv(recievedBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		}
		else if (procRank == 1) {
			MPI_Recv(recievedBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			MPI_Send(sentBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}

	finishTime = MPI_Wtime();

	if (procRank == 0) {
		std::cout << "\n Finished \n";
		std::cout << "\n Msg length : " << bufLength << " Duration : " << finishTime - startTime << " \n";
	}

}

void sSendRecvExperiment(int procRank, int* sentBuf, int* recievedBuf, int bufLength, int iterations) {

	MPI_Status status;
	double startTime, finishTime;

	if (procRank == 0) {
		std::cout << "\n Ssend & Recv methods \n";
	}

	startTime = MPI_Wtime();

	for (int i = 0; i < iterations; i++) {
		if (procRank == 0) {
			MPI_Ssend(sentBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD);
			MPI_Recv(recievedBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		}
		else if (procRank == 1) {
			MPI_Recv(recievedBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			MPI_Ssend(sentBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}

	finishTime = MPI_Wtime();

	if (procRank == 0) {
		std::cout << "\n Finished \n";
		std::cout << "\n Msg length : " << bufLength << " Duration : " << finishTime - startTime << " \n";
	}

}

void rSendRecvExperiment(int procRank, int* sentBuf, int* recievedBuf, int bufLength, int iterations) {

	MPI_Status status;
	double startTime, finishTime;

	if (procRank == 0) {
		std::cout << "\n Rsend & Recv methods \n";
	}

	startTime = MPI_Wtime();

	for (int i = 0; i < iterations; i++) {
		if (procRank == 0) {
			MPI_Rsend(sentBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD);
			MPI_Recv(recievedBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		}
		else if (procRank == 1) {
			MPI_Recv(recievedBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			MPI_Rsend(sentBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}

	finishTime = MPI_Wtime();

	if (procRank == 0) {
		std::cout << "\n Finished \n";
		std::cout << "\n Msg length : " << bufLength << " Duration : " << finishTime - startTime << " \n";
	}

}

void bSendRecvExperiment(int procRank, int* sentBuf, int* recievedBuf, int bufLength, int iterations) {
	MPI_Status status;
	double startTime, finishTime;

	if (procRank == 0) {
		std::cout << "\n Bsend & Recv methods \n";
	}

	startTime = MPI_Wtime();

	int packedMsgSize;
	MPI_Pack_size(bufLength, MPI_INT, MPI_COMM_WORLD, &packedMsgSize);

	int bufferSize = iterations * (MPI_BSEND_OVERHEAD + bufLength);
	int* buf = new int[bufferSize];

	MPI_Buffer_attach(buf, bufferSize);
	for (int i = 0; i < iterations; i++) {
		if (procRank == 0) {
			MPI_Bsend(sentBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD);
			MPI_Recv(recievedBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		}
		else if (procRank == 1) {
			MPI_Bsend(sentBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD);
			MPI_Recv(recievedBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		}
	}
	MPI_Buffer_detach(buf, &bufferSize);

	finishTime = MPI_Wtime();

	if (procRank == 0) {
		std::cout << "\n Finished \n";
		std::cout << "\n Msg length : " << bufLength << " Duration : " << finishTime - startTime << " \n";
	}
}

void combinedSendRecv(int procRank, int* sentBuf, int* recievedBuf, int bufLength, int iterations) {

	MPI_Status status;
	double startTime, finishTime;

	if (procRank == 0) {
		std::cout << "\n Combined Send & Recv methods \n";
	}

	startTime = MPI_Wtime();

	for (int i = 0; i < iterations; i++) {
		if (procRank == 0) {
			MPI_Sendrecv(sentBuf, bufLength, MPI_INT, 1, 0,
				recievedBuf, bufLength, MPI_INT, 1, 0,
				MPI_COMM_WORLD, &status);
		}
		else if (procRank == 1) {
			MPI_Sendrecv(sentBuf, bufLength, MPI_INT, 0, 0,
				recievedBuf, bufLength, MPI_INT, 0, 0,
				MPI_COMM_WORLD, &status);
		}
	}

	finishTime = MPI_Wtime();

	if (procRank == 0) {
		std::cout << "\n Finished \n";
		std::cout << "\n Msg length : " << bufLength << " Duration : " << finishTime - startTime << " \n";
	}


}

void isendIrecvExperiment(int procRank, int* sentBuf, int* recievedBuf, int bufLength, int iterations) {

	MPI_Status statuses[2];
	MPI_Request requests[2];

	double startTime, finishTime;

	if (procRank == 0) {
		std::cout << "\n ISend & IRecv methods \n";
	}

	startTime = MPI_Wtime();

	for (int i = 0; i < iterations; i++) {
		if (procRank == 0) {
			MPI_Isend(sentBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[0]);
			MPI_Irecv(recievedBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[1]);
			MPI_Waitall(2, requests, statuses);
		}
		else if (procRank == 1) {
			MPI_Isend(sentBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &requests[0]);
			MPI_Irecv(recievedBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &requests[1]);
			MPI_Waitall(2, requests, statuses);
		}
	}

	finishTime = MPI_Wtime();

	if (procRank == 0) {
		std::cout << "\n Finished \n";
		std::cout << "\n Msg length : " << bufLength << " Duration : " << finishTime - startTime << " \n";
	}



}

void iSsendIrecvExperiment(int procRank, int* sentBuf, int* recievedBuf, int bufLength, int iterations) {

	MPI_Status statuses[2];
	MPI_Request requests[2];

	double startTime, finishTime;

	if (procRank == 0) {
		std::cout << "\n Issend & IRecv methods \n";
	}

	startTime = MPI_Wtime();

	for (int i = 0; i < iterations; i++) {
		if (procRank == 0) {
			MPI_Issend(sentBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[0]);
			MPI_Irecv(recievedBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[1]);
			MPI_Waitall(2, requests, statuses);
		}
		else if (procRank == 1) {
			MPI_Isend(sentBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &requests[0]);
			MPI_Irecv(recievedBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &requests[1]);
			MPI_Waitall(2, requests, statuses);
		}
	}

	finishTime = MPI_Wtime();

	if (procRank == 0) {
		std::cout << "\n Finished \n";
		std::cout << "\n Msg length : " << bufLength << " Duration : " << finishTime - startTime << " \n";
	}

}

void iRsendIrecvExperiment(int procRank, int* sentBuf, int* recievedBuf, int bufLength, int iterations) {

	MPI_Status statuses[2];
	MPI_Request requests[2];

	double startTime, finishTime;

	if (procRank == 0) {
		std::cout << "\n IRsend & IRecv methods \n";
	}

	startTime = MPI_Wtime();

	for (int i = 0; i < iterations; i++) {
		if (procRank == 0) {
			MPI_Irsend(sentBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[0]);
			MPI_Irecv(recievedBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[1]);
			MPI_Waitall(2, requests, statuses);
		}
		else if (procRank == 1) {
			MPI_Isend(sentBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &requests[0]);
			MPI_Irecv(recievedBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &requests[1]);
			MPI_Waitall(2, requests, statuses);
		}
	}

	finishTime = MPI_Wtime();

	if (procRank == 0) {
		std::cout << "\n Finished \n";
		std::cout << "\n Msg length : " << bufLength << " Duration : " << finishTime - startTime << " \n";
	}

}

void iBsendIrecvExperiment(int procRank, int* sentBuf, int* recievedBuf, int bufLength, int iterations) {
	MPI_Status statuses[2];
	MPI_Request requests[2];

	double startTime, finishTime;

	if (procRank == 0) {
		std::cout << "\n IBsend & IRecv methods \n";
	}

	startTime = MPI_Wtime();

	int packedMsgSize;
	MPI_Pack_size(bufLength, MPI_INT, MPI_COMM_WORLD, &packedMsgSize);

	int bufferSize = iterations * (MPI_BSEND_OVERHEAD + bufLength);
	int* buf = new int[bufferSize];

	MPI_Buffer_attach(buf, bufferSize);
	for (int i = 0; i < iterations; i++) {
		if (procRank == 0) {
			MPI_Ibsend(sentBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[0]);
			MPI_Irecv(recievedBuf, bufLength, MPI_INT, 1, 0, MPI_COMM_WORLD, &requests[1]);
			MPI_Waitall(2, requests, statuses);
		}
		else if (procRank == 1) {
			MPI_Ibsend(sentBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &requests[0]);
			MPI_Irecv(recievedBuf, bufLength, MPI_INT, 0, 0, MPI_COMM_WORLD, &requests[1]);
			MPI_Waitall(2, requests, statuses);
		}
	}
	MPI_Buffer_detach(buf, &bufferSize);
	delete[] buf;

	finishTime = MPI_Wtime();

	if (procRank == 0) {
		std::cout << "\n Finished \n";
		std::cout << "\n Msg length : " << bufLength << " Duration : " << finishTime - startTime << " \n";
	}
}

int main(int argc, char* argv[])
{

	MPI_Init(&argc, &argv);

	int procAmmount, procRank;
	MPI_Comm_size(MPI_COMM_WORLD, &procAmmount);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

	/*for (int index = 0; index < SIZE; index++) {
		int bufLength = BUF_LENGTH[index];
		int* sentBuf = new int[bufLength];
		int* recievedBuf = new int[bufLength];
		std::fill_n(sentBuf, bufLength, 7);

		iSsendIrecvExperiment(procRank, sentBuf, recievedBuf, bufLength, ITERATIONS);
	}*/
	
	for (int index = 0; index < RSEND_SIZE; index++) {
		int bufLength = RSEND_BUF_LENGTH[index];
		int* sentBuf = new int[bufLength];
		int* recievedBuf = new int[bufLength];
		std::fill_n(sentBuf, bufLength, 7);

		iBsendIrecvExperiment(procRank, sentBuf, recievedBuf, bufLength, ITERATIONS);
	}

	MPI_Finalize();

    return 0;
}

