#ifndef _TOOLBOX_LDS_ATTRIBUTE_TYPES_
#define _TOOLBOX_LDS_ATTRIBUTE_TYPES_

// Enum for ColorLoopAction
typedef enum 
{
  EMBER_ZCL_COLOR_LOOP_ACTION_DEACTIVATE = 0,
  EMBER_ZCL_COLOR_LOOP_ACTION_ACTIVATE_FROM_COLOR_LOOP_START_ENHANCED_HUE = 1,
  EMBER_ZCL_COLOR_LOOP_ACTION_ACTIVATE_FROM_ENHANCED_CURRENT_HUE = 2,
} EmberAfColorLoopAction;

// Enum for ColorLoopDirection
typedef enum 
{
  EMBER_ZCL_COLOR_LOOP_DIRECTION_DECREMENT_HUE = 0,
  EMBER_ZCL_COLOR_LOOP_DIRECTION_INCREMENT_HUE = 1,
} EmberAfColorLoopDirection;

// Enum for ColorMode
typedef enum 
{
  EMBER_ZCL_COLOR_MODE_CURRENT_HUE_AND_CURRENT_SATURATION = 0,
  EMBER_ZCL_COLOR_MODE_CURRENT_X_AND_CURRENT_Y = 1,
  EMBER_ZCL_COLOR_MODE_COLOR_TEMPERATURE = 2,
} EmberAfColorMode;

// ZCL attribute types
enum
{
    ZCL_NO_DATA_ATTRIBUTE_TYPE           = 0x00, // No data
    ZCL_BOOLEAN_ATTRIBUTE_TYPE           = 0x10, // Boolean
    ZCL_BITMAP8_ATTRIBUTE_TYPE           = 0x18, // 8-bit bitmap
    ZCL_BITMAP16_ATTRIBUTE_TYPE          = 0x19, // 16-bit bitmap
    ZCL_BITMAP24_ATTRIBUTE_TYPE          = 0x1A, // 24-bit bitmap
    ZCL_BITMAP32_ATTRIBUTE_TYPE          = 0x1B, // 32-bit bitmap
    ZCL_BITMAP64_ATTRIBUTE_TYPE          = 0x1F, // 64-bit bitmap
    ZCL_INT8U_ATTRIBUTE_TYPE             = 0x20, // Unsigned 8-bit integer
    ZCL_INT16U_ATTRIBUTE_TYPE            = 0x21, // Unsigned 16-bit integer
    ZCL_INT24U_ATTRIBUTE_TYPE            = 0x22, // Unsigned 24-bit integer
    ZCL_INT32U_ATTRIBUTE_TYPE            = 0x23, // Unsigned 32-bit integer
    ZCL_INT40U_ATTRIBUTE_TYPE            = 0x24, // Unsigned 40-bit integer
    ZCL_INT48U_ATTRIBUTE_TYPE            = 0x25, // Unsigned 48-bit integer
    ZCL_INT56U_ATTRIBUTE_TYPE            = 0x26, // Unsigned 56-bit integer
    ZCL_INT64U_ATTRIBUTE_TYPE            = 0x27, // Unsigned 64-bit integer
    ZCL_INT8S_ATTRIBUTE_TYPE             = 0x28, // Signed 8-bit integer
    ZCL_INT16S_ATTRIBUTE_TYPE            = 0x29, // Signed 16-bit integer
    ZCL_INT24S_ATTRIBUTE_TYPE            = 0x2A, // Signed 24-bit integer
    ZCL_INT32S_ATTRIBUTE_TYPE            = 0x2B, // Signed 32-bit integer
    ZCL_INT40S_ATTRIBUTE_TYPE            = 0x2C, // Signed 40-bit integer
    ZCL_INT48S_ATTRIBUTE_TYPE            = 0x2D, // Signed 48-bit integer
    ZCL_INT56S_ATTRIBUTE_TYPE            = 0x2E, // Signed 56-bit integer
    ZCL_INT64S_ATTRIBUTE_TYPE            = 0x2F, // Signed 64-bit integer
    ZCL_ENUM8_ATTRIBUTE_TYPE             = 0x30, // 8-bit enumeration
    ZCL_ENUM16_ATTRIBUTE_TYPE            = 0x31, // 16-bit enumeration
    ZCL_PRIORITY_ATTRIBUTE_TYPE          = 0x32, // Priority
    ZCL_STATUS_ATTRIBUTE_TYPE            = 0x33, // Status Code
    ZCL_SINGLE_ATTRIBUTE_TYPE            = 0x39, // Single precision
    ZCL_DOUBLE_ATTRIBUTE_TYPE            = 0x3A, // Double precision
    ZCL_OCTET_STRING_ATTRIBUTE_TYPE      = 0x41, // Octet String
    ZCL_CHAR_STRING_ATTRIBUTE_TYPE       = 0x42, // Character String
    ZCL_LONG_OCTET_STRING_ATTRIBUTE_TYPE = 0x43, // Long Octet String
    ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPE  = 0x44, // Long Character String
    ZCL_ARRAY_ATTRIBUTE_TYPE             = 0x48, // List
    ZCL_STRUCT_ATTRIBUTE_TYPE            = 0x4C, // Structure
    ZCL_GROUP_ID_ATTRIBUTE_TYPE          = 0xC0, // Group ID
    ZCL_ENDPOINT_NO_ATTRIBUTE_TYPE       = 0xC1, // Endpoint Number
    ZCL_VENDOR_ID_ATTRIBUTE_TYPE         = 0xC2, // Vendor ID
    ZCL_DEVTYPE_ID_ATTRIBUTE_TYPE        = 0xC3, // Device Type ID
    ZCL_FABRIC_ID_ATTRIBUTE_TYPE         = 0xC4, // Fabric ID
    ZCL_FABRIC_IDX_ATTRIBUTE_TYPE        = 0xC5, // Fabric Index
    ZCL_ENTRY_IDX_ATTRIBUTE_TYPE         = 0xC6, // Entry Index
    ZCL_DATA_VER_ATTRIBUTE_TYPE          = 0xC7, // Data Version
    ZCL_EVENT_NO_ATTRIBUTE_TYPE          = 0xC8, // Event Number
    ZCL_SEMTAG_ATTRIBUTE_TYPE            = 0xC9, // Semantic Tag
    ZCL_NAMESPACE_ATTRIBUTE_TYPE         = 0xCA, // Namespace
    ZCL_TAG_ATTRIBUTE_TYPE               = 0xCB, // Tag
    ZCL_SYSTIME_US_ATTRIBUTE_TYPE        = 0xD0, // System Time Microseconds
    ZCL_SYSTIME_MS_ATTRIBUTE_TYPE        = 0xD1, // System Time Milliseconds
    ZCL_ELAPSED_S_ATTRIBUTE_TYPE         = 0xD2, // Elapsed Time Seconds
    ZCL_TEMPERATURE_ATTRIBUTE_TYPE       = 0xD8, // Temperature
    ZCL_TOD_ATTRIBUTE_TYPE               = 0xE0, // Time of day
    ZCL_DATE_ATTRIBUTE_TYPE              = 0xE1, // Date
    ZCL_EPOCH_US_ATTRIBUTE_TYPE          = 0xE3, // Epoch Microseconds
    ZCL_EPOCH_S_ATTRIBUTE_TYPE           = 0xE4, // Epoch Seconds
    ZCL_POSIX_MS_ATTRIBUTE_TYPE          = 0xE5, // Posix Time Milliseconds
    ZCL_PERCENT_ATTRIBUTE_TYPE           = 0xE6, // Percentage units 1%
    ZCL_PERCENT100THS_ATTRIBUTE_TYPE     = 0xE7, // Percentage units 0.01%
    ZCL_CLUSTER_ID_ATTRIBUTE_TYPE        = 0xE8, // Cluster ID
    ZCL_ATTRIB_ID_ATTRIBUTE_TYPE         = 0xE9, // Attribute ID
    ZCL_FIELD_ID_ATTRIBUTE_TYPE          = 0xEB, // Field ID
    ZCL_EVENT_ID_ATTRIBUTE_TYPE          = 0xEC, // Event ID
    ZCL_COMMAND_ID_ATTRIBUTE_TYPE        = 0xED, // Command ID
    ZCL_ACTION_ID_ATTRIBUTE_TYPE         = 0xEE, // Action ID
    ZCL_TRANS_ID_ATTRIBUTE_TYPE          = 0xEF, // Transaction ID
    ZCL_NODE_ID_ATTRIBUTE_TYPE           = 0xF0, // Node ID
    ZCL_IPADR_ATTRIBUTE_TYPE             = 0xF2, // IP Address
    ZCL_IPV4ADR_ATTRIBUTE_TYPE           = 0xF3, // IPv4 Address
    ZCL_IPV6ADR_ATTRIBUTE_TYPE           = 0xF4, // IPv6 Address
    ZCL_IPV6PRE_ATTRIBUTE_TYPE           = 0xF5, // IPv6 Prefix
    ZCL_HWADR_ATTRIBUTE_TYPE             = 0xF6, // Hardware Address
    ZCL_UNKNOWN_ATTRIBUTE_TYPE           = 0xFF, // Unknown
};

#endif