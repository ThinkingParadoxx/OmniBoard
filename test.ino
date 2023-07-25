#include <Stepper.h>

int stepPin1 = 2;
int dirPin1 = 5;
int stepPin2 = 3;
int dirPin2 = 6;
int enable = 8;
int magnetPin = 52;

const int boardRows = 17;
const int boardColumns = 19;
int blockSteps = 200;

char chess[boardRows][boardColumns];

String srcBlock = "a2", destBlock = "g1";
int count = 1;

struct coords
{
    int row;
    int col;
} pointer;

// Motor configuration
const int stepsPerRevolution = 200; // Number of steps per revolution for the stepper motor
Stepper motor1(stepsPerRevolution, stepPin1, dirPin1);
Stepper motor2(stepsPerRevolution, stepPin2, dirPin2);

void setup()
{
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

coords convertToCoords(String s)
{
    char c1 = s[0], c2 = s[1];
    coords obj;
    obj.row = 2 * (c2 - '0') - 1;
    obj.col = 2 * (c1 - 'a' + 1);
    return obj;
}

vector<pair<int, int>> dfs(int sr, int sc, int dr, int dc, vector<vector<bool>> &vis)
{
    if (sr == dr && sc == dc)
    {
        vector<pair<int, int>> v;
        v.push_back({dr, dc});
        return v;
    }
    if (sr >= boardRows || sr < 0 || sc >= boardColumns || sc < 0 || vis[sr][sc])
    {
        vector<pair<int, int>> out;
        return out;
    }
    int delr[] = {0, 0, -1, 1, -1, -1, 1, 1};
    int delc[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    vis[sr][sc] = true;
    vector<pair<int, int>> out;
    int mini = INT_MAX;
    for (int i = 0; i < 8; i++)
    {
        int nr = sr + delr[i];
        int nc = sc + delc[i];
        vector<pair<int, int>> ans = dfs(nr, nc, dr, dc, vis);
        if (ans.size() > 0 && ans.size() < mini)
        {
            out = ans;
            mini = ans.size();
        }
    }
    if (out.size() == 0)
    {
        vector<pair<int, int>> temp;
        return temp;
    }
    vis[sr][sc] = false;
    out.push_back({sr, sc});
    return out;
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
    coords resetCoords;
    resetCoords.row = 1;
    resetCoords.col = 0;
    moveChessPiece(pointer, resetCoords);
    pointer.row = resetCoords.row;
    pointer.col = resetCoords.col;
}

void movePointer(coords dest)
{
    moveChessPiece(pointer, dest);
    pointer.row = dest.row;
    pointer.col = dest.col;
}

void moveChessPiece(coords src, coords dest)
{
    int sr = src.row, sc = src.col;
    int dr = dest.row, dc = dest.col;
    if (dr > sr)
    {
        if (dc > sc)
        {
            moveRight(1 * blockSteps);
            moveFront((dr - sr - 1) * blockSteps);
            moveRight((dc - sc - 1) * blockSteps);
            moveFront(1 * blockSteps);
        }
        else if (dc < sc)
        {
            moveLeft(1 * blockSteps);
            moveFront((dr - sr - 1) * blockSteps);
            moveLeft((sc - dc - 1) * blockSteps);
            moveFront(1 * blockSteps);
        }
        else
        {
            moveRight(1 * blockSteps);
            moveFront((dr - sr) * blockSteps);
            moveLeft(1 * blockSteps);
        }
    }
    else if (dr < sr)
    {
        if (dc > sc)
        {
            moveRight(1 * blockSteps);
            moveBack((sr - dr - 1) * blockSteps);
            moveRight((dc - sc - 1) * blockSteps);
            moveBack(1 * blockSteps);
        }
        else if (dc < sc)
        {
            moveLeft(1 * blockSteps);
            moveBack((sr - dr - 1) * blockSteps);
            moveLeft((sc - dc - 1) * blockSteps);
            moveBack(1 * blockSteps);
        }
        else
        {
            moveRight(1 * blockSteps);
            moveBack((sr - dr) * blockSteps);
            moveLeft(1 * blockSteps);
        }
    }
    else
    {
        if (dc > sc)
        {
            moveFront(1 * blockSteps);
            moveRight((dc - sc) * blockSteps);
            moveBack(1 * blockSteps);
        }
        else
        {
            moveFront(1 * blockSteps);
            moveLeft((sc - dc) * blockSteps);
            moveBack(1 * blockSteps);
        }
    }

    pointer.row = dr;
    pointer.col = dc;
}

void loop()
{
    while (count > 0)
    {
        coords src = convertToCoords(srcBlock);
        coords dest = convertToCoords(destBlock);

        vector<vector<bool>> visited(boardRows, vector<bool>(boardColumns, false));
        vector<pair<int, int>> path = dfs(src.row, src.col, dest.row, dest.col, visited);

        if (path.size() > 0)
        {
            for (int i = 1; i < path.size(); i++)
            {
                coords current = {path[i - 1].first, path[i - 1].second};
                coords next = {path[i].first, path[i].second};
                movePointer(current);
                moveChessPiece(current, next);
            }
            resetPointer();
        }

        count--;
    }
}
