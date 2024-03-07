/* Copyright (c) 2020 Sultim Tsyrendashiev
This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License as published by
the Free Software Foundation


This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#pragma once

unsigned char OcclusionCheckVert_Spirv[] = {
0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x08, 0x00, 
0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 
0x01, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 
0x47, 0x4C, 0x53, 0x4C, 0x2E, 0x73, 0x74, 0x64, 0x2E, 0x34, 0x35, 0x30, 
0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x00, 0x00, 0x00, 0x6D, 0x61, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x00, 
0x0D, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 
0x02, 0x00, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x04, 0x00, 0x09, 0x00, 
0x47, 0x4C, 0x5F, 0x41, 0x52, 0x42, 0x5F, 0x73, 0x65, 0x70, 0x61, 0x72, 
0x61, 0x74, 0x65, 0x5F, 0x73, 0x68, 0x61, 0x64, 0x65, 0x72, 0x5F, 0x6F, 
0x62, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x00, 0x00, 0x04, 0x00, 0x09, 0x00, 
0x47, 0x4C, 0x5F, 0x41, 0x52, 0x42, 0x5F, 0x73, 0x68, 0x61, 0x64, 0x69, 
0x6E, 0x67, 0x5F, 0x6C, 0x61, 0x6E, 0x67, 0x75, 0x61, 0x67, 0x65, 0x5F, 
0x34, 0x32, 0x30, 0x70, 0x61, 0x63, 0x6B, 0x00, 0x05, 0x00, 0x04, 0x00, 
0x04, 0x00, 0x00, 0x00, 0x6D, 0x61, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x00, 
0x05, 0x00, 0x06, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x67, 0x6C, 0x5F, 0x50, 
0x65, 0x72, 0x56, 0x65, 0x72, 0x74, 0x65, 0x78, 0x00, 0x00, 0x00, 0x00, 
0x06, 0x00, 0x06, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x67, 0x6C, 0x5F, 0x50, 0x6F, 0x73, 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x00, 
0x06, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
0x67, 0x6C, 0x5F, 0x50, 0x6F, 0x69, 0x6E, 0x74, 0x53, 0x69, 0x7A, 0x65, 
0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x00, 0x00, 
0x02, 0x00, 0x00, 0x00, 0x67, 0x6C, 0x5F, 0x43, 0x6C, 0x69, 0x70, 0x44, 
0x69, 0x73, 0x74, 0x61, 0x6E, 0x63, 0x65, 0x00, 0x05, 0x00, 0x03, 0x00, 
0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 
0x11, 0x00, 0x00, 0x00, 0x69, 0x6E, 0x50, 0x6F, 0x73, 0x69, 0x74, 0x69, 
0x6F, 0x6E, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x0B, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x48, 0x00, 0x05, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 
0x0B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0x47, 0x00, 0x03, 0x00, 0x0B, 0x00, 0x00, 0x00, 
0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x11, 0x00, 0x00, 0x00, 
0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 
0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 
0x02, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 
0x20, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 
0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 
0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x2B, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 
0x01, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x04, 0x00, 0x0A, 0x00, 0x00, 0x00, 
0x06, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x05, 0x00, 
0x0B, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 
0x0A, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x0C, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x04, 0x00, 
0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
0x15, 0x00, 0x04, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
0x01, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x04, 0x00, 0x0E, 0x00, 0x00, 0x00, 
0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 
0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 
0x3B, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 
0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x13, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00, 
0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 
0x3D, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 
0x11, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x13, 0x00, 0x00, 0x00, 
0x14, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 
0x3E, 0x00, 0x03, 0x00, 0x14, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 
0xFD, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00, };
unsigned int OcclusionCheckVert_Size = 728;
