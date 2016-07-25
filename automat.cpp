#ifndef __AUTOMAT_H__
#define __AUTOMAT_H__ 1


#include "automat.h"

Automat::Automat(){}
  Automat::Automat(set<char> _azbuka, deque<Stanje> _stanja, set<Prelaz> _prelazi): azbuka(_azbuka), stanja(_stanja), prelazi(_prelazi){}
  Automat::~Automat(){}

void Automat::dodajPrelaz(Prelaz &prelaz){
  if(!prelazi.empty()){
    set<Prelaz>::iterator it=prelazi.find(prelaz);
    if(it!=prelazi.end()){
      Regex* azuriranaEtiketa=new Unija((*it).Etiketa(),prelaz.Etiketa());
      prelazi.erase(it);
      prelazi.insert(Prelaz(prelaz.UlaznoStanje(), azuriranaEtiketa, prelaz.IzlaznoStanje()));
    }
    else{
      prelazi.insert(prelaz);
    }
  }
  else prelazi.insert(prelaz);
}

void Automat::ucitajAutomat(){
  *this=Automat();
  cout<<"Unesite slova azbuke automata:   (Ctrl-D za kraj)"<<endl;
  char c;
  int k;
  while(cin>>c) 
    azbuka.insert(c);
  cin.clear();
  
  cout<<endl<<"Unesite broj stanja automata:"<<endl;
  int n;
  cin>>n;
  
  for(int i=1; i<=n; i++){
    stanja.push_back(Stanje(i));
  }
  
  cout<<"Unesite pocetna stanja automata u obliku: redni_broj_stanja   (Ctrl-D za kraj)"<<endl;
  while(cin>>k){
    if(k<1 || k>n){
	cout<<endl<<"Broj mora biti u intervalu od 1 do "<<n<<". Pokusajte ponovo."<<endl;
	continue;
      }
    stanja[k-1].setPocetno(true);
    }
  cin.clear();

  cout<<endl<<"Unesite zavrsna stanja automata u obliku: redni_broj_stanja   (Ctrl-D za kraj)"<<endl;
  while(cin>>k){
    if(k<1 || k>n){
      cout<<endl<<"Broj mora biti u intervalu od 1 do "<<n<<". Pokusajte ponovo."<<endl;
      continue;
    }
    stanja[k-1].setZavrsno(true);
    }
  cin.clear();
  
  set<Prelaz> prelazi;
  
  for(int i=0; i<n; i++){
    cout<<endl<<"Unesite prelaze iz stanja "<<stanja[i]<<" u obliku: slovo_azbuke broj_izlaznog_stanja   (Ctrl-D za kraj)"<<endl;
    while(cin>>c){
	cin>>k;
	if(azbuka.find(c)==azbuka.end()){
	  cout<<endl<<"Uneto slovo ne pripada azbuci automata. Pokusajte ponovo."<<endl;
	  continue;
	}
	if(k<1 || k>n){
	  cout<<endl<<"Broj mora biti u intervalu od 1 do "<<n<<". Pokusajte ponovo."<<endl;
	  continue;
	}
	Prelaz prelaz=Prelaz(stanja[i], new Karakter(string(1, c)), stanja[k-1]);
	dodajPrelaz(prelaz);
      }
      cin.clear();
    }  
  }
 
   
  
set<Prelaz> Automat::vratiSvePrelazeIzZadatogStanja(Stanje &Q){
  set<Prelaz> rez;
  for(set<Prelaz>::iterator it=prelazi.begin(); it!=prelazi.end(); it++){
    if((*it).UlaznoStanje()==Q  && !(*it).isPetlja()){
      rez.insert(*it);
    }
  }
  return rez;
}

  
set<Prelaz> Automat::vratiSvePrelazeUZadatoStanje(Stanje &Q){
  set<Prelaz> rez;
  for(set<Prelaz>::iterator it=prelazi.begin(); it!=prelazi.end(); it++){
    if((*it).IzlaznoStanje()==Q  && !(*it).isPetlja()){
      rez.insert(*it);
    }
  }
  return rez;
}
	 

Regex* Automat::vratiJezikPrelazaIzmedjuDvaZadataStanja(Stanje &P, Stanje &Q){
  Regex* etiketa;
  if(!prelazi.empty()){
    for(set<Prelaz>::iterator it=prelazi.begin(); it!=prelazi.end(); it++)
      if((*it).UlaznoStanje()==P && (*it).IzlaznoStanje()==Q){
	etiketa=(*it).Etiketa();
	return etiketa;
      }
  }
  
  if(P==Q)
    return new Karakter("eps");
  return NULL;
}


 
Regex* eliminacijaStanja(const Automat &automat){
  Automat A=Automat(automat);
  
  Stanje alfa=Stanje(0);
  alfa.setPocetno(true);
  for(deque<Stanje>::iterator it=A.stanja.begin(); it!=A.stanja.end(); it++)
    if(it->Pocetno()){
      it->setPocetno(false);
      Prelaz p=Prelaz(alfa, new Karakter("eps"), (*it));
      A.dodajPrelaz(p);
    }
            
  Stanje omega=Stanje(A.stanja.size()+1);
  omega.setZavrsno(true);
  for(deque<Stanje>::iterator it=A.stanja.begin(); it!=A.stanja.end(); it++)
    if(it->Zavrsno()){
      it->setZavrsno(false);
      Prelaz r=Prelaz((*it), new Karakter("eps"), omega);
      A.dodajPrelaz(r);
    }
  
  cout<<"*****************   Generisanje novog pocetnog stanja "<<alfa<<" i zavrsnog "<<omega<<"   *****************"<<endl<<endl;
    
  A.ispisPrelaza();
  
  cout<<endl<<endl;
  
    //eliminacija stanja
  while(!A.stanja.empty()){

    Stanje Q=A.stanja.front();
    A.stanja.pop_front();

    set<Prelaz> prelaziIzQ=A.vratiSvePrelazeIzZadatogStanja(Q);
    set<Prelaz> prelaziUQ=A.vratiSvePrelazeUZadatoStanje(Q);  

      
      for(set<Prelaz>::iterator it1=prelaziUQ.begin(); it1!=prelaziUQ.end(); it1++){
	for(set<Prelaz>::iterator it2=prelaziIzQ.begin(); it2!=prelaziIzQ.end(); it2++){
	  Stanje P=it1->UlaznoStanje();
	  Stanje R=it2->IzlaznoStanje();
	  
      //  Regex Lpr=vratiJezikPrelazaIzmedjuDvaZadataStanja(P, R);
	  Regex* Lpq=A.vratiJezikPrelazaIzmedjuDvaZadataStanja(P, Q);
	  Regex* Lqr=A.vratiJezikPrelazaIzmedjuDvaZadataStanja(Q, R);
	  Regex* Lqq=A.vratiJezikPrelazaIzmedjuDvaZadataStanja(Q, Q);
	  
	  if(Lpq!=NULL && Lqr!=NULL){
	    Regex* iteracija=new Iteracija(Lqq);    // Lqq*
	    Regex* konkatenacija=new Konkatenacija(Lpq, iteracija);
	    Regex* novaEtiketa=new Konkatenacija(konkatenacija, Lqr);    // Lpq(Lqq)*Lqr
	    //          ^  bice Lpr | Lpq(Lqq)*Lqr  kada se doda u prelaze  
	    
	  Prelaz noviPrelaz=Prelaz(P, novaEtiketa, R);
	  A.dodajPrelaz(noviPrelaz);

	  delete iteracija;
	  delete konkatenacija;

	  }
	}
      }

      for(set<Prelaz>::iterator it=A.prelazi.begin(); it!=A.prelazi.end();){
	if((*it).UlaznoStanje()==Q || (*it).IzlaznoStanje()==Q){
	  A.prelazi.erase(it++);
	}
	else
	  ++it;
       }
      
      cout<<"*************************  Prelazi posle eliminacije stanja "<<Q<<"  *************************"<<endl<<endl;
      if(A.prelazi.empty()){
	return NULL;
      }
      
      A.ispisPrelaza();
     
      cout<<endl<<endl;
      
    }

  cout<<"*****************************************************************************************"<<endl<<endl;     
  cout<<endl<<endl;

  return (*(A.prelazi.begin())).Etiketa()->kopija();
  }



    
  
void Automat::ispisPrelaza(){
  for(set<Prelaz>::const_iterator it=prelazi.begin(); it!=prelazi.end(); it++)
    cout<<(*it)<<endl; 

}

  ostream & operator<<(ostream &o, const Automat &A){
    o<<"Azbuka = {";
    for(set<char>::const_iterator it1=A.azbuka.begin(); it1!=A.azbuka.end(); it1++)
      o<<(*it1)<<", ";
    o<<"\b\b"<<"}"<<endl<<endl;
      
    o<<"Pocentna stanja = {";
    for(deque<Stanje>::const_iterator it2=A.stanja.begin(); it2!=A.stanja.end(); it2++)
      if((*it2).Pocetno())
	o<<(*it2)<<", ";
    o<<"\b\b"<<"}"<<endl<<endl;
    
    o<<"Zavrsna stanja = {";
    for(deque<Stanje>::const_iterator it3=A.stanja.begin(); it3!=A.stanja.end(); it3++)
      if((*it3).Zavrsno())
	o<<(*it3)<<", ";
    o<<"\b\b"<<"}"<<endl<<endl;
       
    o<<"Prelazi:"<<endl;
    for(set<Prelaz>::const_iterator it4=A.prelazi.begin(); it4!=A.prelazi.end(); it4++)
      o<<(*it4)<<endl;
    
    cout<<endl;
    return o;    
}




#endif
