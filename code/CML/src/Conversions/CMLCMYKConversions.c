
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"

// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLCMYKtoCMYK (const CMLColorMachine* cm, CMLOutput CMYKd , CMLInput CMYKs, size_t count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(CMYKd, CMYKs, CML_CMYK_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}

// //////////////////////////
// CMYK to anything
// //////////////////////////

CML_API void CMLCMYKtoXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, cmyk, CML_XYZ_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoYuv (const CMLColorMachine* cm, CMLOutput yuv , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, cmyk, CML_Yuv_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, cmyk, CML_Yupvp_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoYxy (const CMLColorMachine* cm, CMLOutput yxy , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, cmyk, CML_Yxy_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, cmyk, CML_Lab_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoLch (const CMLColorMachine* cm, CMLOutput lch , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, cmyk, CML_Lch_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, cmyk, CML_Luv_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, cmyk, CML_RGB_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, cmyk, CML_YCbCr_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, cmyk, CML_HSV_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLCMYKtoHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, cmyk, CML_HSL_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>

