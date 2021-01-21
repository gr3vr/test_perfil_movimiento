//-------- Analitica de movimiento -------------------------------

// ---------- Variables Generales --------------------------------
int   count;            // Contador de muestras actuales.
int   period = 25;      // Periodo de tiempo entre c/ muestra (en milisegundos).
int   lastCheck;        // Cantidad de tiempo transcurrido entre c/ muestra
#define   samples 20    // Cant. de muestras que se registraran.
// ---------------------------------------------------------------

// ---------- Variables por c/ angulo ----------------------------
// ---------- ROLL -----------------------------------------------

float roll_past[samples];         // Ultimos N registros del Roll.
int   roll_analysis;              // Valorización de ultimos 20 registros para el Roll.
int   risky_roll_ang = 20;        // Angulo riesgoso para el Roll.
int   count_ang_roll_wrong = 15;  // Cant. de veces que Roll estuvo en un angulo incorrecta para detectarlo como riesgoso.
unsigned long   roll_wrong;       // Contador movimientos riesgosos para el Roll.

/* NOTA: ¿El tipo de variable unsigned long será suficiente para almacenar
         la cant. de movimiento riesgosos durante el día? 
         
         Rango de unsigned long: 0 a 4.294.967.295         */
// ---------------------------------------------------------------

int roll;

void setup() {
  Serial.begin(19200);

  /* NOTA: ¿Contador roll_wrong se reiniciará cuando el día finalice?
     roll_wrong = 0; */
}
void loop() {

  /* Aqui hacemos la lectura de ROLL, PITCH y YAW */
  
  roll = random(-90, 90);  //-> SOLO PARA DEMOSTRACION!!, Obtenemos un valor aleatorio entre -90 a 90, para simular la lectura del MPU
  
  if (millis() - lastCheck  >= period) {      // Si ha transcurrido la cant. de tiempo establecido para hacer otra muestra.
    roll_past[count] = roll;                  // Guardamos el valor del Roll actual en el array de registro.
    count++;                                  // Aumentamos el número de muestra.
    lastCheck = millis();                     // Y guardamos el tiempo actual que se realizo la muestra.
  }
  
  if (count == (samples - 1)) {                   // Si el Nro de muestras realizadas es igual a la cant. de muestras requeridas.
    count = 0;                                    // Reiniciamos la cantidad de muestras actuales
    roll_analysis = 0;                            // Reiniciamos el contador de valorización.
    for (int i = 0; i < (samples - 1); i++) {     // Recorremos el array de los registros
      if (abs(roll_past[i]) >= risky_roll_ang) {  // Si un registro pasó el angulo riesgoso...
        roll_analysis++;                          // ... Aumentamos el contador de valorización.
      }
    }
    if (roll_analysis >= count_ang_roll_wrong) {  // Si la cant. de veces que se estuvo un angulo incorrecto...
                                                  // ... Es mayor a la cant. establecida
      roll_wrong++;                               // Aumentamos la cant. de movimientos riesgosos.
      /* NOTA: ¿Guardamos la hora cuando se realizó un movimiento de riesgo? */
    }
    Serial.print("roll_analysis: ");    
    Serial.print(roll_analysis);
    Serial.print(" - ");                                            
    Serial.print("Cant. Movimientos riesgosos: ");
    Serial.println(roll_wrong);
  }
}
