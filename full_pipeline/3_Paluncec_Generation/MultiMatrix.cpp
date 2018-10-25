/*#include "MultiMatrix.h"

mM::MultiMatrix(int dimension, int p) 
{
	if (dimension == 2)
	{
		for (int i = 0; i < p; i++)
		{
			m_matrix.push_back(Outer);
		}
	}
	else if (dimension == 1) 
		m_matrix.push_back(new Outer);
	else
	{
		for (int i = 0; i < p; i++)
		{
			m_matrix.push_back(new mM(dimension - 1, p));
		}
	}
}

mM::~MultiMatrix() {}

void mM::back(bmM * &mmPtr, vector<int> &v)
{
	mmPtr = (&m_matrix[v.size() - 1]);
	for (int i = v.size() - 2; i > 0; i--)
	{
		mmPtr = &((*mmPtr)(v[i]));
	}
}


//v= {v[0], v[1]... v[v.size() - 1]}
//v = {value, inner residue(1)... outer residue}
length_t mM::operator()(vector<int> &v)
{
	if (2 > v.size()) return m_matrix[v[1]][v[0]];
	bmM * mmPtr(NULL);
	back(mmPtr, v);
	return (*mmPtr)[v[0]];
}

void mM::push_back(vector<length_t>& v, length_t i)
{
	mM * mmPtr(NULL);
	back(mmPtr, v);
	mmPtr->push_back(i);
}

inline bool mM::is_empty() {return m_matrix.empty();}

inline void mM::empty_matrix() { m_matrix.clear(); }

ostream& operator<<(ostream& os, const mM& matrix)
{
	print(os, matrix, *(new vector<int>));
	return os;
}

void print(ostream& os, const mM& matrix, vector<int> residues)//two conditions: nonleaf or leaf dimension
{
	if (!matrix.m_values.empty()) //has values, leaf dimension
	{
		for (int j = 0; j < residues.size(); j++) os << residues[j] << " ";
		os << endl;
		for (int j = 0; j < matrix.m_values.size(); j++) os << matrix.m_values[j] << endl;
	}
	else //no values, non-leaf dimension, must recurse
	{
		for (int i = 0; i < matrix.m_matrix.size(); i++)
		{
			residues.push_back(i);
			print(os, matrix.m_matrix[i], residues);
		}
	}
}

inline void o::push_back(length_t v) { m_values.push_back(v); }

inline bool o::is_outer() { return true; }

o::Outer():m_values(0){}
*/