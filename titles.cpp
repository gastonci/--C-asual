#include <string>
#include <int.h>

void MUO_titles_a1(char &x,int &y,int &z,int &xyz,std::string* &res)
{
     while(z < xyz)
     {
          x = 0;
          while(x < y)
          {
               res[z] += "oo";
               x++;
          }
          z++;
     }
}

void MUO_titles_a2(char &x,int &y,int &z,std::string* &res)
{
     x = 0;
     while(x < y)
     {
          res[z] += "o";
          x++;
     }
}

std::string* MUO_titles_bigletter(char x,int y)
{
     y += 4;
     std::string* res = new std::string[y];
     if(x == 'a')
     {
          y -= 3;
          int z = 0;
          int xyz = y;
          xyz /= 2;
          MUO_titles_a1(x,y,z,xyz,res);
          y--;
          MUO_titles_a2(x,y,z,res);
          res[z] += "  ";
          MUO_titles_a2(x,y,z,res);
          z++;
          xyz += z;
          if(par(y))
          {
               xyz++;
          }
          while(z < xyz)
          {
               x = 0;
               while(x <= y)
               {
                    res[z] += "oo";
                    x++;
               }
               z++;
          }
          MUO_titles_a2(x,y,z,res);
          res[z] += "  ";
          MUO_titles_a2(x,y,z,res);
          z++;
          MUO_titles_a2(x,y,z,res);
          res[z] += "  ";
          MUO_titles_a2(x,y,z,res);
     }
     else if(x == 'b')
     {
          int z = y,xyz = 0;
          z -= 4;
          x = 0;
          while(x < y)
          {
               while(xyz < z)
               {
                    res[x] += "o";
                    xyz++;
               }
               x++;
               xyz = 0;
          }
          while(xyz < z)
          {
               res[0] += "o";
               xyz++;
          }
          res[0] += "o ";
          y -= 3;
          y /= 2;
          x = 1;
          while(x <= y)
          {
               xyz = 0;
               while(xyz < z)
               {
                    res[x] += " ";
                    xyz++;
               }
               res[x] += " o";
               x++;
          }
          xyz = 0;
          while(xyz < z)
          {
               res[x] += "o";
               xyz++;
          }
          res[x] += "o ";
          y = z;
          y /= 2;
          y += x;
          while(x <= y)
          {
               xyz = 0;
               x++;
               while(xyz < z)
               {
                    res[x] += " ";
                    xyz++;
               }
               res[x] += " o";
          }
          xyz = 0;
          x++;
          while(xyz < z)
          {
               res[x] += "o";
               xyz++;
          }
          res[x] += "o ";
     }
     else if(x == 'c')
     {
          int z = y;
          z -= 3;
          z *= 2;
          x = 1;
          res[0] = " ";
          while(x < z)
          {
               res[0] += "o";
               x++;
          }
          y--;
          res[y] = res[0];
          x = 1;
          while(x < y)
          {
               res[x] = "o";
               x++;
          }
     }
     return res;
}
