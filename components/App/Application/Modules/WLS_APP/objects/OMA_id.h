// LWM2M Security
#define OID_LWM2M_SECURITY 0
#define RID_LWM2M_SERVER_URI 0           // String
#define RID_BOOTSTRAP_SERVER 1           // Boolean
#define RID_SECURITY_MODE 2              // Integer
#define RID_PUBLIC_KEY_OR_IDENTITY 3     // Opaque
#define RID_SERVER_PUBLIC_KEY_OR_IDENTITY 4 // Opaque
#define RID_SECRET_KEY 5                 // Opaque
#define RID_SMS_SECURITY_MODE 6          // Integer
#define RID_SMS_BINDING_KEY_PARAMS 7     // Opaque
#define RID_SMS_BINDING_SECRET_KEYS 8    // Opaque
#define RID_LWM2M_SERVER_SMS_NUMBER 9    // Integer
#define RID_SECURITY_SHORT_SERVER_ID 10           // Integer
#define RID_CLIENT_HOLD_OFF_TIME 11      // Integer

// LWM2M Server
#define OID_LWM2M_SERVER 1
#define RID_SHORT_SERVER_ID 0            // Integer
#define RID_LIFETIME 1                   // Integer
#define RID_DEFAULT_MIN_PERIOD 2         // Integer
#define RID_DEFAULT_MAX_PERIOD 3         // Integer
#define RID_DISABLE 4                    // Integer
#define RID_DISABLE_TIMEOUT 5            // Integer
#define RID_NOTIFICATION_STORING_WHEN_DISABLED_OR_OFFLINE 6 // Boolean
#define RID_BINDING 7                    // String
#define RID_REGISTRATION_UPDATE_TRIGGER 8 // Integer

// LWM2M Access Control
#define OID_LWM2M_ACCESS_CONTROL 2
#define RID_OBJECT_ID 0                 // Integer
#define RID_OBJECT_INSTANCE_ID 1        // Integer
#define RID_ACL 2                       // Integer
#define RID_ACCESS_CONTROL_OWNER 3      // Integer

// Device
#define OID_DEVICE 3
#define RID_MANUFACTURER 0              // String
#define RID_MODEL_NUMBER 1              // String
#define RID_SERIAL_NUMBER 2             // String
#define RID_FIRMWARE_VERSION 3          // String
#define RID_REBOOT 4                    // String
#define RID_FACTORY_RESET 5             // String
#define RID_AVAILABLE_POWER_SOURCES 6   // Integer
#define RID_POWER_SOURCE_VOLTAGE 7      // Integer
#define RID_POWER_SOURCE_CURRENT 8      // Integer
#define RID_BATTERY_LEVEL 9             // Integer
#define RID_MEMORY_FREE 10              // Integer
#define RID_ERROR_CODE 11               // Integer
#define RID_RESET_ERROR_CODE 12         // Integer
#define RID_DEVICE_CURRENT_TIME 13      // Time
#define RID_UTC_OFFSET 14               // String
#define RID_TIMEZONE 15                 // String
#define RID_SUPPORTED_BINDING_AND_MODES 16 // String
#define RID_SOFTWARE_VERSION 19 //String

// Connectivity Monitoring
#define OID_CONNECTIVITY_MONITORING 4
#define RID_NETWORK_BEARER 0            // Integer
#define RID_AVAILABLE_NETWORK_BEARER 1  // Integer
#define RID_RADIO_SIGNAL_STRENGTH 2     // Integer
#define RID_LINK_QUALITY 3              // Integer
#define RID_IP_ADDRESSES 4              // String
#define RID_ROUTER_IP_ADDRESSES 5       // String
#define RID_LINK_UTILIZATION 6          // Integer
#define RID_APN 7                        // String
#define RID_CELL_ID 8                    // Integer
#define RID_SMNC 9                      // Integer
#define RID_SMCC 10                      // Integer

// Firmware Update
#define OID_FIRMWARE_UPDATE 5
#define RID_PACKAGE 0                   // Opaque
#define RID_PACKAGE_URI 1               // String
#define RID_UPDATE 2                    // String
#define RID_STATE 3                     // Integer
#define RID_UPDATE_SUPPORTED_OBJECTS 4  // Boolean
#define RID_UPDATE_RESULT 5             // Integer

// Location
#define OID_LOCATION 6
#define RID_LATITUDE 0                  // String
#define RID_LONGITUDE 1                 // String
#define RID_ALTITUDE 2                  // String
#define RID_UNCERTAINTY 3               // String
#define RID_VELOCITY 4                  // Opaque
#define RID_TIMESTAMP 5                 // Time

// Connectivity Statistics
#define OID_CONNECTIVITY_STATISTICS 7
#define RID_SMS_TX_COUNTER 0            // Integer
#define RID_SMS_RX_COUNTER 1            // Integer
#define RID_TX_DATA 2                   // Integer
#define RID_RX_DATA 3                   // Integer
#define RID_MAX_MESSAGE_SIZE 4         // Integer
#define RID_AVERAGE_MESSAGE_SIZE 5     // Integer
#define RID_START_OR_RESET 6            // Integer

// Portfolio
#define OID_PORTFOLIO 16
#define RID_IDENTITY 0                  // String
#define RID_GET_AUTH_DATA 1             // String
#define RID_AUTH_DATA 2                 // String
#define RID_AUTH_STATUS 3               // Integer

// Non-Access Stratum (NAS) Configuration
#define OID_NAS_CONFIGURATION 18
#define RID_NAS_SIGNALING_PRIORITY 0   // Integer
#define RID_ATTACH_WITH_IMSI 1         // Boolean
#define RID_MINIMUM_PERIODIC_SEARCH_TIMER 2 // Integer
#define RID_NMO_I_BEHAVIOUR 3          // Boolean
#define RID_TIMER_T3245_BEHAVIOR 4     // Boolean
#define RID_EXTENDED_ACCESS_BARRING 5  // Boolean
#define RID_OVERRIDE_NAS_SIGNALING_LOW_PRIORITY 6 // Boolean
#define RID_OVERRIDE_EXTENDED_ACCESS_BARRING 7 // Boolean
#define RID_FAST_FIRST_HIGHER_PRIORITY_PLMN_SEARCH 8 // Boolean
#define RID_EUTRA_DISABLING_ALLOWED_FOR_EMM_CAUSE_15 9 // Boolean
#define RID_SM_RETRY_WAIT_TIME 10      // Boolean
#define RID_SM_RETRY_AT_RAT_CHANGE 11  // Boolean
#define RID_EXCEPTION_DATA_REPORTING_ALLOWED 12 // Boolean

// Digital Input
#define OID_DIGITAL_INPUT 3200
#define RID_DIGITAL_INPUT_STATE 5500          // Boolean
#define RID_DIGITAL_INPUT_COUNTER 5501        // Integer
#define RID_DIGITAL_INPUT_POLARITY 5502       // Boolean
#define RID_DIGITAL_INPUT_DEBOUNCE 5503       // Integer
#define RID_DIGITAL_INPUT_EDGE_SELECTION 5504 // Integer
#define RID_DIGITAL_INPUT_COUNTER_RESET 5505  // Opaque
#define RID_APPLICATION_TYPE 5750            // String
#define RID_SENSOR_TYPE 5751                 // String

// Digital Output
#define OID_DIGITAL_OUTPUT 3201
#define RID_DIGITAL_OUTPUT_STATE 5550       // Boolean
#define RID_DIGITAL_OUTPUT_POLARITY 5551    // Boolean
#define RID_APPLICATION_TYPE 5750           // String

// Analog Input
#define OID_ANALOG_INPUT 3202
#define RID_ANALOG_INPUT_CURRENT_VALUE 5600 // Float
#define RID_MIN_MEASURED_VALUE 5601         // Float
#define RID_MAX_MEASURED_VALUE 5602         // Float
#define RID_MIN_RANGE_VALUE 5603            // Float
#define RID_MAX_RANGE_VALUE 5604            // Float
#define RID_APPLICATION_TYPE 5750           // String
#define RID_SENSOR_TYPE 5751                // String
#define RID_RESET_MIN_AND_MAX_MEASURED_VALUES 5605 // Opaque

// Analog Output
#define OID_ANALOG_OUTPUT 3203
#define RID_ANALOG_OUTPUT_CURRENT_VALUE 5650 // Float
#define RID_APPLICATION_TYPE 5750            // String
#define RID_MIN_RANGE_VALUE 5603             // Float
#define RID_MAX_RANGE_VALUE 5604             // Float

// Generic Sensor
#define OID_GENERIC_SENSOR 3300
#define RID_SENSOR_VALUE 5700              // Float
#define RID_SENSOR_UNITS 5701              // String
#define RID_MIN_MEASURED_VALUE 5601        // Float
#define RID_MAX_MEASURED_VALUE 5602        // Float
#define RID_MIN_RANGE_VALUE 5603           // Float
#define RID_MAX_RANGE_VALUE 5604           // Float
#define RID_APPLICATION_TYPE 5750          // String
#define RID_SENSOR_TYPE 5751               // String
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque

// Illuminance
#define OID_ILLUMINANCE 3301
#define RID_SENSOR_VALUE 5700              // Float
#define RID_MIN_MEASURED_VALUE 5601        // Float
#define RID_MAX_MEASURED_VALUE 5602        // Float
#define RID_MIN_RANGE_VALUE 5603           // Float
#define RID_MAX_RANGE_VALUE 5604           // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_SENSOR_UNITS 5701              // String

// Presence
#define OID_PRESENCE 3302
#define RID_DIGITAL_INPUT_STATE 5500       // Boolean
#define RID_DIGITAL_INPUT_COUNTER 5501     // Integer
#define RID_DIGITAL_INPUT_COUNTER_RESET 5505 // Opaque
#define RID_SENSOR_TYPE 5751               // String
#define RID_BUSY_TO_CLEAR_DELAY 5903       // Integer
#define RID_CLEAR_TO_BUSY_DELAY 5904       // Integer

// Temperature
#define OID_TEMPERATURE 3303
#define RID_SENSOR_VALUE 5700              // Float
#define RID_MIN_MEASURED_VALUE 5601        // Float
#define RID_MAX_MEASURED_VALUE 5602        // Float
#define RID_MIN_RANGE_VALUE 5603           // Float
#define RID_MAX_RANGE_VALUE 5604           // Float
#define RID_SENSOR_UNITS 5701              // String
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // String

// Humidity
#define OID_HUMIDITY 3304
#define RID_SENSOR_VALUE 5700              // Float
#define RID_MIN_MEASURED_VALUE 5601        // Float
#define RID_MAX_MEASURED_VALUE 5602        // Float
#define RID_MIN_RANGE_VALUE 5603           // Float
#define RID_MAX_RANGE_VALUE 5604           // Float
#define RID_SENSOR_UNITS 5701              // String
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque

// Power Measurement
#define OID_POWER_MEASUREMENT 3305
#define RID_INSTANT_ACTIVE_POWER 5800      // Float
#define RID_MIN_MEASURED_ACTIVE_POWER 5801 // Float
#define RID_MAX_MEASURED_ACTIVE_POWER 5802 // Float
#define RID_MIN_RANGE_ACTIVE_POWER 5803    // Float
#define RID_MAX_RANGE_ACTIVE_POWER 5804    // Float
#define RID_CUMULATIVE_ACTIVE_POWER 5805   // Float
#define RID_ACTIVE_POWER_CALIBRATION 5806  // Float
#define RID_INSTANT_REACTIVE_POWER 5810    // Float
#define RID_MIN_MEASURED_REACTIVE_POWER 5811 // Float
#define RID_MAX_MEASURED_REACTIVE_POWER 5812 // Float
#define RID_MIN_RANGE_REACTIVE_POWER 5813  // Float
#define RID_MAX_RANGE_REACTIVE_POWER 5814  // Float
#define RID_CUMULATIVE_REACTIVE_POWER 5815 // Float
#define RID_REACTIVE_POWER_CALIBRATION 5816 // Float
#define RID_POWER_FACTOR 5820              // Float
#define RID_CURRENT_CALIBRATION 5821      // Float
#define RID_RESET_CUMULATIVE_ENERGY 5822   // Opaque
#define RID_POWER_RESET_MIN_MAX_MEASURED_VALUES 5695 // Opaque

// Actuation
#define OID_ACTUATION 3306
#define RID_ON_OFF 5850                   // Boolean
#define RID_DIMMER 5851                   // Integer
#define RID_ON_TIME 5852                  // Integer
#define RID_MULTI_STATE_OUTPUT 5853       // String
#define RID_APPLICATION_TYPE 5750         // String

// Set Point
#define OID_SET_POINT 3308
#define RID_SET_POINT_VALUE 5900          // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_COLOUR 5706                   // String
#define RID_APPLICATION_TYPE 5750         // String

// Load Control
#define OID_LOAD_CONTROL 3310
#define RID_EVENT_IDENTIFIER 5823         // String
#define RID_START_TIME 5824               // String
#define RID_DURATION_IN_MIN 5825          // String
#define RID_CRITICALITY_LEVEL 5826        // String
#define RID_AVG_LOAD_ADJ_PCT 5827         // String
#define RID_DUTY_CYCLE 5828               // String

// Light Control
#define OID_LIGHT_CONTROL 3311
#define RID_ON_OFF 5850                   // Boolean
#define RID_DIMMER 5851                   // Integer
#define RID_ON_TIME 5852                  // Integer
#define RID_CUMULATIVE_ACTIVE_POWER 5805  // Float
#define RID_POWER_FACTOR 5820             // Float
#define RID_COLOUR 5706                   // String
#define RID_SENSOR_UNITS 5701             // String

// Power Control
#define OID_POWER_CONTROL 3312
#define RID_ON_OFF 5850                   // Boolean
#define RID_DIMMER 5851                   // Integer
#define RID_ON_TIME 5852                  // Integer
#define RID_CUMULATIVE_ACTIVE_POWER 5805  // Float
#define RID_POWER_FACTOR 5820             // Float

// Accelerator
#define OID_ACCELERATOR 3313
#define RID_X_VALUE 5702                  // Float
#define RID_Y_VALUE 5703                  // Float
#define RID_Z_VALUE 5704                  // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float

// Magnetometer
#define OID_MAGNETOMETER 3314
#define RID_X_VALUE 5702                  // Float
#define RID_Y_VALUE 5703                  // Float
#define RID_Z_VALUE 5704                  // Float
#define RID_COMPASS_DIRECTION 5705       // Float
#define RID_SENSOR_UNITS 5701             // String

// Barometer
#define OID_BAROMETER 3315
#define RID_SENSOR_VALUE 5700             // Float
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque

// Voltage
#define OID_VOLTAGE 3316
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Current
#define OID_CURRENT 3317
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Frequency
#define OID_FREQUENCY 3318
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Depth
#define OID_DEPTH 3319
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Percentage
#define OID_PERCENTAGE 3320
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Altitude
#define OID_ALTITUDE 3321
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Load
#define OID_LOAD 3322
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Pressure
#define OID_PRESSURE 3323
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Loudness
#define OID_LOUDNESS 3324
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Concentration
#define OID_CONCENTRATION 3325
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Acidity
#define OID_ACIDITY 3326
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Conductivity
#define OID_CONDUCTIVITY 3327
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Power
#define OID_POWER 3328
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Power Factor
#define OID_POWER_FACTOR 3329
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Distance
#define OID_DISTANCE 3330
#define RID_SENSOR_VALUE 5700             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_MEASURED_VALUE 5601       // Float
#define RID_MAX_MEASURED_VALUE 5602       // Float
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821     // String
#define RID_APPLICATION_TYPE 5750         // String

// Energy
#define OID_ENERGY 3331
#define RID_ENERGY_SENSOR_VALUE 5805             // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_RESET_CUMULATIVE_ENERGY 5822  // Opaque
#define RID_APPLICATION_TYPE 5750         // String

// Direction
#define OID_DIRECTION 3332
#define RID_COMPASS_DIRECTION 5705       // Float
#define RID_MIN_MEASURED_VALUE 5601      // Float
#define RID_MAX_MEASURED_VALUE 5602      // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_APPLICATION_TYPE 5750         // String

// Time
#define OID_TIME 3333
#define RID_CURRENT_TIME 5506            // Time
#define RID_FRACTIONAL_TIME 5507         // Float
#define RID_APPLICATION_TYPE 5750         // String

// Gyrometer
#define OID_GYROMETER 3334
#define RID_X_VALUE 5702                // Float
#define RID_Y_VALUE 5703                // Float
#define RID_Z_VALUE 5704                // Float
#define RID_SENSOR_UNITS 5701             // String
#define RID_MIN_RANGE_VALUE 5603          // Float
#define RID_MAX_RANGE_VALUE 5604          // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_APPLICATION_TYPE 5750         // String

// Colour
#define OID_COLOUR 3335
#define RID_COLOUR 5706                 // String
#define RID_SENSOR_UNITS 5701             // String
#define RID_APPLICATION_TYPE 5750         // String

// Location
#define OID_LOCATION_SENSOR 3336
#define RID_LOCATION_LATITUDE 5514               // String
#define RID_LOCATION_LONGITUDE 5515              // String
#define RID_LOCATION_UNCERTAINTY 5516            // String
#define RID_LOCATION_COMPASS_DIRECTION 5705       // Float
#define RID_LOCATION_VELOCITY 5517               // Opaque
#define RID_LOCATION_TIMESTAMP 5518              // Time
#define RID_APPLICATION_TYPE 5750         // String

// Positioner
#define OID_POSITIONER 3337
#define RID_CURRENT_POSITION 5536       // Float
#define RID_TRANSITION_TIME 5537        // Float
#define RID_REMAINING_TIME 5538         // Float
#define RID_MIN_MEASURED_VALUE 5601      // Float
#define RID_MAX_MEASURED_VALUE 5602      // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUE 5605 // Opaque
#define RID_MIN_LIMIT 5519              // Float
#define RID_MAX_LIMIT 5520              // Float
#define RID_APPLICATION_TYPE 5750         // String

// Buzzer
#define OID_BUZZER 3338
#define RID_ON_OFF 5850                 // Boolean
#define RID_DIMMER 5851                 // Integer
#define RID_DELAY_DURATION 5521         // Float
#define RID_MINIMUM_OFF_TIME 5525       // Float
#define RID_APPLICATION_TYPE 5750         // String

// Audio Clip
#define OID_AUDIO_CLIP 3339
#define RID_CLIP 5522                   // Opaque
#define RID_TRIGGER 5523                // Opaque
#define RID_DIMMER 5851                 // Integer
#define RID_AUDIO_DURATION 5524           // Float
#define RID_APPLICATION_TYPE 5750         // String

// Timer
#define OID_TIMER 3340
#define RID_DURATION 5521               // Float
#define RID_REMAINING_TIME 5538         // Float
#define RID_MINIMUM_OFF_TIME 5525       // Float
#define RID_TRIGGER 5523                // Opaque
#define RID_ON_OFF 5850                 // Boolean
#define RID_DIGITAL_INPUT_COUNTER 5501  // Integer
#define RID_CUMULATIVE_TIME 5544        // Float
#define RID_DIGITAL_STATE 5543          // Boolean
#define RID_COUNTER 5534                // Integer
#define RID_MODE 5526                   // Integer
#define RID_APPLICATION_TYPE 5750         // String

// Addressable Text Display
#define OID_ADDRESSABLE_TEXT_DISPLAY 3341
#define RID_TEXT 5527                  // String
#define RID_X_COORDINATE 5528           // Float
#define RID_Y_COORDINATE 5529           // Float
#define RID_MAX_X_COORDINATE 5545      // Float
#define RID_MAX_Y_COORDINATE 5546      // Float
#define RID_CLEAR_DISPLAY 5530         // Integer
#define RID_DIMMER 5851                // Integer
#define RID_CONTRAST 5531              // Float
#define RID_APPLICATION_TYPE 5750        // String

// On/Off switch
#define OID_ON_OFF_SWITCH 3342
#define RID_DIGITAL_INPUT_STATE 5500   // Boolean
#define RID_DIGITAL_INPUT_COUNTER 5501 // Integer
#define RID_ON_TIME 5852                // Integer
#define RID_OFF_TIME 5854               // Integer
#define RID_APPLICATION_TYPE 5750         // String

// Dimmer
#define OID_DIMMER 3343
#define RID_DIMMER 5851                 // Float
#define RID_ON_TIME 5852                // Integer
#define RID_OFF_TIME 5854               // Integer
#define RID_APPLICATION_TYPE 5750         // String

// Up/Down Control
#define OID_UP_DOWN_CONTROL 3344
#define RID_INCREASE_INPUT_STATE 5532  // Boolean
#define RID_DECREASE_INPUT_STATE 5533  // Boolean
#define RID_UP_COUNTER 5541            // Integer
#define RID_DOWN_COUNTER 5542          // Integer
#define RID_APPLICATION_TYPE 5750         // String

// Multiple Axis Joystick
#define OID_MULTIPLE_AXIS_JOYSTICK 3345
#define RID_DIGITAL_INPUT_STATE 5500   // Boolean
#define RID_DIGITAL_INPUT_COUNTER 5501 // Integer
#define RID_X_VALUE 5702                // Float
#define RID_Y_VALUE 5703                // Float
#define RID_Z_VALUE 5704                // Float
#define RID_APPLICATION_TYPE 5750         // String

// Rate
#define OID_RATE 3346
#define RID_SENSOR_VALUE 5700                 // Float
#define RID_SENSOR_UNITS 5701                 // String
#define RID_MIN_MEASURED_VALUE 5601           // Float
#define RID_MAX_MEASURED_VALUE 5602           // Float
#define RID_MIN_RANGE_VALUE 5603              // Float
#define RID_MAX_RANGE_VALUE 5604              // Float
#define RID_RESET_MIN_MAX_MEASURED_VALUES 5605 // Opaque
#define RID_CURRENT_CALIBRATION 5821          // String
#define RID_APPLICATION_TYPE 5750             // String

// Push button
#define OID_PUSH_BUTTON 3347
#define RID_DIGITAL_INPUT_STATE 5500          // Boolean
#define RID_DIGITAL_INPUT_COUNTER 5501        // Integer
#define RID_APPLICATION_TYPE 5750             // String

// Multi-state Selector
#define OID_MULTI_STATE_SELECTOR 3348
#define RID_MULTI_STATE_INPUT 5547           // Integer
#define RID_APPLICATION_TYPE 5750            // String

// 3-Phase Power Meter
#define OID_3_PHASE_POWER_METER 10242
#define RID_MANUFACTURER 0                    // String
#define RID_MODEL_NUMBER 1                   // String
#define RID_SERIAL_NUMBER 2                  // String
#define RID_DESCRIPTION 3                    // String
#define RID_TENSION_R 4                      // Float
#define RID_CURRENT_R 5                      // Float
#define RID_ACTIVE_POWER_R 6                 // Float
#define RID_REACTIVE_POWER_R 7               // Float
#define RID_INDUCTIVE_REACTIVE_POWER_R 8     // Float
#define RID_CAPACITIVE_REACTIVE_POWER_R 9    // Float
#define RID_APPARENT_POWER_R 10              // Float
#define RID_POWER_FACTOR_R 11                // Float
#define RID_THD_V_R 12                       // Float
#define RID_THD_A_R 13                       // Float
#define RID_TENSION_S 14                     // Float
#define RID_CURRENT_S 15                     // Float
#define RID_ACTIVE_POWER_S 16                // Float
#define RID_REACTIVE_POWER_S 17              // Float
#define RID_INDUCTIVE_REACTIVE_POWER_S 18    // Float
#define RID_CAPACITIVE_REACTIVE_POWER_S 19   // Float
#define RID_APPARENT_POWER_S 20              // Float
#define RID_POWER_FACTOR_S 21                // Float
#define RID_THD_V_S 22                       // Float
#define RID_THD_A_S 23                       // Float
#define RID_TENSION_T 24                     // Float
#define RID_CURRENT_T 25                     // Float
#define RID_ACTIVE_POWER_T 26                // Float
#define RID_REACTIVE_POWER_T 27              // Float
#define RID_INDUCTIVE_REACTIVE_POWER_T 28    // Float
#define RID_CAPACITIVE_REACTIVE_POWER_T 29   // Float
#define RID_APPARENT_POWER_T 30              // Float
#define RID_POWER_FACTOR_T 31                // Float
#define RID_THD_V_T 32                       // Float
#define RID_THD_A_T 33                       // Float
#define RID_3_PHASE_ACTIVE_POWER 34          // Float
#define RID_3_PHASE_REACTIVE_POWER 35        // Float
#define RID_3_PHASE_INDUCTIVE_REACTIVE_POWER 36  // Float
#define RID_3_PHASE_CAPACITIVE_REACTIVE_POWER 37 // Float
#define RID_3_PHASE_APPARENT_POWER 38       // Float
#define RID_3_PHASE_POWER_FACTOR 39         // Float
#define RID_3_PHASE_PHI_COSINE 40           // Float
#define RID_ACTIVE_ENERGY 41                 // Float
#define RID_REACTIVE_ENERGY 42               // Float
#define RID_INDUCTIVE_REACTIVE_ENERGY 43     // Float
#define RID_CAPACITIVE_REACTIVE_ENERGY 44    // Float
#define RID_APPARENT_ENERGY 45               // Float
#define RID_TENSION_R_S 46                   // Float
#define RID_TENSION_S_T 47                   // Float
#define RID_TENSION_T_R 48                   // Float
#define RID_FREQUENCY 49                     // Float
#define RID_NEUTRAL_CURRENT 50               // Float

// Single-Phase Power Meter
#define OID_SINGLE_PHASE_POWER_METER 10243
#define RID_SINGLE_P_MANUFACTURER 0                   // String
#define RID_SINGLE_P_MODEL_NUMBER 1                   // String
#define RID_SINGLE_P_SERIAL_NUMBER 2                  // String
#define RID_SINGLE_P_DESCRIPTION 3                    // String
#define RID_SINGLE_P_TENSION 4                        // String
#define RID_SINGLE_P_CURRENT 5                        // Float
#define RID_SINGLE_P_ACTIVE_POWER 6                   // Float
#define RID_SINGLE_P_REACTIVE_POWER 7                 // Float
#define RID_SINGLE_P_INDUCTIVE_REACTIVE_POWER 8       // Float
#define RID_SINGLE_P_CAPACITIVE_REACTIVE_POWER 9      // Float
#define RID_SINGLE_P_APPARENT_POWER 10                // Float
#define RID_SINGLE_P_POWER_FACTOR 11                  // Float
#define RID_SINGLE_P_THD_V 12                         // Float
#define RID_SINGLE_P_THD_A 13                         // Float
#define RID_SINGLE_P_ACTIVE_ENERGY 14                 // Float
#define RID_SINGLE_P_REACTIVE_ENERGY 15               // Float
#define RID_SINGLE_P_APPARENT_ENERGY 16               // Float
#define RID_SINGLE_P_FREQUENCY 17                     // Float

// Vehicle Control Unit
#define OID_VEHICLE_CONTROL_UNIT 10244
#define RID_VEHICLE_UI_STATE 0               // Integer
#define RID_VEHICLE_SPEED 1                  // Integer
#define RID_VEHICLE_SHIFT_STATUS 2           // Integer
#define RID_VEHICLE_AP_POSITION 3            // Integer
#define RID_VEHICLE_POWER 4                  // Float
#define RID_VEHICLE_DRIVE_ENERGY 5           // Float
#define RID_VEHICLE_ENERGY_CONSUMPTION_EFFICIENCY 6  // Float
#define RID_VEHICLE_ESTIMATED_MILEAGE 7     // Integer
#define RID_VEHICLE_CHARGE_CABLE_STATUS 8    // Boolean
#define RID_VEHICLE_CHARGE_STATUS 9          // Integer
#define RID_VEHICLE_CHARGE_VOLTAGE 10        // Float
#define RID_VEHICLE_CHARGE_CURRENT 11        // Float
#define RID_VEHICLE_CHARGE_REMAINING_TIME 12 // Integer
#define RID_BATTERY_PACK_VOLTAGE 13          // Float
#define RID_BATTERY_PACK_CURRENT 14          // Float
#define RID_BATTERY_PACK_REMAINING_CAPACITY 15  // Integer
#define RID_BATTERY_PACK_SOC 16              // Integer
#define RID_BATTERY_PACK_SOH 17              // Integer
#define RID_BATTERY_CELL_MIN_VOLT 18         // Integer
#define RID_BATTERY_CELL_MAX_VOLT 19         // Integer
#define RID_BATTERY_MODULE_MIN_TEMP 20       // Integer
#define RID_BATTERY_MODULE_MAX_TEMP 21       // Integer
#define RID_BATTERY_CONNECTION_STATUS 22     // Boolean
#define RID_MCU_VOLTAGE 24                   // Integer
#define RID_MCU_TEMPERATURE 25               // Integer
#define RID_MOTOR_SPEED 26                   // Integer
#define RID_MOTOR_TEMPERATURE 27             // Integer
#define RID_MOTOR_OT_WARNING 28              // Boolean
#define RID_MCU_OT_WARNING 29                // Boolean
#define RID_BATTERY_PACK_OT_WARNING 30       // Boolean
#define RID_MCU_FAULT 31                     // Boolean
#define RID_MOTOR_ERROR 32                   // Boolean
