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

const int INICIAR_SESION = 1;
const int CREAR_CUENTA_DEBITO = 2;
const int CREAR_CUENTA_CREDITO = 3;
const int SALIR = 4;
const int REALIZAR_COMPRA = 5;
const int REALIZAR_PAGO = 6; 
const int INFORMACION_CUENTA = 7;
const int DEPOSITAR = 8; 
const int RETIRAR = 9;
const int EXIT = 0;




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
        void continuar(){
            cout<<"Presione entrar para continuar . . ."<<endl;
            cin.get();
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
    friend class Banco;
    protected:
        Usuario titular;
        int numeroCuenta = 0;
        int nip;
        float saldo;
        string concepto;
    public:
        Cuenta(int nip, Usuario titular) : titular(titular) {
            this->saldo = 0;
            this->numeroCuenta = totalCuentas++;
            this->nip = nip;
            this->titular = titular;
        }
        void continuar(){
            cout<<"Presione entrar para continuar . . ."<<endl;
            cin.get();
        }
        void mostrarInfo(){
            system(CLEAR);
            cout<<"---Información del usuario---"<<endl;
            this->titular.mostrarInformacion();
            cout<<"---Información de la cuenta--"<<endl;
            cout<<"N.Cuenta: "<<this->numeroCuenta<<endl;
            cout<<"Saldo actual: $"<<this->saldo<<" (mxn)"<<endl;
            continuar();
        }
};

class CuentaDebito : public Cuenta{
    public:
        CuentaDebito(int nip, Usuario titular) : Cuenta(nip, titular) {}
        void retirarDinero(float monto){
            system(CLEAR);
            fflush(stdin);
            string nombre = this->titular.getNombre();
            this->saldo -= monto;
            cout<<"Se han retirado $"<<monto<<" pesos a la cuenta de "<<nombre<<endl;
            continuar();
        }
        void depositarDinero(float monto){
            system(CLEAR);
            fflush(stdin);
            string nombre = this->titular.getNombre();
            this->saldo += monto;
            cout<<"Se han ingresado $"<<monto<<" pesos a la cuenta de "<<nombre<<endl;
            continuar();
        }
        void obtenerSaldo(){
            system(CLEAR);
            cout<<"---Monto actual---"<<endl;
            cout<<"Saldo: $"<<this->saldo<<endl;
            cout<<"Numero de cuenta: "<<this->numeroCuenta<<endl;
            cout<<"------------------"<<endl;
        }
        void informacionCuenta(){
            system(CLEAR);
            fflush(stdin);
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

class CuentaCredito : public Cuenta{
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
            system(CLEAR);
            cout<<"---Saldo actual---"<<endl;
            cout<<"Saldo a pagar en la proxima fecha de limite es: "<<this->deuda<<endl;
            cout<<"Limite disponible: "<<limite-deuda<<endl;
        }
        void realizarCompra(float monto, string concepto){
            system(CLEAR);
            fflush(stdin);
            this->concepto = concepto;
            this->deuda += monto;
            cout<<"Compra de "<<concepto<<" - $"<<monto<<" pesos realizada correctamente"<<endl;
            continuar();
        }
        void realizarPago(float monto){
            system(CLEAR);
            this->deuda -= monto;
            cout<<"Pago de $"<<monto<<" pesos realizado correctamente"<<endl;
            continuar();
        }
        void informacionCuenta(){
            system(CLEAR);
            fflush(stdin);
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

class Banco{
    private:
        vector<CuentaDebito> cuentasDebito;
        vector<CuentaCredito> cuentasCredito;
        int opc;
    public:
        void continuar(){
            cout<<"Presione entrar para continuar . . ."<<endl;
            cin.get();
        }
        void menuPrincipal(){
            system(CLEAR);
            cout<<"---Menu principal---"<<endl;
            cout<<"1-Iniciar sesion"<<endl;
            cout<<"2-Crear cuenta de debito"<<endl;
            cout<<"3-Crear cuenta de credito"<<endl;
            cout<<"0-EXIT"<<endl;
            cout<<"Opcion: ";
            cin>>this->opc;
            fflush(stdin);
            system(CLEAR);
        }
        void subMenuCredito(){
            cout<<"---Cuenta de credito---"<<endl;
            cout<<"5-Realizar compra"<<endl;
            cout<<"6-Realizar pago"<<endl;
            cout<<"7-Informacion de la cuenta"<<endl;
            cout<<"4-Salir de la cuenta"<<endl;
            cout<<"Opcion: ";
            cin>>this->opc;
            fflush(stdin);
        }
        void subMenuDebito(){
            cout<<"---Cuenta de debito---"<<endl;
            cout<<"8-Depositar"<<endl;
            cout<<"9-Retirar"<<endl;
            cout<<"7-Informacion de la cuenta"<<endl;
            cout<<"4-Salir de la cuenta"<<endl;
            cout<<"Opcion: ";
            cin>>this->opc;
            fflush(stdin);
        }
        Usuario crearUsuario(){
            system(CLEAR);
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
            Usuario nuevo = Usuario(nombre, edad, telefono);

            return nuevo;
        }
        void crearCuentaDebito(){
            int nip;
            Usuario nuevo = this->crearUsuario();
            cout<<"---Datos de Cuenta---"<<endl;
            cout<<"Cree un nuevo nip: ";
            cin>>nip;
            fflush(stdin);
            CuentaDebito nueva = CuentaDebito(nip, nuevo);
            this->cuentasDebito.push_back(nueva);
            continuar();
        }
        void crearCuentaCredito(){
            int nip;
            Usuario nuevo = this->crearUsuario();
            cout<<"---Datos de Cuenta---"<<endl;
            cout<<"Cree un nuevo nip: ";
            cin>>nip;
            fflush(stdin);
            CuentaCredito nueva = CuentaCredito(nip, nuevo);
            this->cuentasCredito.push_back(nueva); 
            continuar();
        }
        void iniciarSesion() {
    bool band = true;
    string concepto, nombre;
    float cantidad;
    int nip;
    do {
        this->menuPrincipal();
        switch (this->opc) {
            case INICIAR_SESION: {
                system(CLEAR);
                cout << "---Inicio de sesion---" << endl;
                cout << "Usuario: ";
                cin >> nombre;
                cout << "Nip: ";
                cin >> nip;
                for (int i = 0; i < this->cuentasCredito.size(); i++) {
                    if (nombre == this->cuentasCredito[i].titular.getNombre() && nip == this->cuentasCredito[i].nip) {
                        band = false;
                        cin.get(); // Espera a que el usuario presione Enter para continuar
                        do {
                            this->cuentasCredito[i].saldoAPagar();
                            this->subMenuCredito();
                            switch (this->opc) {
                                case REALIZAR_COMPRA: {
                                    system(CLEAR);
                                    cout << "---Compra---" << endl;
                                    cout << "Ingrese el concepto: ";
                                    cin >> concepto;
                                    cout << "Ingrese el monto: ";
                                    cin >> cantidad;
                                    this->cuentasCredito[i].realizarCompra(cantidad, concepto);
                                    break;
                                }
                                case REALIZAR_PAGO: {
                                    system(CLEAR);
                                    cout << "---Pago---" << endl;
                                    cout << "Ingrese el monto a pagar: ";
                                    cin >> cantidad;
                                    this->cuentasCredito[i].realizarPago(cantidad);
                                    break;
                                }
                                case INFORMACION_CUENTA: {
                                    system(CLEAR);
                                    this->cuentasCredito[i].informacionCuenta();
                                    break;
                                }
                                case SALIR: {
                                    break;
                                }
                                default: {
                                    system(CLEAR);
                                    cout << "Opcion no valida" << endl;
                                    continuar();
                                    break;
                                }
                            }
                        } while (this->opc != SALIR);
                        break;
                    }
                }
                for (int i = 0; i < this->cuentasDebito.size(); i++) {
                    if (nombre == this->cuentasDebito[i].titular.getNombre() && nip == this->cuentasDebito[i].nip) {
                        band = false;
                        do {
                            this->cuentasDebito[i].obtenerSaldo();
                            this->subMenuDebito();
                            switch (this->opc) {
                                case DEPOSITAR: {
                                    system(CLEAR);
                                    cout << "---Deposito---" << endl;
                                    cout << "Ingrese el monto: ";
                                    cin >> cantidad;
                                    this->cuentasDebito[i].depositarDinero(cantidad);
                                    fflush(stdin);
                                    break;
                                }
                                case RETIRAR: {
                                    system(CLEAR);
                                    cout << "---Retiro---" << endl;
                                    cout << "Ingrese el monto: ";
                                    cin >> cantidad;
                                    this->cuentasDebito[i].retirarDinero(cantidad);
                                    break;
                                }
                                case INFORMACION_CUENTA: {
                                    system(CLEAR);
                                    cout << "---Informacion de la cuenta---" << endl;
                                    this->cuentasDebito[i].informacionCuenta();
                                    break;
                                }
                                case SALIR: {
                                    break;
                                }
                                default: {
                                    system(CLEAR);
                                    cout << "Opcion no valida" << endl;
                                    continuar();
                                    break;
                                }
                            }
                        } while (this->opc != SALIR);
                        break;
                    }
                }
                if (band) {
                    system(CLEAR);
                    cout << "El usuario ingresado no tiene cuenta actualmente." << endl;
                    continuar();
                }
                break;
            }
            case CREAR_CUENTA_DEBITO: {
                system(CLEAR);
                this->crearCuentaDebito();
                band = false;
                break;
            }
            case CREAR_CUENTA_CREDITO: {
                system(CLEAR);
                this->crearCuentaCredito();
                band = false;
                break;
            }
            case EXIT: {
                break;
            }
            default: {
                system(CLEAR);
                cout << "Opcion no valida" << endl;
                continuar();
                break;
            }
        }
    } while (this->opc != EXIT);
}
};




#endif
