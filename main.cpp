#include <iostream>
#include <iomanip>
#include <limits>
#include <new>
using namespace std;

static const int NUM_PRODUCTS = 5;
static const int NUM_MP = 4;

static const int REQ[NUM_PRODUCTS][NUM_MP] = {
    {2,1,0,1},
    {1,2,1,0},
    {3,0,1,1},
    {0,1,2,2},
    {1,1,1,1}
};

static const float MP_COST[NUM_MP] = {10.0f,8.0f,5.0f,12.0f};

const char* PNAME[NUM_PRODUCTS] = {"Comp. A","Comp. B","Comp. C","Comp. D","Comp. E"};
const char* MPNAME[NUM_MP] = {"MP-01","MP-02","MP-03","MP-04"};

float readFloat(const char* msg, float a, float b){
    float v;
    for(;;){
        cout<<msg;
        if(cin>>v && v>=a && v<=b) return v;
        cout<<"Entrada invalida.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}
int readInt(const char* msg, int a, int b){
    int v;
    for(;;){
        cout<<msg;
        if(cin>>v && v>=a && v<=b) return v;
        cout<<"Entrada invalida.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}

class SystemCOGS{
    float** plan;
    int weeks;
    float* costUnit;
    float* mpInv;
public:
    SystemCOGS():plan(nullptr),weeks(0),costUnit(nullptr),mpInv(nullptr){
        init(4);
        cout<<"Inicializacion exitosa. Matriz de Planificacion: "<<NUM_PRODUCTS<<" Productos x "<<weeks<<" Semanas.\n\n";
    }
    ~SystemCOGS(){
        freeAll();
    }

    void init(int w){
        if(w<=0) w=1;
        plan=new float*[NUM_PRODUCTS];
        for(int i=0;i<NUM_PRODUCTS;i++){
            plan[i]=new float[w];
            for(int j=0;j<w;j++) plan[i][j]=0.0f;
        }
        weeks=w;
        costUnit=new float[NUM_PRODUCTS];
        for(int i=0;i<NUM_PRODUCTS;i++) costUnit[i]=10.0f+5.0f*i;
        mpInv=new float[NUM_MP];
        mpInv[0]=2000.0f; mpInv[1]=1500.0f; mpInv[2]=1000.0f; mpInv[3]=1200.0f;
    }

    void freeAll(){
        if(plan){
            for(int i=0;i<NUM_PRODUCTS;i++) delete[] plan[i];
            delete[] plan;
            plan=nullptr;
        }
        delete[] costUnit; costUnit=nullptr;
        delete[] mpInv; mpInv=nullptr;
        weeks=0;
    }

    void printPlan() const{
        cout<<"\n--- Plan de Produccion (unidades) ---\n";
        cout<<setw(12)<<"Producto";
        for(int w=0;w<weeks;w++) cout<<setw(10)<<("S"+to_string(w));
        cout<<"\n";
        for(int p=0;p<NUM_PRODUCTS;p++){
            cout<<setw(12)<<PNAME[p];
            for(int w=0;w<weeks;w++) cout<<setw(10)<<fixed<<setprecision(0)<<plan[p][w];
            cout<<"\n";
        }
        cout<<"\n";
    }

    void addWeek(){
        int nw=weeks+1;
        try{
            for(int p=0;p<NUM_PRODUCTS;p++){
                float* row=new float[nw];
                for(int w=0;w<weeks;w++) row[w]=plan[p][w];
                row[nw-1]=0.0f;
                delete[] plan[p];
                plan[p]=row;
            }
            weeks=nw;
            cout<<"Matriz redimensionada a "<<NUM_PRODUCTS<<"x"<<weeks<<". ¡Memoria gestionada con exito!\n";
        }catch(const bad_alloc&){
            cout<<"ERROR: No se pudo ampliar la matriz.\n";
        }
    }

    void setProduction(){
        int p=readInt("Ingrese Producto (0-4): ",0,NUM_PRODUCTS-1);
        int w=readInt(("Ingrese Semana (0-"+to_string(weeks-1)+"): ").c_str(),0,weeks-1);
        float q=readFloat("Cantidad a producir: ",0.0f,1.0e9f);
        plan[p][w]=q;
        cout<<"Actualizado: "<<PNAME[p]<<" en S"<<w<<" = "<<q<<" unidades.\n";
    }

    void consumptionWeek(int w, float outC[NUM_MP]) const{
        for(int m=0;m<NUM_MP;m++) outC[m]=0.0f;
        for(int p=0;p<NUM_PRODUCTS;p++){
            float u=plan[p][w];
            for(int m=0;m<NUM_MP;m++) outC[m]+=u*REQ[p][m];
        }
    }

    void showConsumption(){
        int w=readInt(("Semana para reporte de consumo (0-"+to_string(weeks-1)+"): ").c_str(),0,weeks-1);
        float c[NUM_MP];
        consumptionWeek(w,c);
        cout<<"\n--- Consumo de Materia Prima (Semana "<<w<<") ---\n";
        for(int m=0;m<NUM_MP;m++) cout<<setw(8)<<MPNAME[m]<<": "<<fixed<<setprecision(2)<<c[m]<<" u.\n";
        cout<<"\n";
    }

    void calcCOGS(){
        int w=readInt(("Ingrese Semana para el calculo (0-"+to_string(weeks-1)+"): ").c_str(),0,weeks-1);
        float prod=0.0f;
        float cogs=0.0f;
        for(int p=0;p<NUM_PRODUCTS;p++){
            float u=plan[p][w];
            prod+=u;
            cogs+=u*costUnit[p];
        }
        float c[NUM_MP];
        consumptionWeek(w,c);
        float invIni=0.0f, invFin=0.0f;
        for(int m=0;m<NUM_MP;m++){
            invIni+=mpInv[m]*MP_COST[m];
            float r=mpInv[m]-c[m];
            if(r<0.0f) r=0.0f;
            invFin+=r*MP_COST[m];
        }
        cout<<"\n--- Reporte de Costos (Semana "<<w<<") ---\n";
        cout<<"Produccion Total: "<<fixed<<setprecision(0)<<prod<<" unidades.\n";
        cout<<"Costo Total de Produccion (COGS): $"<<fixed<<setprecision(2)<<cogs<<"\n";
        cout<<"Consumo de Materia Prima:\n";
        for(int m=0;m<NUM_MP;m++) cout<<"  "<<MPNAME[m]<<": "<<fixed<<setprecision(2)<<c[m]<<" u.\n";
        cout<<"Valor del Inventario Inicial (MP): $"<<fixed<<setprecision(2)<<invIni<<"\n";
        cout<<"Valor del Inventario Final  (MP): $"<<fixed<<setprecision(2)<<invFin<<"\n\n";
    }

    void run(){
        bool on=true;
        while(on){
            cout<<"--- Sistema de Planificacion y Costos (COGS) ---\n";
            cout<<"1. Ver Plan de Produccion\n";
            cout<<"2. Agregar Nueva Semana (Redimensionar Matriz)\n";
            cout<<"3. Modificar Produccion\n";
            cout<<"4. Calcular COGS y Final Inventory\n";
            cout<<"5. Reporte de Consumo\n";
            cout<<"6. Salir\n";
            int op=readInt("Opcion: ",1,6);
            if(op==1) printPlan();
            else if(op==2){ cout<<"Agregando Semana "<<weeks<<"...\n"; addWeek(); }
            else if(op==3) setProduction();
            else if(op==4) calcCOGS();
            else if(op==5) showConsumption();
            else if(op==6){ cout<<"Liberando memoria de Matriz y Vectores Dinamicos...\n"; on=false; }
            cout<<"\n";
        }
    }
};

int main(){
    cout.setf(ios::fixed); cout<<setprecision(2);
    try{
        SystemCOGS app;
        app.run();
    }catch(...){
        cerr<<"Error de memoria.\n";
        return 1;
    }
    return 0;
}
