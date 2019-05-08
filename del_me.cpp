#define E 2.71828182845904523536

#define h 0.0001

#include "CMyMatrix.h"
#include <math.h>

std::vector<double(*)(CMyVektor)> func_ptr_vec;

CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x)) {
	CMyVektor grad(x.getDimension());
	CMyVektor tmp = x;
	double func_val = funktion(x);
	for (int i = 0; i < x.getDimension(); i++) {
		tmp[i] += h;
		grad[i] = (funktion(tmp) - func_val) / h;
		tmp[i] = x[i];
	}
	return grad;
}

CMyVektor gradient(CMyVektor x, CMyVektor(*funktion)(CMyVektor x), int pos) {
	CMyVektor grad(x.getDimension());
	CMyVektor tmp = x;
	double func_val = funktion(x)[pos];
	for (int i = 0; i < x.getDimension(); i++) {
		tmp[i] += h;
		grad[i] = (funktion(tmp)[pos] - func_val) / h;
		tmp[i] = x[i];
	}
	return grad;
}

CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x)) {
	CMyMatrix JacMatrix{ 3, x.getDimension() };
	for (int i = 0; i < funktion(x).getDimension(); i++) {
		JacMatrix[i] = gradient(x, funktion, i);
	}
	return JacMatrix;
}

CMyMatrix jacobi(CMyVektor x) {
	CMyMatrix JacMatrix{ 3, x.getDimension() };
	std::cout << "Size von func_ptr_vec: " << func_ptr_vec.size() << std::endl;
	for (int i = 0; i < JacMatrix.getZeilen(); i++) {
		JacMatrix[i] = gradient(x, func_ptr_vec[i]);
	}
	return JacMatrix;
}

double func1(CMyVektor x) {
	return x[0] * x[1] * pow(E, x[2]);
}

double func2(CMyVektor x) {
	return x[1] * x[2] * x[3];
}

double func3(CMyVektor x) {
	return x[3];
}

CMyVektor func_ges(CMyVektor x) {
	CMyVektor tmp{ 3 };
	tmp[0] = func1(x);
	tmp[1] = func2(x);
	tmp[2] = func3(x);
	return tmp;
}

void newton_verfahren()

int main() {
	try {
	func_ptr_vec.resize(3);
	func_ptr_vec[0] = func1;
	func_ptr_vec[1] = func2;
	func_ptr_vec[2] = func3;

	std::cout << "x(0, 1, 2, 3)\n";
	CMyVektor x{4};
	x[0] = 1;	x[1] = 2;	x[2] = 0;	x[3] = 3;
	//gradient(x, func_ptr_vec[3]);
	std::cout << "Jacobi Matrix zu x:\n";
	//jacobi(x).print();
	jacobi(x, func_ges).print();

	/*CMyMatrix m1{ 2, 3 };
	
		m1[0][0] = 3;
		m1[0][1] = 2;
		m1[0][2] = 1;
		m1[1][0] = 1;
		m1[1][1] = 0;
		m1[1][2] = 2;

		for (int i = 0; i < m1.getZeilen(); i++) {
			for (int ii = 0; ii < m1.getSpalten(); ii++)
				std::cout << m1[i][ii] << ", ";
			std::cout << std::endl;
		}
		std::cout << "m1:\n";
		m1.print();
		//std::cout << "Inverse zu m1:\n";
		//m1.invers().print();
		std::cout << "x = m1 * (1,2):\n";
		CMyVektor x{ 3 };
		x[0] = 1;	x[1] = 0;	x[2] = 4;
		x = m1 * x;
		std::cout << "x:\n";
		x.print();*/

	}
	catch (std::out_of_range& err) {
		std::cout << err.what();
		system("pause");
		return -1;
	}
	catch (...) {
		std::cerr << "Sonstiger Error\n";
	}
	system("pause");
	return 0;
}