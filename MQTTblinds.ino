// This #include statement was automatically added by the Particle IDE.
#include "MQTT.h"
// This #include statement was automatically added by the Particle IDE.
// Copyright (c) <year>, <copyright holder>
// All rights reserved.
void callback(char* topic, byte* payload, unsigned int length);
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the <organization> nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//     * Redistribution of this software in source or binary forms shall be free
//       of all charges or fees to the recipient of this software.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// a maximum of eight servo objects can be created 


byte server[] = { 10,0,0,42 };
MQTT client(server, 1883, callback);


Servo myservo;

int val;
int itsatrap = 0;


void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);
    String mytopic(topic);
    if (itsatrap == 0 && mytopic == "blind/bl/command" && message.equals("ON")){  
    myservo.attach(A4);
    delay(500);
    myservo.write(90); 
    client.publish("blind/bl/state", "ON");
    delay(1000);
    myservo.detach();
    }
    else if (mytopic == "blind/bl/command" && message.equalsIgnoreCase("OFF")){
    myservo.attach(A4);
    delay(500);
    myservo.write(0);  
    client.publish("blind/bl/state", "OFF");
    delay(1000);
    myservo.detach();
    }
    else if (mytopic == "blind/bl/level"){
    myservo.attach(A4);
    delay(500);
    val = message.toInt(); //converts command to integer to be used for positional arrangement
    val = map (val, 0, 99, 0, 180);
    myservo.write(val);
    client.publish("blind/bl/state", "ON");
    delay(3000);
    myservo.detach();
    itsatrap = 1;
    }
    else{
        itsatrap = 0;
    }
    
}



void setup() 
{
    RGB.control(true);
    RGB.color(100,0,50);
    Particle.variable("itsatrap", itsatrap);
    myservo.attach(A4);  
    client.connect("particlebl", "", "");
    client.publish("blind/bl/state", "OFF");
    client.subscribe("blind/bl/command");
    client.subscribe("blind/bl/level");
    
        
    
    

}

void loop(){
    client.loop();
    
}


