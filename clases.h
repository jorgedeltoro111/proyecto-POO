#ifndef CLASES_H
#define CLASES_H
#include<iostream>
using namespace std;

extern int totalCuentas;

void continuar(){
    cout<<"Presione entrar para continuar . . ."<<endl;
    cin.get();
    system("cls");
}

class Usuario{
    private:
        string nombreCompleto;
        int edad;
        long long int telefono;
    public:
        Usuario(string nombre, int edad, long long int telefono){
            this->nombreCompleto = nombre;
            this->edad = edad;
            this->telefono = telefono;
        }
        void mostrarInformacion(){
            cout<<"Nombre: "<<this->nombreCompleto<<endl;
            cout<<"Edad: "<<this->edad<<endl;
            cout<<"Telefono: "<<this->telefono<<endl;
            continuar();
        }
        string getNombre(){
            return this->nombreCompleto;
        }
        int getEdad(){
            return this->edad;
        }
        long long int getTelefono(){
            return this->telefono;
        }
};

class Cuenta{
    protected:
        Usuario titular;
        int numeroCuenta = 0;
        int nip;
        float saldo;
    public:
        Cuenta(int nip, Usuario titular) : titular(titular) {
            this->saldo = 0;
            this->numeroCuenta = totalCuentas++;
            this->nip = nip;
            this->titular = titular;
        }
        void mostrarInfo(){
            cout<<"---Información del usuario---"<<endl;
            this->titular.mostrarInformacion();
            cout<<"---Información de la cuenta--"<<endl;
            cout<<"N.Cuenta: "<<this->numeroCuenta<<endl;
            cout<<"Saldo actual: $"<<this->saldo<<" (mxn)"<<endl;
            continuar();
        }
};

class CuentaDebito : protected Cuenta{
    public:
        CuentaDebito(int nip, Usuario titular) : Cuenta(nip, titular) {}
        void depositarDinero(float monto){
            string nombre = this->titular.getNombre();
            this->saldo += monto;
            cout<<"Se han ingresado $"<<monto<<" pesos a la cuenta de "<<nombre<<endl;
            continuar();
        }
        void obtenerSaldo(){
            cout<<"---Monto actual---"<<endl;
            cout<<"Saldo: $"<<this->saldo<<endl;
            cout<<"Numero de cuenta: "<<this->numeroCuenta<<endl;
            cout<<"------------------"<<endl;
            continuar();
        }
        void informacionCuenta(){
            const string nombre = this->titular.getNombre();
            const int edad = this->titular.getEdad();
            const long long int telefono = this->titular.getTelefono();
            cout<<"---Cuenta de "<<nombre<<"---"<<endl;
            cout<<"Tipo: Debito"<<endl;
            cout<<"Numero de cuenta: "<<this->numeroCuenta<<endl;
            cout<<"Telefono: "<<telefono<<endl;
            cout<<"Edad del usuario: "<<edad<<endl;
            cout<<"NIP: "<<this->nip<<endl;
            continuar();
        }
};

class CuentaCredito : protected Cuenta{
    private:
        float deuda = 0;
        float limite;
        float tasaInteres;
        int fechaCorte;
        int fechaLimite;
    public:
        CuentaCredito(int nip, Usuario titular) : Cuenta(nip, titular) {
            this->limite = 5000;
            this->tasaInteres = 0.25;
            this->fechaCorte = 26;
            this->fechaLimite = 5;
        }
        void saldoAPagar(){ 
            cout<<"---Saldo actual---"<<endl;
            cout<<"Saldo a pagar en la proxima fecha de limite es: "<<this->deuda<<endl;
            cout<<"Limite disponible: "<<limite-deuda<<endl;
            continuar();
        }
        void realizarCompra(float monto){
            this->deuda += monto;
            cout<<"Compra de $"<<monto<<" pesos realizada correctamente"<<endl;
            continuar();
        }
        void realizarPago(float monto){
            this->deuda -= monto;
            cout<<"Pago de $"<<monto<<" pesos realizado correctamente"<<endl;
            continuar();
        }
        void informacionCuenta(){
            const string nombre = this->titular.getNombre();
            const int edad = this->titular.getEdad();
            const long long int telefono = this->titular.getTelefono();
            cout<<"---Cuenta de "<<nombre<<"---"<<endl;
            cout<<"Tipo: Credito"<<endl;
            cout<<"N.Cuenta: "<<this->numeroCuenta<<endl;
            cout<<"Telefono: "<<telefono<<endl;
            cout<<"Edad del usuario: "<<edad<<endl;
            cout<<"NIP: "<<this->nip<<endl;
            continuar();
        }
};


class Banco{
    private:
        Cuenta* cabeza;

};


#endif
