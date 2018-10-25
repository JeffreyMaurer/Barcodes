/*#pragma once
#include<vector>
#include"Tenengolts.h"

using namespace std;

class BaseMultiMatrix;
class MultiMatrix;

typedef BaseMultiMatrix bmM;
typedef MultiMatrix mM;

class BaseMultiMatrix
{
	virtual inline bool is_outer() = 0;
	virtual void push_back(length_t value) = 0;
};

class MultiMatrix : BaseMultiMatrix
{
private:
	vector<bmM*> m_matrix;
	friend void print(ostream& os, const bmM& matrix, vector<int> residues);
	void back(MultiMatrix*& mmPtr, vector<int>& residue_values);
	void push_back(length_t value); //do nothing
public:
	MultiMatrix(int dimensions, int length); //dim = del, length = mod p
	//MultiMatrix(int, int, const mM&);
	~MultiMatrix();
	void push_back(vector<int>& residue_values, length_t code);
	inline bool is_empty();
	void empty_matrix();
	friend ostream& operator<<(ostream& os, const mM& matrix);
	inline bool is_outer();
};

class Outer : BaseMultiMatrix
{
private:
	vector<length_t> m_values;
public:
	Outer();
	void push_back(length_t value);
	inline bool is_outer();
	length_t operator[](length_t index);
};

typedef Outer o;
*/