#include <xmmintrin.h>
#include <iostream>
#include <fvec.h>
using namespace std;

void mmulSSE_obj(const float *a, const float *b, float *r, int size){
				
				_declspec(align(32)) float* results =	new _declspec(align(32)) float[4]; //declare this array to be used as vector response...

	float result = 0;
	int rcounter = 0;
	for (int i = 0; i < size; i++){/// this will iterate thru every row
		
		int index = 0;
		_declspec(align(32)) float* arraya = new _declspec(align(32)) float[size]; 
		for (int row = size*i; row <= (size*(i+1)) -1; row++){ /// this will itirate over every element of the row
			arraya[index] = a[row];
			index++;
		}
		
		for (int kk = 0; kk< size; kk++){//this will itirate over every column
			_declspec(align(32)) float* arrayb = new _declspec(align(32)) float[size]; 
			int index2 = 0;
				for (int column = kk; column <= ((size*size)-size) + kk; column+=size){ //this will itirate over every element of the column
					arrayb[index2] = b[column];
					index2++;
				}
				result = 0;	

				////insert SSE code right here...where multiplying both vectors...4 at the time...

				float number = 0;
				for (int sind = 0; sind < size; sind+=4){	
					F32vec4 *av=(F32vec4 *) &arraya[sind];
					F32vec4 *bv=(F32vec4 *) &arrayb[sind];
					F32vec4 *result=(F32vec4 *) results;
					*result=*av * *bv;
					
				int i;				
				for (i = 0; i < 4; i++) number = number + results[i];	
												
				}
				r[rcounter] = number;
				rcounter++;

		}
	}
}	

void mmulSSE_asm(const float *a, const float *b, float *r, int size)
{
	float result = 0;
	int rcounter = 0;
	for (int i = 0; i < size; i++){/// this will iterate thru every row
		
		int index = 0;
		float* arraya = new float[size]; 
		for (int row = size*i; row <= (size*(i+1)) -1; row++){ /// this will itirate over every element of the row
			arraya[index] = a[row];
			index++;
		}
		
		for (int kk = 0; kk< size; kk++){//this will itirate over every column
			float* arrayb = new float[size]; 
			int index2 = 0;
				for (int column = kk; column <= ((size*size)-size) + kk; column+=size){ //this will itirate over every element of the column
					arrayb[index2] = b[column];
					index2++;
				}
				result = 0;	

				float number = 0;
				for (int sind = 0; sind < size; sind+=4){	
					float vectorIn1[] = {arraya[sind+0], arraya[sind+1], arraya[sind+2], arraya[sind+3]};
					float vectorIn2[] = {arrayb[sind+0], arrayb[sind+1], arrayb[sind+2], arrayb[sind+3]};
					float results[4] = {0.0, 0.0, 0.0, 0.0};// = {arrayb[sind+3], arrayb[sind+2], arrayb[sind+1], arrayb[sind+0]};
					
					 __asm
					{		
							movups xmm0, [vectorIn1] //move arrays into mmx's
							movups xmm1, [vectorIn2]
							mulps xmm0, xmm1 //multiply packed single fp #'s
							movups [results], xmm0 //store xmm0 into results[]
					}

					   				
				int i;				
				for (i = 0; i < 4; i++) number = number + results[i];
				
				}
				r[rcounter] = number;
				rcounter++;

		}
	}
}

void mmulSSE_intr(const float *a, const float *b, float *r, int size)
{
				///LOAD VARIABLES FOR VECTORIZATION...
				__m128 t0, t1;
				float* results = new float[4];
				

	float result = 0;
	int rcounter = 0;
	for (int i = 0; i < size; i++){/// this will iterate thru every row
		
		int index = 0;
		_declspec(align(32)) float* arraya = new _declspec(align(32)) float[size]; 
		for (int row = size*i; row <= (size*(i+1)) -1; row++){ /// this will itirate over every element of the row
			arraya[index] = a[row];
			index++;
		}
		
		for (int kk = 0; kk< size; kk++){//this will itirate over every column
			_declspec(align(32)) float* arrayb = new _declspec(align(32)) float[size]; 
			int index2 = 0;
				for (int column = kk; column <= ((size*size)-size) + kk; column+=size){ //this will itirate over every element of the column
					arrayb[index2] = b[column];
					index2++;
				}
				result = 0;	

				////insert SSE code right here...where multiplying both vectors...4 at the time...
				float number = 0;
				for (int sind = 0; sind < size; sind+=4){				
			
				t0 = _mm_set_ps(arraya[sind+3], arraya[sind+2], arraya[sind+1], arraya[sind+0]); //load aligned elements of float array...
				t1 = _mm_set_ps(arrayb[sind+3], arrayb[sind+2], arrayb[sind+1], arrayb[sind+0]);
				t0 = _mm_mul_ps(t0, t1); //multiply vectors...
				_mm_storeu_ps(results, t0); //store in resulting vector...

				//compute the result for the entry..					
				int i;				
				for (i = -0; i < 4; i++) number = number + results[i];							
				}
				r[rcounter] = number; //store the result into the resulting array
				rcounter++;

		}
	}
}	

void mmul_cpp(const float *a, const float *b, float *r, int size)
{				
	float result = 0;
	int rcounter = 0;
	for (int i = 0; i < size; i++){/// this will iterate thru every row
		
		int index = 0;
		float* arraya = new float[size]; 
		for (int row = size*i; row <= (size*(i+1)) -1; row++){ /// this will itirate over every element of the row
			arraya[index] = a[row];
			index++;
		}
		
		for (int kk = 0; kk< size; kk++){//this will itirate over every column
			float* arrayb = new float[size]; 
			int index2 = 0;
				for (int column = kk; column <= ((size*size)-size) + kk; column+=size){ //this will itirate over every element of the column
					arrayb[index2] = b[column];
					index2++;
				}
				result = 0;	

				////insert SSE code right here...where multiplying both vectors...4 at the time...

				float number = 0;
				for (int sind = 0; sind < size; sind+=4){	//storing vectors for processing...(4 in lenght...)
					float* a1 = new float[4];
					float* b1 = new float[4];
					float* results = new float[4];
				
				for (int i = 0; i < 4; i++){ //calculate each entry...using c++ code only.
					a1[i] = arraya[sind+i];
					b1[i] = arrayb[sind+i];
					results[i] = a1[i] * b1[i];
					number = number + results[i];
				}
												
				}
				r[rcounter] = number;
				rcounter++;

		}
	}
}	
