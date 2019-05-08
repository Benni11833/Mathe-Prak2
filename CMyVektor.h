#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <string>

class CMyVektor{
private:
    unsigned int dimension_;
    std::vector<double> spalte_;
public:
    CMyVektor(unsigned int dimension)
    :dimension_{dimension}{
		spalte_.resize(dimension);
    }
	~CMyVektor() {
		spalte_.erase(spalte_.begin(), spalte_.end());
	}
    unsigned int getDimension()const{
        return dimension_;
    }
    const double operator[](int index)const throw (std::out_of_range){
		if (index >= 0 && index <= dimension_)
			return spalte_[index];
		else
			throw std::out_of_range("Spalte(" + std::to_string(index) + ") out of Range\n");
    }
    double& operator[](int index)throw (std::out_of_range){
        if(index >= 0 && index <= dimension_)
            return spalte_[index];
        else
			throw std::out_of_range("Spalte(" + std::to_string(index) + ") out of Range\n");
    }
    double getLen()const{
        long double sum{0};
        for(unsigned int i=0; i < dimension_; i++)
            sum += pow(spalte_[i], 2);
        return sqrt(sum);
    }
    void print()const{
        for(unsigned int i=0; i < dimension_; i++){
			std::cout << std::setw(5) << spalte_[i];
            if(i%10 == 0 && i!=0)
                std::cout << std::endl;
        }
         std::cout << std::endl;
    }
	void print_vals()const {
		std::cout << "(";
		for (int i = 0; i < getDimension(); i++)
			std::cout << spalte_[i] << "; ";
		std::cout << ")" << std::endl;
	}
    friend CMyVektor operator+(CMyVektor a, CMyVektor b);
    friend CMyVektor operator*(CMyVektor a, double lambda);
};

CMyVektor operator+(CMyVektor a, CMyVektor b){
	if (a.getDimension() != b.getDimension()) {
		std::cerr << "Vektoren haben nicht die gleiche Dimension." << std::endl;
	}
	else
		for (unsigned int i = 0; i < a.getDimension(); i++)
			a.spalte_[i] += b.spalte_[i];

    return a;
}

CMyVektor operator*(CMyVektor a, double lambda){
    for(unsigned int i=0; i < a.getDimension(); i++)
        a.spalte_[i] *= lambda;
    return a;
}