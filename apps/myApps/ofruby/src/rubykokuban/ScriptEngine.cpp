#include "rubykokuban/ScriptEngine.hpp"

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/compile.h"
#include "mruby/irep.h"
#include "mruby/string.h"
#include "ofMain.h"
#include "rubykokuban/Bind.hpp"
#include <stdint.h>

namespace rubykokuban {

// buitin.rb
// const uint8_t BuiltIn[] = {
// 0x45,0x54,0x49,0x52,0x30,0x30,0x30,0x33,0x96,0xfa,0x00,0x00,0x0c,0x5e,0x4d,0x41,
// 0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x0b,0x71,0x30,0x30,
// 0x30,0x30,0x00,0x00,0x00,0x6b,0x00,0x01,0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x0b,
// 0x05,0x00,0x80,0x00,0x44,0x00,0x80,0x00,0x45,0x00,0x80,0x00,0x05,0x00,0x80,0x00,
// 0x44,0x40,0x80,0x00,0xc5,0x00,0x80,0x00,0x05,0x00,0x80,0x00,0x05,0x00,0x00,0x01,
// 0x43,0x80,0x80,0x00,0x45,0x01,0x80,0x00,0x4a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 0x00,0x00,0x00,0x03,0x00,0x09,0x44,0x65,0x62,0x75,0x67,0x49,0x6e,0x66,0x6f,0x00,
// 0x00,0x07,0x43,0x6f,0x6e,0x73,0x6f,0x6c,0x65,0x00,0x00,0x0c,0x53,0x65,0x71,0x75,
// 0x65,0x6e,0x63,0x65,0x53,0x68,0x6f,0x74,0x00,0x00,0x00,0x00,0x69,0x00,0x01,0x00,
// 0x02,0x00,0x03,0x00,0x00,0x00,0x0e,0x00,0x06,0x00,0x80,0x00,0x47,0x40,0x80,0x00,
// 0xc0,0x00,0x00,0x01,0x46,0x00,0x80,0x00,0x06,0x00,0x80,0x00,0x47,0x40,0x80,0x00,
// 0xc0,0x02,0x00,0x01,0x46,0x40,0x80,0x00,0x06,0x00,0x80,0x00,0x47,0x40,0x80,0x00,
// 0xc0,0x04,0x00,0x01,0x46,0x80,0x80,0x00,0x04,0x01,0x80,0x00,0x29,0x00,0x00,0x00,
// 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x66,0x70,0x73,0x00,0x00,0x06,
// 0x77,0x69,0x6e,0x64,0x6f,0x77,0x00,0x00,0x05,0x6d,0x6f,0x75,0x73,0x65,0x00,0x00,
// 0x00,0x00,0x72,0x00,0x02,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x0b,0x00,0x00,0x00,
// 0x26,0x00,0x00,0x00,0x3d,0x00,0x00,0x01,0x06,0x00,0x80,0x01,0xbd,0x00,0x00,0x02,
// 0x06,0x00,0x80,0x02,0x20,0x40,0x80,0x02,0x20,0x01,0x80,0x01,0x3e,0xc0,0x00,0x01,
// 0x3d,0x01,0x80,0x01,0x3e,0xc0,0x00,0x01,0x29,0x00,0x00,0x01,0x00,0x00,0x00,0x03,
// 0x00,0x00,0x00,0x00,0x00,0x05,0x25,0x33,0x2e,0x32,0x66,0x00,0x00,0x04,0x20,0x66,
// 0x70,0x73,0x00,0x00,0x00,0x02,0x00,0x06,0x66,0x6f,0x72,0x6d,0x61,0x74,0x00,0x00,
// 0x0e,0x67,0x65,0x74,0x5f,0x66,0x72,0x61,0x6d,0x65,0x5f,0x72,0x61,0x74,0x65,0x00,
// 0x00,0x00,0x00,0xd9,0x00,0x02,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x17,0x00,0x00,
// 0x26,0x00,0x00,0x00,0x3d,0x00,0x00,0x01,0x06,0x00,0x80,0x01,0x20,0x00,0x80,0x01,
// 0x3e,0xc0,0x00,0x01,0xbd,0x00,0x80,0x01,0x3e,0xc0,0x00,0x01,0x06,0x00,0x80,0x01,
// 0x20,0x40,0x80,0x01,0x3e,0xc0,0x00,0x01,0x3d,0x01,0x80,0x01,0x3e,0xc0,0x00,0x01,
// 0x06,0x00,0x80,0x01,0x20,0x80,0x80,0x01,0x3e,0xc0,0x00,0x01,0xbd,0x00,0x80,0x01,
// 0x3e,0xc0,0x00,0x01,0x06,0x00,0x80,0x01,0x20,0xc0,0x80,0x01,0x3e,0xc0,0x00,0x01,
// 0xbd,0x01,0x80,0x01,0x3e,0xc0,0x00,0x01,0x29,0x00,0x00,0x01,0x00,0x00,0x00,0x04,
// 0x00,0x00,0x0d,0x77,0x69,0x6e,0x64,0x6f,0x77,0x5f,0x70,0x6f,0x73,0x3a,0x20,0x28,
// 0x00,0x00,0x02,0x2c,0x20,0x00,0x00,0x0a,0x29,0x2c,0x20,0x73,0x69,0x7a,0x65,0x3a,
// 0x20,0x28,0x00,0x00,0x01,0x29,0x00,0x00,0x00,0x04,0x00,0x0c,0x77,0x69,0x6e,0x64,
// 0x6f,0x77,0x5f,0x70,0x6f,0x73,0x5f,0x78,0x00,0x00,0x0c,0x77,0x69,0x6e,0x64,0x6f,
// 0x77,0x5f,0x70,0x6f,0x73,0x5f,0x79,0x00,0x00,0x0c,0x77,0x69,0x6e,0x64,0x6f,0x77,
// 0x5f,0x77,0x69,0x64,0x74,0x68,0x00,0x00,0x0d,0x77,0x69,0x6e,0x64,0x6f,0x77,0x5f,
// 0x68,0x65,0x69,0x67,0x68,0x74,0x00,0x00,0x00,0x01,0x53,0x00,0x03,0x00,0x09,0x00,
// 0x03,0x00,0x00,0x00,0x31,0x00,0x00,0x00,0x26,0x00,0x00,0x00,0x3d,0x00,0x00,0x01,
// 0x01,0x80,0x80,0x01,0x06,0x00,0x00,0x02,0xbd,0x00,0x80,0x02,0x91,0x00,0x00,0x03,
// 0x20,0x80,0x00,0x03,0x91,0x00,0x80,0x03,0x20,0xc0,0x80,0x03,0xa0,0x01,0x00,0x02,
// 0xac,0x00,0x81,0x01,0x01,0xc0,0x00,0x01,0x3d,0x01,0x00,0x02,0xac,0x00,0x81,0x01,
// 0x01,0xc0,0x00,0x01,0x83,0xff,0x3f,0x02,0x83,0x00,0xc0,0x02,0x41,0x00,0x01,0x02,
// 0x40,0x01,0x80,0x02,0x21,0x40,0x01,0x02,0xbd,0x01,0x80,0x02,0xa0,0x80,0x01,0x02,
// 0xac,0x00,0x81,0x01,0x01,0xc0,0x00,0x01,0x3d,0x02,0x00,0x02,0xac,0x00,0x81,0x01,
// 0x01,0xc0,0x00,0x01,0x83,0xff,0x3f,0x02,0x83,0x00,0xc0,0x02,0x41,0x00,0x01,0x02,
// 0x40,0x03,0x80,0x02,0x21,0x40,0x01,0x02,0xbd,0x01,0x80,0x02,0xa0,0x80,0x01,0x02,
// 0xac,0x00,0x81,0x01,0x01,0xc0,0x00,0x01,0xbd,0x02,0x00,0x02,0xac,0x00,0x81,0x01,
// 0x01,0xc0,0x00,0x01,0x83,0xff,0x3f,0x02,0x83,0x00,0xc0,0x02,0x41,0x00,0x01,0x02,
// 0x40,0x05,0x80,0x02,0x21,0x40,0x01,0x02,0xbd,0x01,0x80,0x02,0xa0,0x80,0x01,0x02,
// 0xac,0x00,0x81,0x01,0x01,0xc0,0x00,0x01,0x29,0x00,0x80,0x01,0x00,0x00,0x00,0x06,
// 0x00,0x00,0x07,0x6d,0x6f,0x75,0x73,0x65,0x3a,0x20,0x00,0x00,0x0a,0x28,0x25,0x34,
// 0x64,0x2c,0x20,0x25,0x34,0x64,0x29,0x00,0x00,0x09,0x20,0x70,0x72,0x65,0x73,0x73,
// 0x3f,0x3a,0x20,0x00,0x00,0x00,0x00,0x00,0x08,0x20,0x64,0x6f,0x77,0x6e,0x3f,0x3a,
// 0x20,0x00,0x00,0x0b,0x20,0x72,0x65,0x6c,0x65,0x61,0x73,0x65,0x3f,0x3a,0x20,0x00,
// 0x00,0x00,0x07,0x00,0x06,0x66,0x6f,0x72,0x6d,0x61,0x74,0x00,0x00,0x05,0x49,0x6e,
// 0x70,0x75,0x74,0x00,0x00,0x07,0x6d,0x6f,0x75,0x73,0x65,0x5f,0x78,0x00,0x00,0x07,
// 0x6d,0x6f,0x75,0x73,0x65,0x5f,0x79,0x00,0x00,0x01,0x2b,0x00,0x00,0x03,0x6d,0x61,
// 0x70,0x00,0x00,0x04,0x6a,0x6f,0x69,0x6e,0x00,0x00,0x00,0x00,0x5d,0x00,0x03,0x00,
// 0x06,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0x26,0x00,0x00,0x02,0x11,0x00,0x80,0x01,
// 0x01,0x40,0x00,0x02,0xa0,0x40,0x80,0x01,0x19,0x01,0xc0,0x01,0x3d,0x00,0x80,0x01,
// 0x97,0x00,0x40,0x00,0xbd,0x00,0x80,0x01,0x29,0x00,0x80,0x01,0x00,0x00,0x00,0x02,
// 0x00,0x00,0x01,0x31,0x00,0x00,0x01,0x30,0x00,0x00,0x00,0x02,0x00,0x05,0x49,0x6e,
// 0x70,0x75,0x74,0x00,0x00,0x0c,0x6d,0x6f,0x75,0x73,0x65,0x5f,0x70,0x72,0x65,0x73,
// 0x73,0x3f,0x00,0x00,0x00,0x00,0x5c,0x00,0x03,0x00,0x06,0x00,0x00,0x00,0x00,0x00,
// 0x09,0x00,0x00,0x00,0x26,0x00,0x00,0x02,0x11,0x00,0x80,0x01,0x01,0x40,0x00,0x02,
// 0xa0,0x40,0x80,0x01,0x19,0x01,0xc0,0x01,0x3d,0x00,0x80,0x01,0x97,0x00,0x40,0x00,
// 0xbd,0x00,0x80,0x01,0x29,0x00,0x80,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x01,0x31,
// 0x00,0x00,0x01,0x30,0x00,0x00,0x00,0x02,0x00,0x05,0x49,0x6e,0x70,0x75,0x74,0x00,
// 0x00,0x0b,0x6d,0x6f,0x75,0x73,0x65,0x5f,0x64,0x6f,0x77,0x6e,0x3f,0x00,0x00,0x00,
// 0x00,0x5f,0x00,0x03,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x09,0x26,0x00,0x00,0x02,
// 0x11,0x00,0x80,0x01,0x01,0x40,0x00,0x02,0xa0,0x40,0x80,0x01,0x19,0x01,0xc0,0x01,
// 0x3d,0x00,0x80,0x01,0x97,0x00,0x40,0x00,0xbd,0x00,0x80,0x01,0x29,0x00,0x80,0x01,
// 0x00,0x00,0x00,0x02,0x00,0x00,0x01,0x31,0x00,0x00,0x01,0x30,0x00,0x00,0x00,0x02,
// 0x00,0x05,0x49,0x6e,0x70,0x75,0x74,0x00,0x00,0x0e,0x6d,0x6f,0x75,0x73,0x65,0x5f,
// 0x72,0x65,0x6c,0x65,0x61,0x73,0x65,0x3f,0x00,0x00,0x00,0x00,0x93,0x00,0x01,0x00,
// 0x02,0x00,0x04,0x00,0x00,0x00,0x14,0x00,0x03,0x06,0xc0,0x00,0x0e,0x00,0x80,0x00,
// 0x06,0x00,0x80,0x00,0x47,0x40,0x80,0x00,0xc0,0x00,0x00,0x01,0x46,0x40,0x80,0x00,
// 0x06,0x00,0x80,0x00,0x47,0x40,0x80,0x00,0xc0,0x02,0x00,0x01,0x46,0x80,0x80,0x00,
// 0x06,0x00,0x80,0x00,0x47,0x40,0x80,0x00,0xc0,0x04,0x00,0x01,0x46,0xc0,0x80,0x00,
// 0x06,0x00,0x80,0x00,0x47,0x40,0x80,0x00,0xc0,0x06,0x00,0x01,0x46,0x00,0x81,0x00,
// 0x04,0x02,0x80,0x00,0x29,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,
// 0x00,0x0c,0x40,0x66,0x6f,0x6e,0x74,0x5f,0x68,0x65,0x69,0x67,0x68,0x74,0x00,0x00,
// 0x04,0x69,0x6e,0x69,0x74,0x00,0x00,0x01,0x70,0x00,0x00,0x04,0x64,0x72,0x61,0x77,
// 0x00,0x00,0x05,0x63,0x6c,0x65,0x61,0x72,0x00,0x00,0x00,0x00,0xcf,0x00,0x06,0x00,
// 0x09,0x00,0x01,0x00,0x00,0x00,0x15,0x00,0x26,0x00,0x20,0x04,0x17,0x01,0x40,0x00,
// 0x17,0x01,0x40,0x00,0x17,0x01,0x40,0x00,0x83,0x2b,0xc1,0x01,0x83,0x5e,0x40,0x02,
// 0x0e,0x00,0x80,0x00,0x8e,0x00,0x00,0x01,0x0e,0x01,0x80,0x01,0x8e,0x01,0x00,0x02,
// 0x01,0x00,0x01,0x03,0x8d,0x02,0x80,0x03,0xb1,0x00,0x01,0x03,0x20,0x80,0x01,0x03,
// 0x8e,0x03,0x00,0x03,0x37,0x80,0x01,0x03,0x0e,0x04,0x00,0x03,0x91,0x04,0x00,0x03,
// 0x40,0x01,0x80,0x03,0x21,0x80,0x02,0x03,0x29,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
// 0x00,0x00,0x00,0x0b,0x00,0x02,0x40,0x78,0x00,0x00,0x02,0x40,0x79,0x00,0x00,0x06,
// 0x40,0x77,0x69,0x64,0x74,0x68,0x00,0x00,0x07,0x40,0x68,0x65,0x69,0x67,0x68,0x74,
// 0x00,0x00,0x01,0x2f,0x00,0x00,0x0c,0x40,0x66,0x6f,0x6e,0x74,0x5f,0x68,0x65,0x69,
// 0x67,0x68,0x74,0x00,0x00,0x04,0x74,0x6f,0x5f,0x69,0x00,0x00,0x09,0x40,0x6c,0x69,
// 0x6e,0x65,0x5f,0x6e,0x75,0x6d,0x00,0x00,0x05,0x40,0x74,0x65,0x78,0x74,0x00,0x00,
// 0x06,0x4b,0x65,0x72,0x6e,0x65,0x6c,0x00,0x00,0x0a,0x63,0x6c,0x61,0x73,0x73,0x5f,
// 0x65,0x76,0x61,0x6c,0x00,0x00,0x00,0x00,0x61,0x00,0x01,0x00,0x04,0x00,0x01,0x00,
// 0x00,0x00,0x0b,0x00,0x48,0x00,0x80,0x00,0x04,0x00,0x00,0x01,0x84,0x00,0x80,0x01,
// 0x05,0x00,0x00,0x02,0x20,0x81,0x80,0x00,0x06,0x00,0x80,0x00,0x47,0x40,0x80,0x00,
// 0xc0,0x00,0x00,0x01,0x46,0x40,0x80,0x00,0x84,0x00,0x80,0x00,0x29,0x00,0x80,0x00,
// 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x05,0x6f,0x72,0x67,0x5f,0x70,0x00,
// 0x00,0x01,0x70,0x00,0x00,0x0c,0x61,0x6c,0x69,0x61,0x73,0x5f,0x6d,0x65,0x74,0x68,
// 0x6f,0x64,0x00,0x00,0x00,0x00,0x60,0x00,0x03,0x00,0x06,0x00,0x00,0x00,0x00,0x00,
// 0x0c,0x00,0x00,0x00,0x26,0x00,0x08,0x00,0x06,0x00,0x80,0x01,0x37,0x00,0x01,0x02,
// 0x01,0x40,0x80,0x02,0x38,0x40,0x01,0x02,0xa0,0x3f,0x80,0x01,0x91,0x00,0x80,0x01,
// 0x37,0x00,0x01,0x02,0x01,0x40,0x80,0x02,0x38,0x40,0x01,0x02,0xa0,0xbf,0x80,0x01,
// 0x29,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x05,0x6f,0x72,
// 0x67,0x5f,0x70,0x00,0x00,0x07,0x43,0x6f,0x6e,0x73,0x6f,0x6c,0x65,0x00,0x00,0x01,
// 0x70,0x00,0x00,0x00,0x00,0x96,0x00,0x03,0x00,0x06,0x00,0x01,0x00,0x00,0x00,0x11,
// 0x26,0x00,0x08,0x00,0x01,0x40,0x80,0x01,0x91,0x00,0x00,0x02,0xa0,0x00,0x80,0x01,
// 0x99,0x03,0xc0,0x01,0x0d,0x01,0x80,0x01,0x01,0x40,0x00,0x02,0x40,0x01,0x80,0x02,
// 0x21,0xc0,0x00,0x02,0xac,0x00,0x81,0x01,0x0e,0x01,0x80,0x01,0x17,0x02,0x40,0x00,
// 0x0d,0x01,0x80,0x01,0x01,0x40,0x00,0x02,0x20,0x80,0x01,0x02,0xa0,0x40,0x81,0x01,
// 0x29,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x0c,0x69,0x6e,
// 0x73,0x74,0x61,0x6e,0x63,0x65,0x5f,0x6f,0x66,0x3f,0x00,0x00,0x05,0x41,0x72,0x72,
// 0x61,0x79,0x00,0x00,0x05,0x40,0x74,0x65,0x78,0x74,0x00,0x00,0x03,0x6d,0x61,0x70,
// 0x00,0x00,0x01,0x2b,0x00,0x00,0x02,0x3c,0x3c,0x00,0x00,0x07,0x69,0x6e,0x73,0x70,
// 0x65,0x63,0x74,0x00,0x00,0x00,0x00,0x34,0x00,0x03,0x00,0x05,0x00,0x00,0x00,0x00,
// 0x00,0x04,0x00,0x00,0x26,0x00,0x00,0x02,0x01,0x40,0x80,0x01,0x20,0x00,0x80,0x01,
// 0x29,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x07,0x69,0x6e,
// 0x73,0x70,0x65,0x63,0x74,0x00,0x00,0x00,0x01,0x6a,0x00,0x02,0x00,0x08,0x00,0x01,
// 0x00,0x00,0x00,0x31,0x26,0x00,0x00,0x00,0x0d,0x00,0x00,0x01,0x20,0x40,0x00,0x01,
// 0x19,0x01,0x40,0x01,0x05,0x00,0x00,0x01,0x29,0x00,0x00,0x01,0x0d,0x00,0x00,0x01,
// 0x20,0x80,0x00,0x01,0x0d,0x02,0x80,0x01,0xb5,0xc0,0x00,0x01,0x19,0x04,0x40,0x01,
// 0x0d,0x00,0x00,0x01,0x0d,0x00,0x80,0x01,0x20,0x80,0x80,0x01,0x0d,0x02,0x00,0x02,
// 0xae,0x80,0x81,0x01,0x0d,0x02,0x00,0x02,0x20,0x41,0x01,0x01,0x0e,0x00,0x00,0x01,
// 0x06,0x00,0x00,0x01,0x20,0xc0,0x01,0x01,0x06,0x00,0x00,0x01,0x03,0x7f,0xc0,0x01,
// 0x03,0x7f,0x40,0x02,0x03,0x7f,0xc0,0x02,0xa0,0x01,0x02,0x01,0x06,0x00,0x00,0x01,
// 0x0d,0x05,0x80,0x01,0x8d,0x05,0x00,0x02,0x0d,0x06,0x80,0x02,0x8d,0x06,0x00,0x03,
// 0x20,0x42,0x02,0x01,0x06,0x00,0x00,0x01,0x20,0x80,0x03,0x01,0x06,0x00,0x00,0x01,
// 0x83,0xff,0xbf,0x01,0x83,0xff,0x3f,0x02,0x83,0xff,0xbf,0x02,0xa0,0x01,0x02,0x01,
// 0x06,0x00,0x00,0x01,0x0d,0x05,0x80,0x01,0x8d,0x05,0x00,0x02,0x0d,0x06,0x80,0x02,
// 0x8d,0x06,0x00,0x03,0x20,0x42,0x02,0x01,0x0d,0x00,0x00,0x01,0x40,0x01,0x80,0x01,
// 0x21,0xc0,0x03,0x01,0x29,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,
// 0x00,0x05,0x40,0x74,0x65,0x78,0x74,0x00,0x00,0x04,0x6e,0x69,0x6c,0x3f,0x00,0x00,
// 0x06,0x6c,0x65,0x6e,0x67,0x74,0x68,0x00,0x00,0x01,0x3e,0x00,0x00,0x09,0x40,0x6c,
// 0x69,0x6e,0x65,0x5f,0x6e,0x75,0x6d,0x00,0x00,0x02,0x5b,0x5d,0x00,0x00,0x01,0x2d,
// 0x00,0x00,0x08,0x73,0x65,0x74,0x5f,0x66,0x69,0x6c,0x6c,0x00,0x00,0x09,0x73,0x65,
// 0x74,0x5f,0x63,0x6f,0x6c,0x6f,0x72,0x00,0x00,0x04,0x72,0x65,0x63,0x74,0x00,0x00,
// 0x02,0x40,0x78,0x00,0x00,0x02,0x40,0x79,0x00,0x00,0x06,0x40,0x77,0x69,0x64,0x74,
// 0x68,0x00,0x00,0x07,0x40,0x68,0x65,0x69,0x67,0x68,0x74,0x00,0x00,0x0b,0x73,0x65,
// 0x74,0x5f,0x6e,0x6f,0x5f,0x66,0x69,0x6c,0x6c,0x00,0x00,0x0f,0x65,0x61,0x63,0x68,
// 0x5f,0x77,0x69,0x74,0x68,0x5f,0x69,0x6e,0x64,0x65,0x78,0x00,0x00,0x00,0x00,0x7a,
// 0x00,0x04,0x00,0x0b,0x00,0x00,0x00,0x00,0x00,0x0e,0x00,0x00,0x26,0x00,0x00,0x04,
// 0x06,0x00,0x00,0x02,0x01,0x40,0x80,0x02,0x8d,0x00,0x00,0x03,0xad,0x82,0x00,0x03,
// 0x8d,0x01,0x80,0x03,0x0d,0x02,0x00,0x04,0xac,0x80,0x80,0x03,0x0d,0x02,0x00,0x04,
// 0x01,0x80,0x80,0x04,0xb0,0x40,0x01,0x04,0xac,0x80,0x80,0x03,0xa0,0x01,0x00,0x02,
// 0x29,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x04,0x74,0x65,
// 0x78,0x74,0x00,0x00,0x02,0x40,0x78,0x00,0x00,0x01,0x2b,0x00,0x00,0x02,0x40,0x79,
// 0x00,0x00,0x0c,0x40,0x66,0x6f,0x6e,0x74,0x5f,0x68,0x65,0x69,0x67,0x68,0x74,0x00,
// 0x00,0x01,0x2a,0x00,0x00,0x00,0x00,0x4d,0x00,0x02,0x00,0x04,0x00,0x00,0x00,0x00,
// 0x00,0x09,0x00,0x00,0x26,0x00,0x00,0x00,0x0d,0x00,0x00,0x01,0x20,0x40,0x00,0x01,
// 0x19,0x01,0x40,0x01,0x05,0x00,0x00,0x01,0x29,0x00,0x00,0x01,0x37,0x80,0x00,0x01,
// 0x0e,0x00,0x00,0x01,0x29,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
// 0x00,0x05,0x40,0x74,0x65,0x78,0x74,0x00,0x00,0x04,0x6e,0x69,0x6c,0x3f,0x00,0x00,
// 0x00,0x00,0x50,0x00,0x01,0x00,0x03,0x00,0x02,0x00,0x00,0x00,0x08,0x00,0x00,0x00,
// 0x48,0x00,0x80,0x00,0xc0,0x00,0x00,0x01,0x46,0x00,0x80,0x00,0x48,0x00,0x80,0x00,
// 0xc0,0x02,0x00,0x01,0x46,0x40,0x80,0x00,0x84,0x00,0x80,0x00,0x29,0x00,0x80,0x00,
// 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x0a,0x69,0x6e,0x69,0x74,0x69,0x61,
// 0x6c,0x69,0x7a,0x65,0x00,0x00,0x06,0x75,0x70,0x64,0x61,0x74,0x65,0x00,0x00,0x00,
// 0x00,0x75,0x00,0x04,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x0d,0x26,0x00,0x20,0x00,
// 0x17,0x01,0x40,0x00,0x17,0x01,0x40,0x00,0x17,0x01,0x40,0x00,0x83,0x02,0xc0,0x00,
// 0x83,0x18,0x40,0x01,0x0e,0x00,0x80,0x00,0x8e,0x00,0x00,0x01,0x83,0xff,0x3f,0x02,
// 0x0e,0x01,0x00,0x02,0x83,0xff,0x3f,0x02,0x8e,0x01,0x00,0x02,0x29,0x00,0x00,0x02,
// 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x09,0x40,0x69,0x6e,0x74,0x65,0x72,
// 0x76,0x61,0x6c,0x00,0x00,0x06,0x40,0x6c,0x69,0x6d,0x69,0x74,0x00,0x00,0x06,0x40,
// 0x69,0x6e,0x64,0x65,0x78,0x00,0x00,0x06,0x40,0x66,0x72,0x61,0x6d,0x65,0x00,0x00,
// 0x00,0x01,0x29,0x00,0x02,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x00,0x00,
// 0x26,0x00,0x00,0x00,0x0d,0x00,0x00,0x01,0x83,0xff,0xbf,0x01,0xb5,0x40,0x00,0x01,
// 0x99,0x01,0x40,0x01,0x0d,0x01,0x00,0x01,0x0d,0x00,0x80,0x01,0xb6,0xc0,0x00,0x01,
// 0x19,0x01,0x40,0x01,0x05,0x00,0x00,0x01,0x29,0x00,0x00,0x01,0x0d,0x02,0x00,0x01,
// 0x0d,0x03,0x80,0x01,0xa0,0x40,0x01,0x01,0x83,0xff,0xbf,0x01,0xb2,0xc0,0x01,0x01,
// 0x19,0x07,0x40,0x01,0x11,0x04,0x00,0x01,0x20,0x40,0x02,0x01,0x3d,0x00,0x80,0x01,
// 0x06,0x00,0x00,0x02,0xbd,0x00,0x80,0x02,0x0d,0x01,0x00,0x03,0x20,0xc1,0x02,0x02,
// 0x3e,0x00,0x81,0x01,0x3d,0x01,0x00,0x02,0x3e,0x00,0x81,0x01,0xa0,0x80,0x02,0x01,
// 0x0d,0x01,0x00,0x01,0xad,0x00,0x03,0x01,0x0e,0x01,0x00,0x01,0x0d,0x02,0x00,0x01,
// 0xad,0x00,0x03,0x01,0x0e,0x02,0x00,0x01,0x29,0x00,0x00,0x01,0x00,0x00,0x00,0x03,
// 0x00,0x00,0x0e,0x73,0x65,0x71,0x75,0x65,0x6e,0x63,0x65,0x5f,0x73,0x68,0x6f,0x74,
// 0x5f,0x00,0x00,0x04,0x25,0x30,0x33,0x64,0x00,0x00,0x04,0x2e,0x70,0x6e,0x67,0x00,
// 0x00,0x00,0x0d,0x00,0x06,0x40,0x6c,0x69,0x6d,0x69,0x74,0x00,0x00,0x01,0x3e,0x00,
// 0x00,0x06,0x40,0x69,0x6e,0x64,0x65,0x78,0x00,0x00,0x02,0x3e,0x3d,0x00,0x00,0x06,
// 0x40,0x66,0x72,0x61,0x6d,0x65,0x00,0x00,0x01,0x25,0x00,0x00,0x09,0x40,0x69,0x6e,
// 0x74,0x65,0x72,0x76,0x61,0x6c,0x00,0x00,0x02,0x3d,0x3d,0x00,0x00,0x05,0x49,0x6d,
// 0x61,0x67,0x65,0x00,0x00,0x0b,0x67,0x72,0x61,0x62,0x5f,0x73,0x63,0x72,0x65,0x65,
// 0x6e,0x00,0x00,0x04,0x73,0x61,0x76,0x65,0x00,0x00,0x07,0x73,0x70,0x72,0x69,0x6e,
// 0x74,0x66,0x00,0x00,0x01,0x2b,0x00,0x4c,0x56,0x41,0x52,0x00,0x00,0x00,0xcf,0x00,
// 0x00,0x00,0x0d,0x00,0x03,0x73,0x74,0x72,0x00,0x01,0x76,0x00,0x01,0x78,0x00,0x01,
// 0x79,0x00,0x05,0x77,0x69,0x64,0x74,0x68,0x00,0x06,0x68,0x65,0x69,0x67,0x68,0x74,
// 0x00,0x04,0x61,0x72,0x67,0x73,0x00,0x03,0x61,0x72,0x67,0x00,0x03,0x6f,0x62,0x6a,
// 0x00,0x04,0x74,0x65,0x78,0x74,0x00,0x05,0x69,0x6e,0x64,0x65,0x78,0x00,0x08,0x69,
// 0x6e,0x74,0x65,0x72,0x76,0x61,0x6c,0x00,0x05,0x6c,0x69,0x6d,0x69,0x74,0xff,0xff,
// 0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x01,
// 0x00,0x01,0xff,0xff,0x00,0x00,0x00,0x01,0x00,0x01,0xff,0xff,0x00,0x00,0x00,0x01,
// 0x00,0x01,0xff,0xff,0x00,0x00,0x00,0x02,0x00,0x01,0x00,0x03,0x00,0x02,0x00,0x04,
// 0x00,0x03,0x00,0x05,0x00,0x04,0xff,0xff,0x00,0x00,0x00,0x06,0x00,0x01,0xff,0xff,
// 0x00,0x00,0x00,0x07,0x00,0x01,0xff,0xff,0x00,0x00,0x00,0x08,0x00,0x01,0xff,0xff,
// 0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x09,0x00,0x01,0x00,0x0a,0x00,0x02,0xff,0xff,
// 0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x0b,0x00,0x01,0x00,0x0c,0x00,0x02,0xff,0xff,
// 0x00,0x00,0xff,0xff,0x00,0x00,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
// };

//----------------------------------------------------------
ScriptEngine::ScriptEngine(const char* aScriptPath)
: mScriptPath(aScriptPath)
, mMrb(NULL)
, mErroredMrb(NULL)
, mErrorMsg()
, mConsoleModule(NULL)
{
}

//----------------------------------------------------------
ScriptEngine::~ScriptEngine()
{
    close();
}

namespace {
string dirname(string aPath)
{
    return aPath = aPath.substr(0, aPath.find_last_of('/')) + '/'; // Need last '/'
}
}

//----------------------------------------------------------
void ScriptEngine::setup()
{
    string dataRoot = dirname(mScriptPath);
    
    // set texture & script root
    ofSetDataPathRoot(dataRoot);

    // open mrb
    open();
    
    // load builtin library
    // mrb_load_irep(mMrb, BuiltIn);
    // mConsoleModule = mrb_class_get(mMrb, "Console");
    
    // bind
    Bind::All(mMrb);

    // load user script
    load();

    // call setup
    funcallIf("setup");
}

//----------------------------------------------------------
void ScriptEngine::funcallIf(const char* aName)
{
    if (mMrb) {
      funcallIf(kernel_obj(), aName);
    }
}

//----------------------------------------------------------
void ScriptEngine::funcallIf(mrb_value aModule, const char* aName)
{
    if (mMrb && isExistFunction(aModule, aName)) {
        int ai = mrb_gc_arena_save(mMrb);
        mrb_funcall(mMrb, aModule, aName, 0);
        mrb_gc_arena_restore(mMrb, ai);
        closeOnException();
    }
}

//----------------------------------------------------------
void ScriptEngine::funcallIf(const char* aName, mrb_value aArg1, mrb_value aArg2)
{
    if (mMrb && isExistFunction(kernel_obj(), aName)) {
        int ai = mrb_gc_arena_save(mMrb);
        mrb_funcall(mMrb, kernel_obj(), aName, 2, aArg1, aArg2);
        mrb_gc_arena_restore(mMrb, ai);
        closeOnException();
    }
}

//----------------------------------------------------------
void ScriptEngine::funcallIf(const char* aName, mrb_value aArg1, mrb_value aArg2, mrb_value aArg3)
{
    if (mMrb && isExistFunction(kernel_obj(), aName)) {
        int ai = mrb_gc_arena_save(mMrb);
        mrb_funcall(mMrb, kernel_obj(), aName, 3, aArg1, aArg2, aArg3);
        mrb_gc_arena_restore(mMrb, ai);
        closeOnException();
    }
}

//----------------------------------------------------------
void ScriptEngine::draw()
{
    if (mMrb) {
        funcallIf("draw");
        // funcallIf(mrb_obj_value(mConsoleModule), "draw");
        
    } else {
        ofSetColor(0, 0, 0);
        ofBackground(255, 255, 255);
        ofDrawBitmapString(mErrorMsg, 0, 60); // Shift the y pos for iOS7
    }
}

//----------------------------------------------------------
void ScriptEngine::reload()
{
    setup();
}

//----------------------------------------------------------
void ScriptEngine::open()
{
    close();                            // close if still open.
    mMrb = mrb_open();
}

//----------------------------------------------------------
void ScriptEngine::load()
{
    FILE *fd = fopen(mScriptPath, "r");
    mrb_load_file(mMrb, fd);
    fclose(fd);
}
    
//----------------------------------------------------------
void ScriptEngine::close()
{
    if (mErroredMrb) {
        mrb_close(mErroredMrb);
        mErroredMrb = NULL;
    }

    if (mMrb) {
        mrb_close(mMrb);
        mMrb = NULL;
    }
}

//----------------------------------------------------------
bool ScriptEngine::isExistFunction(mrb_value aSelf, const char* aFuncName)
{
    struct RClass *c = mrb_class(mMrb, aSelf);
    struct RProc *p = mrb_method_search_vm(mMrb, &c, mrb_intern_cstr(mMrb, aFuncName));
    return p != NULL;
}

//----------------------------------------------------------
void ScriptEngine::closeOnException()
{
    if (mMrb->exc) {
        // Kernel.p
        mrb_p(mMrb, mrb_obj_value(mMrb->exc));

        // Save error message & Draw to display
        mrb_value str = mrb_funcall(mMrb, mrb_obj_value(mMrb->exc), "inspect", 0);
        mErrorMsg = mrb_string_value_cstr(mMrb, &str);

        // Insert a line break at the 40 digits each
        static const int COLUMN = 40;
        int insertPos = COLUMN;
        while  (mErrorMsg.length() > insertPos) {
            mErrorMsg.insert(insertPos, "\n");
            insertPos += COLUMN + 1;
        }

        // Close mrb
        mErroredMrb = mMrb;
        mMrb = NULL;
    }
}

}

