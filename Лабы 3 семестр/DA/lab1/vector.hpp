#ifndef VECTOR_HPP
#define VECTOR_HPP
const int BASIC_VECTOR_BUFFER = 128;

template<typename T>
class TVector {
	private:
		int vectorsize;
		int buffer;
		T *massive;
	public:
		TVector();
		TVector(const int lenth);
		~TVector();
		void push_back(const T &element);
		void Resize(const int sz);
		void ChangeSize(const int sz);
		int size() const;
		T& operator[](const int id) const;
};

template<typename T>
TVector<T>::TVector(): vectorsize(0), buffer(0), massive(0) {}

template<typename T>
TVector<T>::TVector(const int lenth): vectorsize(0), buffer(lenth) {
	massive = new T[lenth];
}

template<typename T>
TVector<T>::~TVector() {
	delete []massive;
}

template<typename T>
void TVector<T>::push_back(const T &element) {
	if (buffer == 0) {
		massive = new T[BASIC_VECTOR_BUFFER]{T()};
		buffer = BASIC_VECTOR_BUFFER;
	} else {
		if (vectorsize == buffer) {
			T *temporaryMassive = new T[buffer * 2]{T()};
			buffer*=2;
			for (int i = 0; i < vectorsize; ++i) {
				temporaryMassive[i] = massive[i];
			}
			delete []massive;
			massive = temporaryMassive;
		}
	}
	massive[vectorsize] = element;
	vectorsize++;
}

template<typename T>
void TVector<T>::Resize(const int sz) {
	T *temporaryMassive = new T[sz];
	buffer=sz;
	if (vectorsize >= sz) {
		for (int i = 0; i < sz; ++i) {
			temporaryMassive[i] = massive[i];
		}
		vectorsize = sz;
	} 
	delete []massive;
	massive = temporaryMassive;
}

template<typename T>
void TVector<T>::ChangeSize(const int sz) {
	vectorsize = sz;
}

template<typename T>
int TVector<T>::size() const {
	return vectorsize;
}

template<typename T>
T& TVector<T>::operator[](const int id) const {
	return massive[id];
}

#endif