#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <string>
#include <map>
#include <vector>

using namespace std;

class Enrutador
{
private:
    map<string,int> conexiones;

public:
    Enrutador();
    map<string, int> getConexiones() const;
    void setConexiones(string, vector<string>);
    void setConexiones(map<string, int>);
    bool existeconexion(string, int*);
    void enrutadorappend(string,int);
    void eliminarconexion(string);
    vector<int> retornarcostosmc(vector<string>);
};

#endif // ENRUTADOR_H
