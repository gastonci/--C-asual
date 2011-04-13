#ifndef INT_H
#define INT_H
const double dNULL = 2.23e-308;
const double MUO_pidegrade = 57.295779513082320876798154814105;
const double MUO_pigrade = 0.0174533;//M_PI / 180º
double MUO_int_pow(int, int);

inline bool inpar(int &x){return x == 0?false:x&1;}//odd

bool par(int &x){return x&1? false: x;}//even

inline bool between(double &x,double &y,double &b_cmp)
{
     if(x == y){return x == b_cmp ? true : false;}
     double min = x < y ? x : y;
     double max = x > y ? x : y;
     return min <= b_cmp && max >= b_cmp ? true : false;
}

inline bool MUO_int_read_between_the_chars(char x,char y,char z){return y <= x && z >= x ? true : false;}

double atod(const char* str)
{
     int x = 1;
     double res = 0;
     while(*str == ' ')
     {
         str++;
     }
     if(*str == '-')
     {
          x = -1;
          str++;
     }
     else if(*str == '+'){str++;}
     while(MUO_int_read_between_the_chars(*str,'0','9'))
     {
         res *= 10;
         res += *str;
         res -= '0';
         str++;
     }
     if((*str == '.') || (*str == ','))
     {
          str++;
          double y = 1,z;
          while(MUO_int_read_between_the_chars(*str,'0','9'))
          {
               y /= 10;
               z = *str;
               z -= '0';
               z *= y;
               res += z;
               str++;
          }
     }
     return res;
}
#endif
