#pragma once
#include "CMyVektor.h"
#include <string>

class CMyMatrix {
private:
	int zeilen_, spalten_;
	std::vector<CMyVektor*> zeile_;

public:
	CMyMatrix(unsigned int zeilen, unsigned int spalten) {
		zeilen_ = zeilen;
		spalten_ = spalten;
		zeile_.resize(zeilen);
		for (int i = 0; i < zeilen; i++)
			zeile_[i] = new CMyVektor{ spalten };
	}
	const CMyVektor operator[](int index)const throw (std::out_of_range){
		if (index >= 0 && index <= zeilen_)
			return *zeile_[index];
		else
			throw std::out_of_range("Zeile(" + std::to_string(index) + ") out of Range\n");
	}
	CMyVektor& operator[](int index) throw (std::out_of_range){
		if (index >= 0 && index <= zeilen_)
			return *zeile_[index];
		else
			throw std::out_of_range("Zeile(" + std::to_string(index) + ") out of Range\n");
	}
	unsigned int getZeilen()const {
		return zeilen_;
	}
	unsigned int getSpalten()const {
		return spalten_;
	}
	CMyMatrix invers() throw (std::out_of_range){
		//zuerst fuer 2x2 matrix
		if (zeilen_ == 2 && spalten_ == 2){
			CMyMatrix inverse{ 2, 2 };
			inverse[0][0] = zeile_[1]->operator[](1);
			inverse[0][1] = -(zeile_[0]->operator[](1));
			inverse[1][0] = -(zeile_[1]->operator[](0));
			inverse[1][1] = zeile_[0]->operator[](0);
			return inverse;
		}
		else
			throw std::out_of_range("Fehler bei Invers: keine 2x2 Matrix\nUebergebene Matrix hat Dimension " + std::to_string(zeilen_)+'x'+ std::to_string(spalten_)+"\n");
	}
	void print()const {
		for (int i = 0; i < zeilen_; i++) {
			zeile_[i]->print();
			//std::cout << std::endl;
		}
	}
	friend CMyVektor operator*(CMyMatrix A, CMyVektor x) throw (std::out_of_range){
		if (A.getSpalten() != x.getDimension())
			throw std::out_of_range("Vektor Dimension stimmt nicht mit Matrix Spalten-Anzahl ueberein\n");
		else {
			CMyVektor tmp{ A.getZeilen() };
			for (int i = 0; i < A.getZeilen(); i++) {
				for (int ii = 0; ii < A.getSpalten(); ii++) {
					tmp[i] += A[i][ii] * x[ii];
				}
			}
			return tmp;
		}
	}
};