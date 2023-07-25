int stepPin1 = 2;
int dirPin1 = 5;
int stepPin2 = 3;
int dirPin2 = 6;
int enable = 8;
int magnetPin = 52;

const int boardRows = 17;
const int boardColumns = 19;
int blockSteps = 186;

char chess[boardRows][boardColumns];

// String srcBlock = "a6", destBlock = "g6";
int count = 1;

struct coords
{
    int row;
    int col;
} pointer;

void setup()
{
    pinMode(stepPin1, OUTPUT);
    pinMode(dirPin1, OUTPUT);
    pinMode(stepPin2, OUTPUT);
    pinMode(dirPin2, OUTPUT);
    pinMode(enable, OUTPUT);
    digitalWrite(enable, LOW);
    pinMode(magnetPin, OUTPUT);
    Serial.begin(9600);
    pointer.row = 1;
    pointer.col = 0;
}

void rotate(int motor, int steps, int dxn)
{
    int dirPin, stepPin;
    if (motor == 1)
    {
        dirPin = dirPin1;
        stepPin = stepPin1;
    }
    if (motor == 2)
    {
        dirPin = dirPin2;
        stepPin = stepPin2;
    }
    if (dxn == 1)
    {
        digitalWrite(dirPin, HIGH);
    }
    if (dxn == 2)
    {
        digitalWrite(dirPin, LOW);
    }
    for (int x = 0; x < steps; x++)
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
    }
    delay(1000);
}

void rotateBothMotors(int steps, int dir1, int dir2)
{
    if (dir1 == 1)
    {
        digitalWrite(dirPin1, HIGH);
    }
    else
    {
        digitalWrite(dirPin1, LOW);
    }
    if (dir2 == 1)
    {
        digitalWrite(dirPin2, HIGH);
    }
    else
    {
        digitalWrite(dirPin2, LOW);
    }
    for (int i = 0; i < steps; i++)
    {
        digitalWrite(stepPin1, HIGH);
        digitalWrite(stepPin2, HIGH);
        delayMicroseconds(10);
        digitalWrite(stepPin1, LOW);
        digitalWrite(stepPin2, LOW);
        delayMicroseconds(2000);
    }
    delay(1000);
}

void callibrateFrontLeft()
{
    rotate(2, 50, 2);
}

void callibrateFrontRight()
{
    rotate(2, 187, 1);
}
void callibrateBackLeft()
{
    rotate(2, 187, 2);
}

void callibrateBackRight()
{
    rotate(1, 187, 2);
}

void moveFront(int steps)
{
    rotateBothMotors(steps, 1, 1);
}

void moveBack(int steps)
{
    rotateBothMotors(steps, 2, 2);
}

void moveLeft(int steps)
{
    rotateBothMotors(steps, 1, 2);
}

void moveRight(int steps)
{
    rotateBothMotors(steps, 2, 1);
}

void resetPointer()
{
    coords resetCoods;
    resetCoods.row = 1;
    resetCoods.col = 0;
    pointer.row = resetCoods.row;
    pointer.col = resetCoods.col;
}

void loop()
{
    // while (count > 1)
    // {

        // resetPointer();
        // moveLeft(186);
        // moveBack(186);
        // moveRight(186);
        // moveFront(186);
        // callibrateFrontRight();
        callibrateBackLeft();
        // callibrateBackRight();
    //     count--;
    // }
}