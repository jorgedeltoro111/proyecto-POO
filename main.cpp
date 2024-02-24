#include "clases.h"
#include<iostream>
#include <vector> 
using namespace std;

int totalCuentas = 1;


int main(){
    //Creacion de usuario
    Usuario jorge("Jorge", 21, 3317050177);
    //Creacion de cuenta de prueba 1
    CuentaCredito cuenta1(2121, jorge);

    cuenta1.saldoAPagar();
    cuenta1.realizarCompra(1000);
    cuenta1.saldoAPagar();
    cuenta1.realizarPago(500);
    cuenta1.informacionCuenta();


    return 0;
}