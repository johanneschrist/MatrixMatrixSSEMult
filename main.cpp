#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//using namespace System;
using namespace std;

//declare the prototypes,
void mmul_cpp(const float *a, const float *b, float *r, int size); //using c++ only
void mmulSSE_obj(const float *a, const float *b, float *r, int size); //SSE using objects
void mmulSSE_intr(const float *a, const float *b, float *r, int size); //SSE using intrinsics
void mmulSSE_asm(const float *a, const float *b, float *r, int size); //SSE using inline assembly

int _tmain(int argc, _TCHAR* argv[])
{
__int64 ctr1 = 0, ctr2 = 0, freq = 0;
int acc = 0, i = 0;

//Create arrays of specific sizes... treat arrays as linear elements
srand(1.0f*time(NULL)); //start seeding...
float numberium, numberium2;	
numberium = rand() % 10 + 1.0f;

int size;
cout<<"Please input the square matrix size for \ngenerating random arrays, always multiples of 4: ";
cin>>size; //ask user to input array size ---> ALWAYS multiples of 4 <---

float* a = new float[size*size];
float* b = new float[size*size];
float* r = new float[size*size];

for (int i = 0; i < (size*size); i++){
	numberium = rand() % 10 + 0.1f * i;
	numberium2 = rand() % 10 + 0.1f * i;
	a[i] = numberium; //initialize each matrix with a rand value...
	b[i] = numberium2; //initialize each matrix with a rand value...
}

cout<<"\n\nThis is Array [A]"<<endl;
for (int i = 0; i < (size*size); i++){
	if (i % size == 0) cout<<endl;
	cout<<a[i]<<"\t";
}
						
cout<<"\n\nThis is Array [B]"<<endl;
for (int i = 0; i < (size*size); i++){
	if (i % size == 0) cout<<endl;
	cout<<b[i]<<"\t";
}

int option = 0;
cout<<"\n\n\nPlease select which version of multiplication to use: \n\n0 - Straight C++ code \n1 - SSE Intrinsics \n2 - SSE inline assembly \n3 - SSE C++ Objects \n\nOption --> "; 
cin>>option;

// Start timing the code.
if (QueryPerformanceCounter((LARGE_INTEGER *)&ctr1)!= 0)
{

// Code segment is being timed.
// Start TIMER

/////////////////////////////chose wich version of matrix-matrix to be used.../////////

if (option == 0) mmul_cpp(&a[0],&b[0],&r[0], size); //straight c++
if (option == 1) mmulSSE_intr(&a[0],&b[0],&r[0], size); //SSE intrinsics
if (option == 2) mmulSSE_asm(&a[0],&b[0],&r[0], size); //SSE Assembly
if (option == 3) mmulSSE_obj(&a[0],&b[0],&r[0], size); //SSE objects

///////////////////////////////////////uncomment this if wanting to show results, comment other wise.....///////
						
						
						cout<<"\n\nThis is [A]*[B]"<<endl;
						for (int i = 0; i < (size*size); i++){
						if (i % size == 0) cout<<endl;
						cout<<r[i]<<"\t";
						}
/////////////////////////////////////////////////////////////////////////////////////////////////
//STOP TIMER
// output the time difference stop_time-Star_time
// Finish timing the code.
QueryPerformanceCounter((LARGE_INTEGER *)&ctr2);
//Console::WriteLine("Start Value: {0}",ctr1.ToString());
//Console::WriteLine("End Value: {0}",ctr2.ToString());
QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
// freq is number of counts per second. It approximates the CPU frequency
//Console::WriteLine("QueryPerformanceFrequency : {0} counts per Seconds.",freq.ToString());
// Console::WriteLine(S"QueryPerformanceCounter minimum resolution: 1/{0} Seconds.",freq.ToString());
//Console::WriteLine("QueryPerformanceCounter minimum resolution: 1/{0} Seconds.",freq.ToString());
// In Visual Studio 2005, this line should be changed to: Console::WriteLine("QueryPerformanceCounter minimum resolution: 1/{0} Seconds.",freq.ToString());
//Console::WriteLine("ctr2 - ctr1: {0} counts.",((ctr2 - ctr1) * 1.0 / 1.0).ToString());
cout<<"\n\n65536 Increments by 1 computation time: {0} seconds... "<<((ctr2 - ctr1) * 1.0 / freq)<<endl;
}
else
{
DWORD dwError = GetLastError();
//Console::WriteLine("Error value = {0}",dwError.ToString());
// Console::WriteLine(S"Error value = {0}",dwError.ToString());// In Visual Studio 2005, this line should be changed to: Console::WriteLine("Error value = {0}",dwError.ToString());
}
// Make the console window wait.
///Console::WriteLine();
///Console::Write("Press ENTER to finish.");
///Console::Read();
return 0;
}
