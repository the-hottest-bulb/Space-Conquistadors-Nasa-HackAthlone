// made during HackAthlone; 03/10/2025 - 05/10/2025
// using an Arduino Mega; C++
//
// creating a module-based space habitat
// a combination of digital and electronical inputs to scan co=ordinates of a matrix
// voltage division to read specific resistors values and assign a module to it
//

se;
  }
  for (int r = 0; r < ROW; r++){
    for (int c = 0; c < COL; c++){
      visited[r][c] = f// define LEDs and RGB LED
#define RED 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5
#define PURPLE 6

#define R 8
#define G 9
#define B 10

#define THRESHOLD 80

// set the # of rows and column
const int ROW = 8, COL = 8;

// set an array for the pins
const int analogPin[ROW] = {A0, A1, A2, A3, A4, A5, A6, A7};
const int digitalPin[COL] = {14, 15, 16, 17, 18, 19, 20, 21};

// set the grid as empty (no modules)
int grid[ROW][COL] = {{0}};

// create visted array to detect multiple islands
bool visited[ROW][COL];

// orthogonal checks for depth-first-search
int dx[4] = {0, 0, -1, 1}; // left, right
int dy[4] = {-1, 1, 0, 0}; // up, down

// tracks which errors are present
bool error_code[7];

void dfs(int r, int c){
  visited[r][c] = true;
  
  for (int i = 0; i < 4; i++){
    int nr = r + dy[i];
    int nc = c + dx[i];
    
    if (nr < 0 || nr >= ROW || nc < 0 || nc >= COL){  }
    else if (!visited[nr][nc] && grid[nr][nc] > THRESHOLD){ dfs(nr, nc);}
  }
}

void checkErrors(){
  for (int i = 0; i < 7; i++) {
  	error_code[i] = falalse; // reset visited
    }
  }
  
  int startRow = -1, startCol = -1;
  
  for (int r = 0; r < ROW; r++){
    for (int c = 0; c < COL; c++){
      if (grid[r][c] > THRESHOLD){
        startRow = r; startCol = c;
        break;
      }
    }
    if (startRow != -1) break;
  }
  
  if (startRow == -1){ // no modules on grid
    error_code[0] = true;
    return;
  }
  
  if (startRow != -1) dfs(startRow, startCol);
  
  for (int r = 0; r < ROW; r++){
    for (int c = 0; c < COL; c++){
      if (grid[r][c] > THRESHOLD && !visited[r][c]){
        error_code[1] = true; // disconnected module
  	  }
	  }
	}
  
  // error_codes[2-6] would output true when there is not enough of a certain module
  // not implemented due to time constraints
}

String findModule(int av){
  if (av <= THRESHOLD) return"       0       ";
  else if (av < 400) return  "    storage    ";
  else if (av < 600) return  " communications";
  else if (av < 820) return  "  life support ";
  else if (av < 950) return  "     waste     ";
  else if (av < 1024) return " living amenity";
  return "unknown";
}
  
void displayResult(){
  if (error_code[6]){digitalWrite(YELLOW, HIGH); Serial.println("Change # of living amenities");} else {digitalWrite(YELLOW, LOW);}
  if (error_code[5]){digitalWrite(GREEN, HIGH); Serial.println("Change # of waste");} else {digitalWrite(GREEN, LOW);}
  if (error_code[4]){digitalWrite(RED, HIGH); Serial.println("Change # of life support");} else {digitalWrite(RED, LOW);}
  if (error_code[3]){digitalWrite(BLUE, HIGH); Serial.println("Change # of communications");} else {digitalWrite(BLUE, LOW);}
  if (error_code[2]){digitalWrite(PURPLE, HIGH); Serial.println("Change # of storage");} else {digitalWrite(PURPLE, LOW);}
  if (error_code[1]) Serial.println("Disconnected module found");
  if (error_code[0]) Serial.println("No modules detected");

  if (error_code[2] || error_code[3] || error_code[4] || error_code[5] || error_code[6]){
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
  } else if (error_code[1] || error_code[0]){
  	digitalWrite(R, HIGH);
    digitalWrite(G, HIGH); 
  } else {
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH); 
  }
}

void setup(){ // runs once
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(PURPLE, OUTPUT);
  
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  digitalWrite(G, LOW);
  
  // set digital pins as INPUT for high-impedance
  for (int i = 0; i < ROW; i++){
    pinMode(digitalPin[i], INPUT);
  }
}
  
  // analog pins set to INPUT by default

void loop(){ 
  for(int col = 0; col < COL; col++){
    pinMode(digitalPin[col], OUTPUT);
    digitalWrite(digitalPin[col], HIGH); // activate only one column
    
    for (int row = 0; row < ROW; row++){
      grid[row][col] = analogRead(analogPin[row]); // if there is a resistor connecting the two pins an analog value is given depending on the resistor via voltage division
    }
    
    digitalWrite(digitalPin[col], LOW);
    pinMode(digitalPin[col], INPUT); // deactivate column
  }
  
  // print 2D matrix
  for (int i = 0; i < ROW; i++){
    Serial.print("(");
    for (int j = 0; j < COL; j++){
      Serial.print(findModule(grid[i][j]));
      if (j < COL - 1) Serial.print(" ");
    }
    Serial.println(")");
  }
  Serial.println("-----------------------------");// break line
  
  checkErrors();
  
  displayResult();
  
  
  delay(1000);
}
