#pragma once
#include<algorithm> //sort and erase/remove
#include<cmath>     //floor
#include<ctime>     //profiling
#include<string> //string manipulation
#include<vector>
#include"Helberg_Functions.h"

using namespace std;

const float GC_min = 0.25; 		//GC Parameters
const float GC_max = 0.75;

const int TR_Cutoff = 9;		//Tandem Repeat Parameters
const int STR_size = 5;

const int Palindrome_min = 4; 		//Palindrome parameter

const float Stacking_cutoff = 3.0; 	//Base Stacking parameter, more research needed

int Biochem(vector<length_t>&, int);						//determines biochemical stability of codewords in codebook, returns GC partition
string Assign_Nucleotides(int, int, int);					//Assigns nucleotides A, T, C and G to 0, 1, 2 and 3
string Reverse_Complement(string);						//Returns the reverse complement
void Palindromes(vector<vector<int> >&, vector<vector<string> >&);		//Searches for palindromes and inverse repeats
void Base_Stacking_Stability(vector<vector<int> >&, vector<vector<string> >&);	//check base stacking stability
void GC_Content(vector<vector<int> >&, vector<vector<string> >&);		//GC content
void Tandem_Repeat(vector<vector<int> >&, vector<vector<string> >&);		//look for tandem repeats
double Stacking_Stability(string);						//returns the stability of the BP neighbor interactions
void Add_Bad_Code(vector<vector<int> >&, int, int); 				//reduce redundancy
