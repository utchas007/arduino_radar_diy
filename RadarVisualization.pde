
import processing.serial.*;

// Serial communication
Serial myPort; 

// Variables for radar
int angle = 0;
int distance = 0;

// Setup the window size
void setup() {
  size(600, 600);
  // Change "COM3" to the port your Arduino is connected to
  // For Mac/Linux, it might be something like "/dev/tty.usbmodemXXXX"
  myPort = new Serial(this, "COM3", 9600); 
  myPort.bufferUntil('
');
  background(0);
}

void draw() {
  // Drawing is handled in the serialEvent function
}

// Receive data from Arduino
void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    String[] values = split(data, ' ');
    if (values.length == 2) {
      angle = int(values[0]);
      distance = int(values[1]);

      // Convert polar coordinates to Cartesian for display
      float x = width / 2 + distance * cos(radians(angle)) * 2;
      float y = height / 2 - distance * sin(radians(angle)) * 2;

      // Draw radar sweep
      stroke(0, 255, 0);
      strokeWeight(2);
      line(width / 2, height / 2, x, y);

      // Draw detected point
      noStroke();
      fill(255, 0, 0);
      ellipse(x, y, 5, 5);

      // Fade effect
      fill(0, 10);
      rect(0, 0, width, height);
    }
  }
}
