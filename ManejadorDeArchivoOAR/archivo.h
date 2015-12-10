#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <string>
#include <ios>
#include <fstream>
using namespace std;

class Archivo
{
public:
    Archivo();
    ~Archivo();
    bool open(string);//Abre el archivo
    bool close();//Cierra el archivo
    int read(char*,int);//lee del archivo y asigna lo leido a un string
    int write(const char*,int);//escribe en el archivo el string enviado
    string readRecord(int,int,int);//lee un registro
    bool writeRecord(const char*,int,int,int);//escribe un registro
    bool updateRecord();//actualiza el archivo
    int deleteRecord(int,int,int);//elimina un registro
    bool flush();//flushea el archivo
    bool seekg(int,ios_base::seekdir);//mueve el puntero de lectura
    bool seekp(int,ios_base::seekdir);//mueve el puntero de escritura
    int tellp();//indica la posicion del puntero de escritura
    int tellg();//indica la posicion del puntero de lectura
    bool isOpen();//Determina si el archivo esta abierto
    bool isOk();//Determina si el archivo esta en condiciones para operar con el
    bool isBoF();//Indica si el puntero de lectura o escritura esta al principio
    bool isEoF();//Indica si el puntero de lectura o escritura esta al final
    fstream file;//es el archivo en si
    string filename;//guarda el nombre del archivo
};

#endif // ARCHIVO_H
