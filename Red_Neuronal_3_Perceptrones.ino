/* Red Neuronal con 3 Perceptrones
 *  
 * NOMBRE: IVAN FERNANDO VARGAS OCHOA
 * C.C : 1006558319
 */ 

// Para entrenar una sola vez la red neuronal
int a = 1;

// Se declara el valor de las entradas
int P1[4] = {0,0,1,1};
int P2[4] = {0,1,0,1};
int AA[4] = {0,1,0,0};
int AB[4] = {0,0,1,0};

// Se declara el valor de la salida
int  Y[4] = {0,1,1,0};

// Se declaran los pesos
float W[9] = {1,1,1,1,1,1,1,1,1};

// Se declara el valor termino independiente
int b = 1;

float pesos[3], pesos1[3], pesos2[3], pesos3[3];

void setup() {

  // Se le dan valores aleatorios a los pesos
  for(int i=1; i<=8; i++){
    W[i] = random(1);
  }

  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(4, INPUT);

  pinMode(5, OUTPUT);
}

void loop() {

  // Se entrena la red neuronal con 3 perceptrones
  if(a == 1){
    
    // Se encuentra los pesos de la primera neurona
    perceptron(W[0], W[1], W[2], P1, P2, AA, b);
    asignarpesos(pesos1, pesos);

    // Se encuentran los pesos de la segunda neurona
    perceptron(W[3], W[4], W[5], P1, P2, AB, b);
    asignarpesos(pesos2, pesos);

    // Se encuentran los pesos de la tercera neurona
    perceptron(W[6], W[7], W[8], AA, AB, Y, b);
    asignarpesos(pesos3, pesos);
    
    // Para comprobar la salida de la red neuronal
    float s1[4], s2[4], salida[4];

    Serial.println("La salida de la red neuronal es: ");

    for(int i = 0; i<=3; i++){
      float y1 = ( P1[i]*pesos1[1] + P2[i]*pesos1[2] + pesos1[0]*b);
      float y2 = ( P1[i]*pesos2[1] + P2[i]*pesos2[2] + pesos2[0]*b);

      if(y1>=b){
        y1 = 1;
      } else {
        y1 = 0;
      }

      if(y2>=b){
        y2 = 1;
      } else {
        y2 = 0;
      }

      s1[i] = y1;
      s2[i] = y2;

      float y = (s1[i]*pesos3[1] + s2[i]*pesos3[2] + pesos3[0]*b);

      if(y>=b){
        y = 1;
      } else {
        y = 0;
      }
      salida[i] = y;
      Serial.println(salida[i]);
    }
    
    a = 2;
  }
  

  // Aqui comienza la comprobacion en tiempo real de la red neuronal
  int P1 = digitalRead(3);
  int P2 = digitalRead(4);
  
    float s1, s2, salida;

    Serial.println("La salida de la red neuronal es: ");

      float y1 = ( P1*pesos1[1] + P2*pesos1[2] + pesos1[0]*b);
      float y2 = ( P1*pesos2[1] + P2*pesos2[2] + pesos2[0]*b);

      if(y1>=b){
        y1 = 1;
      } else {
        y1 = 0;
      }

      if(y2>=b){
        y2 = 1;
      } else {
        y2 = 0;
      }

      s1 = y1;
      s2 = y2;

      float y = (s1*pesos3[1] + s2*pesos3[2] + pesos3[0]*b);

      if(y>=b){
        y = 1;
      } else {
        y = 0;
      }
      salida = y;
      Serial.println(salida);
      digitalWrite(5,salida);

      delay(1000);
}

// Funcion Perceptron
void perceptron(int w0,int w1,int w2,int x1[4],int x2[4],int Y[4], int b0){
  
  // Valor de los errores
  float error[4] = {1,1,1,1};
  float errorglobal = error[0] + error[1] + error[2] + error[3];

  int i = 0;

  while(errorglobal!=0){
   float y =( w1*x1[i] + w2*x2[i] + w0*b0);

    if(y>=b0){
      y=1;
    } else{
      y=0;
    }

    error[i] = Y[i] - y;

    if(error[i] != 0){
        w1 = w1 + (error[i] * x1[i]);
        w2 = w2 + (error[i] * x2[i]);
        w0 = w0 + (error[i] * b0);
    }

    error[i] = abs(error[i]);

    if(i==3){
      i = 0;
    } else {
      i = i + 1;
    }

    errorglobal = error[0] + error[1] + error[2] + error[3];
  }

  pesos[0] = w0;
  pesos[1] = w1;
  pesos[2] = w2;
  
}

// Funcion asignar pesos
void asignarpesos(float pesos_n[3], float pesos[3]){
  for(int i=0; i<=2; i++){
      pesos_n[i] = pesos[i];
    }
}
