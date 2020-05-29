#include "TMath.h"

double Ex11_exampleMacro()
{	double x =10;
	double y;
	y = TMath::Gaus(x);
	return y;
}

int main() {
	Ex11_exampleMacro();
   return 0;
}
