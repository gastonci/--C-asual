//MASTER FILE STREAM
//2010
//VER 0.5969
//
//TODO THREE
//2 UNICODE & CODIFICATIONS HANDLING
//0.3 gustavo_proff                 NOT EVER
//0.2 beta test & FABU              NOT YET
//0.1 read unicode char             NOT YET
///////////////////////////////////
//1 BASIC COMANDS & CLASS_ASSAMBLER 3/20
//0.9 gustavo_proff                 NOT EVER
//0.8 beta test & FABU              NOT YET
//0.7 changeline                    TRUE -0.25bit
//0.6 operators                     TRUE -0.1818bit
//0.5 class_assambler opcode/task   FALSE 0.7bit
//0.4 class_assambler type def      TRUE -0.125bit
//0.3 class_assambler object def    TRUE -0.25bit
//0.2 all the other basic comands   TRUE
//0.1 write, rewrite & goto         TRUE

#include <fstream>
#include <coder>
#include <math.h>
//#include <mfs_assembler_class.cpp>


std::string MUO_mfstream_wrderase(std::string str,int x);//elimina la palabra numero x del str
void MUO_mfstream_erasewrd(std::string erase_this,std::string& from_this);
int MUO_magick_can_of_bean(std::string &x,int &y);//uso exclusivo de mfs::class_assembler()
int filesize(const char* flnm);
unsigned short MUO_fstream_loop[1];

class mfstream
{
      private:
              std::string data;//los datos del archivo en la RAM(archivo dinamico)
              int position;//la linea donde se ejecutan funciones
              std::string lain[255];//la cantida maxima del archivo dinamico
              int rooms;//numero de lineas en el archivo dinamico
              std::string flnm;//el nombre del archivo
              bool nothing;//saved()
      public:
             bool open(const char*const&);//crea el archivo dinamico
             inline int lines(){return rooms;}//devuelve la cantidad de lineas en el archivo dinamico
             inline bool gt(short x){return x > rooms || x < 0 ? false: position = x;}//posisiona el valor en la linea deseada
             bool next();//salta una linea
             bool back();//vuelve una linea
             int pos();//devuelve la posisicion actual
             std::string line(short where,int x,const char* y,const char* z,const char* xyz,const char* a,const char* b,const char* c,const char* abc);//devuelve la linea deseada
             const char* doline(short where,int x,const char* y,const char* z,const char* xyz,const char* a,const char* b,const char* c,const char* abc);//devuelve la modificacion de la linea con el class_asambler
             bool changeline(short where,int x,const char* y,const char* z,const char* xyz,const char* a,const char* b,const char* c,const char* abc);//modifica la linea con el class_asambler y guarda el cambio
             bool write(const char* str);//ingresa una linea al archivo dinamico
             bool rewrite(const char* str);//reescribi una linea del archivo dinamico
             bool back(const char* str);//agrega str al principio de la linea
             bool front(const char* str);//agrega str al final de la linea
             bool save();//setea los datos del archivo origen por los del dinamico
             bool deletef();//elimina el archivo origen
             void clear();//borra el archivo dinamico
             void erase(short wich_line = -1);//borra una linea (por default la linea actual)
             bool saved();//falso si el archivo dinamico tiene algun cambio sin guardar
             bool renamef(const char* str);//cambia el nombre al archivo de origen
             bool saveas(const char* str);//cambia el nombre del archivo dinamico (en adelante se guardara con ese nombre)
             bool save_as(const char* str);//crea otro archivo con otro nombre donde se guardan los cambios
             const char* c_str();//convierte el archivo dinamico en const char* (ideal para cout)
             int ncmp(short where,const char* b_cmpr,size_t num);//Compara los caracteres de una strings y una linea del archivo dinamicp
             const char* const class_assembler(int& x,std::string& str,std::string y,std::string z,std::string xyz,std::string a,std::string b,std::string c,std::string abc);
             mfstream(bool MUO);
             std::string operator [] (short&);//devuelve la line x
             inline bool operator < (mfstream&mfs){return rooms < mfs.rooms ? true : false;}
             inline bool operator <= (mfstream&mfs){return rooms <= mfs.rooms ? true : false;}
             inline bool operator > (mfstream&mfs){return rooms > mfs.rooms ? true : false;}
             inline bool operator >= (mfstream&mfs){return rooms >= mfs.rooms ? true : false;}
             inline bool operator == (mfstream&mfs){return rooms == mfs.rooms ? true : false;}
             inline bool operator != (mfstream&mfs){return rooms != mfs.rooms ? true : false;}
             void operator = (mfstream&);
             void operator += (mfstream&);//agrega las lineas mfs al final del archivo dinamico
             void operator <<= (mfstream&);//agrega las lineas mfs al principio del archivo dinamico
             void operator -= (mfstream&);//no del todo seguro... puede que cambie su funcionamiento
             virtual ~mfstream();
//           bool end();//es como fstream::EOF
};

mfstream::mfstream(bool MUO = true)
{
    nothing = true;
    rooms = 0;
    position = 0;
    data = '\0';
    flnm = "\0";
}

std::string mfstream::operator[] (short &where)
{
    if(where < 0)
             return "";
    if(where > rooms)
             return "";
    return lain[where];
}

void mfstream::operator= (mfstream &rpt)
{
    rooms = rpt.lines();
    position = rpt.pos();
    short count = 1;
    while(count <= rooms)
    {
        lain[count] = rpt[count];
        count++;
    }
    data = rpt.c_str();
    nothing = false;
    return;
}

void mfstream::operator+= (mfstream &rpt)
{
    short count[1];
    count[0] = rooms;
    count[0] += 1;
    count[1] = 1;
    rooms += rpt.rooms;
    position += rpt.position;
    while(count[0] <= rooms)
    {
        lain[count[0]] = rpt[count[1]];
        count[0]++;
        count[1]++;
    }
    if(data[0] == '\0')
                    data = rpt.data;
    else
    {
        data += "\n";
        data += rpt.data;
    }
    nothing = false;
    return;
}

void mfstream::operator-= (mfstream &rpt)
{
     unsigned short count[3];
     count[0] = 1;
     count[1] = rooms;
     count[2] = 1;
     count[3] = rpt.rooms;
     while(count[0] <= count[1])
     {
          while(count[2] <= count[3])
          {
               if(strcmp(lain[count[0]].c_str(),rpt.lain[count[2]].c_str()) == 0)
               {
                    erase(count[0]);
                    count[2] = count[3];
               }
               count[2]++;
          }
          count[0]++;
     }
     return;
}

void mfstream::operator<<= (mfstream &rpt)
{
     unsigned short count[1];
     count[0] = 0;
     count[1] = rpt.rooms;
     data = rpt.data + data;
     position += rpt.position;
     while(count[0] < rpt.rooms)
     {
          lain[count[1]] = lain[count[0]];
          lain[count[0]] = rpt.lain[count[0]];
          count[1]++;
          count[0]++;
     }
     rooms = count[1];
     return;
}

bool mfstream::open(const char* const &var)
{
     std::ifstream file(var);
     flnm = var;
     if(filesize(var) == 0)
     {
                      rooms = 0;
                      position = 0;
                      data.clear();
                      file.close();
                      return false;
     }
     std::string x;
     rooms = 1;
     getline(file,x);
     data = x;
     lain[1] = x;
     while(!file.eof())
     {
                       rooms++;
                       data += "\n";
                       getline(file,x);
                       lain[rooms] = x;
                       data += x;
     }
     position = rooms;
     file.close();
     nothing = true;
     return true;
}

/*inline bool mfstream::gt(short x)OLD VERSION
{
     if(x > rooms)
          return false;
     if(x < 0)
          return false;
     position = x;
     return true;
}*/

bool mfstream::front(const char* str)
{
     unsigned short x;
     if((position < 1) || (position > rooms))
                 return false;
     else if(position == rooms)
     {
          rooms++;
          lain[rooms] = str;
          position++;
     }
     else
         lain[position] += str;
     data.clear();
     for(x = 1;x < rooms;x++)
     {
           data += lain[x];
           data += "\n";
     }
     data += lain[x];
     nothing = false;
     return true;
}

bool mfstream::back(const char* str)
{
     unsigned short x;
     if((position < 1) || (position > rooms))
                 return false;
     else if(position == rooms)
     {
          rooms++;
          lain[rooms] = str;
          position++;
     }
     else
         lain[position] = str + lain[position];
     data.clear();
     for(x = 1;x < rooms;x++)
     {
           data += lain[x];
           data += "\n";
     }
     data += lain[x];
     nothing = false;
     return true;
}

int mfstream::ncmp(short where,const char* b_cmpr,size_t num)
{
    return strncmp(lain[where].c_str(),b_cmpr,num);
}

const char* mfstream::c_str()
{
      return data.c_str();
}

/*inline bool mfstream::end()
{
    return position > rooms ? true : false; DOES NOT EXIST ANY MORE
}*/

std::string mfstream::line(short where = -1,int x = 0,const char* y = "",const char* z = "",const char* xyz = "",const char* a = "",const char* b = "",const char* c = "",const char* abc = "")
{
      if(where == -1)
               where = position;
      std::string dos = y,tres = z,cuatro = xyz,primero = a,segundo = b,tercero = c,cuarto = abc;
       if(where > rooms)
       {
                return "";
       }
       else
       {
           position = where;
           
           if(x == 0)
           {
                return lain[where].c_str();
           }
           else
           {
               return class_assembler(x,lain[where],dos,tres,cuatro,primero,segundo,tercero,cuarto);
           }
       }
}

const char* mfstream::doline(short where = -1,int x = 0,const char* y = "",const char* z = "",const char* xyz = "",const char* a = "",const char* b = "",const char* c = "",const char* abc = "")
{
      if(where == -1)
               where = position;
       if(where > rooms)
       {
                return "";
       }
       else
       {
           nothing = false;
           const char* res;
           position = where;
           if(x == 0)
           {
                return lain[where].c_str();
           }
           else
           {
               res = class_assembler(x,lain[where],y,z,xyz,a,b,c,abc);
               position = where;
               rewrite(res);
               return res;
           }
       }
}

bool mfstream::changeline(short where = -1,int x = 0,const char* y = "",const char* z = "",const char* xyz = "",const char* a = "",const char* b = "",const char* c = "",const char* abc = "")
{
     if(where == -1)
               where = position;
      std::string dos = y,tres = z,cuatro = xyz,primero = a,segundo = b,tercero = c,cuarto = abc;
       if(where > rooms)
       {
                return false;
       }
       else
       {
           std::string res = "";
           position = where;
           
           if(x == 0)
           {
                return false;
           }
           else
           {
               nothing = false;
               if(x == 1)//mfs::word
               {
                      int count = 0, words = strwrds(lain[where].c_str()), when = atoi(dos.c_str()) - 1;
                      while(count < words)
                      {
                           if(count == when)
                                    res += class_assembler(x,lain[where],dos,tres,cuatro,primero,segundo,tercero,cuarto);
                           else
                               res += strbcle(lain[where],count);
                           count++;
                      }
               }
               else if(x == 101)//mfs::chars
               {
                    int calc = atoi(dos.c_str());
                    if(calc < 0)
                             calc = MUO_magick_can_of_bean(lain[where],calc);
                    std::string *eraseme = new std::string(lain[where],0,calc);
                    res = eraseme[0];
                    res += class_assembler(x,lain[where],dos,tres,cuatro,primero,segundo,tercero,cuarto);
                    int calco = atoi(tres.c_str());
                    if(calco < 0)
                    {
                            calco = MUO_magick_can_of_bean(lain[where],calco);
                            calco -= calc;
                            calc = calco;
                            ++calc;
                    }
                    else
                    {
                        calc += calco;
                    }
                    eraseme = new std::string(lain[where],calc,lain[where].length());
                    res += eraseme[0];
                    delete eraseme;
               }
               else if(x == 100)//mfs::lines
               {
                    res = class_assembler(x,lain[where],dos,tres,cuatro,primero,segundo,tercero,cuarto);
               }
               else if(x == 10)//mfs::fromto
               {
                    int temp = lain[where].find_first_of(dos);
                    res = redo(lain[where],0,temp);
                    res += class_assembler(x,lain[where],dos,tres,cuatro,primero,segundo,tercero,cuarto);
                    temp *= -1;
                    temp += lain[where].find_last_of(tres);
                    temp += tres.length();
                    res += redo(lain[where],temp,lain[where].length() - temp);
                    ////////////////////////////////////////////////////////////
                    //old version
                    /*res[0] = '\0';
                    bool end = false;
                    short count[1];
                    count[0] = 0;
                    const char* str = lain[where].c_str();
                    count[1] = strlen(str) - dos.length();
                    const char* b_cmpr = redo(str,0,dos.length()).c_str();
                    while((strcmp(dos.c_str(),b_cmpr) != 0) && !end)//from
                    {
                         res += str[count[0]];
                         b_cmpr = redo(str,count[0],dos.length()).c_str();
                         count[0]++;
                         if(count[0] == lain[where].length())
                                     end = true;
                    }
                    dos = "";
                    b_cmpr = redo(str,count[0],tres.length()).c_str();
                    while(!end && (strcmp(tres.c_str(),b_cmpr) != 0))
                    {
                         dos += str[count[0]];
                         b_cmpr = redo(str,count[0],tres.length()).c_str();
                         count[0]++;
                         if(count[0] == lain[where].length())
                                     end = true;
                    }
                    if(!end)
                    {
                         count[1] = count[0] + tres.length() -1;
                         while(count[0] < count[1])
                         {
                              dos += str[count[0]];
                              count[0]++;
                         }
                         x = atoi(cuatro.c_str());
                         if(x != 0)
                              dos = class_assembler(x,lain[where],dos,primero,segundo,tercero,cuarto,"","");
                         res += dos;
                    }
                    while(count[0] < lain[where].length())
                    {
                                   res += str[count[0]];
                                   count[0]++;
                    }*/
                    //
                    ////////////////////////////////////////////////////////////
                    //@even older version
                    //
                    //res = redo(lain[where],0,frstmtch(lain[where],dos)-1);
                    //res += class_asambler(x,lain[where],dos,tres,cuatro,primero,segundo,tercero,cuarto);
                    //int temp = lstmtch(lain[where],tres)-frstmtch(lain[where],dos)+tres.length();
                    //res += redo(lain[where],temp,lain[where].length() - temp);
               }
               else if(x == 111)//mfs::fromto
               {
                    res[0] = '\0';
                    bool end = false;
                    short count[1];
                    count[0] = 0;
                    const char* str = lain[where].c_str();
                    count[1] = strlen(str) - dos.length();
                    const char* b_cmpr = redo(str,0,dos.length()).c_str();
                    while((strcmp(dos.c_str(),b_cmpr) != 0) && !end)//desde el principio hasta el from
                    {
                         res += str[count[0]];
                         b_cmpr = redo(str,count[0],dos.length()).c_str();
                         count[0]++;
                         if(count[0] == lain[where].length())
                                     end = true;
                    }
                    bool staying_alive = end;
                    count[1] = 0;
                    end = staying_alive;
                    while((count[1] < dos.length()) && !end)//from
                    {
                         res += str[count[0]];
                         count[0]++;
                         count[1]++;
                    }
                    count[1] = lain[where].length();
                    end = staying_alive;
                    dos.clear();
                    if(!end)
                            b_cmpr = redo(str,count[0],tres.length()).c_str();
                    else
                        b_cmpr = "\0";
                    while((strcmp(tres.c_str(),b_cmpr) != 0) && !end)//desde from hasta to
                    {
                         dos += str[count[0]];
                         b_cmpr = redo(str,count[0]+1,tres.length()).c_str();
                         count[0]++;
                         if(count[0] >= count[1])
                                     end = true;
                    }
                    x = atoi(cuatro.c_str());
                    if(x)
                         dos = class_assembler(x,lain[where],dos,primero,segundo,tercero,cuarto,"","");
                    res += dos;
                    while(!end)
                    {
                         res += str[count[0]];
                         count[0]++;
                         if(count[0] >= count[1])
                                     end = true;
                    }
               }
               else if(110)//mfs::chr
               {
                    x = atoi(tres.c_str());
                    short count[1];
                    count[0] = 0;
                    count[1] = atoi(dos.c_str());
                    while(count[0] < lain[where].length())
                    {
                         if(count[0] == count[1])
                         {
                              res += class_assembler(x,dos,chrtostr(lain[where][count[0]]),cuatro,primero,segundo,tercero,"","");
                         }
                         else
                         {
                             res += lain[where][count[0]];
                         }
                         count[0]++;
                    }
               }
               return rewrite(res.c_str());;
           }
       }
}

bool mfstream::write(const char* str = "")
{
     std::string x;
     int y;
     if(strcmp(str,"") == 0)
     {
                       getline(std::cin,x);
                       str = x.c_str();
     }
     if(rooms == 0)
     {
              rooms++;
              lain[rooms] = str;
              position++;
     }
     else if(position == rooms)
     {
                 rooms++;
                 lain[rooms] = str;
                 position++;
     }
     else if((position < rooms) & (position >= 0))
     {
          rooms++;
          for(y = rooms; y > 0;y--)
          {
                if((y - 1) == position)
                {
                      lain[y] = str;
                      position++;
                      y = 0;
                }
                else
                {
                    lain[y] = lain[y-1];
                }
          }
     }
     else
         return false;
     data = "";
     for(y = 1;y < rooms;y++)
     {
           data += lain[y];
           data += "\n";
     }
     data += lain[y];
     nothing = false;
     return true;
}

bool mfstream::rewrite(const char* str)//usar "\b" para los renglones vacios
{
     std::string x;
     int y;
     if(strcmp(str,"") == 0)
     {
                       erase();
                       return true;
     }
     if((position <= rooms) & (position >= 0))
     {
                  lain[position] = str;
     }
     else
         return false;
     data = "";
     for(y = 1;y < rooms;y++)
     {
           data += lain[y];
           data += "\n";
     }
     data += lain[y];
     nothing = false;
     return true;
}

bool mfstream::save()
{
     if(flnm[0] == '\0')
                        return false;
     if(nothing)
                return true;
     std::ofstream file(flnm.c_str());
     if(file.fail())
                    return false;
     file << data;
     file.close();
     nothing = true;
     return true;
}

bool mfstream::saveas(const char* str)
{
     std::ofstream file(str);
     if(file.fail())
                    return false;
     flnm = str;
     file << data;
     file.close();
     nothing = true;
     return true;
}

bool mfstream::save_as(const char* str)
{
     std::ofstream file(str);
     if(file.fail())
                    return false;
     file << data;
     file.close();
     return true;
}

void mfstream::clear()
{
     data.clear();
     short count = 0;
     while(count <= rooms)
     {
                 lain[count].clear();
                 count++;
     }
     rooms = 0;
     position = 0;
     nothing = false;
     return;
}

inline bool mfstream::deletef()
{
     if(remove(flnm.c_str()) != 0)
                             return false;
     nothing = false;
     return true;//inline int deletf(){return remove(flnm.c_str());}//y con el nothin que mierda hago????
}

void mfstream::erase(short wich_line)
{
     if(wich_line == -1)
                  wich_line = position;
     int x;
     data.clear();
     for(x = wich_line;x < rooms;x++)
     {
           lain[x] = lain[x+1];
     }
     rooms--;
     for(x = 1;x < rooms;x++)
     {
           data += lain[x];
           data += "\n";
     }
     lain[rooms+1].clear();
     data += lain[x];
     nothing = false;
     return;
}

inline bool mfstream::saved()
{
     return nothing;
}

inline bool mfstream::next()
{
    if(position < rooms)
    {
         position++;
         return true;
    }
    return false;
    //return position < rooms ? position++ : position; OLD VERSION era int;
}

inline bool mfstream::back()
{
    if(position > 0)
    {
         position--;
         return true;
    }
    return false;
    //return position > 0 ? position-- : position; OLD VERSION era int;
}

inline int mfstream::pos()
{
    return position;
}

bool mfstream::renamef(const char* str)
{
     if(rename(flnm.c_str(),str) != 0)
                                 return false;
     flnm = str;
     return true;
}

class mfs//(numero de linea,objeto,tipo_de_objeto,tarea)
{
      public:
             //1-7 definicion de objeto
             static int words;//empieza de 1
             static int chars;//leer definicion
             static int line;
             static int fromto;
             static int infromto;
             static int chr;//empieza a contar desde cero
////////////////////////////////////////////////////////////////////////////////
             //8-15 tipo de objeto
             static char* str;
             static char* intgr;
             static char* dbl;
             static char* flt;//double pero con coma en vez de punto
             static char* bin;
             static char* b_s;
             static char* s_b;
////////////////////////////////////////////////////////////////////////////////
             //16-x   /x = 25 tarea a aplicar sobre el objeto
             static char* cmpr;//imprime un error... no printear!!!! (apunta a una locacion incorrecta)
             static char* mayor;//idem
             static char* menor;//idem
             static char* add;
             static char* sub;
             static char* mul;
             static char* div;
             static char* pow;
             static char* sqr;
////////////////////////////////////////////////////////////////////////////////
             //magick can of bean
             static char* ffalnum;//find first alpha-numeric
             static char* ffa;//alpha
             static char* ffc;//control characters
             static char* ffd;//digit
             static char* ffg;//con representacion grafica
             static char* ffl;//lower
             static char* ffp;//punct
             static char* ffs;//space
             static char* ffu;//upper
             static char* ffx;//hexadecimal
             static char* flalnum;//find last alpha-numeric
             static char* fla;
             static char* flc;
             static char* fld;
             static char* flg;
             static char* fll;
             static char* flp;
             static char* fls;
             static char* flu;
             static char* flx;
};

int mfs::words = 1;//objeto
                   //segundo::funcion     tercero::entero(**)
                   //Define al objeto como la palabra numero ** de la linea

int mfs::fromto = 10;//objeto
                    //segundo::funcion    tercero::palabra(*)   cuarto::palabra(**)
                    //El objeto se define con los caracteres desde (*) hasta (**)
                    //(*) == "/0"?empieza del principio;   (**) == "/0")? hasta el final;

int mfs::line = 100;//objeto
                    //segundo::funcion
                    //Objeto = Linea

int mfs::chars = 101;//objeto
                     //segundo::funcion   tercero::numero(*)    cuarto::numero(**)
                     //A la linea se le quitan (*) letras del principio y de ahi hasta (**) chares mas
                     //(*) == "0"?empieza del principio;   (**) == "/0"? (**) = str.length();

int mfs::chr  = 110;//objeto
                    //segundo::funcion    tercero::numero(*)
                    //Definicion dada por el char numero (*) de la linea, empieza de cero
                    
int mfs::infromto = 111;//objeto
                        //segundo::funcion    tercero::palabra(*)   cuarto::palabra(**)
                        //Todo lo que esté dentro del fromto sera la definicion

char* mfs::str = "1000";//tipo_de_objeto
                       //tercero::tipo_de_objeto
                       //realiza las tareas como se las realizaria a un char, char*, buff(char[array]) o a un string

char* mfs::intgr = "1001";//tipo_de_objeto
                          //tercero::tipo_de_objeto
                          //Lo "convierte" a int, lo q incluye redondeo

char* mfs::dbl = "1010";//tipo_de_objeto
                        //tercero::tipo_de_objeto
                        //Se usa como double para realizar toda clase de tareas, incluso las mas sencillas como extraer leche de la manteca
                        
char* mfs::flt = "1110";//tipo_de_objeto
                        //tercero::tipo_de_objeto
                        //Es como un double, con un coma en vez de punto, tanto en entrada como salida

char* mfs::bin = "1011";//tipo_de_objeto
                       //tercero::tipo_de_objeto
                       //Pasa char por char a binario, ejecuta la operacion (caso contrario devuelve los numeros[no printear]) y devuelve el nuevo array formado

char* mfs::b_s = "1100";//tipo_de_objeto
                        //tercero::tipo_de_objeto
                        //hace lo mismo q binario pero al terminar la tarea vuelve a str

char* mfs::s_b = "1101";//tipo_de_onjeto
                        //tercero::tipo_de_objeto
                        //la viceversa de b_s

char* mfs::cmpr = "20";//tarea
                       //cuarto::tarea    quinto::char* (numero o lo q sea)
                       //Devuelve verdadero (sin son iguales) o falso

char* mfs::mayor = "21";

char* mfs::menor = "210";

char* mfs::add = "211";//tarea
                       //cuarto::tarea     quinto::char* (numero o lo q sea)
                       //si es un tipo_de_objeto numerico se suman devuelve el resultado, caso contrario se le agregara al final con str[0] = `\b` lo agrega al principio

char* mfs::sub = "2100";//tarea
                        //cuarto::tarea     quinto::char* (numero o lo q sea)
                        //con numeros resta y con str:
                        //empezas con 0 desde el principio hasta el final o 1 desde el final para atras...
                        //con \b eleminas un caracter con \t elimina una palabra \n pasa a la siguiente palabra

char* mfs::mul = "2101";//tarea
                        //cuarto::tarea       quinto::char* (numero o lo q sea)
                        //con los numericos los multiplica y con str multiplica la palabra tantas veces como (char*) se diga

char* mfs::div = "2110";

char* mfs::pow = "2111";

char* mfs::sqr = "3001";



char* mfs::ffalnum = "-1";
char* mfs::ffa = "-10";
char* mfs::ffc = "-11";
char* mfs::ffd = "-100";
char* mfs::ffg = "-101";
char* mfs::ffl = "-110";
char* mfs::ffp = "-111";
char* mfs::ffs = "-1000";
char* mfs::ffu = "-1001";
char* mfs::ffx = "-1010";

char* mfs::flalnum = "-1011";
char* mfs::fla = "-1100";
char* mfs::flc = "-1101";
char* mfs::fld = "-1110";
char* mfs::flg = "-1111";
char* mfs::fll = "-2001";
char* mfs::flp = "-2010";
char* mfs::fls = "-2011";
char* mfs::flu = "-2100";
char* mfs::flx = "-2101";

const char* const mfstream::class_assembler(int& x,std::string& str,std::string y = "",std::string z = "",std::string xyz = "",std::string a = "",std::string b = "",std::string c = "",std::string abc = "")
{
     //std::cout << x << std::endl << y << std::endl << z << std::endl << xyz << std::endl << a << std::endl << b << std::endl << c << std::endl << abc << std::endl;
     //system("PAUSE");
     if(x == 0)
     {
          return y.c_str();
     }
     else if(x == 1)//mfs::words
     {
          int wich_word = atoi(y.c_str());
          if(wich_word > strwrds(str.c_str()))
          {
                       if(!z.empty())
                       {
                            x = atoi(z.c_str());
                            return class_assembler(x,str,"",xyz,a,b,c);
                       }
                       else
                       {
                           return "";
                       }
          }
          else
          {
              wich_word--;
              std::string res = strbcle(str,wich_word);
              if(!z.empty())
              {
                   x = atoi(z.c_str());
                   return class_assembler(x,str,res,xyz,a,b,c);
              }
              else
              {
                  return res.c_str();
              }
          }
     }
     else if(x == 10)//mfs::fromto (renombrado de chars)
     {
          unsigned int fmy = (strcmp(y.c_str(),"/0") == 0)?0:str.find_first_of(y),lmz = (strcmp(z.c_str(),"/0") == 0)?str.length()-fmy:str.find_last_of(z);//no son shorts en caso de que find_firs/last_of devuelva std::string::npos
          if((lmz != std::string::npos) && (fmy != std::string::npos) && (lmz != fmy))
          {
                             //lmz -= fmy;
                             //lmz += z.length();
                             std::string res(str,fmy,lmz);
                             if(!xyz.empty())
                             {
                                    x = atoi(xyz.c_str());
                                    return class_assembler(x,str,res,a,b,c,abc);
                             }
                             return res.c_str();
          }
          else
          {
              return "";
          }
     }
     else if(x == 100)//mfs::line
     {
          std::string res = str;
          if(!y.empty())
          {
               x = atoi(y.c_str());
               return class_assembler(x,str,res,z,xyz,a,b);
          }
          return res.c_str();
     }
     else if(x == 101)//mfs::chars
     {
          int n = atoi(y.c_str()), p = atoi(z.c_str());
          if(n < 0)
               n = MUO_magick_can_of_bean(str,n);
          if(p < 0)
          {
               p = MUO_magick_can_of_bean(str,p);
               p -= n;
               ++p;
          }
          else if(strcmp(z.c_str(),"/0") == 0)
          {
               p = str.length();
               p -= n;
          }
          std::string res(str,n,p);
          if(!xyz.empty())
          {
                 x = atoi(xyz.c_str());
                 return class_assembler(x,str,res,a,b,c,abc);
          }
          return res.c_str();
     }
     else if(x == 110)//mfs::chr
     {
          std::string res = "\0";
          x = atoi(y.c_str());
          if(x >= str.length())
               res = "\0";
          else
          {
              res[0] = str[x];
              res[1] = '\0';
          }
          if(!z.empty())
          {
               x = atoi(z.c_str());
               return class_assembler(x,str,res,xyz,a,b,c);
          }
          return res.c_str();
     }
     else if(x == 111)//mfs::infromto//falta corregir con mfs_assembler_class
     {
          int from = str.find_first_of(y);
          std::string res;
          if(from == std::string::npos)
                  res = "\0";
          else
          {
              from += y.length();
              int to = str.find_last_of(z);
              if(to == std::string::npos)
                    res = "\0";
              else
              {
                  to -=from;
                  to -= z.length();
                  ++to;
                  res = redo(str,from,to);
              }
          }
          if(!xyz.empty())
          {
                          x = atoi(xyz.c_str());
                          return class_assembler(x,str,res,a,b,c,abc);
          }
          return res.c_str();
     }
     else if(x == 1000)//mfs::str
     {
          if(z.empty())
          {
               return y.c_str();
          }
          x = atoi(z.c_str());
          return class_assembler(x,str,"str",y,xyz,a,b);
     }
     else if(x == 1001)//mfs::intgr
     {
          x = atoi(z.c_str());
          std::string res = itostr(atoi(y.c_str()));
          if(x == 0)
               return res.c_str();
          return class_assembler(x,str,"int",res,xyz,a,b);
     }
     else if(x == 1010)//mfs::dbl
     {
          x = atoi(z.c_str());
          suckvoid(y.c_str());
          y = dtostr(strtod(y.c_str(),NULL));
          if(x == 0)
               return y.c_str();
          return class_assembler(x,str,"dbl",y,xyz,a,b);
     }
     else if(x == 1011)//mfs::bin
     {
          x = atoi(z.c_str());
          std::string res = strbin(y);
          if(x == 0)
               return res.c_str();
          return class_assembler(x,str,"bin",res,xyz,a,b);
     }
     else if(x == 1100)//mfs::b_s
     {
          x = atoi(z.c_str());
          std::string res = strbin(y);
          if(x == 0)
               return res.c_str();
          return class_assembler(x,str,"b_s",res,xyz,a,b);
     }
     else if(x == 1101)//mfs::s_b
     {
          if(!z.empty())
               return y.c_str();
          x = atoi(z.c_str());
          if(x == 0)
               return strbin(y).c_str();
          return class_assembler(x,str,"s_b",y,xyz,a,b);
     }
     else if(x == 1110)//mfs::flt
     {
          x = atoi(z.c_str());
          suckvoid(y.c_str());
          if(z == "")
               return dtocc(strtod(y.c_str(),NULL),44);
          else
              return class_assembler(x,str,"flt",dtocc(strtod(y.c_str(),NULL),44),xyz,a,b);
     }
     else if(x == 20)//mfs::cmpr
     {
          if(y == "int")
          {
               if(atoi(z.c_str()) == atoi(xyz.c_str()))
                          return (char*)1;
               else
                   return (char*)0;
          }
          else if((y == "dbl")||(y == "flt"))
          {
              if(strtod(z.c_str(),NULL) == strtod(xyz.c_str(),NULL))
                         return (char*)1;
              else
                  return (char*)0;
          }
          else if(y == "b_s")//el numero con el q comparas tiene q ser binario
          {
               xyz = binstr(xyz.c_str());
               z = binstr(z.c_str());
               if(strcmp(z.c_str(),xyz.c_str()) == 0)
                                return (char*)1;
               else
                   return (char*)0;
          }
          else
          {
              if(strcmp(z.c_str(),xyz.c_str()) == 0)
                               return (char*)1;
              else
                  return (char*)0;
          }
     }
     else if(x == 21)//mfs::mayor
     {
          if((strcmp(y.c_str(),"str") == 0) || (strcmp(y.c_str(),"s_b")))
          {
               if(strcmp(z.c_str(),xyz.c_str()) == -1)
                                 return (char*)1;
               else
                   return (char*)0;
          }
          else if(strcmp(y.c_str(),"int") == 0)
          {
               if(atoi(z.c_str()) > atoi(xyz.c_str()))
                          return (char*)1;
               else
                   return (char*)0;
          }
          else
          {
              if(strtod(z.c_str(),NULL) < strtod(xyz.c_str(),NULL))
                         return (char*)1;
              else
                  return (char*)0;
          }
     }
     else if(x == 210)//mfs::menor
     {
          if((strcmp(y.c_str(),"str") == 0) || (strcmp(y.c_str(),"s_b")==0))
          {
               if(strcmp(z.c_str(),xyz.c_str()) == 1)
                                 return (char*)1;
               else
                   return (char*)0;
          }
          else if(y == "int")
          {
               if(atoi(z.c_str()) > atoi(xyz.c_str()))
                          return (char*)1;
               else
                   return (char*)0;
          }
          else
          {
              if(strtod(z.c_str(),NULL) > strtod(xyz.c_str(),NULL))
                         return (char*)1;
              else
                  return (char*)0;
          }
     }
     else if(x == 211)//mfs::add
     {
          if(strcmp(y.c_str(),"str") == 0)
          {
               if((int)z[0] == 8)
               {
                            z = chrbcle(z.c_str(),1,z.length());
                            z = xyz + z;
               }
               else
                   z += xyz;
               return z.c_str();
          }
          else if(y == "int")
          {
               int res = atoi(z.c_str()) + atoi(xyz.c_str());
               return itostr(res).c_str();
          }
          else if(y == "dbl")
          {
              double res = strtod(z.c_str(),NULL) + strtod(xyz.c_str(),NULL);
              return dtostr(res).c_str();
          }
          else if(y == "flt")
          {
               double oper = strtod(z.c_str(),NULL) + strtod(xyz.c_str(),NULL);
               std::string res = dtocc(oper,44);
               return res.c_str();
          }
          else if(y == "s_b")
          {
               z += xyz;
               z = strbin(z);
               return z.c_str();
          }
          else
          {
              //strbcle suma palabra por palabra
              std::string long_buff = z, res;
              int numero_bucle = 0, numero_total_de_numeros_binarios = strwrds(long_buff.c_str()), operador;
              while(numero_bucle < numero_total_de_numeros_binarios)
              {
                  operador = atoi(strbcle(long_buff,numero_bucle).c_str()) + atoi(z.c_str());
                  res += itostr(operador);
                  numero_bucle++;
              }
              if(y == "b_s")
              {
                   res = binstr(res.c_str());
              }
              return res.c_str();
          }
     }
     else if(x == 2100)//mfs::sub
     {
         if(y == "str")
         {
             if((int)z[0] == 0)//empieza del principio
             {
                 int len = 0;
                 std::string operators = "";
                 std::string res;
                 while((int)xyz[len] < 11)//separa los operadores de las parlabras
                 {
                     operators += xyz[len];
                     len++;
                 }
                 xyz = chrbcle(xyz.c_str(),len,xyz.length());//deja las palabras sin los operadores
                 int count = 0;
                 while(count <= len)//realiza las operaciones
                 {
                     if((int)operators[count] == 8)// '\b' quita el primer caracter
                         z = chrbcle(z.c_str(),1,z.length());
                     else if((int)operators[count] == 9)// '\t' quita la primer palabra
                          z = wrdbcle(z,1,0);
                     else if((int)operators[count] == 10)// '\n" pasa a la siguiente palabra
                     {
                          res = strbcle(z,0);
                          z = wrdbcle(z,1,0);
                     }
                     count++;
                 }
                 res += z;
                 MUO_mfstream_erasewrd(xyz,res);//aca usa las palabras
                 return res.c_str();
             }
             if((int)z[0] == 1)//empieza desde el final
             {
                 int len = 0;
                 std::string operators = "";
                 std::string res;
                 while((int)xyz[len] < 11)
                 {
                     operators += xyz[len];
                     len++;
                 }
                 xyz = chrbcle(xyz.c_str(),len,xyz.length());
                 int count = 0;
                 int only_for_true = strwrds(z.c_str());
                 while(count <= len)
                 {
                     if((int)operators[count] == 8)// '\b' quita el ultimo caracter
                         z.erase(z.length()-1);
                     else if((int)operators[count] == 9)// '\t' quita la ultima palabra
                     {
                          z = wrdbcle(z,0,only_for_true);
                          only_for_true--;
                     }
                     else if((int)operators[count] == 10)// '\n' pasa a la siguiente palabra
                     {
                          res = strbcle(z,only_for_true);
                          z = wrdbcle(z,0,only_for_true);
                          only_for_true--;
                     }
                     count++;
                 }
                 res += z;
                 MUO_mfstream_erasewrd(xyz,res);
                 return res.c_str();
             }
             else
             {
                 std::string res = z,words_to_extract = xyz;
                 MUO_mfstream_erasewrd(words_to_extract,res);
                 return res.c_str();
             }
          }
          else if(y == "int")
          {
               int res = atoi(z.c_str()) - atoi(xyz.c_str());
               return itostr(res).c_str();
          }
          else if(y == "s_b")
          {
               z = ccbin(z.c_str());
               return z.c_str();
          }
          else
          {
              double res = strtod(z.c_str(),NULL) - strtod(xyz.c_str(),NULL);
              if(y == "dbl")
                   return dtostr(res).c_str();
              else
              {
                  std::string str_res = dtocc(res,44);
                  return str_res.c_str();
              }
          }
     }
     else if(x == 2101)//mfs::mul
     {
          if(y == "str")
          {
               x = atoi(xyz.c_str());
               if(x == 0)
               {
                    return "";
               }
               std::string res = "";
               int temp = 0;
               if((int)z[0] == 8)
               {
                    while(temp <= x)
                         res = z + res;
               }
               else
               {
                   while(temp <= x)
                              res += z;
               }
               return res.c_str();
          }
          else if(y == "int")
          {
               x = atoi(xyz.c_str());
               x = atoi(z.c_str()) * x;
               a = itostr(x);
               return a.c_str();
          }
          else if(y == "b_s")
          {
               int count = 0,bclend = strwrds(z.c_str());
               double allocated;
               const char* dynamic;
               std::string res = "";
               while(count != bclend)
               {
                    dynamic = strbcle(z,count).c_str();
                    allocated = strtod(dynamic,NULL);
                    allocated = pow(allocated,strtod(xyz.c_str(),NULL));
                    res += itostr(MUO_char_dtoi(allocated));
                    count++;
               }
               return res.c_str();
          }
          else
          {
               double num1 = strtod(xyz.c_str(),NULL);
               double num2 = strtod(z.c_str(),NULL);
               num1 = num1 * num2;
               if(y == "dbl")
                    return dtostr(num1).c_str();
               else
                   return dtocc(num1,44);
          }
     }
     else if(x == 2111)//mfs::pow
     {
          if(y == "str")
          {
               std::cout << "opcion temporalmente inexistente\n";
               return "";
          }
          else if(y == "int")
          {
               x = MUO_char_dtoi(pow(atoi(xyz.c_str()),atoi(z.c_str())));
               a = itostr(x);
               return a.c_str();
          }
          else if(y == "b_s")
          {
               int count = 0,bclend = strwrds(z.c_str());
               double allocated;
               const char* dynamic;
               std::string res = "";
               while(count != bclend)
               {
                    dynamic = strbcle(z,count).c_str();
                    allocated = strtod(dynamic,NULL);
                    allocated = pow(allocated,strtod(xyz.c_str(),NULL));
                    res += itostr(MUO_char_dtoi(allocated));
                    count++;
               }
               return res.c_str();
          }
          else
          {
               double num1 = strtod(xyz.c_str(),NULL);
               double num2 = strtod(z.c_str(),NULL);
               num1 = pow(num1,num2);
               return y == "dbl" ? dtostr(num1).c_str() : dtocc(num1,44);
          }
     }
     else
     {
         return "";
     }
}

mfstream::~mfstream()
{
    clear();
}

std::string MUO_mfstream_wrderase(std::string str,int x)
{
    if(x > strwrds(str.c_str()))
         return str;
    int y = 0, z = 0, len = str.length();
    bool xyz = false;
    std::string res = "";
    while(z < len)
    {
        if(xyz)
        {
            if((int)str[z] == 32)
                xyz = false;
        }
        else
        {
            if((int)str[z] != 32)
            {
                ++y;
                xyz = true;
            }
        }
        if(y != x)
        {
             res += str[z];
        }
        ++z;
    }
    return res;
}

void MUO_mfstream_erasewrd(std::string erase_this,std::string& from_this)
{
    int x, y, z = strwrds(erase_this.c_str()),xyz = strwrds(from_this.c_str()), res;
    for(x = 0;x < z;++x)
    {
        for(y = 0;y < xyz;++y)
        {
            if(strcmp(strbcle(erase_this,x).c_str(),strbcle(from_this,y).c_str()) == 0)
            {
                res = y;
                ++res;
                from_this = MUO_mfstream_wrderase(from_this,res);
                --xyz;
                --y;
            }
        }
    }
    return;
}

int MUO_magick_can_of_bean(std::string &x,int &y)
{
    int res = -1;//Es el pilar de la funcion (borrarlo podria causar un error en la aplicacion) 
    //unsigned short loop[1];
    if(y == -1)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isalnum(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -10)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isalpha(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -11)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(iscntrl(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -100)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isdigit(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -101)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isgraph(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -110)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(islower(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -111)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isprint(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -1000)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isspace(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -1001)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isupper(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -1010)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isxdigit(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
    }
    else if(y == -1011)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         res = MUO_fstream_loop[0];
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isalnum(x[MUO_fstream_loop[1]]))
              {
                   res = MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    else if(y == -1100)
    {
         MUO_fstream_loop[0] = res = x.length();
         MUO_fstream_loop[1] = 0;
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isalpha(x[MUO_fstream_loop[1]]))
              {
                   res = MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    else if(y == -1101)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         res = MUO_fstream_loop[0];
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(iscntrl(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    else if(y == -1110)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         res = MUO_fstream_loop[0];
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isdigit(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    else if(y == -1111)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         res = MUO_fstream_loop[0];
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isgraph(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    else if(y == -21)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         res = MUO_fstream_loop[0];
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(islower(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    else if(y == -210)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         res = MUO_fstream_loop[0];
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isprint(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    else if(y == -211)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         res = MUO_fstream_loop[0];
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isspace(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    else if(y == -2100)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         res = MUO_fstream_loop[0];
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isupper(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    else if(y == -2101)
    {
         MUO_fstream_loop[0] = x.length();
         MUO_fstream_loop[1] = 0;
         res = MUO_fstream_loop[0];
         while(MUO_fstream_loop[1] < MUO_fstream_loop[0])
         {
              if(isxdigit(x[MUO_fstream_loop[1]]))
              {
                   return MUO_fstream_loop[1];
              }
              ++MUO_fstream_loop[1];
         }
         return res;
    }
    return MUO_fstream_loop[0];//en caso de que los if de los while nunca lleguen a ser verdaderos
}

int filesize(const char* flnm)
{
    std::ifstream strm(flnm);
    if(strm.fail())//para que termine y devuelva cero si no existe el archivo
    {
                   return 0;
    }
    std::string x;
    char z;
    int y = 0, res = 0, xyz = 0;
    while(!strm.eof())
    {
                      getline(strm,x);
                      ++y;
                      ++xyz;
    }
    if(y != 0)
    {
         --y;//el primer renglon no cuenta
         res = y * 2;//un salto de renglon pesa 2 bites
         y = 0;
    }
    strm.clear();//dios creo esta funcion para salvarnos a todos de esos malditos bits
    strm.seekg(0L,std::ios::beg);//ios::beg es un tipo de implementacion de valores, aunque un short talvez seria mejor idea
    while(!strm.eof())
    {
                     strm.get(z);
                     y++;//cada caracter exeptuando los espacios raros de windows (el tab es un caracter comun) pesan 1 bite
    }
    y -= xyz;//al final de cada renglon hay un caracter invisible (tipo \º, en ubuntu el vim deja ^M) que lo indica, este pesa 1 bite
    res += y;
    strm.close();
    return res;
}
