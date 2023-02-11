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
            float x[10] = {0};
            uint16_t votes[2] = { 0 };

            scanner.scan();
            convertToFeatures(scanner, x);

            if (x[4] <= -33.0) {  if (x[6] <= -82.5) {   votes[0] += 1;  } else {  if (x[5] <= -29.5) {   votes[1] += 1;  } else {  if (x[2] <= -63.0) {   votes[1] += 1;  } else {   votes[0] += 1;  }   }   }   } else {  if (x[8] <= -63.5) {  if (x[7] <= -78.0) {   votes[1] += 1;  } else {  if (x[5] <= -77.5) {   votes[0] += 1;  } else {  if (x[6] <= -32.0) {   votes[1] += 1;  } else {  if (x[7] <= -68.0) {   votes[0] += 1;  } else {  if (x[7] <= -64.5) {   votes[1] += 1;  } else {  if (x[7] <= -61.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   }   }   }   }   } else {   votes[0] += 1;  }   } 
            if (x[8] <= -76.5) {  if (x[5] <= -73.5) {  if (x[0] <= -39.5) {   votes[0] += 1;  } else {  if (x[7] <= -76.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   } else {   votes[1] += 1;  }   } else {  if (x[4] <= -34.5) {  if (x[8] <= -67.0) {  if (x[8] <= -71.0) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {  if (x[7] <= -62.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   } else {  if (x[0] <= -28.0) {   votes[0] += 1;  } else {  if (x[3] <= -39.0) {   votes[0] += 1;  } else {  if (x[7] <= -63.0) {  if (x[8] <= -66.0) {  if (x[7] <= -74.0) {   votes[0] += 1;  } else {  if (x[2] <= -71.5) {   votes[1] += 1;  } else {  if (x[2] <= -67.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   }   } else {   votes[0] += 1;  }   } else {   votes[1] += 1;  }   }   }   }   } 
            if (x[4] <= -33.0) {  if (x[4] <= -83.5) {  if (x[6] <= -37.5) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {   votes[1] += 1;  }   } else {  if (x[0] <= -32.5) {   votes[0] += 1;  } else {  if (x[2] <= -76.0) {   votes[0] += 1;  } else {  if (x[7] <= -68.5) {   votes[1] += 1;  } else {  if (x[8] <= -55.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   }   }   } 
            if (x[6] <= -32.0) {  if (x[4] <= -85.5) {  if (x[7] <= -65.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {   votes[1] += 1;  }   } else {  if (x[2] <= -68.0) {  if (x[3] <= -37.5) {   votes[0] += 1;  } else {  if (x[5] <= -77.5) {   votes[0] += 1;  } else {  if (x[9] <= -87.0) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   }   } else {  if (x[8] <= -51.0) {  if (x[7] <= -67.5) {  if (x[2] <= -65.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {   votes[0] += 1;  }   } else {  if (x[2] <= -45.0) {   votes[1] += 1;  } else {   votes[0] += 1;  }   }   }   } 
            if (x[5] <= -73.5) {  if (x[4] <= -36.5) {  if (x[0] <= -35.0) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {  if (x[7] <= -71.0) {  if (x[5] <= -77.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {   votes[0] += 1;  }   }   } else {  if (x[5] <= -29.5) {  if (x[3] <= -37.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {  if (x[4] <= -37.5) {  if (x[2] <= -63.0) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {   votes[0] += 1;  }   }   } 
            if (x[8] <= -77.5) {   votes[1] += 1;  } else {  if (x[1] <= -77.5) {   votes[1] += 1;  } else {  if (x[5] <= -32.5) {  if (x[7] <= -72.5) {   votes[0] += 1;  } else {  if (x[4] <= -41.5) {   votes[1] += 1;  } else {  if (x[5] <= -75.5) {   votes[0] += 1;  } else {  if (x[7] <= -64.5) {   votes[1] += 1;  } else {   votes[0] += 1;  }   }   }   }   } else {  if (x[4] <= -42.0) {  if (x[8] <= -67.0) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {   votes[0] += 1;  }   }   }   } 
            if (x[0] <= -28.0) {   votes[0] += 1;  } else {  if (x[4] <= -33.0) {  if (x[1] <= -69.5) {   votes[1] += 1;  } else {  if (x[6] <= -36.0) {   votes[1] += 1;  } else {   votes[0] += 1;  }   }   } else {  if (x[5] <= -72.0) {   votes[0] += 1;  } else {  if (x[2] <= -74.5) {   votes[1] += 1;  } else {  if (x[7] <= -55.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   }   }   } 
            if (x[0] <= -33.5) {   votes[0] += 1;  } else {  if (x[2] <= -71.5) {   votes[1] += 1;  } else {  if (x[9] <= -83.0) {   votes[0] += 1;  } else {  if (x[4] <= -38.0) {  if (x[4] <= -86.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {  if (x[7] <= -71.0) {   votes[1] += 1;  } else {  if (x[2] <= -62.0) {  if (x[7] <= -66.5) {  if (x[3] <= -39.0) {   votes[0] += 1;  } else {  if (x[2] <= -67.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   } else {   votes[0] += 1;  }   } else {   votes[1] += 1;  }   }   }   }   }   } 
            if (x[7] <= -71.0) {  if (x[3] <= -37.5) {   votes[0] += 1;  } else {  if (x[2] <= -68.0) {  if (x[5] <= -78.5) {  if (x[8] <= -73.0) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {  if (x[7] <= -76.0) {  if (x[1] <= -37.0) {   votes[1] += 1;  } else {  if (x[2] <= -79.0) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   } else {   votes[1] += 1;  }   }   } else {   votes[0] += 1;  }   }   } else {  if (x[6] <= -37.5) {   votes[1] += 1;  } else {  if (x[1] <= -80.0) {   votes[1] += 1;  } else {  if (x[7] <= -50.5) {  if (x[0] <= -32.5) {   votes[0] += 1;  } else {  if (x[5] <= -73.5) {   votes[0] += 1;  } else {  if (x[4] <= -80.5) {   votes[0] += 1;  } else {  if (x[7] <= -69.5) {   votes[0] += 1;  } else {  if (x[2] <= -68.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   }   }   }   } else {  if (x[0] <= -32.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   }   }   }   } 
            if (x[5] <= -73.5) {  if (x[4] <= -39.5) {   votes[1] += 1;  } else {   votes[0] += 1;  }   } else {  if (x[5] <= -29.5) {  if (x[0] <= -38.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {  if (x[7] <= -71.0) {   votes[1] += 1;  } else {  if (x[2] <= -64.5) {  if (x[8] <= -68.5) {   votes[0] += 1;  } else {   votes[1] += 1;  }   } else {   votes[0] += 1;  }   }   }   } 
            

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
                
                case 0: return (lastRoomName = "a");
                
                case 1: return (lastRoomName = "b");
                
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

                
                if (ssid == "OnePlus 7T") {
                    x[0] = rssi;
                    continue;
                }
                
                if (ssid == "Ben's Galaxy Z Fold3 5G") {
                    x[1] = rssi;
                    continue;
                }
                
                if (ssid == "UoN-guest") {
                    x[2] = rssi;
                    continue;
                }
                
                if (ssid == "AndroidAP_4580") {
                    x[3] = rssi;
                    continue;
                }
                
                if (ssid == "ppp") {
                    x[4] = rssi;
                    continue;
                }
                
                if (ssid == "M00N-VOORJE-MAN") {
                    x[5] = rssi;
                    continue;
                }
                
                if (ssid == "Jj") {
                    x[6] = rssi;
                    continue;
                }
                
                if (ssid == "UoN-secure") {
                    x[7] = rssi;
                    continue;
                }
                
                if (ssid == "eduroam") {
                    x[8] = rssi;
                    continue;
                }
                
                if (ssid == "CSiTrobots") {
                    x[9] = rssi;
                    continue;
                }
                
            }
        }
};



WiFiIndoorPositioning positioning;
