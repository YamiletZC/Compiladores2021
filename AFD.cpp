#include <iostream>
#include <string>
#include <stdlib.h>


using namespace std;
class AFD {
private:
	string* Q;	
	char* Sigma;	
	string** delta;	
	string q0;	
	string* F;	
	int nQ;			
	int nSigma;		
	int nF;		

public:
	AFD() {			//entrada de los parámetros del AFD
		int i;
		nQ = 3;
		nSigma = 2;
		nF = 1;
		Q = new string[nQ];
		F = new string[nF];
		Sigma = new char[nSigma];
		delta = new string * [nQ];
		for (i = 0; i < nQ; i++) {
			delta[i] = new string[nSigma];
		}
		
		//generar entradas por el usuario para definir los parámetros del AFD
		q0 = "q0";

		Q[0] = "q0";
		Q[1] = "q1";
		Q[2] = "q2";
		
		F[0] = "q1";

		Sigma[0] = '0';		// alfabeto
		Sigma[1] = '1';

		delta[0][0] = "q0";
		delta[0][1] = "q1";
		delta[1][0] = "q2";
		delta[1][1] = "q1";
		delta[2][0] = "q1";
		delta[2][1] = "q1";
	}

	~AFD() {
		int i;
		for (i = 0; i < nQ; i++) {
			delete[] delta[i];
		}
		delete[] delta;
		delete[] Q;
		delete[] F;
		delete[] Sigma;
	}

	friend ostream& operator<<(ostream & stream, const AFD & afd) {
		int i, j;
		stream << "Q " << "\t" << "Sigma" << "\n";
		for (i = 0; i < afd.nSigma; i++) {
			stream << "----------";
		}
		stream << "\n";
		stream << "  " << "\t";
		for (i = 0; i < afd.nSigma; i++) {
			stream << afd.Sigma[i] << " \t";
		}
		stream << "\n"; 
		for (i = 0; i < afd.nSigma; i++) {
			stream << "----------";
		}
		stream << "\n";
		for (i = 0; i < afd.nQ; i++) {
			stream << afd.Q[i] << "\t";
			for (j = 0; j < afd.nSigma; j++) {
				stream << afd.delta[i][j] << "\t";
			}
			stream << "\n";
		}
		return stream;
	}

	int indexQ(const string & q, const AFD & afd) {
		int i, r = -1;

		for (i = 0; i < afd.nQ; i++) {
			if (q == afd.Q[i]) {
				r = i; 
				break;
			}
		}

		return r;
	}

	int indexSigma(const char & c, const AFD& afd) {
		int i, r = -1;

		for (i = 0; i < afd.nSigma; i++) {
			if (c == afd.Sigma[i]) {
				r = i;
				break;
			}
		}

		return r;
	}

	int verifyF(const string& q, const AFD& afd) {
		int i, r = 0;

		for (i = 0; i < afd.nF; i++) {
			if (q == afd.F[i]) {
				r = 1;
				break;
			}
		}

		return r;
	}

	int verifyQ(const string& q, const AFD& afd) {
		int i, r = 0;

		for (i = 0; i < afd.nQ; i++) {
			if (q == afd.Q[i]) {
				r = 1;
				break;
			}
		}

		return r;
	}

	int stringVerification(const string & str, const AFD & afd) {
		int i, j, q, iSigma, v = 0;

		string q1;
		string str1 = str;

		string::iterator p;
		
		p = str1.begin();

		// Obtener estado inicial
		q1 = afd.q0;
		q = indexQ(q1, afd);
		for (i = 0; i < str.size(); i++) {
			q1 = afd.delta[q][indexSigma(str[i], afd)];		
			q = indexQ(q1, afd);
		}
		if (verifyF(q1, afd)) v = 1;
		return v;
	}
	};

	int main() {
		AFD afd1;
		string str1 = "1100";		//Cadena a ser analizada

		cout << afd1;
		
		cout << "\n\n";
		cout << "Cadena de entrada: " << str1;

		cout << "\n\n";
		cout << "\tCadena ";
		if (afd1.stringVerification(str1, afd1)) cout << "Valida";
		else cout << "Rechazada";		
		cout << "\n\n\n";
		system("pause");
		return 0;
	}
