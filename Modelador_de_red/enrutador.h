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

};

#endif // ENRUTADOR_H
