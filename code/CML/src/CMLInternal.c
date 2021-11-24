
#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"




CML_HIDDEN void CMLInternalGraytoChanneledBufferHSL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
  float luminance;
  cm = cm; // no warning
  luminance = 1.f - *gray;
  cmlSet3(buffer, 0.f, 0.f, luminance);
}
CML_HIDDEN void CMLInternalGraytoChanneledBufferHSV(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
  float luminance;
  cm = cm; // no warning
  luminance = 1.f - *gray;
  cmlSet3(buffer, 0.f, 0.f, luminance);
}
CML_HIDDEN void CMLInternalGraytoChanneledBufferG(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
  float luminance;
  cm = cm; // no warning
  luminance = 1.f - *gray;
  cmlSet3(buffer, luminance, luminance, luminance);
}
CML_HIDDEN void CMLInternalGraytoChanneledBufferLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
  float luminance;
  cm = cm; // no warning
  luminance = 1.f - *gray;
  cmlSet3(buffer, 100.f * luminance, 0.f, 0.f);
}
CML_HIDDEN void CMLInternalGraytoChanneledBufferL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
  float luminance;
  cm = cm; // no warning
  luminance = 1.f - *gray;
  cmlSet3(buffer, 100.f * luminance, 0.f, 0.f);
}
CML_HIDDEN void CMLInternalGraytoChanneledBufferY(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
  float luminance = 1.f - *gray;
  const float* whitepointYxy = cmlGetReferenceWhitepointYxy(&(cm->observer));
  cmlSet3(buffer, luminance, whitepointYxy[1], whitepointYxy[2]);
}
CML_HIDDEN void CMLInternalGraytoChanneledBufferYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
  float luminance;
  cm = cm; // no warning
  luminance = 1.f - *gray;
  cmlSet3(buffer, luminance, 0.f, 0.f);
}




CML_HIDDEN void CMLInternalChanneledBuffertoGrayHSL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
  cm = cm; // no warning
  *gray = 1.f - buffer[2];
}
CML_HIDDEN void CMLInternalChanneledBuffertoGrayHSV(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
  cm = cm; // no warning
  *gray = 1.f - buffer[2];
}
CML_HIDDEN void CMLInternalChanneledBuffertoGrayG(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
  cm = cm; // no warning
  *gray = 1.f - buffer[1];
}
CML_HIDDEN void CMLInternalChanneledBuffertoGrayLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
  cm = cm; // no warning
  *gray = 1.f - (buffer[0] * .01f);
}
CML_HIDDEN void CMLInternalChanneledBuffertoGrayL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
  cm = cm; // no warning
  *gray = 1.f - (buffer[0] * .01f);
}
CML_HIDDEN void CMLInternalChanneledBuffertoGrayY(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
  cm = cm; // no warning
  *gray = 1.f - buffer[0];
}
CML_HIDDEN void CMLInternalChanneledBuffertoGrayYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
  cm = cm; // no warning
  *gray = 1.f - buffer[0];
}




CML_HIDDEN void CMLInternalXYZtoLabCIELAB(const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cmlInternalXYZtoCIELAB(out, in, count, cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)), cm->labspace.responseL.forwardfunc);
}

CML_HIDDEN void CMLInternalXYZtoLabCIELAB_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatalign){
  cmlInternalXYZtoCIELAB_SB(buf, count, floatalign, cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)), cm->labspace.responseL.forwardfunc);
}


CML_HIDDEN void CMLInternalXYZtoLabChromaticValence(const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  const float* inverseWhitepointXYZ = cmlGetReferenceInverseWhitepointXYZ(&(cm->observer));
  while(count){

    float xr = in[0] * inverseWhitepointXYZ[0];
    float yr = in[1] * inverseWhitepointXYZ[1];
    float zr = in[2] * inverseWhitepointXYZ[2];
    
    float fy = cmlInternalEval(cm->labspace.responseL.forwardfunc, yr);
    out[0] = 100.f * fy;

    if(fy == 0.f){
      out[1] = 0.f;
      out[2] = 0.f;
    }else{
      float fyinverse = cmlInverse(fy);
      out[1] = (xr - yr) * cm->labspace.adamschromaticityvalenceK * 100.f * fyinverse;
      out[2] = (yr - zr) * cm->labspace.adamschromaticityvalenceK * cm->labspace.adamschromaticityvalenceke * 100.f * fyinverse;
    }

    in += CML_XYZ_NUMCHANNELS;
    out += CML_Lab_NUMCHANNELS;
    count--;
  }
}

CML_HIDDEN void CMLInternalXYZtoLabChromaticValence_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatalign){
  const float* inverseWhitepointXYZ = cmlGetReferenceInverseWhitepointXYZ(&(cm->observer));
  while(count){

    float xr = buf[0] * inverseWhitepointXYZ[0];
    float yr = buf[1] * inverseWhitepointXYZ[1];
    float zr = buf[2] * inverseWhitepointXYZ[2];
    
    float fy = cmlInternalEval(cm->labspace.responseL.forwardfunc, yr);
    buf[0] = 100.f * fy;

    if(fy == 0.f){
      buf[1] = 0.f;
      buf[2] = 0.f;
    }else{
      float fyinverse = cmlInverse(fy);
      buf[1] = (xr - yr) * cm->labspace.adamschromaticityvalenceK * 100.f * fyinverse;
      buf[2] = (yr - zr) * cm->labspace.adamschromaticityvalenceK * cm->labspace.adamschromaticityvalenceke * 100.f * fyinverse;
    }

    buf += floatalign;
    count--;
  }
}


CML_HIDDEN void CMLInternalLabtoXYZCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cmlInternalCIELABtoXYZ(out, in, count, cmlGetReferenceWhitepointXYZ(&(cm->observer)), cm->labspace.responseL.backwardfunc);
}


CML_HIDDEN void CMLInternalLabtoXYZCIELAB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatalign){
  cmlInternalCIELABtoXYZ_SB(buf, count, floatalign, cmlGetReferenceWhitepointXYZ(&(cm->observer)), cm->labspace.responseL.backwardfunc);
}



CML_HIDDEN void CMLInternalLabtoXYZChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  const float* whitepointXYZ = cmlGetReferenceWhitepointXYZ(&(cm->observer));
  while(count){

    float xr, yr, zr;
    
    float fy = in[0] * .01f;
    yr = cmlInternalEval(cm->labspace.responseL.backwardfunc, fy);

    if((cm->labspace.adamschromaticityvalenceK == 0.f) || (cm->labspace.adamschromaticityvalenceke == 0.f)){
      xr = 0.f;
      zr = 0.f;
    }else{
      xr = yr + fy * in[1] / (cm->labspace.adamschromaticityvalenceK * 100.f);
      zr = yr - fy * in[2] / (cm->labspace.adamschromaticityvalenceK * cm->labspace.adamschromaticityvalenceke * 100.f);
    }

    out[0] = xr * whitepointXYZ[0];
    out[1] = yr * whitepointXYZ[1];
    out[2] = zr * whitepointXYZ[2];

    in += CML_Lab_NUMCHANNELS;
    out += CML_XYZ_NUMCHANNELS;
    count--;
  }
}


CML_HIDDEN void CMLInternalLabtoXYZChromaticValence_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatalign){
  const float* whitepointXYZ = cmlGetReferenceWhitepointXYZ(&(cm->observer));
  while(count){

    float xr, yr, zr;
    
    float fy = buf[0] * .01f;
    yr = cmlInternalEval(cm->labspace.responseL.backwardfunc, fy);

    if((cm->labspace.adamschromaticityvalenceK == 0.f) || (cm->labspace.adamschromaticityvalenceke == 0.f)){
      xr = 0.f;
      zr = 0.f;
    }else{
      xr = yr + fy * buf[1] / (cm->labspace.adamschromaticityvalenceK * 100.f);
      zr = yr - fy * buf[2] / (cm->labspace.adamschromaticityvalenceK * cm->labspace.adamschromaticityvalenceke * 100.f);
    }

    buf[0] = xr * whitepointXYZ[0];
    buf[1] = yr * whitepointXYZ[1];
    buf[2] = zr * whitepointXYZ[2];

    buf += floatalign;
    count--;
  }
}


CML_HIDDEN void CMLInternalRGBtoCMYKStandard(const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cm = cm; // no warning
  while(count){

    out[0] = 1.f - in[0];
    out[1] = 1.f - in[1];
    out[2] = 1.f - in[2];
    out[3] = 0.f;

    in += CML_RGB_NUMCHANNELS;
    out += CML_CMYK_NUMCHANNELS;
    count--;
  }
}

CML_HIDDEN void CMLInternalRGBtoCMYKStandard_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatalign){
  cm = cm; // no warning
  while(count){

    buf[0] = 1.f - buf[0];
    buf[1] = 1.f - buf[1];
    buf[2] = 1.f - buf[2];
    buf[3] = 0.f;

    buf += floatalign;
    count--;
  }
}



CML_HIDDEN void CMLInternalRGBtoCMYKUCR(const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cm = cm; // no warning
  while(count){

    out[0] = 1.f - in[0];
    out[1] = 1.f - in[1];
    out[2] = 1.f - in[2];
    out[3] = out[0];
    if(out[1]<out[3]){out[3] = out[1];}
    if(out[2]<out[3]){out[3] = out[2];}
    out[0] -= out[3];
    out[1] -= out[3];
    out[2] -= out[3];

    in += CML_RGB_NUMCHANNELS;
    out += CML_CMYK_NUMCHANNELS;
    count--;
  }
}

CML_HIDDEN void CMLInternalRGBtoCMYKUCR_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatalign){
  cm = cm; // no warning
  while(count){

    buf[0] = 1.f - buf[0];
    buf[1] = 1.f - buf[1];
    buf[2] = 1.f - buf[2];
    buf[3] = buf[0];
    if(buf[1]<buf[3]){buf[3] = buf[1];}
    if(buf[2]<buf[3]){buf[3] = buf[2];}
    buf[0] -= buf[3];
    buf[1] -= buf[3];
    buf[2] -= buf[3];

    buf += floatalign;
    count--;
  }
}



CML_HIDDEN void CMLInternalCMYKtoRGBStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cm = cm; // no warning
  while(count){

    out[0] = 1.f - in[0];
    out[1] = 1.f - in[1];
    out[2] = 1.f - in[2];

    in += CML_CMYK_NUMCHANNELS;
    out += CML_RGB_NUMCHANNELS;
    count--;
  }
}


CML_HIDDEN void CMLInternalCMYKtoRGBStandard_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatalign){
  cm = cm; // no warning
  while(count){

    buf[0] = 1.f - buf[0];
    buf[1] = 1.f - buf[1];
    buf[2] = 1.f - buf[2];

    buf += floatalign;
    count--;
  }
}


CML_HIDDEN void CMLInternalCMYKtoRGBUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cm = cm; // no warning
  while(count){

    out[0] = 1.f - (in[0]+in[3]);
    out[1] = 1.f - (in[1]+in[3]);
    out[2] = 1.f - (in[2]+in[3]);

    in += CML_CMYK_NUMCHANNELS;
    out += CML_RGB_NUMCHANNELS;
    count--;
  }
}


CML_HIDDEN void CMLInternalCMYKtoRGBUCR_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatalign){
  cm = cm; // no warning
  while(count){

    buf[0] = 1.f - (buf[0]+buf[3]);
    buf[1] = 1.f - (buf[1]+buf[3]);
    buf[2] = 1.f - (buf[2]+buf[3]);

    buf += floatalign;
    count--;
  }
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
