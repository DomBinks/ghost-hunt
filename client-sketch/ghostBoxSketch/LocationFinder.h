#pragma once
#include <stdio.h>

#include "WiFi.h"

class WifiScanner {
public:

  /**
                 * Reset iterator
                 */
                void reset() {
                    i = 0;
                }

                /**
                 * Test if we can iterate over the networks
                 * @return
                 */
                bool hasNext() {
                    return i < numNetworks;
                }

                /**
                 * Advance iterator
                 */
                void next() {
                    i += 1;
                }
                    String ssid() {
                    if (hasNext())
                        return ssidAt(i);

                    return "";
                }
                  int rssi() {
                    if (hasNext())
                        return rssiAt(i);

                    return 0;
                }

  /**
 * Identify networks by SSID
 */
  void identifyBySSID() {
    useMac = false;
  }

  /**
 * Identify networks by MAC address
 */
  void identifyByMAC() {
    useMac = true;
  }

  /**
 * Perform scan
 */
  void scan() {
    numNetworks = WiFi.scanNetworks();
  }


  /**
                 * Get SSID of given network
                 * @param i
                 * @return
                 */
  virtual String ssidAt(uint8_t i) {
    return WiFi.SSID(i);
  }


  /**
                 * Get Mac address of given network
                 * @param i
                 * @return
                 */
  virtual String macAt(uint8_t id) {
    //uint8_t* bssid = WiFi.BSSID(&id);
    uint8_t* bssid;
    //Serial.println("here!");
    WiFi.BSSID(id,bssid);
    //bssid = WiFi.BSSID(id,NULL);
    return this->hex(bssid[0]) + ":" + this->hex(bssid[1]) + ":" + this->hex(bssid[2]) + ":" + this->hex(bssid[3]) + ":" + this->hex(bssid[4]) + ":" + this->hex(bssid[5]) + ":" + this->hex(bssid[6]);
  }



  /**
                 * Get RSSI of given network
                 * @param i
                 * @return
                 */
  virtual int rssiAt(uint8_t i) {
    return WiFi.RSSI(i);
  }



  /**
                 * Get identifier of given network
                 * @param i
                 * @return
                 */
  virtual String idAt(uint8_t i) {
    return useMac ? macAt(i) : ssidAt(i);
  }

  /**
                 * Print scan results as JSON
                 * @tparam Stream
                 * @param stream
                 */
  template<typename Stream>
  void printAsJson(Stream& stream) {
    stream.print('{');

    for (uint8_t i = 0; i < numNetworks; i++) {
      stream.print('"');
      stream.print(idAt(i));
      stream.print('"');
      stream.print(':');
      stream.print(rssiAt(i));

      if (i < numNetworks - 1)
        stream.print(',');
    }

    stream.print('}');
    stream.print('\n');
  }

protected:
  int i = 0;
  uint8_t numNetworks;
  bool useMac = false;

  /**
                 * Convert byte to hex string
                 * @param byte
                 * @return
                 */
  String hex(uint8_t byte) {
    String alphabet = "0123456789ABCDEF";
    char hex[3] = {
      alphabet.charAt(byte >> 4),
      alphabet.charAt(byte & 0b1111),
      '\0'
    };
    return String(hex);
  }
};
class WiFiIndoorPositioning {
    public:

        /**
         * Get current room id
         */
        template<typename Scanner>
        int predictRoomId(Scanner& scanner) {
            float x[14] = {0};
            uint16_t votes[2] = { 0 };

            scanner.scan();
            convertToFeatures(scanner, x);

            if (x[1] <= -65.5) {  if (x[10] <= -74.0) {   votes[0] += 1;  } else {  if (x[5] <= -67.0) {  if (x[5] <= -75.0) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {  if (x[3] <= -73.5) {   votes[1] += 1;  } else {   votes[0] += 1;  }   }   }   } else {   votes[1] += 1;  } 
            if (x[11] <= -65.0) {  if (x[5] <= -64.5) {  if (x[9] <= -87.5) {   votes[0] += 1;  } else {  if (x[11] <= -71.5) {   votes[1] += 1;  } else {  if (x[3] <= -64.5) {  if (x[13] <= -40.5) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {   votes[1] += 1;  }   }   }   } else {   votes[0] += 1;  }   } else {   votes[1] += 1;  } 
            if (x[10] <= -33.0) {  if (x[2] <= -27.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {  if (x[11] <= -69.0) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } 
            if (x[2] <= -28.0) {  if (x[2] <= -66.5) {  if (x[13] <= -87.5) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {   votes[0] += 1;  }   } else {  if (x[8] <= -34.0) {   votes[1] += 1;  } else {  if (x[0] <= -39.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   } 
            if (x[2] <= -27.5) {   votes[0] += 1;  } else {  if (x[10] <= -75.0) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } 
            if (x[3] <= -64.5) {  if (x[3] <= -73.5) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {   votes[1] += 1;  } 
            if (x[2] <= -27.5) {   votes[0] += 1;  } else {   votes[1] += 1;  } 
            if (x[1] <= -65.5) {  if (x[10] <= -34.0) {  if (x[9] <= -38.0) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {  if (x[5] <= -72.5) {   votes[1] += 1;  } else {   votes[0] += 1;  }   }   } else {  if (x[3] <= -64.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } 
            if (x[1] <= -66.0) {  if (x[13] <= -84.0) {   votes[0] += 1;  } else {  if (x[13] <= -40.5) {   votes[1] += 1;  } else {  if (x[7] <= -35.0) {  if (x[9] <= -86.0) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {   votes[0] += 1;  }   }   }   } else {   votes[1] += 1;  } 
            if (x[11] <= -68.5) {  if (x[3] <= -73.5) {   votes[1] += 1;  } else {  if (x[1] <= -56.0) {  if (x[6] <= -36.5) {  if (x[1] <= -71.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {   votes[0] += 1;  }   } else {   votes[1] += 1;  }   }   } else {  if (x[10] <= -33.0) {   votes[1] += 1;  } else {  if (x[9] <= -82.0) {  if (x[4] <= -38.0) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {   votes[1] += 1;  }   }   } 
            

            // return argmax of votes
            uint8_t classIdx = 0;
            float maxVotes = votes[0];

            for (uint8_t i = 1; i < 2; i++) {
                if (votes[i] > maxVotes) {
                    classIdx = i;
                    maxVotes = votes[i];
                }
            }

            return (lastRoomId = classIdx);
        }

        /**
         * Get current room name
         */
        template<typename Scanner>
        String predictRoomName(Scanner& scanner) {
            uint8_t roomId = predictRoomId(scanner);

            switch (roomId) {
                
                case 0: return (lastRoomName = "roomA");
                
                case 1: return (lastRoomName = "roomB");
                
                default: return (lastRoomName = "???");
            }
        }

        /**
         * Test if current location is the given one by id
         */
        bool isIn(uint8_t roomId) {
            return roomId == lastRoomId;
        }

        /**
         * Test if current location is the given one by name
         */
        bool isIn(String roomName) {
            return roomName == lastRoomName;
        }


    protected:
        uint8_t lastRoomId = 255;
        String lastRoomName;

        template<typename Scanner>
        void convertToFeatures(Scanner& scanner, float *x) {
            while (scanner.hasNext()) {
                String ssid = scanner.ssid();
                float rssi = scanner.rssi();

                scanner.next();

                
                if (ssid == "internet") {
                    x[0] = rssi;
                    continue;
                }
                
                if (ssid == "eduroam") {
                    x[1] = rssi;
                    continue;
                }
                
                if (ssid == "SteamDuck") {
                    x[2] = rssi;
                    continue;
                }
                
                if (ssid == "UoN-guest") {
                    x[3] = rssi;
                    continue;
                }
                
                if (ssid == "IP in the shower") {
                    x[4] = rssi;
                    continue;
                }
                
                if (ssid == "M00N-VOORJE-MAN") {
                    x[5] = rssi;
                    continue;
                }
                
                if (ssid == "DIRECT-69-HP 420x DUPLEX") {
                    x[6] = rssi;
                    continue;
                }
                
                if (ssid == "Jj") {
                    x[7] = rssi;
                    continue;
                }
                
                if (ssid == "Ben's Galaxy Z Fold3 5G") {
                    x[8] = rssi;
                    continue;
                }
                
                if (ssid == "ppp") {
                    x[9] = rssi;
                    continue;
                }
                
                if (ssid == "Kieran's laptop") {
                    x[10] = rssi;
                    continue;
                }
                
                if (ssid == "UoN-secure") {
                    x[11] = rssi;
                    continue;
                }
                
                if (ssid == "AndroidAP_4580") {
                    x[12] = rssi;
                    continue;
                }
                
                if (ssid == "CSiTrobots") {
                    x[13] = rssi;
                    continue;
                }
                
            }
        }
};


WiFiIndoorPositioning positioning;
