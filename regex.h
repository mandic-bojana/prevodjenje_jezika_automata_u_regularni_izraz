#ifndef _REGEX_H_
#define _REGEX_H_ 1

#include <iostream>
#include <set>


using namespace std;

class Regex{
public:
  virtual Regex* kopija()const=0;
  virtual void ispis(ostream &o)const=0;
  // prioriteti, zbog ispisivanja zagrada
  virtual int prioritet()const=0;
  virtual ~Regex(){}
};


class Iteracija: public Regex{
protected:
  Regex* operand;
public:
  Iteracija(){}
  Iteracija(Regex* _operand){
    operand=_operand->kopija();
  }
  ~Iteracija(){
    delete operand;
  }
  Iteracija(const Iteracija &i){
    operand=i.operand->kopija();
  }
  Iteracija& operator=(Iteracija &i){
    if(this!=&i){
      delete operand;
      operand=i.operand->kopija();
    }
    return *this;
  }

  Regex* kopija()const{
    return new Iteracija(*this);
  }
  
  int prioritet()const;

  void ispis(ostream& o)const;
};
 

class Binarni: public Regex{
protected:
  Regex* prvi;
  Regex* drugi;

public:
  Binarni(){}
  Binarni(Regex* p, Regex* d){
    prvi=p->kopija();
    drugi=d->kopija();
  }
  Binarni(const Binarni &b){
    prvi=b.prvi->kopija();
    drugi=b.drugi->kopija();
  }

  Binarni& operator=(const Binarni &b){
    if(this!=&b){
      delete prvi;
      delete drugi;
      prvi=b.prvi->kopija();
      drugi=b.drugi->kopija();
    }
    return *this;
  }
  
  ~Binarni(){
    delete prvi;
    delete drugi;
  }
  

};


class Unija: public Binarni{
public:
  Unija(){}
  Unija(Regex* prvi, Regex* drugi): Binarni(prvi, drugi){}
  ~Unija(){}
  Regex* kopija()const{
    return new Unija(*this);
  }
  void ispis(ostream& o)const;

  int prioritet()const;

};


class Konkatenacija: public Binarni{
public:
  Konkatenacija(){}
  Konkatenacija(Regex* prvi, Regex* drugi): Binarni(prvi, drugi){}
  ~Konkatenacija(){}
  Regex* kopija()const{
    return new Konkatenacija(*this);
  }

  void ispis(ostream& o)const;

  int prioritet()const;
};


class Karakter: public Regex{
private:
  string s;
public:
  Karakter(){}
  Karakter(string _s): s(_s){}
  ~Karakter(){}

  void ispis(ostream &o)const;

  Regex* kopija()const{
    return new Karakter(*this);
  }

  int prioritet()const;
};


ostream& operator<<(ostream &o, const Regex& r);


#endif
