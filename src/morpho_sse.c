#include "morpho_sse.h"

uint8** erosion_sse(uint8 **frame, long nrl, long nrh, long ncl, long nch)
{
    uint8 **f_ero = ui8matrix(nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE);
 	vuint8 out;

    for(long i=nrl; i<nrh; i++)
    {
        for(long j=ncl; j<nch; j+=16)
        {
            out = _mm_set1_epi8(0xff);
            
            out = _mm_and_si128(out, _mm_loadu_si128((vuint8 *) &frame[i-1][j-1]));
            out = _mm_and_si128(out, _mm_loadu_si128((vuint8 *) &frame[i-1][j]));
            out = _mm_and_si128(out, _mm_loadu_si128((vuint8 *) &frame[i-1][j+1]));
            out = _mm_and_si128(out, _mm_loadu_si128((vuint8 *) &frame[i][j-1]));
            out = _mm_and_si128(out, _mm_loadu_si128((vuint8 *) &frame[i][j]));
            out = _mm_and_si128(out, _mm_loadu_si128((vuint8 *) &frame[i][j+1]));
            out = _mm_and_si128(out, _mm_loadu_si128((vuint8 *) &frame[i+1][j-1]));
            out = _mm_and_si128(out, _mm_loadu_si128((vuint8 *) &frame[i+1][j]));
            out = _mm_and_si128(out, _mm_loadu_si128((vuint8 *) &frame[i+1][j+1]));

            _mm_storeu_si128((vuint8*) &f_ero[i][j], out);
        }
    }
    
    return f_ero;
}

uint8** dilatation_sse(uint8 **frame, long nrl,long nrh,long ncl, long nch)
{
    uint8 **f_ero = ui8matrix(nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE_SSE);
 	vuint8 out;

    for(long i=nrl; i<nrh; i++)
    {
        for(long j=ncl; j<nch; j+=16)
        {
            out = _mm_setzero_si128();
            
            out = _mm_or_si128(out, _mm_loadu_si128((vuint8 *) &frame[i-1][j-1]));
            out = _mm_or_si128(out, _mm_loadu_si128((vuint8 *) &frame[i-1][j]));
            out = _mm_or_si128(out, _mm_loadu_si128((vuint8 *) &frame[i-1][j+1]));
            out = _mm_or_si128(out, _mm_loadu_si128((vuint8 *) &frame[i][j-1]));
            out = _mm_or_si128(out, _mm_loadu_si128((vuint8 *) &frame[i][j]));
            out = _mm_or_si128(out, _mm_loadu_si128((vuint8 *) &frame[i][j+1]));
            out = _mm_or_si128(out, _mm_loadu_si128((vuint8 *) &frame[i+1][j-1]));
            out = _mm_or_si128(out, _mm_loadu_si128((vuint8 *) &frame[i+1][j]));
            out = _mm_or_si128(out, _mm_loadu_si128((vuint8 *) &frame[i+1][j+1]));

            _mm_storeu_si128((vuint8*) &f_ero[i][j], out);
        }
    }
    
    return f_ero;    
}

uint8** ouverture_sse(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	uint8 **f_temp = erosion_sse(frame, nrl, nrh, ncl, nch);
	uint8 **f_ouv = dilatation_sse(f_temp,nrl,nrh,ncl,nch);
	free_ui8matrix(f_temp, nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE_SSE);
	return f_ouv;
}

uint8** fermeture_sse(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	uint8 **f_temp = dilatation_sse(frame, nrl, nrh, ncl, nch);
	uint8 **f_fer = erosion_sse(f_temp,nrl,nrh,ncl,nch);
	free_ui8matrix(f_temp, nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE_SSE);
	return f_fer;
}