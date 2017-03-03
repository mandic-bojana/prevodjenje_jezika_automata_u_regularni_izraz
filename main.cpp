#include <iostream>
#include "automat.h"


using namespace std;

int main(){
  
  Automat A;
  A.ucitajAutomat();
  cout<<endl<<endl;
  cout<<A<<endl<<endl;
  Regex* jezik=eliminacijaStanja(A);
  
  if(jezik==NULL)
	cout<<endl<<endl<<"Jezik automata je prazan skup."<<endl<<endl;
  else
    cout<<"Regularni izraz za jezik automata je: "<<*jezik<<endl<<endl;

  return 0;
}
