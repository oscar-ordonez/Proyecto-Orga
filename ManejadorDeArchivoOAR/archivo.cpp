#include "archivo.h"
#include <string>
#include <ios>
#include <fstream>
#include <sstream>
using namespace std;

Archivo::Archivo(){

}

Archivo::~Archivo(){

}

bool Archivo::open(string name){//Abre el archivo
    filename=name;
    file.open(name.c_str(), fstream::in | fstream::out);//abre el archivo en modo escritura y lectura
    if(!file.is_open()){//Se crea el archivo y se le escribe un espacio, ya que si no tiene un byte tiene problemas al momento de escribir
        file.open(name.c_str(),fstream::out);
        file.write(" ",1);
        file.flush();
        file.close();
        file.open(name.c_str(), fstream::in | fstream::out);
    }
    if (file.is_open())
        return true;//si no hubo problemas, signiica que esta abierto el archivo

    return false;//No se pudo abrir el archivo
}

bool Archivo::close(){//Cierra el archivo
    if (!file.is_open())//determina primero si el archivo esta abierto
        return false;
    file.close();
    if(file.rdstate()!= 0)//Si el archivo tuvo problemas para cerrarse retorna falso
        return false;

    return true;
}

string Archivo::readRecord(int p,int init,int size_record){//Lee un registro
    file.seekg(0,ios_base::beg);//Mueve el puntero al principio
    file.seekg(init,ios_base::cur);//Luego lo mueve hacia donde comienzan los registros
    file.seekg((size_record*p),ios_base::cur);//mueve el puntero al registro deseado
    char buffer[size_record];//se crea un buffer del tamanio del registro
    file.read(buffer,size_record);//se lee el registro
    buffer[size_record]='\0';//se asigna manualmente el NULL al final
    stringstream ss;
    ss << buffer;//se agrega el buffer al StringStream para poder devolverlo como string
    return ss.str();
}

int Archivo::read(char* buffer,int s){//Lee una cierta cantidad de bytes
    if (!file.is_open())
        return -1;
    file.read(buffer,s);
    return file.gcount();
}

int Archivo::write(const char* buffer,int s){//Escribe en el archivo
    if (!file.is_open())
        return -1;
    file.write(buffer,s);
    if(file.rdstate()!= 0)
        return -1;

    return s;
}

bool Archivo::writeRecord(const char* buffer,int where,int init,int size_record){//Escribe un Registro en el archivo
    file.seekp(0,ios_base::beg);//mueve el puntero al principio
    file.seekp(init,ios_base::cur);//mueve el puntero hacia donde comienzan los registros
    if(where == -1){//Si no hay nada en el Avail List se agrega el registro al final
        file.seekp(0,ios_base::end);
        file.write(buffer,size_record);
    }
    else if(where == -2){//Si es el primer registro agrega el registro al final
        file.seekp(0,ios_base::end);
        file.write(buffer,size_record);
    }
    else{//SI hay algo en el AL
        file.seekp((size_record*where),ios_base::cur);//Se mueve el puntero hacia donde se encuentra la proxima posicion a insertar
        file.write(buffer,size_record);//se escribe el archivo
    }
    file.flush();
    if(file.rdstate()!= 0)
        return false;
    return true;
}

bool ADTRecordFile::updateRecord(){

    return this->flush();//Flushea el archivo
}

int Archivo::deleteRecord(int p,int init,int size_record){//Elimina un registro
    file.seekp(0,ios_base::beg);//MUeve el puntero hacia el principio
    file.seekp(init,ios_base::cur);//Mueve el puntero hacia donde comienzan los registros
    file.seekp((p*size_record),ios_base::cur);//Se mueve hacia el registro que se desea eliminar
    file.write("*",1);//Marca el registro como borrado
    file.flush();
    return p;//Para el availList
}

bool Archivo::flush(){//Flushea el archivo
    if (!file.is_open())
        return false;
    file.flush();
    if(file.rdstate()!= 0)
       return false;

    return true;
}

bool Archivo::seekg(int n,ios_base::seekdir way){//Es el metodo de mover el puntero de lectura
    if (!file.is_open())
        return false;

    file.seekg(n,way);

    return true;
}
bool Archivo::seekp(int n,ios_base::seekdir way){//Es el metodo de mover el puntero de escritura
    if (!file.is_open())
        return false;

    file.seekp(n,way);
    return true;
}

int Archivo::tellg(){//indica la posicion del puntero de lectura
    if (!file.is_open())
        return -1;

    return file.tellg();
}

int Archivo::tellp(){//indica la posicion del puntero de escritura
    if (!file.is_open())
        return -1;

    return file.tellp();
}

bool Archivo::isOpen(){//Determina si el archivo esta abierto
    if(file.is_open())
        return true;

    return false;
}

bool Archivo::isOk(){//determina si el archivo esta en condiciones para usarse
    if (!file.is_open())
        return false;

    if(file.good())
        return true;

    return false;
}

bool Archivo::isBoF(){//Indica si el puntero de lectura o escritura esta al principio
    if (!file.is_open())
        return false;

    if(file.tellg()==0)
        return true;

    return false;
}

bool Archivo::isEoF(){//Indica si el puntero de lectura o escritura esta al final
    if(file.eof())
        return true;
    return false;
}
