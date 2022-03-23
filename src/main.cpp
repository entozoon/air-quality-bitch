#include <Arduino.h>
#include <pms.h>
Pmsx003 pms(D3, D4); // Receiving D3
void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
  };
  Serial.println("Pmsx003");
  pms.begin();
  pms.waitForData(Pmsx003::wakeupTime);
  pms.write(Pmsx003::cmdModeActive);
}
auto lastRead = millis();
void loop(void) {
  const auto n = Pmsx003::Reserved;
  Pmsx003::pmsData data[n];
  Pmsx003::PmsStatus status = pms.read(data, n);
  switch (status) {
  case Pmsx003::OK: {
    Serial.println("_________________");
    auto newRead = millis();
    Serial.print("Wait time ");
    Serial.println(newRead - lastRead);
    lastRead = newRead;
    // For loop starts from 3
    // Skip the first three data (PM1dot0CF1, PM2dot5CF1, PM10CF1)
    for (size_t i = Pmsx003::PM1dot0; i < n; ++i) {
      Serial.print(data[i]);
      Serial.print("\t");
      Serial.print(Pmsx003::dataNames[i]);
      Serial.print(" [");
      Serial.print(Pmsx003::metrics[i]);
      Serial.print("]");
      Serial.println();
    }
    break;
  }
  case Pmsx003::noData:
    break;
  default:
    Serial.println("_________________");
    Serial.println(Pmsx003::errorMsg[status]);
  };
}
// _________________
// Wait time 846
// 19      PM1.0 [mcg/m3]
// 30      PM2.5 [mcg/m3]
// 30      PM10. [mcg/m3]
// 3399    Particles < 0.3 micron [/0.1L]
// 947     Particles < 0.5 micron [/0.1L]
// 208     Particles < 1.0 micron [/0.1L]
// 6       Particles < 2.5 micron [/0.1L]
// 0       Particles < 5.0 micron [/0.1L]
// 0       Particles < 10. micron [/0.1L]
// _________________
// Wait time 917
// 19      PM1.0 [mcg/m3]
// 28      PM2.5 [mcg/m3]
// 28      PM10. [mcg/m3]
// 3432    Particles < 0.3 micron [/0.1L]
// 935     Particles < 0.5 micron [/0.1L]
// 186     Particles < 1.0 micron [/0.1L]
// 2       Particles < 2.5 micron [/0.1L]
// 1       Particles < 5.0 micron [/0.1L]
// 0       Particles < 10. micron [/0.1L]
// _________________
// Wait time 846
// 19      PM1.0 [mcg/m3]
// 28      PM2.5 [mcg/m3]
// 28      PM10. [mcg/m3]
// 3432    Particles < 0.3 micron [/0.1L]
// 935     Particles < 0.5 micron [/0.1L]
// 186     Particles < 1.0 micron [/0.1L]
// 2       Particles < 2.5 micron [/0.1L]
// 1       Particles < 5.0 micron [/0.1L]
// 0       Particles < 10. micron [/0.1L]
// _________________
// Wait time 846
// 21      PM1.0 [mcg/m3]
// 30      PM2.5 [mcg/m3]
// 31      PM10. [mcg/m3]
// 3528    Particles < 0.3 micron [/0.1L]
// 998     Particles < 0.5 micron [/0.1L]
// 200     Particles < 1.0 micron [/0.1L]
// 4       Particles < 2.5 micron [/0.1L]
// 0       Particles < 5.0 micron [/0.1L]
// 0       Particles < 10. micron [/0.1L]