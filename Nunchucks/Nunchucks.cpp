/*
    Nunchucks.h - Library for reading multiple nunchucks.
    Created by Daniel Esteban, February 15, 2013.
    Released into the public domain.

    This will be improved soon.. it has a bazillion copy pastes. ;P
*/

#include "Nunchucks.h"

Nunchucks::Nunchucks(nunchuckAnalogEvent onJoyChange, nunchuckAnalogEvent onAccelChange, nunchuckButtonEvent onDown, nunchuckButtonEvent onUp) {
    _onJoyChange = onJoyChange;
    _onAccelChange = onAccelChange;
    _onDown = onDown;
    _onUp = onUp;
    _nunchucks = NULL;
    //_lastRead = 0;
    Wire.begin();
}

/*void Nunchucks::activate(byte pin) { //Switches data line with a transistor.
    if(_active) digitalWrite(_active, LOW);
    digitalWrite(pin, HIGH);
    _active = pin;
    //delay(1);
}*/

void Nunchucks::setup(/*byte pin, byte eepromByte */) {
    nunchuck * n = (nunchuck *) malloc(sizeof(nunchuck));
    //n->pin = pin;
    n->cnt = n->reading = n->jXRead = n->jXSum = n->JoyXZero = n->jYRead = n->jYSum = n->JoyYZero = n->xRead = n->xSum = /*n->yRead = n->ySum = n->zRead = n->zSum =*/ 0;
    for(byte x=0; x<nunchucksReadings; x++) {
        n->jXReadings[x] = n->jYReadings[x] = n->xReadings[x] = /*n->yReadings[x] = n->zReadings[x] =*/ 0;
    }
    byte eepromByte = 0;
    n->xZero = (int) EEPROM.read(eepromByte) + ((int) EEPROM.read(eepromByte + 1) << 8);
    n->xZero == 65535 && (n->xZero = 0);
    //n->yZero = (int) EEPROM.read(eepromByte + 2) + ((int) EEPROM.read(eepromByte + 3) << 8);
    //n->yZero == 65535 && (n->xZero = 0);
    //n->zZero = (int) EEPROM.read(eepromByte + 4) + ((int) EEPROM.read(eepromByte + 5) << 8);
    //n->zZero == 65535 && (n->xZero = 0);
    //n->next = _nunchucks;
    _nunchucks = n;
    //pinMode(pin, OUTPUT);
    //activate(pin);
    Wire.beginTransmission(0x52);
    Wire.write(0xF0);
    Wire.write(0x55);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission(0x52);
    Wire.write(0xFB);
    Wire.write((uint8_t) 0x00);
    Wire.endTransmission();
    delay(100);
    for(byte x=0; x<nunchucksReadings * 2; x++) {
        read(true);
        delay(1);
    }
    n->JoyXZero = n->jXRead;
    n->JoyYZero = n->jYRead;
}

void Nunchucks::read(bool dontTriggerEvents) {
    //unsigned long t = millis();
    //if(t < _lastRead + 1) return;
    //_lastRead = t;
    nunchuck * n = _nunchucks;
    //while(n) {
        //activate(n->pin);

        Wire.requestFrom(0x52, 6); // request data from nunchuck
        while(Wire.available() && n->cnt < 6) {
            n->status[n->cnt] = Wire.read();
            n->cnt++;
        }

        if(n->cnt > 5) {
            n->cnt = 0;

            //Averaging of analog inputs

            int read;

            n->jXSum -= n->jXReadings[n->reading];
            n->jXReadings[n->reading] = n->status[0];
            n->jXSum += n->jXReadings[n->reading];
            read = round((float) n->jXSum / (float) nunchucksReadings);
            if(abs(n->jXRead - read) > 1) {
                read >= n->JoyXZero - 1 && read <= n->JoyXZero + 1 && (read = n->JoyXZero);
                n->jXRead = read;
                if(!dontTriggerEvents && _onJoyChange != NULL) _onJoyChange(/*n->pin,*/ 0, read - n->JoyXZero);
            }

            n->jYSum -= n->jYReadings[n->reading];
            n->jYReadings[n->reading] = n->status[1];
            n->jYSum += n->jYReadings[n->reading];
            read = round((float) n->jYSum / (float) nunchucksReadings);
            if(abs(n->jYRead - read) > 1) {
                read >= n->JoyYZero - 1 && read <= n->JoyYZero + 1 && (read = n->JoyYZero);
                n->jYRead = read;
                if(!dontTriggerEvents && _onJoyChange != NULL) _onJoyChange(/*n->pin,*/ 1, n->JoyYZero - read);
            }

            n->xSum -= n->xReadings[n->reading];
            n->xReadings[n->reading] = ((int) n->status[2] << 2) + ((n->status[5] & B00001100) >> 2);
            n->xSum += n->xReadings[n->reading];
            read = round((float) n->xSum / (float) nunchucksReadings);
            if(abs(n->xRead - read) > 1) {
                read >= n->xZero - 10 && read <= n->xZero + 10 && (read = n->xZero);
                n->xRead = read;
                if(_onAccelChange != NULL) _onAccelChange(/*n->pin, */0, read - n->xZero);
            }

            /*n->ySum -= n->yReadings[n->reading];
            n->yReadings[n->reading] = ((int) n->status[3] << 2) + ((n->status[5] & B00110000) >> 4);
            n->ySum += n->yReadings[n->reading];
            read = round((float) n->ySum / (float) nunchucksReadings);
            if(abs(n->yRead - read) > 1) {
                read >= n->yZero - 1 && read <= n->yZero + 1 && (read = n->yZero);
                n->yRead = read;
                if(_onAccelChange != NULL) _onAccelChange(n->pin, 1, n->yZero - read);
            }*/

            /*n->zSum -= n->zReadings[n->reading];
            n->zReadings[n->reading] = ((int) n->status[4] << 2) + ((n->status[5] & B11000000) >> 6);
            n->zSum += n->zReadings[n->reading];
            read = round((float) n->zSum / (float) nunchucksReadings);
            if(abs(n->zRead - read) > 1) {
                read >= n->zZero - 1 && read <= n->zZero + 1 && (read = n->zZero);
                n->zRead = read;
                if(_onAccelChange != NULL) _onAccelChange(n->pin, 2, n->zZero - read);
            }*/
            
            n->reading++;
            n->reading >= nunchucksReadings && (n->reading = 0);


            //Buttons with debounce

            bool bRead;
            
            bRead = !(n->status[5] & B00000001);
            //n->bZRead != bRead && (n->bZDebounce = t);
            n->bZRead = bRead;
            if(n->bZStatus != bRead /*&& (t - n->bZDebounce) > 25*/) {
                n->bZStatus = bRead;
                if(bRead == 1) {
                    if(!dontTriggerEvents && _onDown != NULL) _onDown(/*n->pin,*/ 0);
                } else if(!dontTriggerEvents && _onUp != NULL) _onUp(/*n->pin,*/ 0);
            }

            bRead = !((n->status[5] & B00000010) >> 1);
            //n->bCRead != bRead && (n->bZDebounce = t);
            n->bCRead = bRead;
            if(n->bCStatus != bRead /*&& (t - n->bCDebounce) > 25*/) {
                n->bCStatus = bRead;
                if(bRead == 1) {
                    if(!dontTriggerEvents && _onDown != NULL) _onDown(/*n->pin,*/ 1);
                } else if(!dontTriggerEvents && _onUp != NULL) _onUp(/*n->pin,*/ 1);
            }

            Wire.beginTransmission(0x52);
            Wire.write((uint8_t) 0x00);
            Wire.endTransmission();
        }
        //n = n->next;
    //}
}

nunchuck * Nunchucks::get(/*byte pin*/) {
    return _nunchucks;
    /*nunchuck * n = _nunchucks;
    while(n) {
        if(n->pin == pin) return n;
        n = n->next;
    }*/
}
