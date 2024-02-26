#ifndef CLASES_H
#define CLASES_H
#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || (__MACH__)
#define CLEAR "clear"
#else
#error "S0 no soportado para limpiar pantalla"
#endif
#include<iostream>
#include<vector>
using namespace std;

extern int totalCuentas;

void continuar(){
    cout<<"Presione entrar para continuar . . ."<<endl;
    cin.get();
    system(CLEAR);
}

class Usuario{
    private:
        string nombreCompleto;
        int edad;
        string telefono;
    public:
        Usuario(string nombre, int edad, string telefono){
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
        string getTelefono(){
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
            const string telefono = this->titular.getTelefono();
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
            const string telefono = this->titular.getTelefono();
            cout<<"---Cuenta de "<<nombre<<"---"<<endl;
            cout<<"Tipo: Credito"<<endl;
            cout<<"N.Cuenta: "<<this->numeroCuenta<<endl;
            cout<<"Telefono: "<<telefono<<endl;
            cout<<"Edad del usuario: "<<edad<<endl;
            cout<<"NIP: "<<this->nip<<endl;
            continuar();
        }
};
/**---menu principal---
 * 1-iniciar sesion
 * 2-crear cuenta de credito 
 * 3-crear cuenta de debito
 * 4-salir
*/
/**---submenu de la opcion 1---
 * 1
*/

class Banco{
    private:
        vector<CuentaDebito*> cuentasDebito;
        vector<CuentaCredito*> cuentasCredito;
    public:
        Usuario* crearUsuario(){
            string nombre; 
            int edad; 
            string telefono;
            cout<<"---Datos Usuario---"<<endl;
            cout<<"Ingrese el nombre del titular: ";
            cin>>nombre;
            cin.ignore();
            cout<<"Ingrese la edad del titular: ";
            cin>>edad;
            cin.ignore();
            cout<<"Ingrese el telefono del titular: ";
            cin>>telefono;
            cin.ignore();
            Usuario* nuevo = new nuevo(string nombre, int edad, string telefono);

            return nuevo;
        }
        void crearCuentaDebito(){
            int nip;
            Usuario* nuevo = this->crearUsuario();
            cout<<"---Datos de Cuenta---"<<endl;
            cout<<"Cree un nuevo nip: ";
            cin>>nip;
            CuentaDebito* nueva = new CuentaDebito(nip, nuevo);
            this->cuentasDebito.push_back(nueva);
            continuar();
        }
        void crearCuentaCredito(){
            int nip;
            Usuario* nuevo = this->crearUsuario();
            cout<<"---Datos de Cuenta---"<<endl;
            cout<<"Cree un nuevo nip: ";
            cin>>nip;
            CuentaCredito* nueva = new CuentaCredito(nip, nuevo);
            this->crearCuentaCredito.push_back(nueva); 
            continuar();
        }
        void iniciarSesion(){
            bool band = true;
            string nombre;
            int nip;
            cout<<"---Inicio de sesion---"<<endl;
            cout<<"Usuario: ";
            cin>>nombre;
            cin.ignore();
            cout<<"Nip: ";
            cin>>nip;
            cin.ignore();
            for(int i=0; i<this->cuentasCredito; i++){
                if(nombre == this->cuentasCredito[i] && nip == this->cuentasCredito[i]){
                    //submenu
                }else if(nombre == this->cuentasDebito[i] && nip == this->cuentasDebito[i]){
                    //submenu
                }
            }
            if(band){
                cout<<"El usuario ingresado no tiene cuenta actualmete."<<endl;
                continuar();
            }

        }


};




#endif
