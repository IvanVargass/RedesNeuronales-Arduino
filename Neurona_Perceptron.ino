/* Neurona Perceptron
 *  
 * NOMBRE: IVAN FERNANDO VARGAS OCHOA
 * C.C : 1006558319
 */ 

// Para entrenar una sola vez la red neuronal
int a = 1;

// Se declara el valor de las entradas
int x1[4] = {1,1,0,0};
int x2[4] = {1,0,1,0};

// Se declara el valor de la salida
int  Y[4] = {1,1,1,0};

// Se declaran los pesos
float w0 = random(1);
float w1 = random(1);
float w2 = random(1);

// Se declara el valor termino independiente
int b0 = 1;

void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(4, INPUT);

  pinMode(5, OUTPUT);
}

void loop() {

  if(a == 1){

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

  // Valor de los pesos
  Serial.println("El valor de los pesos es: ");
  Serial.println(w0);
  Serial.println(w1);
  Serial.println(w2);

  // Se comprueba la salida del perceptron
  int salida[4] = {1,1,1,1};

  Serial.println("El valor de salida del perceptron es: ");

  for(int i=0; i<=3; i++){
    float C = (w1*x1[i] + w2*x2[i] + w0*b0);

    if(C>=b0){
      C = 1;
    } else {
      C = 0;
    }
    salida[i] = C;
    Serial.println(salida[i]);
  }
    a = 2;
  }

  // Aqui comienza la comprobacion en tiempo real de la neurona perceptron
  int x1 = digitalRead(3);
  int x2 = digitalRead(4);  
  
  float salida;
  
  Serial.println("El valor de salida del perceptron es: ");

    float C = (w1*x1 + w2*x2 + w0*b0);

    if(C>=b0){
      C = 1;
    } else {
      C = 0;
    }
    
    salida = C;
    Serial.println(salida);
    digitalWrite(5, salida);
    delay(1000);
}
