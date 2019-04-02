#ifndef OTCLASS_H
#define OTCLASS_H

class OrderType{
public:
  int nthrackles;
  int number;
  unsigned char cn;

  bool operator<(const OrderType x){
    return (x.nthrackles <= this->nthrackles);
  }
};
#endif
