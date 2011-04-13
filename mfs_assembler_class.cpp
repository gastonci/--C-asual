#include <coder>

extern int MUO_magick_can_of_bean(std::string &x,int &y);

bool MUO_mfs_class_assembler_debug(int &MUO_mfs_class_assembler_def,std::string &MUO_mfs_class_assembler_str,std::string &MUO_mfs_class_assembler_x,std::string &MUO_mfs_class_assembler_y,std::string &MUO_mfs_class_assembler_z)
{
    int x = mfsint(MUO_mfs_class_assembler_def);
    if(x == 0)
         return std::cout << "--------------------------------------------------\n";//std::cout<<setfill('-')<<setw(50)<<"-"<<endl;
    if(x > 0)
    {//<positivos>
        if(x < 8)
        {//<objetos>
             std::cout << "Definiendo objeto...\n";
             if(x == 1)
             {
                  std::cout << "mfs::words = palabra numero... " << MUO_mfs_class_assembler_x << " = " << strbcle(MUO_mfs_class_assembler_str,atoi(MUO_mfs_class_assembler_x.c_str())-1) << std::endl;
             }
             else if(x == 2)
             {
                  unsigned int x = (strcmp(MUO_mfs_class_assembler_x.c_str(),"/0") == 0)?0:MUO_mfs_class_assembler_str.find_first_of(MUO_mfs_class_assembler_x),y = (strcmp(MUO_mfs_class_assembler_y.c_str(),"/0") == 0)?MUO_mfs_class_assembler_str.length():MUO_mfs_class_assembler_str.find_last_of(MUO_mfs_class_assembler_y);
                  if(strcmp(MUO_mfs_class_assembler_x.c_str(),"/0") == 0)
                       MUO_mfs_class_assembler_x = "str.begin";
                  if(strcmp(MUO_mfs_class_assembler_y.c_str(),"/0") == 0)
                  {
                       MUO_mfs_class_assembler_y = "str.end";
                       y -= x;
                  }
                  std::cout << "mfs::fromto = from (" << MUO_mfs_class_assembler_x << ") to (" << MUO_mfs_class_assembler_y << ") = " << redo(MUO_mfs_class_assembler_str,x,y+1-x) << std::endl;
             }
             else if(x == 4)
             {
                  std::cout << "mfs::line = " << MUO_mfs_class_assembler_str << std::endl;
             }
             else if(x == 5)
             {
                  int y = atoi(MUO_mfs_class_assembler_x.c_str());
                  if(y < 0)
                  {
                       std::cout << "Uso de magick can of bean... (" << MUO_mfs_class_assembler_str << "," << y << ") = ";
                       y = MUO_magick_can_of_bean(MUO_mfs_class_assembler_str,y);
                       std::cout << y << std::endl;
                  }
                  int z = atoi(MUO_mfs_class_assembler_y.c_str());
                  if(z < 0)
                  {
                       std::cout << "Uso de magick can of bean... (" << MUO_mfs_class_assembler_str << "," << z << ") = ";
                       z = MUO_magick_can_of_bean(MUO_mfs_class_assembler_str,z);
                       std::cout << z << std::endl;
                  }
                  else if(MUO_mfs_class_assembler_y == "/0")
                  {
                       z = MUO_mfs_class_assembler_str.length();
                       z -= y;
                  }
                  std::cout << "mfs::chars = redo(" << MUO_mfs_class_assembler_str << "," << y << "," << z << ") = " << redo(MUO_mfs_class_assembler_str,y,z) << std::endl;
             }
             else if(x == 6)
             {
                  short x = atoi(MUO_mfs_class_assembler_x.c_str());
                  if(x >= MUO_mfs_class_assembler_str.length())
                       std::cout << "mfs::chr = str[out of reach] = NULL\n";
                  else
                      std::cout << "mfs::chr = str[" << x << "] = " << MUO_mfs_class_assembler_str[x] << std::endl;
             }
             else if(x == 7)
             {
                  int x = MUO_mfs_class_assembler_str.find_first_of(MUO_mfs_class_assembler_x);
                  if(x == std::string::npos)
                       std::cout << "mfs::infromto = no se encontro from(" << MUO_mfs_class_assembler_x << ")\n";
                  else
                  {
                      x += MUO_mfs_class_assembler_x.length();
                      int y = MUO_mfs_class_assembler_str.find_last_of(MUO_mfs_class_assembler_y);
                      if(y == std::string::npos)
                           std::cout << "mfs::infromto = no se encontro to(" << MUO_mfs_class_assembler_y << ")\n";
                      else
                      {
                          y -=x;
                          y -= MUO_mfs_class_assembler_y.length();
                          y++;
                          std::cout << "mfs::infromto = from (" << MUO_mfs_class_assembler_x << ") to (" << MUO_mfs_class_assembler_y << ") = " << redo(MUO_mfs_class_assembler_str,x,y) << std::endl;
                      }
                  }
             }
             else
             {
                 std::cout << x << " no es un objeto existente.\n";
                 return false;
             }
        }//</objetos>
        else if(x < 16)
        {//<tipo_de_objeto>
             std::cout << "Definiendo el tipo de objeto...\nLinea: " << MUO_mfs_class_assembler_str << "\nObjeto: " << MUO_mfs_class_assembler_x << std::endl;
             {
                  if(x == 8)
                  {
                       std::cout << "Tipo de objeto: <std::string>\nObjeto reinterpretado: " << MUO_mfs_class_assembler_x << std::endl;
                  }
                  else if(x == 9)
                  {
                       std::cout << "Tipo de objeto: <int>\nObjeto reinterpretado: " << atoi(MUO_mfs_class_assembler_x.c_str()) << std::endl;
                  }
                  else if(x == 10)
                  {
                       char* x;
                       std::cout << "Tipo de objeto: <double>\nObjeto reinterpretado: " << strtod(MUO_mfs_class_assembler_x.c_str(),&x) << std::endl;
                  }
                  else if(x == 14)
                  {
                       std::cout << "Tipo de objeto: <international_double>\nObjeto reinterpretado: " << dtocc(strtod(MUO_mfs_class_assembler_x.c_str(),NULL),44) << std::endl;
                  }
                  else
                  {
                      std::cout << x << " no es un tipo de objeto existente.\n";
                      return false;
                  }
             }
        }//</tipo_de_objeto>
        else
        {
            std::cout << x << " no se encuentra en mfstream::class_assembler()\n";
        }
    }//</positivos>
    return true;
}

